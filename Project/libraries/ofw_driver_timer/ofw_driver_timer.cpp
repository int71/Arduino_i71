/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	driver/timer									2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				"ofw_driver_timer.hpp"

//
//		using
//

using namespace ofw::driver;

//
//		class:TIMER
//

//	public

VOID					TIMER::stNew(
	const IDCLOCK			cidclock
){
	ATOMIC					atomic;

	TCCR1A=0x00;
	TCCR1B=cidclock;
	TIMSK1&=~0x01;
	return;
}

VOID					TIMER::stDelete(VOID){
	return;
}

VOID					TIMER::stSet(
	CWORD					cwitime
){
	ATOMIC					atomic;

	TCNT1=cwitime;
	return;
}

WORD					TIMER::stwiGet(VOID){
	ATOMIC					atomic;

	return TCNT1;
}

VOID					TIMER::stWaitUntil(
	CWORD					cwitime
){
	while(stwiGet()<cwitime);
	return;
}
