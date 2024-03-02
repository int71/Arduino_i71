/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/ps											2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw_device_pin.hpp>

//
//		namespace:ofw
//

namespace ofw{

	//
	//		namespace:stub
	//

	namespace stub{

		//
		//		class
		//

		class PS;
		typedef const PS		CPS;
		typedef PS*				LPPS;
		typedef CPS*			LPCPS;

		//
		//		class:PS
		//

		class PS{
		public:

			//
			//		const
			//

			//	REGISTER

			#define OFW_STUB_PS_REGISTER_DDR	DDRD
			#define OFW_STUB_PS_REGISTER_PORT	PORTD
			#define OFW_STUB_PS_REGISTER_PIN	PIND
			static CBYTE			REGISTER_stcbiBitDAT=0;
			static CBYTE			REGISTER_stcbcMaskDAT=1<<REGISTER_stcbiBitDAT;
			static CBYTE			REGISTER_stcbiBitCMD=7;
			static CBYTE			REGISTER_stcbcMaskCMD=1<<REGISTER_stcbiBitCMD;
			static CBYTE			REGISTER_stcbiBitSEL=2;
			static CBYTE			REGISTER_stcbcMaskSEL=1<<REGISTER_stcbiBitSEL;
			static CBYTE			REGISTER_stcbiBitCLK=6;
			static CBYTE			REGISTER_stcbcMaskCLK=1<<REGISTER_stcbiBitCLK;
			static CBYTE			REGISTER_stcbiBitACK=1;
			static CBYTE			REGISTER_stcbcMaskACK=1<<REGISTER_stcbiBitACK;
			static CBYTE			REGISTER_stcbcPORTDefault=0x38;

			//
			//		body:PS
			//

		public:
			static VOID				stNew(VOID);
			static VOID				stDelete(VOID);
			static INLINE BOOL		steTrytoOpen(VOID){
				return ((OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskSEL)==0x00);
			}
			static VOID				stOpen(VOID);
			static VOID				stClose(VOID);
			static BYTE				stbWriteBYTE(BYTE bcdata);
			static BYTE				stbWriteBYTEHS(BYTE bcdata);
			static VOID				stWriteACK(VOID);
		private:
			static VOID				stWaitClockAdjust(VOID);
			static VOID				stWaitClock(VOID);
			static INLINE VOID		stWaitClockHS(VOID){
//				OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();
				return;
			}
		};
	}
}
