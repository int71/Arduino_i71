/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	device/analog									2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				"ofw_device_analog.hpp"

//
//		using
//

using namespace ofw::device;

//
//		class:ANALOG
//

//	public

VOID					ANALOG::stNew(VOID){
	return;
}

VOID					ANALOG::stDelete(VOID){
	return;
}

VOID					ANALOG::stSelect(
	BYTE					biregister
){
	ADMUX=0x40|biregister;
	ADCSRA|=1<<ADSC;
	return;
}

WORD					ANALOG::stwRead(VOID){
	BYTE					bilow,bihigh;

	while(ADCSRA&(1<<ADSC));
	bilow=ADCL;
	bihigh=ADCH;
	return (WORD(bihigh)<<8)|WORD(bilow);
}
