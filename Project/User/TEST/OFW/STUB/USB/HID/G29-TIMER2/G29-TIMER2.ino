//	use "switch_i71.bat"
//         TX   RX
//         UART UART
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

//	use "switch_i71.bat"
//	「ofw_stub_usb_hid_g29ps4.cpp」は下記のように
//		_DEBUG_PIN:ON
//		・「stub::USB_HID_G29PS4」FEATURE読み書き期間:PD0
//		・「stub::USB_HID_G29PS4::EP_Main_stWrite」実行期間:PD1
//		_DEBUG_SERIAL:OFF←ONだと処理に時間かかるのでタイミング確認には超重要
//		_DEBUG_NOG29:OFF

#include				<ofw_driver_timer.hpp>
#include				<ofw_driver_usb_hid.hpp>
#include				<ofw_stub_usb_hid_g29ps4.hpp>
#include				<ofw_driver_ps.hpp>
#include				<ofw_application_g29fromnegconplus.hpp>

driver::USB_HID			dusbThis;	//	自動変数領域だと「はみ出る」模様
stub::USB_HID_G29PS4	susbThis(&dusbThis);	//	G29実機からの認証情報受け取りのため、USBホストシールドインタフェイスが必要
driver::PS				psThis;

INT						main(VOID){
	OFW::stNew();
	driver::TIMER::stNew(driver::TIMER::IDClock_Division8);
	if(dusbThis.eNew()){
		WORD					wdtimingoffset=0;

		{
			constexpr WORD			cwieiend=0x0400;
			constexpr WORD			cwiperiodicstart=cwieiend+0x500;
		
			susbThis.New();
			psThis.New();
			application::G29FROMNEGCONPLUS::stNew();
			driver::TIMER::stSet(cwieiend+wdtimingoffset);
			while(TRUE){
				{
					ATOMIC					atomic;

					if(susbThis.eIsReadable()){
						//	使おうが使うまいがバッファを開けるためにチェックは必要
						//	フォースフィードバックエミュレーションを行うならここで
					}
					driver::TIMER::stWaitUntil(cwiperiodicstart+wdtimingoffset);
					psThis.Main();
					if(psThis.idGetDevice()==driver::PS::IDDevice_HS_neGconPlus){
						application::G29FROMNEGCONPLUS::stWrite(&susbThis.writeDelegateThis(),&psThis.creadDelegateThis(),256);
					}
				}
				//	↓FEATURE割り込みやるならここでやれ
				stub::USB::stMain();
				if(7000<=driver::TIMER::stwiGet())wdtimingoffset=4000;	//	4(msec) mode
				else wdtimingoffset=0;	//	2(msec) mode
				driver::TIMER::stSet(0);	//	ここをタイミング測定の起点に
				dusbThis.Main();
				driver::TIMER::stWaitUntil(cwieiend+wdtimingoffset);
				//	↑FEATURE割り込みやるならここでやれ
			}
		}
	}else{
		//	USBホストシールド使用不能の場合
		DDRB|=0x01;
		while(TRUE){
			PORTB|=0x01;
			OFW::stWait(500);
			PORTB&=~0x01;
			OFW::stWait(500);
		}
	}
	return 0;
}
