/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	device/analog									2024 written by int71	**
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

	namespace device{

		//
		//		class
		//

		class ANALOG;
		typedef const ANALOG	CPS;
		typedef ANALOG*			LPPS;
		typedef CPS*			LPCPS;

		//
		//		class:ANALOG
		//

		class ANALOG{
		public:
			static VOID				stNew(VOID);
			static VOID				stDelete(VOID);
			static VOID				stSelect(BYTE biregister);
			static INLINE BOOL		steIsReady(VOID){
				return ((ADCSRA&(1<<ADSC))==0);
			}
			static WORD				stwRead(VOID);
		};
	}
}
