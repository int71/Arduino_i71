#include				<ofw_driver_usb_hid.hpp>
using namespace driver;

USB_HID					usbThis;
VOID					Print(BYTE bsource);
VOID					Print(WORD wsource);

VOID					setup(VOID){
	Serial.begin(115200);
	while(!Serial);
	usbThis.New();
	return;
}

VOID					loop(VOID){
	WORD					wicount;

	for(;;){
		usbThis.Main();
		wicount++;
		if((wicount&0xfff)==0)if(usbThis.eIsConnected()){
			BYTE					i;

			Serial.print(F("VID:"));Print(usbThis.wGetVID());Serial.print(F(" "));
			Serial.print(F("PID:"));Print(usbThis.wGetPID());Serial.println(F(""));
			for(i=0;i<2;i++){
				BYTE					j;

				for(j=0;j<32;j++){
					Print(usbThis.creadGetThis().arbcThis[i*32+j]);
					Serial.print(F(" "));
				}
				Serial.println(F(""));
			}
			Serial.println(F(""));
		}
	}
	return;
}

VOID					Print(
	BYTE					bsource
){
	Serial.print(bsource>>4,HEX);
	Serial.print(bsource&0xf,HEX);
	return;
}

VOID					Print(
	WORD					wsource
){
	Print((BYTE)(wsource>>8));
	Print((BYTE)wsource);
	return;
}
