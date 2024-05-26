#include				<ofw.hpp>
#include				<ofw_stub_usb_hid_ds3.hpp>

int main(void){
	stub::USB_HID_DS3		usbthis;

	OFW::stNew();
	usbthis.New();
	DDRB=0xff;
	PORTB=0xff;
	while(TRUE){
		static WORD			stwtemp=0x0000;

		{
			ATOMIC				atomic;

			stub::USB::stMain();
		}
		stwtemp++;
		if(stwtemp&0x0040){
			usbthis.writeDelegateThis().eButtonCircle=TRUE;
			PORTB=0x00;
		}else{
			usbthis.writeDelegateThis().eButtonCircle=FALSE;
			PORTB=0x01;
		}
	}
	return 0;
}
