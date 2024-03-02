/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb_hid_ds3ps3								2024 written by int71	**
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

		class USB_HID_DS3PS3;
		typedef const USB_HID_DS3PS3	CUSB_HID_DS3PS3;
		typedef USB_HID_DS3PS3*	LPUSB_HID_DS3PS3;
		typedef CUSB_HID_DS3PS3*	LPCUSB_HID_DS3PS3;

		//
		//		class:USB_HID_DS3PS3
		//

		class USB_HID_DS3PS3:public USB_HID{
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
			//	READ
			class READ;
			typedef const READ		CREAD;
			typedef READ*			LPREAD;
			typedef CREAD*			LPCREAD;
			#define GREAD			static PROGMEM CREAD
			typedef LPG<READ>		LPGREAD;
			typedef const LPGREAD	CLPGREAD;
			#define ARGREAD(...)	(LPGREAD)({GREAD stargreadtemp[]={__VA_ARGS__};stargreadtemp;})
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
			//		class:READ
			//

			class READ{
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
			//		body:USB_HID_DS3PS3
			//

		private:
			READ					readThis;
			WRITE					writeThis;
			BYTE					arbcAddress[6];
			BYTE					bcEF;
			BOOL					eReadValid:1;
		public:
			INLINE CREAD&			creadDelegateThis(VOID)const{
				return readThis;
			}
			INLINE WRITE&			writeDelegateThis(VOID){
				return writeThis;
			}
			INLINE BOOL				eIsReadValid(VOID){
				BOOL					ereturn=eReadValid;

				eReadValid=FALSE;
				return ereturn;
			}
		private:
			VOID					Main_Self(VOID);
			BYTE					EP_Initialize_bcConfigType(BYTE biep);
			VOID					VECTOR_Request_Standard_Descriptor_Device(VOID);
			VOID					VECTOR_Request_Standard_Descriptor_Configuration(VOID);
			VOID					VECTOR_Request_Standard_Descriptor_String(BYTE bithis);
			VOID					New_Self2(VOID);
			VOID					Delete_Self2(VOID);
			VOID					VECTOR_Request_Standard_Descriptor_Report(VOID);
			VOID					VECTOR_Request_Class_Interface_Read(LPREQUEST lpreqsource,LPCBYTE lpcbsource,SIZE sznsource);
			SIZE					VECTOR_Request_Class_Interface_sznWrite(LPREQUEST lpreqsource,LPBYTE lpbdestination);
		};
	}
}
