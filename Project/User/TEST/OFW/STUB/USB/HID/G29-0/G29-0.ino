//	use "switch_i71.bat"
//	「ofw_stub_usb_hid_g29ps4.cpp」は下記のように
//		_DEBUG_PIN:ON
//		_DEBUG_SERIAL:ON
//		_DEBUG_NOG29:OFF

#include				<ofw_driver_usb_hid.hpp>
#include				<ofw_stub_usb_hid_g29ps4.hpp>
#include				<ofw_driver_ps.hpp>
#include				<ofw_application_g29fromnegconplus.hpp>
#include				<ofw_driver_serial0.hpp>

driver::USB_HID			dusbThis;	//	自動変数領域だと「はみ出る」模様
stub::USB_HID_G29PS4	susbThis(&dusbThis);	//	G29実機からの認証情報受け取りのため、USBホストシールドインタフェイスが必要
driver::PS				psThis;

INT						main(VOID){
	OFW::stNew();
	if(dusbThis.eNew()){
		susbThis.New();
		psThis.New();
		application::G29FROMNEGCONPLUS::stNew();
		while(TRUE){
			stub::USB::stMain();
			if(susbThis.eIsReadable()){
				//	使おうが使うまいがバッファを開けるためにチェックは必要
				//	フォースフィードバックエミュレーションを行うならここで
			}
			dusbThis.Main();
			psThis.Main();
			dusbThis.GPIO_Write(psThis.idGetDevice());
			if(psThis.idGetDevice()==driver::PS::IDDevice_HS_neGconPlus){
				application::G29FROMNEGCONPLUS::stWrite(&susbThis.writeDelegateThis(),&psThis.creadDelegateThis(),256);
			}
		}
	}else{
		//	USBホストシールド使用不能の場合
		driver::SERIAL0::stNew(115200);
		driver::SERIAL0::stPrintClear();
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
