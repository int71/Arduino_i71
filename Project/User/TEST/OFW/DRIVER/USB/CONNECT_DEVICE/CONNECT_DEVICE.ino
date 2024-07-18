//	use "switch_i71.bat"
#include				<ofw_driver_serial0.hpp>
#include				<ofw_driver_usb_hid.hpp>
using namespace driver;

USB_HID					usbThis;

int main(void){
	OFW::stNew();
	SERIAL0::stNew(115200);
	SERIAL0::stPrintClear();
	if(usbThis.eNew()){
		SERIAL0::stPrint(ARGSTR("UHS CON\r\n"));
		while(TRUE){
			usbThis.Main();
			if(usbThis.eIsConnected())SERIAL0::stPrint(ARGSTR("CON!\r\n"));
		}
	}else{
		DDRB=0xff;
		PORTB=0xff;
		while(TRUE){
			SERIAL0::stPrint(ARGSTR("-\r\n"));
			OFW::stWait(1000);
		}
	}
	return 0;
}
