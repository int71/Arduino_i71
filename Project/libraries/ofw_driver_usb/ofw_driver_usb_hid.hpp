/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	driver/usb_hid									2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw.hpp>
#include				<ofw_driver_usb_hiduniversal.hpp>

//
//		namespace:ofw
//

namespace ofw{

	//
	//		namespace:driver
	//

	namespace driver{

		//
		//		class
		//

		class USB_HID;
		typedef const USB_HID	CUSB_HID;
		typedef USB_HID*		LPUSB_HID;
		typedef CUSB_HID*		LPCUSB_HID;

		//
		//		class:USB_HID
		//

		class USB_HID:public HIDUniversal{
		public:

			//
			//		class
			//

			//	READ_DS4
			class READ_DS4;
			typedef const READ_DS4	CREAD_DS4;
			typedef READ_DS4*		LPREAD_DS4;
			typedef CREAD_DS4*		LPCREAD_DS4;
			//	READ_G29
			class READ_G29;
			typedef const READ_G29	CREAD_G29;
			typedef READ_G29*		LPREAD_G29;
			typedef CREAD_G29*		LPCREAD_G29;
			//	READ
			class READ;
			typedef const READ		CREAD;
			typedef READ*			LPREAD;
			typedef CREAD*			LPCREAD;

			//
			//		class:READ_DS4
			//

			class READ_DS4{
			public:
				BYTE					bcReportID;			//	00		01
				BYTE					biAxisLX;			//	01
				BYTE					biAxisLY;			//	02
				BYTE					biAxisRX;			//	03
				BYTE					biAxisRY;			//	04
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
				BYTE					eTrackClick:1;
				BYTE					n6iCounter:6;
				BYTE					biButtonL2;			//	08
				BYTE					biButtonR2;			//	09
				BYTE					arbUnknown0[2];		//	0a~0b
				BYTE					biBattery;			//	0c
				BYTE					bUnknown1;			//	0d
				WORDS					wsiAccelZ;			//	0e~0f
				WORDS					wsiAccelY;			//	10~11
				WORDS					wsiAccelX;			//	12~13
				WORDS					wsiGyroX;			//	14~15
				WORDS					wsiGyroY;			//	16~17
				WORDS					wsiGyroZ;			//	18~19
				BYTE					arbUnknown2[4];		//	1a~1d
				BYTE					bcExternal;			//	1e
				BYTE					arbUnknown3[3];		//	1f~21
				BYTE					biTrackCounter;		//	22
				DWORD					biTrack0Number:7;	//	23~26
				DWORD					eTrack0Released:1;
				DWORD					n12Track0X:12;
				DWORD					n12Track0Y:12;
				DWORD					biTrack1Number:7;	//	27~2a
				DWORD					eTrack1Released:1;
				DWORD					n12Track1X:12;
				DWORD					n12Track1Y:12;
				BYTE					biTrackPreviousCounter;		//	2b
				DWORD					biTrackPrevious0Number:7;	//	2c~2f
				DWORD					eTrackPrevious0Released:1;
				DWORD					n12TrackPrevious0X:12;
				DWORD					n12TrackPrevious0Y:12;
				DWORD					biTrackPrevious1Number:7;	//	30~33
				DWORD					eTrackPrevious1Released:1;
				DWORD					n12TrackPrevious1X:12;
				DWORD					n12TrackPrevious1Y:12;
				BYTE					arbUnknown4[12];	//	34~3f
			public:
				VOID					Initialize(VOID);
				VOID					Clear(VOID);
			};

			//
			//		class:READ_G29
			//

			class READ_G29{
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
				VOID					Initialize(VOID);
				VOID					Clear(VOID);
			};

			//
			//		class:READ
			//

			class READ{
			public:
				union{
					BYTE					arbcThis[64];
					READ_DS4				readVID054CPID09CC;
					READ_G29				readVID046DPIDC260;
				};
			};

			//
			//		body:USB_HID
			//

		private:
			USB						usbThis;
			READ					readThis;
		public:
			/* VOID */				USB_HID(VOID):HIDUniversal(&usbThis){
				return;
			}
			INLINE BOOL				eNew(VOID);
			INLINE VOID				Delete(VOID);
			INLINE VOID				Main(VOID);
			INLINE BOOL				eIsConnected(VOID);
			INLINE WORD				wGetVID(VOID){
				return HIDUniversal::VID;
			}
			INLINE WORD				wGetPID(VOID){
				return HIDUniversal::PID;
			}
			INLINE CREAD&			creadDelegateThis(VOID){
				return readThis;
			}
			INLINE VOID				ReadControlReport(BYTE bcreportid,LPVOID lpreport,BYTE bnsize);
			INLINE VOID				WriteControlReport(BYTE bcreportid,LPCVOID lpcreport,BYTE bnsize);
			INLINE VOID				GPIO_Write(BYTE bsource);
			INLINE BYTE				GPIO_bRead(VOID);
		private:
			VOID					ParseHIDData(USBHID *hid,BOOL is_rpt_id,uint8_t len,uint8_t *buf);
			uint8_t					OnInitSuccessful(VOID);
			VOID					sendOutputReport(LPBYTE lpbreport,BYTE bnsize);
			BOOL					VIDPIDOK(uint16_t vid,uint16_t pid);
		};
	}
}
