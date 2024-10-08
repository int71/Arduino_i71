/****************************************************************************
**																			**
**																			**
**							整数71の電子工作								**
**																			**
**	DS3-SHOWDELAY									2024 written by int71	**
 ****************************************************************************/
//	use "switch_i71.bat"

//	_DEBUG_RESPONSE
//		デバッグ用入力断続化レスポンス確認

//#define _DEBUG_RESPONSE

//
//		include
//

#include				<ofw_driver_timer.hpp>
#include				<ofw_driver_ps.hpp>
#include				<ofw_stub_usb_hid_ds3.hpp>
#include				<ofw_application_ds3fromdigital.hpp>
#include				<ofw_application_ds3fromdualshock2.hpp>

driver::PS				psThis;					//	スタックオーバー回避のため大域変数に
stub::USB_HID_DS3		susbThis;				//	スタックオーバー回避のため大域変数に

//
//		entry
//

INT						main(VOID){
	constexpr WORD			cwieiend=0x0180;
	constexpr WORD			cwiperiodicstart0=cwieiend+0x0080;
	constexpr WORD			cwiperiodicstart1=cwiperiodicstart0+0x0080;

	OFW::stNew();
	DDRB|=0x01;
	DDRD|=0x20;
	PORTB|=0x01;
	PORTD|=0x20;
	driver::TIMER::stNew(driver::TIMER::IDClock_Division8);
	psThis.New(TRUE);
	susbThis.New();
	application::DS3FROMDIGITAL::stNew();
	application::DS3FROMDUALSHOCK2::stNew();
	driver::TIMER::stSet(cwieiend);
	while(TRUE){
		driver::TIMER::stWaitUntil(cwieiend);
		{
			ATOMIC					atomic;

			driver::TIMER::stWaitUntil(cwiperiodicstart0);
			if(susbThis.eIsReadable()){
				if(
					(psThis.idGetDevice()==driver::PS::IDDevice_HS_DUALSHOCK2)&&
					(susbThis.bcGetReportID()==0x01)
				){
					if(susbThis.cread1DelegateThis().eMotorS)PORTD&=~0x20;
					else PORTD|=0x20;
				}
			}
			driver::TIMER::stWaitUntil(cwiperiodicstart1);
			psThis.Main();
			switch(psThis.idGetDevice()){
			case driver::PS::IDDevice_NS_Digital:
			case driver::PS::IDDevice_HS_Digital:
				application::DS3FROMDIGITAL::stWrite(&susbThis.writeDelegateThis(),&psThis.creadDelegateThis());
				break;
			case driver::PS::IDDevice_HS_DUALSHOCK2:
				application::DS3FROMDUALSHOCK2::stWrite(&susbThis.writeDelegateThis(),&psThis.creadDelegateThis());
				break;
			}
#ifdef _DEBUG_RESPONSE
			{
				static BYTE				stbicounter=0;

				if(stbicounter&1)susbThis.writeDelegateThis().Clear();
				++stbicounter;
			}
#endif
			if(psThis.creadDelegateThis().DUALSHOCK2.eButtonSelect)PORTB|=0x01;
			else PORTB&=~0x01;
			stub::USB::stMain();
			driver::TIMER::stSet(0);	//	ここをタイミング測定の起点に
		}
	}
	return;
}
