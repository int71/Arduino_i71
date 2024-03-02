#include				<ofw_driver_usb_hid.hpp>
using namespace driver;

USB_HID					usbThis;
VOID					Print(BYTE bsource);
VOID					Print(WORD wsource);

VOID					setup(VOID){
	usbThis.New();
	return;
}

VOID					loop(VOID){
	usbThis.Main();
	usbThis.GPIO_Write(usbThis.GPIO_bRead());
	return;
}
