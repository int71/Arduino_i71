//	use "switch_i71.bat"
#include				<ofw_driver_serial0.hpp>

int main(void){
	OFW::stNew();
	driver::SERIAL0::stNew(115200);
	driver::SERIAL0::stPrintClear();
	{
		ATOMIC					atomic;

		TCCR1A=0x00;
		TCCR1B=0x04;
		TIMSK1&=~0x01;
	}
	while(TRUE){
		ATOMIC					atomic;
		const auto				cwicounter=WORD(TCNT1);
		static BYTE				stbicounter=0;

		driver::SERIAL0::stPrintHEX(BYTE(cwicounter>>8));driver::SERIAL0::stPrintHEX(BYTE(cwicounter&0xff));
		driver::SERIAL0::stPrint(ARGSTR("\r\n"));
		OFW::stWait(10);
		if(stbicounter==32){
			stbicounter=0;
			TCNT1=0;
		}
		++stbicounter;
	}
	return 0;
}
