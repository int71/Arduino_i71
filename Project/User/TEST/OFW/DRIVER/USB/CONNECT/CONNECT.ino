//	use "switch_i71.bat"
#include				<ofw_driver_serial0.hpp>
#include				<ofw_driver_usb_hid.hpp>
using namespace driver;

USB_HID					usbThis;

int main(void){
	BOOL					ehost;
	OFW::stNew();
	SERIAL0::stNew(115200);
	SERIAL0::stPrintClear();
	ehost=usbThis.eNew();
	while(TRUE){
		if(ehost){
			usbThis.Main();
			usbThis.GPIO_Write(usbThis.GPIO_bRead());
			SERIAL0::stPrintHEX(usbThis.GPIO_bRead());
			SERIAL0::stPrint(ARGSTR("\r\n"));
		}
		else SERIAL0::stPrint(ARGSTR("-\r\n"));
		delay(1000);
	}
	return 0;
}
