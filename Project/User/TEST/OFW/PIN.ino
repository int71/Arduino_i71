#include				<ofw.hpp>

INT						main(VOID){
	OFW::stNew();
	DDRF=0xff;
	for(;;){
		PORTF=0xff;
		PORTF=0x00;
	}
	return 0;
}
