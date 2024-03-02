#include				<ofw_driver_usb_hid.hpp>
#include				<ofw_driver_serial0.hpp>
using namespace driver;

USB_HID					usbThis;
VOID					Read(BYTE bcreportid);
VOID					Write(BYTE bcreportid,LPGBYTE lpgbsource,BYTE bnsize);

int main(void){
	WORD					wicount;
	BYTE					biprogress;

	OFW::stNew();
	driver::SERIAL0::stNew(230400);
	driver::SERIAL0::stPrintClear();
	usbThis.New();
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
	return 0;
}


VOID					loop(VOID){

	return;
}

VOID					Read(
	BYTE					bcreportid
){
	BYTE					arbread[64];
	BYTE					i;

	usbThis.ReadControlReport(bcreportid,arbread,sizeof(arbread));
	SERIAL0::stPrint(ARGSTR("READ ("));
	SERIAL0::stPrintHEX(bcreportid);
	SERIAL0::stPrint(ARGSTR("):"));
	for(i=0;i<sizeof(arbread);i++){
		SERIAL0::stPrintHEX(arbread[i]);
		SERIAL0::stPrint(ARGSTR(" "));
	}
	SERIAL0::stPrint(ARGSTR("\r\n"));
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
	SERIAL0::stPrint(ARGSTR("WRITE("));
	SERIAL0::stPrintHEX(bcreportid);
	SERIAL0::stPrint(ARGSTR("):"));
	for(i=0;i<bnsize;i++){
		SERIAL0::stPrintHEX(arbread[i]);
		SERIAL0::stPrint(ARGSTR(" "));
	}
	SERIAL0::stPrint(ARGSTR("\r\n"));
	usbThis.WriteControlReport(bcreportid,arbread,bnsize);
	return;
}
