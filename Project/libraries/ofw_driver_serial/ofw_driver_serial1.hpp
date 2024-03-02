/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	driver/serial1									2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#if defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)
#include				<ofw.hpp>

//
//		namespace:ofw
//

namespace ofw{

	//
	//		namespace:driver
	//

	namespace driver{

		//
		//		macro
		//

		#define UDRx			UDR1
		#define UBRRx			UBRR1
		#define UCSRxA			UCSR1A
		#define UCSRxB			UCSR1B
		#define UCSRxC			UCSR1C
		#define DDRx			DDRD
		#define PORTx			PORTD
		#define OFW_DRIVER_SERIAL_stcbiRXD	2
		#define OFW_DRIVER_SERIAL_stcbiTXD	3
		#define USARTx_RX_vect	USART1_RX_vect

		//
		//		class:SERIAL1
		//

		class SERIAL1{
		public:

			//
			//		const
			//

			static CBYTE			stcbnBuffer=64;
			static CBYTE			stcbnPacketSize=32;
			static CBYTE			stcbiRXD=OFW_DRIVER_SERIAL_stcbiRXD;
			static CBYTE			stcbiTXD=OFW_DRIVER_SERIAL_stcbiTXD;
			enum IDLENGTH{
				IDLength_5bits,
				IDLength_6bits,
				IDLength_7bits,
				IDLength_8bits,
				IDLength_9bits
			};
			enum IDPARITY{
				IDParity_None,
				IDParity_Even,
				IDParity_Odd
			};
			enum IDSTOPBIT{
				IDStopbit_1,
				IDStopbit_2
			};

			//
			//		class
			//

			//	ST
			class ST;
			typedef const ST		CST;
			typedef ST*				LPST;
			typedef CST*			LPCST;

			//
			//		class:ST
			//

			class ST{
			public:
				BYTE					arbRead[stcbnBuffer];
				BYTE					biReadDone;
				BYTE					biReadCurrent;
			};

			//
			//		body:SERIALx
			//

		private:
			static ST				st;
		public:
			static VOID				stNew(DWORD dwnrate);
			static VOID				stNew(DWORD dwnrate,IDLENGTH idlength,IDPARITY idparity,IDSTOPBIT idstopbit);
			static VOID				stDelete(VOID);
			static VOID				stReset(VOID);
			static INLINE VOID		stVectorRead(VOID){
				st.arbRead[st.biReadDone]=UDRx;
				st.biReadDone=(st.biReadDone+1)&(stcbnBuffer-1);
				return;
			}
			static INLINE BOOL		steRead(VOID){
				return (st.biReadDone!=st.biReadCurrent);
			}
			static BYTE				stbRead(VOID);
			static BYTE				stbRead(WORDS& wsnusectimeout);
			static VOID				stRead(LPVOID lpdestination,BYTE bnsize);
			static VOID				stRead(LPVOID lpdestination,BYTE& bnsize,WORDS& wsnusectimeout);
			static VOID				stWrite(BYTE bsource);
			static VOID				stWrite(LPCVOID lpcsource,BYTE bnsize);
			static VOID				stWrite(LPGVOID lpgsource,BYTE bnsize);
			static BOOL				steRequestRead(BYTE bccode,LPVOID lpdestination,BYTE bnsize,WORDS wsnusectimeout);
			static BOOL				steRequestWrite(BYTE bccode,LPCVOID lpcsource,BYTE bnsize,WORDS wsnusectimeout);
			static BOOL				steRequestWrite(BYTE bccode,LPGVOID lpgsource,BYTE bnsize,WORDS wsnusectimeout);
			static BYTE				stbnReplyRead(LPCVOID lpcsource,BYTE bnsize,WORDS wsnusectimeout);
			static BYTE				stbnReplyRead(LPGVOID lpgsource,BYTE bnsize,WORDS wsnusectimeout);
			static BYTE				stbnReplyWrite(LPVOID lpdestination,BYTE bnsize,WORDS wsnusectimeout);
			static VOID				stPrint(LPCSTR lpcstrsource);
			static VOID				stPrint(LPGSTR lpgstrsource);
			static VOID				stPrint(LONG lsource);
			static VOID				stPrintHEX(BYTE bsource);
			static VOID				stPrintHEX(WORD wsource);
			static VOID				stPrintHEX(DWORD dwsource);
			static VOID				stPrintClear(VOID);
			static VOID				stPrintSetPosition(BYTE bix,BYTE biy);
			static VOID				stPrintSetForeColor(BYTE bccolor);
			static VOID				stPrintSetBackColor(BYTE bccolor);
		private:
			static INLINE VOID		stIncrementCurrent(VOID){
				st.biReadCurrent=(st.biReadCurrent+1)&(stcbnBuffer-1);
				return;
			}
			static VOID				stPrintHEX_Half(BYTE bsource);
		};
	}
}

#endif
