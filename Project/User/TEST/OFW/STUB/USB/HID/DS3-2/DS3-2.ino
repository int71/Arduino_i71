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
	while(TRUE){
		stub::USB::stMain();
		if(usbthis.eIsWritable()){
			OFW::stWaitFine(220);
			psthis.Main();
			if(psthis.idGetDevice()==driver::PS::IDDevice_HS_DUALSHOCK2){
				application::DS3FROMDUALSHOCK2::stWrite(&usbthis.writeDelegateThis(),&psthis.creadDelegateThis());
			}
		}
	}
	return 0;
}
