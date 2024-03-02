/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	application/g29fromnegconplus					2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				"ofw_application_g29fromnegconplus.hpp"

//
//		using
//

using namespace ofw::application;

//
//		class:G29FROMNEGCONPLUS
//

//	static

G29FROMNEGCONPLUS::ST	G29FROMNEGCONPLUS::st;

//	public

VOID					G29FROMNEGCONPLUS::stNew(VOID){
	st.wnTimingCounterOneSecond=1000/5;
	st.wiTimingCounter=st.wnTimingCounterOneSecond-1;
	st.wiTimingCounterNext=st.wnTimingCounterOneSecond;
	st.wiTimingCounterFrame=stcwnFPS;
	st.btnThis.wcData=0x0000;
	st.wiCounter=0;
	st.biOptionButton=0;
	st.idMode=IDMode_Command;
	st.eModeChanging=FALSE;
	st.eModeChanged=FALSE;
	st.idShift=IDShift_N;
	return;
}

VOID					G29FROMNEGCONPLUS::stDelete(VOID){
	return;
}

VOID					G29FROMNEGCONPLUS::stWrite(
	stub::USB_HID_G29PS4::LPWRITE	lpwritedestination,
	driver::PS::LPCREAD		lpcreadsource,
	CDWORD					cdwnsteeringmultiply
){
	BUTTON					btnchanged;
	WORD					wicounter;
	BYTE					bcpad;

	{
		BUTTON					btncurrent;

		//	Button status
		btncurrent.wcData=0x0000;
		btncurrent.eButtonStart=!lpcreadsource->NEGCONPLUS.eButtonStart;
		btncurrent.eButtonUp=!lpcreadsource->NEGCONPLUS.eButtonUp;
		btncurrent.eButtonRight=!lpcreadsource->NEGCONPLUS.eButtonRight;
		btncurrent.eButtonDown=!lpcreadsource->NEGCONPLUS.eButtonDown;
		btncurrent.eButtonLeft=!lpcreadsource->NEGCONPLUS.eButtonLeft;
		btncurrent.eButtonR=!lpcreadsource->NEGCONPLUS.eButtonR;
		btncurrent.eButtonB=!lpcreadsource->NEGCONPLUS.eButtonB;
		btncurrent.eButtonA=!lpcreadsource->NEGCONPLUS.eButtonA;
		if(0xa000<lpcreadsource->NEGCONPLUS.wiAxisSteering)btncurrent.eAxisSteeringR=TRUE;
		else if(lpcreadsource->NEGCONPLUS.wiAxisSteering<0x6000)btncurrent.eAxisSteeringL=TRUE;
		if(0x1000<lpcreadsource->NEGCONPLUS.wiButtonI)btncurrent.eButtonI=TRUE;
		if(0x1000<lpcreadsource->NEGCONPLUS.wiButtonII)btncurrent.eButtonII=TRUE;
		if(0x1000<lpcreadsource->NEGCONPLUS.wiButtonL)btncurrent.eButtonL=TRUE;
		btnchanged.wcData=btncurrent.wcData^st.btnThis.wcData;
		wicounter=st.wiCounter;
		//	Keep pushing
		if(btncurrent.wcData==st.btnThis.wcData){
			if(st.wiCounter<0xffff)st.wiCounter++;
		}else{
			st.btnThis.wcData=btncurrent.wcData;
			st.wiCounter=0;
		}
	}
	{
		GBYTE					argbcpad[]={
				//	7    0    1
				//	  UL U UR
				//	6 L  8  R 2
				//	  DL D DR
				//	5    4    3
				//	LDRU
			8,	//	0000:
			0,	//	0001:U
			2,	//	0010:R
			1,	//	0011:UR
			4,	//	0100:D
			8,	//	0101:
			3,	//	0110:DR
			2,	//	0111:R
			6,	//	1000:L
			7,	//	1001:UL
			8,	//	1010:
			0,	//	1011:U
			5,	//	1100:DL
			6,	//	1101:L
			4,	//	1110:D
			8	//	1111:
		};

		//	Pad
		bcpad=((LPGBYTE)argbcpad)[
			(st.btnThis.eButtonUp?		1:0)|
			(st.btnThis.eButtonRight?	2:0)|
			(st.btnThis.eButtonDown?	4:0)|
			(st.btnThis.eButtonLeft?	8:0)
		];
		if(st.eModeChanged){
			if(bcpad==8)st.eModeChanged=FALSE;
			else bcpad=8;
		}
	}
	//	Control
	if(st.btnThis.eButtonStart){
		if(
			(!st.btnThis.eButtonUp)&&
			(!st.btnThis.eButtonRight)&&
			(!st.btnThis.eButtonDown)&&
			(!st.btnThis.eButtonLeft)&&
			(!st.btnThis.eButtonR)&&
			(!st.btnThis.eButtonB)&&
			(!st.btnThis.eButtonA)&&
			(!st.btnThis.eAxisSteeringR)&&
			(!st.btnThis.eAxisSteeringL)&&
			(!st.btnThis.eButtonI)&&
			(!st.btnThis.eButtonII)&&
			(!st.btnThis.eButtonL)&&
			(st.wnTimingCounterOneSecond<=st.wiCounter)&&
			(!st.eModeChanging)
		){
			//	PS ON
			lpwritedestination->eButtonPS=TRUE;
		}else{
			//	Mode change
			switch(bcpad){
			case 0://	U
				stWrite_ModeChange(lpwritedestination,IDMode_Command);
				break;
			case 2://	R
				stWrite_ModeChange(lpwritedestination,IDMode_DriveSequentialShifter);
				break;
			case 4://	D
				stWrite_ModeChange(lpwritedestination,IDMode_DriveHShifter);
				break;
			case 6://	L
				stWrite_ModeChange(lpwritedestination,IDMode_DrivePaddle);
				break;
			}
			bcpad=8;
		}
	}else{
		if((!st.eModeChanging)&&(btnchanged.eButtonStart)&&(wicounter<st.wnTimingCounterOneSecond)){
			st.biOptionButton=st.wnTimingCounterOneSecond>>3;
		}
		st.eModeChanging=FALSE;
	}
	//	Option button
	if(st.biOptionButton){
		st.biOptionButton--;
		lpwritedestination->eButtonOption=TRUE;
	}
	//	Mapping
	switch(st.idMode){
	case IDMode_Command:
		lpwritedestination->n4cPad=				bcpad;
		lpwritedestination->eButtonCircle=		st.btnThis.eButtonA;
		lpwritedestination->eButtonCross=		st.btnThis.eButtonI;
		lpwritedestination->eButtonTriangle=	st.btnThis.eButtonB;
		lpwritedestination->eButtonSquare=		st.btnThis.eButtonII;
		lpwritedestination->eButtonL1=			st.btnThis.eButtonL;
		lpwritedestination->eButtonR1=			st.btnThis.eButtonR;
		break;
	default:
		//	Drive mode
		{
			BOOL					esteeringsign;
			DWORD					dwisteering;

			//	Steering
			if(lpcreadsource->NEGCONPLUS.wiAxisSteering<0x8000){
				esteeringsign=TRUE;
				dwisteering=(DWORD)(0x8000-lpcreadsource->NEGCONPLUS.wiAxisSteering);
			}else{
				esteeringsign=FALSE;
				dwisteering=(DWORD)(lpcreadsource->NEGCONPLUS.wiAxisSteering-0x8000);
			}
			if(dwisteering<stcdwnSteeringMargin)dwisteering=0;
			else dwisteering-=stcdwnSteeringMargin;
			dwisteering*=cdwnsteeringmultiply;dwisteering>>=8;
			if(32767<dwisteering)dwisteering=32767;
			if(esteeringsign)lpwritedestination->wiSteering=0x8000-(WORD)dwisteering;
			else lpwritedestination->wiSteering=0x8000+(WORD)dwisteering;
		}
		{
			DWORD					dwiaccel;

			//	Accel
			dwiaccel=(DWORD)lpcreadsource->NEGCONPLUS.wiButtonI;
			if(dwiaccel<stcdwnAccelMargin)dwiaccel=0;
			else dwiaccel-=stcdwnAccelMargin;
			dwiaccel*=stcdwnAccelMultiply;dwiaccel>>=8;
			if(0xffff<dwiaccel)dwiaccel=0xffff;
			lpwritedestination->wiPedalAccel=0xffff-(WORD)dwiaccel;
		}
		{
			DWORD					dwibrake;

			//	Brake
			dwibrake=(DWORD)lpcreadsource->NEGCONPLUS.wiButtonII;
			if(dwibrake<stcdwnBrakeMargin)dwibrake=0;
			else dwibrake-=stcdwnBrakeMargin;
			dwibrake*=stcdwnBrakeMultiply;dwibrake>>=8;
			if(0xffff<dwibrake)dwibrake=0xffff;
			lpwritedestination->wiPedalBrake=0xffff-(WORD)dwibrake;
		}
		lpwritedestination->eButtonCircle=		st.btnThis.eButtonA;
		lpwritedestination->eButtonTriangle=	st.btnThis.eButtonB;
		if(st.idMode==IDMode_DrivePaddle){
			//	Without clutch
			lpwritedestination->n4cPad=				bcpad;
			lpwritedestination->eButtonR1=			st.btnThis.eButtonR;
			lpwritedestination->eButtonL1=			st.btnThis.eButtonL;
		}else{
			//	With clutch
			{
				DWORD					dwiclutch;

				//	Clutch
				dwiclutch=(DWORD)lpcreadsource->NEGCONPLUS.wiButtonL;
				if(dwiclutch<stcdwnClutchMargin)dwiclutch=0;
				else dwiclutch-=stcdwnClutchMargin;
				dwiclutch*=stcdwnClutchMultiply;dwiclutch>>=8;
				if(0xffff<dwiclutch)dwiclutch=0xffff;
				lpwritedestination->wiPedalClutch=0xffff-(WORD)dwiclutch;
			}
			if(st.btnThis.eButtonR){
				//	Button
				lpwritedestination->n4cPad=				bcpad;
				stWrite_Shift(lpwritedestination,st.idShift);
			}else{
				if(st.idMode==IDMode_DriveSequentialShifter){
					//	Paddle
					lpwritedestination->eButtonR1=			st.btnThis.eButtonDown;
					lpwritedestination->eButtonL1=			st.btnThis.eButtonUp;
				}else{
					//	Shift
					//	7    0    1
					//	  UL U UR
					//	6 L  8  R 2
					//	  DL D DR
					//	5    4    3
					switch(bcpad){
					case 0:
					case 1:
					case 7:
						if(btnchanged.eButtonUp&&(IDShift_Minimum<st.idShift))st.idShift=st.idShift-1;
						stWrite_Shift(lpwritedestination,IDShift_N);
						break;
					case 3:
					case 4:
					case 5:
						if(btnchanged.eButtonDown&&(st.idShift<IDShift_Maximum))st.idShift=st.idShift+1;
						stWrite_Shift(lpwritedestination,IDShift_N);
						break;
					case 2:
					case 6:
						st.idShift=IDShift_N;
					default:
						stWrite_Shift(lpwritedestination,st.idShift);
						break;
					}
				}
			}
		}
	}
	return;
}

VOID					G29FROMNEGCONPLUS::stWrite_Shift(
	stub::USB_HID_G29PS4::LPWRITE	lpwritedestination,
	IDSHIFT					idshift
){
	lpwritedestination->eShift1=FALSE;
	lpwritedestination->eShift2=FALSE;
	lpwritedestination->eShift3=FALSE;
	lpwritedestination->eShift4=FALSE;
	lpwritedestination->eShift5=FALSE;
	lpwritedestination->eShift6=FALSE;
	lpwritedestination->eShiftR=FALSE;
	switch(idshift){
	case IDShift_R:
		lpwritedestination->eShiftR=TRUE;
		break;
	case IDShift_N:
		break;
	case IDShift_1:
		lpwritedestination->eShift1=TRUE;
		break;
	case IDShift_2:
		lpwritedestination->eShift2=TRUE;
		break;
	case IDShift_3:
		lpwritedestination->eShift3=TRUE;
		break;
	case IDShift_4:
		lpwritedestination->eShift4=TRUE;
		break;
	case IDShift_5:
		lpwritedestination->eShift5=TRUE;
		break;
	case IDShift_6:
		lpwritedestination->eShift6=TRUE;
		break;
	}
	return;
}

VOID					G29FROMNEGCONPLUS::stWrite_ModeChange(
	stub::USB_HID_G29PS4::LPWRITE	lpwritedestination,
	IDMODE					idmode
){
	st.idMode=idmode;
	st.eModeChanging=TRUE;
	st.eModeChanged=TRUE;
	st.idShift=IDShift_N;
	stWrite_Shift(lpwritedestination,IDShift_N);
	return;
}
