#include				<ofw_stub_usb_hid_ds3.hpp>
#include				<ofw_driver_ps.hpp>
#include				<ofw_application_ds3fromdualshock2.hpp>

int main(void){
	stub::USB_HID_DS3		usbthis;
	driver::PS				psthis;

	OFW::stNew();
	usbthis.New();
	psthis.New();
	application::DS3FROMDUALSHOCK2::stNew();
//	DDRC=0x40;
	while(TRUE){
//		PORTC=0x40;
		stub::USB::stMain();
//		PORTC=0x00;
		OFW::stWaitFine(210);
		if(usbthis.eIsReadable()){
			//	32.7um
			if(usbthis.bcGetReportID()==0x01){
				//	2.67um
				psthis.SetRumbleS(
					usbthis.cread1DelegateThis().eMotorS,
					usbthis.cread1DelegateThis().bnMotorSLength
				);
				psthis.SetRumbleL(
					usbthis.cread1DelegateThis().nMotorLStrength*0x55,
					usbthis.cread1DelegateThis().bnMotorLLength
				);
			}else{
				OFW::stWaitFine(1);
			}
		}else{
			OFW::stWaitFine(20);
		}
		psthis.Main();
		if(psthis.idGetDevice()==driver::PS::IDDevice_HS_DUALSHOCK2){
			application::DS3FROMDUALSHOCK2::stWrite(&usbthis.writeDelegateThis(),&psthis.creadDelegateThis());
		}
	}
	return 0;
}
