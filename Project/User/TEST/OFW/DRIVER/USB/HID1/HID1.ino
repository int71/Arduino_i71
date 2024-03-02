#include				<ofw_driver_usb_hid.hpp>
#include				<ofw_driver_serial0.hpp>
using namespace driver;

USB_HID					usbThis;

INT						main(VOID){
	BYTE					i;

	OFW::stNew();
	SERIAL0::stNew(230400);
	SERIAL0::stPrintClear();
	usbThis.New();
	SERIAL0::stPrintClear();
	SERIAL0::stPrintSetForeColor(6);
	SERIAL0::stPrintSetPosition(0,0);SERIAL0::stPrint(ARGSTR("VID:"));
	SERIAL0::stPrintSetPosition(9,0);SERIAL0::stPrint(ARGSTR("PID:"));
	for(i=0;i<16;i++){
		SERIAL0::stPrintSetPosition(8+i*3,1);SERIAL0::stPrintHEX(i);
	}
	SERIAL0::stPrintSetPosition(8,2);for(i=0;i<16;i++)SERIAL0::stPrint(ARGSTR("-- "));
	for(i=0;i<4;i++){
		SERIAL0::stPrintSetPosition(4,i+3);SERIAL0::stPrintHEX((BYTE)(i*0x10));SERIAL0::stPrint(ARGSTR(": "));
	}
	for(i=0;i<64;i++){
		SERIAL0::stPrintSetPosition(4+i*3,8);SERIAL0::stPrintHEX(i);
	}
	SERIAL0::stPrintSetPosition(4,9);for(i=0;i<64;i++)SERIAL0::stPrint(ARGSTR("-- "));
	SERIAL0::stPrintSetForeColor(9);
	for(;;){
		usbThis.Task();
		if(usbHID.eIsConnected()){
			BYTE					i;

			SERIAL0::stPrintSetPosition(4,0);SERIAL0::stPrintHEX(usbHID.wGetVID());
			SERIAL0::stPrintSetPosition(13,0);SERIAL0::stPrintHEX(usbHID.wGetPID());
			for(i=0;i<4;i++){
				BYTE					j;

				SERIAL0::stPrintSetPosition(8,i+3);
				for(j=0;j<16;j++){
					SERIAL0::stPrintHEX(usbHID.arbcReport[i*16+j]);
					SERIAL0::stPrint(ARGSTR(" "));
				}
			}
			SERIAL0::stPrintSetPosition(4,10);
			for(i=0;i<64;i++){
				BYTE					j;

				SERIAL0::stPrintHEX(usbHID.arbcReport[i]);
				SERIAL0::stPrint(ARGSTR(" "));
			}
		}
		OFW::stWait(20);
	}
	return;
}
