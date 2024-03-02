/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb_hid_g29ps4								2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw_stub_usb_hid.hpp>
#include				<ofw_driver_usb_hid.hpp>

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

		class USB_HID_G29PS4;
		typedef const USB_HID_G29PS4	CUSB_HID_G29PS4;
		typedef USB_HID_G29PS4*	LPUSB_HID_G29PS4;
		typedef CUSB_HID_G29PS4*	LPCUSB_HID_G29PS4;

		//
		//		class:USB_HID_G29PS4
		//

		class USB_HID_G29PS4:public USB_HID{
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
				BYTE					bcReportID;			//	00		05
				BYTE					arbcFeedback[31];
			public:
				INLINE					New(VOID){
					OFW::stFill(this,sizeof(*this),0x00);
					return;
				}
				INLINE					Delete(VOID){
					return;
				}
			};

			//
			//		class:WRITE
			//

			class WRITE{
			public:
				BYTE					bcReportID;			//	00		01
				BYTE					arbFixed0[4];		//	01~04	80 80 80 80
				BYTE					n4cPad:4;			//	05
				BYTE					eButtonSquare:1;
				BYTE					eButtonCross:1;
				BYTE					eButtonCircle:1;
				BYTE					eButtonTriangle:1;
				BYTE					eButtonL1:1;		//	06
				BYTE					eButtonR1:1;
				BYTE					eButtonL2:1;
				BYTE					eButtonR2:1;
				BYTE					eButtonShare:1;
				BYTE					eButtonOption:1;
				BYTE					eButtonL3:1;
				BYTE					eButtonR3:1;
				BYTE					eButtonPS:1;		//	07
				BYTE					n7Fixed1:7;
				BYTE					arbFixed2[35];		//	08~2a	00...00
				WORD					wiSteering;			//	2b~2c
				WORD					wiPedalAccel;		//	2d~2e
				WORD					wiPedalBrake;		//	2f~30
				WORD					wiPedalClutch;		//	31~32
				BYTE					eShift1:1;			//	33
				BYTE					eShift2:1;
				BYTE					eShift3:1;
				BYTE					eShift4:1;
				BYTE					eShift5:1;
				BYTE					eShift6:1;
				BYTE					n1Fixed:1;
				BYTE					eShiftR:1;
				BYTE					arbFixed3[2];		//	34~35	ff ff
				BYTE					eDialEnter:1;		//	36
				BYTE					eDialL:1;
				BYTE					eDialR:1;
				BYTE					eAdjusterMinus:1;
				BYTE					eAdjusterPlus:1;
				BYTE					n5Fixed4:3;
				BYTE					arbFixed4[9];		//	37~3f	00...00
			public:
				INLINE VOID				New(VOID){
					OFW::stFill(this,sizeof(*this),0x00);
					bcReportID=		0x01;
					arbFixed0[0]=	0x80;
					arbFixed0[1]=	0x80;
					arbFixed0[2]=	0x80;
					arbFixed0[3]=	0x80;
					arbFixed3[0]=	0xff;
					arbFixed3[1]=	0xff;
					Clear();
					return;
				}
				INLINE VOID				Delete(VOID){
					return;
				}
				VOID					Clear(VOID);
			};

			//
			//		body:USB_HID_G29PS4
			//

		private:
			READ					readThis;
			WRITE					writeThis;
			driver::LPUSB_HID		lpusbDS4;
		public:
			/* VOID */				USB_HID_G29PS4(driver::LPUSB_HID lpusbds4):
				lpusbDS4(lpusbds4)
			{}
			INLINE CREAD&			creadDelegateThis(VOID)const{
				return readThis;
			}
			INLINE WRITE&			writeDelegateThis(VOID){
				return writeThis;
			}
			INLINE BOOL				eIsReadValid(VOID){
				if(readThis.bcReportID==0x05)return TRUE;
				return FALSE;
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
			BOOL					eDS4(VOID);
		};
	}
}
