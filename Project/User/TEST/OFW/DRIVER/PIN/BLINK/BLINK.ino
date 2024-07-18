//	use "switch_i71.bat"
#include				<ofw.hpp>

INT						main(VOID){
	DDRB|=0x10;
	while(TRUE){
		static BYTE			stbicounter=0;

		if(stbicounter&1)PORTB|=0x10;
		else PORTB&=~0x10;
		++stbicounter;
		OFW::stWait(200);
	}
	return;
}
