//	use "switch_i71.bat"
#include				<ofw.hpp>

int main(void){
	OFW::stNew();
	DDRD|=0x01;
	{
		ATOMIC					atomic;

		TCCR1A=0x00;
		TCCR1B=0x02;
		TIMSK1&=~0x01;
	}
	while(TRUE){
		ATOMIC					atomic;

		while(TCNT1<0x800);
		PORTD|=0x01;TCNT1=0;
		while(TCNT1<0x800);
		PORTD&=~0x01;TCNT1=0;
	}
	return 0;
}
