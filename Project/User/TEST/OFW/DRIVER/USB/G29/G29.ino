//	use "switch_i71.bat"
#include				<ofw_driver_usb_hid.hpp>
using namespace driver;

USB_HID					usbThis;

int main(void){
	OFW::stNew();
	if(usbThis.eNew()){
		while(TRUE){
			usbThis.Main();
			if(usbThis.eIsConnected()){
				if(
					(usbThis.wGetVID()==0x046d)&&
					(usbThis.wGetPID()==0xc260)
				){
					usbThis.Poll();
					usbThis.GPIO_Write(BYTE(usbThis.creadDelegateThis().readVID046DPIDC260.wiSteering>>8));
				}else{
					usbThis.GPIO_Write(0xf0);
					delay(250);
					usbThis.GPIO_Write(usbThis.wGetVID()>>8);
					delay(250);
					usbThis.GPIO_Write(0x0f);
					delay(250);
					usbThis.GPIO_Write(usbThis.wGetVID()&0xff);
					delay(250);
				}
			}else{
				usbThis.GPIO_Write(0xff);
				delay(250);
				usbThis.GPIO_Write(0x00);
				delay(250);
			}
		}
	}
	DDRB=0xff;
	PORTB=0xff;
	while(TRUE){
		PORTB=0x01;
		delay(500);
		PORTB=0x00;
		delay(500);
	}
	return 0;
}
