/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	application/g29fromnegcon						2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw_driver_ps.hpp>
#include				<ofw_stub_usb_hid_g29ps4.hpp>

//
//		namespace:ofw
//

namespace ofw{

	//
	//		namespace:application
	//

	namespace application{

		//
		//		class
		//

		class G29FROMNEGCON;
		typedef const G29FROMNEGCON	CG29FROMNEGCON;
		typedef G29FROMNEGCON*	LPG29FROMNEGCON;
		typedef CG29FROMNEGCON*	LPCG29FROMNEGCON;

		//
		//		class:G29FROMNEGCON
		//

		class G29FROMNEGCON{
		public:

			//
			//		const
			//

			static CWORD			stcwnFPS=60;
			static CDWORD			stcdwnSteeringMargin=2;
			static CDWORD			stcdwnAccelMargin=3;
			static CDWORD			stcdwnAccelMultiply=320;
			static CDWORD			stcdwnBrakeMargin=3;
			static CDWORD			stcdwnBrakeMultiply=320;
			static CDWORD			stcdwnClutchMargin=3;
			static CDWORD			stcdwnClutchMultiply=512;
			//	NEGCONMODE
			enum IDMODE{
				IDMode_Command,
				IDMode_DrivePaddle,
				IDMode_DriveSequentialShifter,
				IDMode_DriveHShifter
			};
			//	SHIFT
			enum IDSHIFT{
				IDShift_Minimum	=0x00,
				IDShift_R		=IDShift_Minimum,
				IDShift_N		=0x01,
				IDShift_1		=0x02,
				IDShift_2		=0x03,
				IDShift_3		=0x04,
				IDShift_4		=0x05,
				IDShift_5		=0x06,
				IDShift_6		=0x07,
				IDShift_Maximum	=IDShift_6
			};

			//
			//		class
			//

			//	BUTTON
			class BUTTON;
			typedef const BUTTON	CBUTTON;
			typedef BUTTON*			LPBUTTON;
			typedef CBUTTON*		LPCBUTTON;
			//	ST
			class ST;
			typedef const ST		CST;
			typedef ST*				LPST;
			typedef CST*			LPCST;

			//
			//		class:BUTTON
			//

			class BUTTON{
			public:
				union{
					struct{
						BYTE					eButtonStart:1;
						BYTE					eButtonUp:1;
						BYTE					eButtonRight:1;
						BYTE					eButtonDown:1;
						BYTE					eButtonLeft:1;
						BYTE					eButtonR:1;
						BYTE					eButtonB:1;
						BYTE					eButtonA:1;
						BYTE					eAxisSteeringR:1;
						BYTE					eAxisSteeringL:1;
						BYTE					eButtonI:1;
						BYTE					eButtonII:1;
						BYTE					eButtonL:1;
					};
					WORD					wcData;
				};
			};

			//
			//		class:ST
			//

			class ST{
			public:
				WORD					wnTimingCounterOneSecond;
				WORD					wiTimingCounter;
				WORD					wiTimingCounterNext;
				WORD					wiTimingCounterFrame;
				BUTTON					btnThis;
				WORD					wiCounter;
				WORD					biOptionButton;
				IDMODE					idMode;
				BOOL					eModeChanging:1;
				BOOL					eModeChanged:1;
				IDSHIFT					idShift;
			};

			//
			//		body:G29FROMNEGCON
			//

		private:
			static ST				st;
		public:
			static VOID				stNew(VOID);
			static VOID				stDelete(VOID);
			static VOID				stWrite(stub::USB_HID_G29PS4::LPWRITE lpwritedestination,driver::PS::LPCREAD lpcreadsource,CDWORD cdwnsteeringmultiply);
		private:
			static VOID				stWrite_Shift(stub::USB_HID_G29PS4::LPWRITE lpwritedestination,IDSHIFT idshift);
			static VOID				stWrite_ModeChange(stub::USB_HID_G29PS4::LPWRITE lpwritedestination,IDMODE idmode);
		};
	}
}
