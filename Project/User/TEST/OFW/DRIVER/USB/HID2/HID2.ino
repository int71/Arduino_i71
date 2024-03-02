#include				<ofw_driver_serial0.hpp>
#include				<ofw_driver_usbhosthid.hpp>
using namespace driver;

USB						usbThis;
USBHOSTHID				usbHID(&usbThis);

INT						main(VOID){
	OFW::stNew();
	SERIAL0::stNew(230400);
	SERIAL0::stPrintClear();

	SERIAL0::stPrint(ARGSTR("START\r\n"));
	if(usbThis.Init()==-1){
		OFW::stWait(100);
		OFW::stReset();
		SERIAL0::stPrint(ARGSTR("    RESET\r\n"));
	}
	do{
		usbThis.Task();
		SERIAL0::stPrint(ARGSTR("WAITING...\r\n"));
	}while(!usbHID.eIsConnected());
	return;
}
