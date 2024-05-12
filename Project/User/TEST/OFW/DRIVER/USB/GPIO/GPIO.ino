//	use "switch_i71.bat"
#include				<ofw_driver_usb_hid.hpp>
using namespace driver;

USB_HID					usbThis;

int main(void){
	OFW::stNew();

	if(usbThis.eNew()){
		while(TRUE){
			usbThis.Main();
			usbThis.GPIO_Write(~usbThis.GPIO_bRead());
			delay(250);
			usbThis.GPIO_Write(0x00);
			delay(250);
		}
	}else{
		DDRB=0xff;
		PORTB=0xff;
		while(TRUE){
			PORTB=0x01;
			delay(250);
			PORTB=0x00;
			delay(250);
		}
	}
	return 0;
}
