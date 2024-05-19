//	use "switch_i71.bat"
//	「ofw_stub_usb_hid_g29ps4.cpp」は下記のように
//		_DEBUG_PIN:ON
//		_DEBUG_SERIAL:OFF←ONだと処理に時間かかるのでタイミング確認には超重要
//		_DEBUG_NOG29:OFF

#include				<ofw_driver_usb_hid.hpp>
#include				<ofw_stub_usb_hid_g29ps4.hpp>
#include				<ofw_driver_ps.hpp>
#include				<ofw_application_g29fromnegconplus.hpp>
#include				<ofw_driver_serial0.hpp>

driver::USB_HID			dusbThis;	//	自動変数領域だと「はみ出る」模様
stub::USB_HID_G29PS4	susbThis(&dusbThis);	//	G29実機からの認証情報受け取りのため、USBホストシールドインタフェイスが必要
driver::PS				psThis;
constexpr WORD			cwiEIEnd=0x0400;
constexpr WORD			cwiPeriodicStart=cwiEIEnd+0x500;

INT						main(VOID){
	OFW::stNew();
	DDRC|=0x40;
	DDRE|=0x40;
	{
		ATOMIC					atomic;

		TCCR1A=0x00;
		TCCR1B=0x02;
		TIMSK1&=~0x01;
	}
	if(dusbThis.eNew()){
		susbThis.New();
		psThis.New();
		application::G29FROMNEGCONPLUS::stNew();
		{
			ATOMIC					atomic;

			TCNT1=cwiEIEnd;
		}
		while(TRUE){
			{
				ATOMIC					atomic;

				PORTC|=0x40;
				while(TCNT1<cwiPeriodicStart);
				PORTE|=0x40;
				psThis.Main();
				PORTE&=~0x40;
				if(psThis.idGetDevice()==driver::PS::IDDevice_HS_neGconPlus){
					application::G29FROMNEGCONPLUS::stWrite(&susbThis.writeDelegateThis(),&psThis.creadDelegateThis(),256);
				}
				stub::USB::stMain();TCNT1=0;	//	ここをタイミング測定の起点に
				if(susbThis.eIsReadable()){
					//	使おうが使うまいがバッファを開けるためにチェックは必要
					//	フォースフィードバックエミュレーションを行うならここで
				}
				dusbThis.Main();
				PORTC&=~0x40;
			}
			//	↓FEATURE割り込みやるならここでやれ
			while(TRUE){
				ATOMIC					atomic;

				if(cwiEIEnd<=TCNT1)break;
			}
			//	↑FEATURE割り込みやるならここでやれ
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
