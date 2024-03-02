/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb_hid_ds3								2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw_stub_usb_hid.hpp>

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

		class USB_HID_DS3;
		typedef const USB_HID_DS3	CUSB_HID_DS3;
		typedef USB_HID_DS3*	LPUSB_HID_DS3;
		typedef CUSB_HID_DS3*	LPCUSB_HID_DS3;

		//
		//		class:USB_HID_DS3
		//

		class USB_HID_DS3:public USB_HID{
		public:

			//
			//		const
			//

			//	IDSTRINGDESC
			enum IDSTRINGDESC{
				IDStringDesc_Language=0,
				IDStringDesc_Manufacturer=1,
				IDStringDesc_Product=2,
				IDStringDesc_Serial=0
			};
			//	IDENDPOINT
			enum IDENDPOINT{
				IDEndPoint_Read0=2,
				IDEndPoint_Write0=1
			};
			static CBYTE			stcbnEndPoint=2;

			//
			//		class
			//

			//	USERDESC
			class USERDESC;
			typedef const USERDESC	CUSERDESC;
			typedef USERDESC*		LPUSERDESC;
			typedef CUSERDESC*		LPCUSERDESC;
			#define GUSERDESC		static PROGMEM CUSERDESC
			typedef LPG<USERDESC>	LPGUSERDESC;
			typedef const LPGUSERDESC	CLPGUSERDESC;
			#define ARGUSERDESC(...)	(LPGUSERDESC)({GUSERDESC starguserdesctemp[]={__VA_ARGS__};starguserdesctemp;})
			//	READ0
			class READ0;
			typedef const READ0		CREAD0;
			typedef READ0*			LPREAD0;
			typedef CREAD0*			LPCREAD0;
			#define GREAD0			static PROGMEM CREAD0
			typedef LPG<READ0>		LPGREAD0;
			typedef const LPGREAD0	CLPGREAD0;
			#define ARGREAD0(...)	(LPGREAD0)({GREAD0 stargreadtemp[]={__VA_ARGS__};stargreadtemp;})
			//	READ1
			class READ1;
			typedef const READ1		CREAD1;
			typedef READ1*			LPREAD1;
			typedef CREAD1*			LPCREAD1;
			#define GREAD1			static PROGMEM CREAD1
			typedef LPG<READ1>		LPGREAD1;
			typedef const LPGREAD1	CLPGREAD1;
			#define ARGREAD1(...)	(LPGREAD1)({GREAD1 stargreadtemp[]={__VA_ARGS__};stargreadtemp;})
			//	WRITE
			class WRITE;
			typedef const WRITE		CWRITE;
			typedef WRITE*			LPWRITE;
			typedef CWRITE*			LPCWRITE;
			#define GWRITE			static PROGMEM CWRITE
			typedef LPG<WRITE>		LPGWRITE;
			typedef const LPGWRITE	CLPGWRITE;
			#define ARGWRITE(...)	(LPGWRITE)({GWRITE stargwritetemp[]={__VA_ARGS__};stargwritetemp;})

			//
			//		class:USERDESC
			//

			class USERDESC{
			public:
				CONFIGDESC				cfgdescThis;
				INTERFACEDESC			ifdescThis;
				HIDDESC					hiddescThis;
				ENDPOINTDESC			epdescRead0;
				ENDPOINTDESC			epdescWrite0;
			};

			//
			//		class:READ0
			//

			class READ0{
			public:
				BYTE					bcReportID;			//	 0		00
				BYTE					bcCommand;			//	 1		SIXAXIS_COMMAND_SET_MOTORS(2)
				BYTE					_padding0[3];		//	 2~4
				BYTE					bnMotorSLength;		//	 5		xx
				BYTE					eMotorS:1;
				BYTE					_padding1:7;		//	 6		xx
				BYTE					bnMotorLLength;		//	 7		xx
				BYTE					_padding2:6;
				BYTE					nMotorLStrength:2;	//	 8		xx
				BYTE					_padding4[39];		//	 9~47
			public:
				INLINE VOID				New(VOID){
					OFW::stFill(this,sizeof(*this),0x00);
					return;
				}
				INLINE VOID				Delete(VOID){
					return;
				}
			};

			//
			//		class:READ1
			//

			class READ1{
			public:
				BYTE					bcReportID;			//	 0		01
				BYTE					eAnalog10:1;
				BYTE					_padding0:1;
				BYTE					eAccel8:1;
				BYTE					_padding1:4;
				BYTE					eSpecial:1;			//	 1		xx
				BYTE					bnMotorSLength;		//	 2		xx
				BYTE					eMotorS:1;
				BYTE					_padding2:7;		//	 3		xx
				BYTE					bnMotorLLength;		//	 4		xx
				BYTE					_padding3:6;
				BYTE					nMotorLStrength:2;	//	 5		xx
				BYTE					_padding4[42];		//	 6~47
			public:
				INLINE VOID				New(VOID){
					OFW::stFill(this,sizeof(*this),0x00);
					return;
				}
				INLINE VOID				Delete(VOID){
					return;
				}
			};

			//
			//		class:WRITE
			//

			class WRITE{
			public:
				BYTE					bcReportID;			//	 0		01
				BYTE					bcFixed0;			//	 1		00
				BYTE					eButtonSelect:1;
				BYTE					eButtonL3:1;
				BYTE					eButtonR3:1;
				BYTE					eButtonStart:1;
				BYTE					eButtonUp:1;
				BYTE					eButtonRight:1;
				BYTE					eButtonDown:1;
				BYTE					eButtonLeft:1;		//	 2		xx
				BYTE					eButtonL2:1;
				BYTE					eButtonR2:1;
				BYTE					eButtonL1:1;
				BYTE					eButtonR1:1;
				BYTE					eButtonTriangle:1;
				BYTE					eButtonCircle:1;
				BYTE					eButtonCross:1;
				BYTE					eButtonSquare:1;	//	 3		xx
				BYTE					eButtonPS:1;
				BYTE					_padding0:7;		//	 4		xx
				BYTE					bcFixed1;			//	 5		00
				BYTE					biAxisLX;			//	 6		xx
				BYTE					biAxisLY;			//	 7		xx
				BYTE					biAxisRX;			//	 8		xx
				BYTE					biAxisRY;			//	 9		xx
				BYTE					arbcFixed2[4];		//	10~13	00 00 00 00
				BYTE					biButtonUp;			//	14		xx
				BYTE					biButtonRight;		//	15		xx
				BYTE					biButtonDown;		//	16		xx
				BYTE					biButtonLeft;		//	17		xx
				BYTE					biButtonL2;			//	18		xx
				BYTE					biButtonR2;			//	19		xx
				BYTE					biButtonL1;			//	20		xx
				BYTE					biButtonR1;			//	21		xx
				BYTE					biButtonTriangle;	//	22		xx
				BYTE					biButtonCircle;		//	23		xx
				BYTE					biButtonCross;		//	24		xx
				BYTE					biButtonSquare;		//	25		xx
				BYTE					arbcFixed3[14];		//	26~39	00 00 00 03 ef 16 00 00 00 00 33 46 77 01
				WORD					niAccelX:10;
				WORD					_padding1:6;		//	40~41	xx xx
				WORD					niAccelY:10;
				WORD					_padding2:6;		//	42~43	xx xx
				WORD					niAccelZ:10;
				WORD					_padding3:6;		//	44~45	xx xx
				WORD					niGyro:10;
				WORD					_padding4:6;		//	46~47	xx xx
				BYTE					bcFixed4;			//	48		ec
			public:
				INLINE VOID				New(VOID){
					OFW::stFill(this,sizeof(*this),0x00);
					bcReportID=		0x01;
					arbcFixed3[ 3]=	0x03;
					arbcFixed3[ 4]=	0xef;
					arbcFixed3[ 5]=	0x16;
					arbcFixed3[10]=	0x33;
					arbcFixed3[11]=	0x46;
					arbcFixed3[12]=	0x77;
					arbcFixed3[13]=	0x01;
					bcFixed4=		0xec;
					Clear();
					return;
				}
				INLINE VOID				Delete(VOID){
					return;
				}
				INLINE VOID				Clear(VOID);
			};

			//
			//		body:USB_HID_DS3
			//

		private:
			union{
				READ0					read0This;
				READ1					read1This;
			};
			WRITE					writeThis;
			WRITE					writeFeature;
		public:
			INLINE CREAD0&			cread0DelegateThis(VOID)const{
				return read0This;
			}
			INLINE CREAD1&			cread1DelegateThis(VOID)const{
				return read1This;
			}
			INLINE WRITE&			writeDelegateThis(VOID){
				return writeThis;
			}
			INLINE BYTE				bcGetReportID(VOID){
				return read0This.bcReportID;
			}
		private:
			VOID					Main_Self(VOID);
			BYTE					EP_Initialize_bcConfigType(BYTE biep);
			VOID					VECTOR_Request_Standard_Descriptor_Device(VOID);
			VOID					VECTOR_Request_Standard_Descriptor_Configuration(VOID);
			VOID					VECTOR_Request_Standard_Descriptor_String(BYTE bithis);
			VOID					VECTOR_Request_Class_Interface(LPREQUEST lpreqsource);
			VOID					New_Self2(VOID);
			VOID					Delete_Self2(VOID);
			VOID					VECTOR_Request_Standard_Descriptor_Report(VOID);
		};
	}
}
