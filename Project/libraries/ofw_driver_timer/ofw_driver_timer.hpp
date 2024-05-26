/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	driver/timer									2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw.hpp>

//
//		namespace:ofw
//

namespace ofw{

	//
	//		namespace:device
	//

	namespace driver{

		//
		//		class
		//

		class TIMER;
		typedef const TIMER		CTIMER;
		typedef TIMER*			LPTIMER;
		typedef CTIMER*			LPCTIMER;

		//
		//		class:TIMER
		//

		class TIMER{
		public:

			//
			//		const
			//

			enum IDCLOCK:BYTE{
				IDClock_Stop=0x00,
				IDClock_Division1=0x01,		//	    256(usec)@0x1000/16MHz
				IDClock_Division8=0x02,		//	  2,048(usec)@0x1000/16MHz
				IDClock_Division64=0x03,	//	 16,384(usec)@0x1000/16MHz
				IDClock_Division256=0x04,	//	 65,536(usec)@0x1000/16MHz
				IDClock_Division1024=0x05	//	262,144(usec)@0x1000/16MHz
			};

			//
			//		body:TIMER
			//

		public:
			static VOID				stNew(const IDCLOCK cidclock);
			static VOID				stDelete(VOID);
			static VOID				stSet(CWORD cwitime);
			static WORD				stwiGet(VOID);
			static VOID				stWaitUntil(CWORD cwitime);
		};
	}
}
