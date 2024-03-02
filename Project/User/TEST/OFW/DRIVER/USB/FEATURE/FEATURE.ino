#include				<ofw_driver_usb_hid.hpp>
using namespace driver;

USB_HID					usbThis;
VOID					Read(BYTE bcreportid);
VOID					Write(BYTE bcreportid,LPGBYTE lpgbsource,BYTE bnsize);
VOID					Print(WORD wsource);
VOID					Print(BYTE bsource);
VOID					PrintDigit(BYTE bsource);

VOID					setup(VOID){
	Serial.begin(115200);
	while(!Serial);
	usbThis.New();
	return;
}

VOID					loop(VOID){
	WORD					wicount;
	BYTE					biprogress;

	wicount=0;
	biprogress=0;
	for(;;){
		usbThis.Main();
		wicount++;
		if((wicount&0xfff)==0)if(usbThis.eIsConnected())switch(biprogress){
		case 0:
			Read(0x01);
			biprogress++;
			break;
		case 1:
			Read(0xf2);
			biprogress++;
			break;
		case 2:
			Read(0xf5);
			biprogress++;
			break;
		case 3:
			Write(0xf5,ARGBYTE(
				0x01,0x00,0x90,0x34,0xfc,0x44,0x8e,0x11
			),0x08);
			biprogress++;
			break;
		case 4:
			Read(0xf5);
			biprogress++;
			break;
		case 5:
			Write(0xef,ARGBYTE(
				0x00,0x00,0x00,0x00,0x03,0x01,0xa0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
			),0x30);
			biprogress++;
			break;
		case 6:
			Read(0xef);
			biprogress++;
			break;
		case 7:
			Write(0xef,ARGBYTE(
				0x00,0x00,0x00,0x00,0x03,0x01,0xb0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
				0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
			),0x30);
			biprogress++;
			break;
		case 8:
			Read(0xef);
			biprogress++;
			break;
		case 9:
			Read(0xf8);
			biprogress++;
			break;
		}
	}
	return;
}

VOID					Read(
	BYTE					bcreportid
){
	BYTE					arbread[64];
	BYTE					i;

	usbThis.ReadControlReport(bcreportid,arbread,sizeof(arbread));
	Serial.print(F("READ ("));
	Print(bcreportid);
	Serial.print(F("):"));
	for(i=0;i<sizeof(arbread);i++){
		Print(arbread[i]);
		Serial.print(F(" "));
	}
	Serial.print(F("\r\n"));
	return;
}

VOID					Write(
	BYTE					bcreportid,
	LPGBYTE					lpgbsource,
	BYTE					bnsize
){
	BYTE					arbread[64];
	BYTE					i;

	OFW::stCopy(arbread,lpgbsource,bnsize);
	Serial.print(F("WRITE("));
	Print(bcreportid);
	Serial.print(F("):"));
	for(i=0;i<bnsize;i++){
		Print(arbread[i]);
		Serial.print(F(" "));
	}
	Serial.print(F("\r\n"));
	usbThis.WriteControlReport(bcreportid,arbread,bnsize);
	return;
}

VOID					Print(
	WORD					wsource
){
	Print((BYTE)(wsource>>8));
	Print((BYTE)wsource);
	return;
}

VOID					Print(
	BYTE					bsource
){
	PrintDigit(bsource>>4);
	PrintDigit(bsource&0xf);
	return;
}

VOID					PrintDigit(
	BYTE					bsource
){
	if(bsource<10)Serial.print((char)('0'+bsource));
	else Serial.print((char)('a'-10+bsource));
	return;
}
