#include				<ofw_driver_serial0.hpp>

int main(void){
	OFW::stNew();
	driver::SERIAL0::stNew(230400);
	driver::SERIAL0::stPrintClear();
	for(;;){
		driver::SERIAL0::stPrint(ARGSTR("TEST\r\n"));
		delay(1000);
	}
	return 0;
}
