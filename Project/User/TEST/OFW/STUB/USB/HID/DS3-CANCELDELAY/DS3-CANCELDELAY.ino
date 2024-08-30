/****************************************************************************
**																			**
**																			**
**							整数71の電子工作								**
**																			**
**	DS3-CANCELDELAY									2024 written by int71	**
 ****************************************************************************/
//	use "switch_i71.bat"

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
	BYTE					biskip=0;

	OFW::stNew();
	DDRB|=0x01;
	DDRD|=0x20;
	PORTB|=0x01;
	PORTD|=0x20;
	driver::TIMER::stNew(driver::TIMER::IDClock_Division8);
	psThis.New();
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
			++biskip;
			if((biskip==4)||(psThis.idGetDevice()!=driver::PS::IDDevice_HS_DUALSHOCK2)){
				psThis.Main();
				biskip=0;
			}
			switch(psThis.idGetDevice()){
			case driver::PS::IDDevice_NS_Digital:
			case driver::PS::IDDevice_HS_Digital:
				application::DS3FROMDIGITAL::stWrite(&susbThis.writeDelegateThis(),&psThis.creadDelegateThis());
				break;
			case driver::PS::IDDevice_HS_DUALSHOCK2:
				application::DS3FROMDUALSHOCK2::stWrite(&susbThis.writeDelegateThis(),&psThis.creadDelegateThis());
				break;
			}
			stub::USB::stMain();
			driver::TIMER::stSet(0);	//	ここをタイミング測定の起点に
		}
	}
	return;
}
