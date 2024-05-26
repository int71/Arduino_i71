//	use "switch_i71.bat"
#include				<ofw.hpp>

INT						main(VOID){
	DDRB|=0x01;
	while(TRUE){
		static BYTE			stbicounter=0;

		if(stbicounter&1)PORTB|=0x01;
		else PORTB&=~0x01;
		++stbicounter;
		OFW::stWait(250);
	}
	return;
}
