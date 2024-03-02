#include				<ofw.hpp>
#include				<ofw_driver_serial0.hpp>
#include				<ofw_stub_usb_hid_ds3.hpp>
stub::USB_HID_DS3		usbThis;

int main(void){
	OFW::stNew();
	driver::SERIAL0::stNew(230400);
	driver::SERIAL0::stPrintClear();
	usbThis.New();
	for(;;){
		static BYTE			stbtemp=0;

		stub::USB::stMain();
		stbtemp++;
		if(stbtemp&0x80)usbThis.writeThis.eButtonCircle=TRUE;
		else usbThis.writeThis.eButtonCircle=FALSE;
		if(usbThis.eIsReadValid()&&usbThis.readThis.eMotorS)driver::SERIAL0::stPrint(ARGSTR("MOTOR\r\n"));
	}
	return 0;
}
