/****************************************************************************
**																			**
**																			**
**							整数71の電子工作								**
**																			**
**	ORECON_REV1.0									2024 written by int71	**
 ****************************************************************************/
//	use "switch_i71.bat"

//	<USBホストシールド無し時>
//	「DualShock3モード」で動作
//
//	<DIPSW(USBホストシールドあり時)>
//	0: OFF:DualShock3モード ON:G29モード
//	1: OFF:ステアリング感度+0 ON:ステアリング感度+1※G29時のみ
//	2: OFF:ステアリング感度+0 ON:ステアリング感度+2※G29時のみ
//	3: OFF:ステアリング感度+0 ON:ステアリング感度+4※G29時のみ
//	4:
//	5:
//	6:
//	7: OFF:LED無点灯 ON:接続コントローラ識別子表示モード
//
//	<DualShock3モード時の仕様>
//	基本は「MotioninJoy」互換という事なんですけど、
//	SONY純正ドライバとやらの謎の仕様に対応するため、下記を実施。
//		・「HidD_GetFeature」に応答するよう、HIDクラスリクエストのGET_REPORTに対応
//		・ReportID:0の振動コマンドに対応(動作未確認)
//
//	<G29モード時の仕様>
//	PS5の場合、認証はG29じゃないとダメぽい。
//
//	<G29モード時のneGconキーバインド>
//	START長押し:PS
//	START短押し:オプション
//	START+上:メニュー操作モードに切り替え
//		十字:十字
//		A:〇
//		I:×
//		B:△
//		II:□
//		L:L1
//		R:R1
//	START+左:セミオートマチックモードに切り替え
//		十字:十字
//		ねじり:ステアリング
//		A:〇
//		I:アクセル
//		B:△
//		II:ブレーキ
//		L:L1
//		R:R1
//	START+右:シーケンシャルシフトマニュアルモードに切り替え
//		十字(↑):L1
//		十字(↓):R1
//		ねじり:ステアリング
//		A:〇
//		I:アクセル
//		B:△
//		II:ブレーキ
//		L:クラッチ
//		R:押下時のみ、十字を十字に一時的に割り当て
//	START+下:Hシフトマニュアルモードに切り替え
//		十字(↑):押下で「N」、解放時にシフトダウン
//		十字(↓):押下で「N」、解放時にシフトアップ
//		ねじり:ステアリング
//		A:〇
//		I:アクセル
//		B:△
//		II:ブレーキ
//		L:クラッチ
//		R:押下時のみ、十字を十字に一時的に割り当て
//
//	<デバッグ>
//	・ofw_stub_usb_hid_ds3.cpp
//		_DEBUG_PIN(デバッグ用PIN出力):
//			PD1:「親」側へのコントローラ情報送信時「H」
//	・ofw_stub_usb_hid_g29ps4.cpp
//		_DEBUG_PIN(デバッグ用PIN出力):
//			PD0:FEATURE読み書き処理時「H」
//			PD1:「親」側へのコントローラ情報送信時「H」
//	・ORECON_REV1.0.ino
//		_DEBUG_PIN(デバッグ用PIN出力):
//			PC6:PSコントローラ処理時「H」
//			PE6:割り込み禁止期間中「H」
//
//         TX   RX             WRT  INT       PS        ATMC
//         UART UART           DBG  DBG       DBG       DBG
//     +---PD3  PD2  GND  GND  PD1  PD0  PD4  PC6  PD7  PE6  PB4  PB5 -+
//     |    〇   〇   〇   〇   〇   〇   〇   〇   〇   〇   〇   〇  |
//     |                                                               |
//     |                                                 PB0           |
//     |                                                 ■TX LED(表)  |
//    +|                                                               |
//    ||                                                               |
//    +|                                                               |
//     |                                                 ■RX LED(表)  |
//     |                                                 PD5           |
//     |                                                               |
//     |    〇   〇   〇   〇   〇   〇   〇   〇   〇   〇   〇   〇  |
//     +---RAW  GND  RST  VCC  PF4  PF5  PF6  PF7  PB1  PB3  PB2  PB6 -+
//                             PS   PS   PS   PS   SPI  SPI  SPI  SPI
//                             CLK  SEL  CMD  DAT  SCLK MISO MOSI SS

//#define _DEBUG_PIN

//
//		include
//

#include				<ofw_driver_timer.hpp>
#include				<ofw_driver_ps.hpp>
#include				<ofw_driver_usb_hid.hpp>
#include				<ofw_stub_usb_hid_ds3.hpp>
#include				<ofw_stub_usb_hid_g29ps4.hpp>
#include				<ofw_application_ds3fromdigital.hpp>
#include				<ofw_application_ds3fromdualshock2.hpp>
#include				<ofw_application_g29fromnegcon.hpp>
#include				<ofw_application_g29fromnegconplus.hpp>
#include				<ofw_application_g29fromdualshock2.hpp>

driver::USB_HID			dusbThis;				//	スタックオーバー回避のため大域変数に
driver::PS				psThis;					//	スタックオーバー回避のため大域変数に

VOID					ORECON_DS3(CBOOL cedusb);
VOID					ORECON_G29(VOID);

//
//		entry
//

INT						main(VOID){
	OFW::stNew();
#ifdef _DEBUG_PIN
	DDRC|=0x40;
	DDRE|=0x40;
#endif
	driver::TIMER::stNew(driver::TIMER::IDClock_Division8);
	psThis.New();
	if(dusbThis.eNew()){
		CBYTE					cbcswitch=dusbThis.GPIO_bRead();

		if(cbcswitch&0x01)ORECON_DS3(TRUE);
		else ORECON_G29();
	}else{
		ORECON_DS3(FALSE);
	}
	return 0;
}

VOID					ORECON_DS3(
	CBOOL					cedusb
){
	constexpr WORD			cwieiend=0x0180;
	constexpr WORD			cwiperiodicstart0=cwieiend+0x0080;
	constexpr WORD			cwiperiodicstart1=cwiperiodicstart0+0x0080;
	stub::USB_HID_DS3		susbthis;				//	大域共用体でも良いがおとなしく自動変数に

	susbthis.New();
	application::DS3FROMDIGITAL::stNew();
	application::DS3FROMDUALSHOCK2::stNew();
	driver::TIMER::stSet(cwieiend);
	while(TRUE){
		//	↓FEATURE割り込みやるならここでやれ
		if(cedusb){
			const auto				cbcswitch=~dusbThis.GPIO_bRead();
			const auto				ceshowstatus=((cbcswitch&0x80)!=0);

			dusbThis.Main();
			if(ceshowstatus)dusbThis.GPIO_Write(BYTE(psThis.idGetDevice()));
			else dusbThis.GPIO_Write(0);
		}
		driver::TIMER::stWaitUntil(cwieiend);
		//	↑FEATURE割り込みやるならここでやれ
		{
			ATOMIC					atomic;

#ifdef _DEBUG_PIN
			PORTE|=0x40;
#endif
			driver::TIMER::stWaitUntil(cwiperiodicstart0);
#ifdef _DEBUG_PIN
			PORTC|=0x40;
#endif
			if(susbthis.eIsReadable()){
				if(
					(psThis.idGetDevice()==driver::PS::IDDevice_HS_DUALSHOCK2)&&
					(susbthis.bcGetReportID()==0x01)
				){
					psThis.SetRumbleS(
						susbthis.cread1DelegateThis().eMotorS,
						susbthis.cread1DelegateThis().bnMotorSLength
					);
					psThis.SetRumbleL(
						susbthis.cread1DelegateThis().nMotorLStrength*0x55,
						susbthis.cread1DelegateThis().bnMotorLLength
					);
				}
			}
#ifdef _DEBUG_PIN
			PORTC&=~0x40;
#endif
			driver::TIMER::stWaitUntil(cwiperiodicstart1);
#ifdef _DEBUG_PIN
			PORTC|=0x40;
#endif
			psThis.Main();
			switch(psThis.idGetDevice()){
			case driver::PS::IDDevice_NS_Digital:
				application::DS3FROMDIGITAL::stWrite(&susbthis.writeDelegateThis(),&psThis.creadDelegateThis());
				break;
			case driver::PS::IDDevice_HS_DUALSHOCK2:
				application::DS3FROMDUALSHOCK2::stWrite(&susbthis.writeDelegateThis(),&psThis.creadDelegateThis());
				break;
			}
#ifdef _DEBUG_PIN
			PORTC&=~0x40;
#endif
			stub::USB::stMain();
			driver::TIMER::stSet(0);	//	ここをタイミング測定の起点に
#ifdef _DEBUG_PIN
			PORTE&=~0x40;
#endif
		}
	}
	return;
}

VOID					ORECON_G29(VOID){
	constexpr WORD			cwieiend=0x0700;
	constexpr WORD			cwiperiodicstart0=cwieiend+0x0200;
	constexpr WORD			cwiperiodicstart1=cwiperiodicstart0+0x0080;
	WORD					wdtimingoffset=0;
	stub::USB_HID_G29PS4	susbthis(&dusbThis);	//	大域共用体でも良いがおとなしく自動変数に

	susbthis.New();
	application::G29FROMNEGCON::stNew();
	application::G29FROMNEGCONPLUS::stNew();
	application::G29FROMDUALSHOCK2::stNew();
	while(TRUE){
		//	↓FEATURE割り込みやるならここでやれ
		const auto				cbcswitch=~dusbThis.GPIO_bRead();
		const auto				ceshowstatus=((cbcswitch&0x80)!=0);
		const auto				cdwnsteeringmultiply=DWORD((cbcswitch>>1)&0x07)*24+24+64;

		dusbThis.Main();
		if(ceshowstatus)dusbThis.GPIO_Write(BYTE(psThis.idGetDevice()));
		else dusbThis.GPIO_Write(0);
		driver::TIMER::stWaitUntil(cwieiend+wdtimingoffset);
		//	↑FEATURE割り込みやるならここでやれ
		{
			ATOMIC					atomic;

#ifdef _DEBUG_PIN
			PORTE|=0x40;
#endif
			driver::TIMER::stWaitUntil(cwiperiodicstart0+wdtimingoffset);
#ifdef _DEBUG_PIN
			PORTC|=0x40;
#endif
			if(susbthis.eIsReadable()){
				//	使おうが使うまいがバッファを開けるためにチェックは必要
				//	フォースフィードバックエミュレーションを行うならここで
			}
#ifdef _DEBUG_PIN
			PORTC&=~0x40;
#endif
			driver::TIMER::stWaitUntil(cwiperiodicstart1+wdtimingoffset);
#ifdef _DEBUG_PIN
			PORTC|=0x40;
#endif
			psThis.Main();
			switch(psThis.idGetDevice()){
			case driver::PS::IDDevice_NS_neGcon:
				application::G29FROMNEGCON::stWrite(&susbthis.writeDelegateThis(),&psThis.creadDelegateThis(),cdwnsteeringmultiply);
				break;
			case driver::PS::IDDevice_HS_neGconPlus:
				application::G29FROMNEGCONPLUS::stWrite(&susbthis.writeDelegateThis(),&psThis.creadDelegateThis(),cdwnsteeringmultiply);
				break;
			case driver::PS::IDDevice_HS_DUALSHOCK2:
				application::G29FROMDUALSHOCK2::stWrite(&susbthis.writeDelegateThis(),&psThis.creadDelegateThis());
				break;
			}
#ifdef _DEBUG_PIN
			PORTC&=~0x40;
#endif
			stub::USB::stMain();
			if(7000<=driver::TIMER::stwiGet())wdtimingoffset=4000;	//	4(msec) mode
			else wdtimingoffset=0;	//	2(msec) mode
			driver::TIMER::stSet(0);	//	ここをタイミング測定の起点に
#ifdef _DEBUG_PIN
			PORTE&=~0x40;
#endif
		}
	}
	return;
}
