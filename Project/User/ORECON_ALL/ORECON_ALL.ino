//	<DIPSW>
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

#include				<ofw_driver_usb_hid.hpp>
#include				<ofw_driver_ps.hpp>
#include				<ofw_stub_usb_hid_ds3.hpp>
#include				<ofw_stub_usb_hid_g29ps4.hpp>
#include				<ofw_application_ds3fromdigital.hpp>
#include				<ofw_application_ds3fromdualshock2.hpp>
#include				<ofw_application_g29fromnegcon.hpp>
#include				<ofw_application_g29fromnegconplus.hpp>
#include				<ofw_application_g29fromdualshock2.hpp>

driver::USB_HID			drvusbThis;

VOID					ORECON_DS3(VOID);
VOID					ORECON_G29(VOID);

INT						main(VOID){
	OFW::stNew();
	drvusbThis.New();
	{
		CBYTE					cbcswitch=drvusbThis.GPIO_bRead();

		if(cbcswitch&0x01)ORECON_DS3();
		else ORECON_G29();
	}
	return 0;
}

VOID					ORECON_DS3(VOID){
	stub::USB_HID_DS3		stbusbthis;
	driver::PS				psthis;

	stbusbthis.New();
	psthis.New();
	application::DS3FROMDIGITAL::stNew();
	application::DS3FROMDUALSHOCK2::stNew();
	while(TRUE){
		const auto				cbcswitch=~drvusbThis.GPIO_bRead();
		const auto				ceshowstatus=((cbcswitch&0x80)!=0);

		if(ceshowstatus)drvusbThis.GPIO_Write(BYTE(psthis.idGetDevice()));
		else drvusbThis.GPIO_Write(0);
		stub::USB::stMain();
		psthis.Main();
		switch(psthis.idGetDevice()){
		case driver::PS::IDDevice_NS_Digital:
			application::DS3FROMDIGITAL::stWrite(&stbusbthis.writeDelegateThis(),&psthis.creadDelegateThis());
			break;
		case driver::PS::IDDevice_HS_DUALSHOCK2:
			application::DS3FROMDUALSHOCK2::stWrite(&stbusbthis.writeDelegateThis(),&psthis.creadDelegateThis());
			switch(stbusbthis.bcGetReportID()){
			case 0:
				psthis.SetRumbleS(
					stbusbthis.cread0DelegateThis().eMotorS,
					stbusbthis.cread0DelegateThis().bnMotorSLength
				);
				psthis.SetRumbleL(
					stbusbthis.cread0DelegateThis().nMotorLStrength*0x55,
					stbusbthis.cread0DelegateThis().bnMotorLLength
				);
				break;
			case 1:
				psthis.SetRumbleS(
					stbusbthis.cread1DelegateThis().eMotorS,
					stbusbthis.cread1DelegateThis().bnMotorSLength
				);
				psthis.SetRumbleL(
					stbusbthis.cread1DelegateThis().nMotorLStrength*0x55,
					stbusbthis.cread1DelegateThis().bnMotorLLength
				);
				break;
			}
			break;
		}
	}
	return;
}

VOID					ORECON_G29(VOID){
	stub::USB_HID_G29PS4	stbusbthis(&drvusbThis);
	driver::PS				psthis;

	stbusbthis.New();
	psthis.New();
	application::G29FROMNEGCON::stNew();
	application::G29FROMNEGCONPLUS::stNew();
	application::G29FROMDUALSHOCK2::stNew();
	while(TRUE){
		const auto				cbcswitch=~drvusbThis.GPIO_bRead();
		const auto				ceshowstatus=((cbcswitch&0x80)!=0);
		const auto				cdwnsteeringmultiply=DWORD((cbcswitch>>1)&0x07)*24+24+64;

		if(ceshowstatus)drvusbThis.GPIO_Write(BYTE(psthis.idGetDevice()));
		else drvusbThis.GPIO_Write(0);
		stub::USB::stMain();
		psthis.Main();
		switch(psthis.idGetDevice()){
		case driver::PS::IDDevice_NS_neGcon:
			application::G29FROMNEGCON::stWrite(&stbusbthis.writeDelegateThis(),&psthis.creadDelegateThis(),cdwnsteeringmultiply);
			break;
		case driver::PS::IDDevice_HS_neGconPlus:
			application::G29FROMNEGCONPLUS::stWrite(&stbusbthis.writeDelegateThis(),&psthis.creadDelegateThis(),cdwnsteeringmultiply);
			break;
		case driver::PS::IDDevice_HS_DUALSHOCK2:
			application::G29FROMDUALSHOCK2::stWrite(&stbusbthis.writeDelegateThis(),&psthis.creadDelegateThis());
			break;
		}
	}
	return;
}
