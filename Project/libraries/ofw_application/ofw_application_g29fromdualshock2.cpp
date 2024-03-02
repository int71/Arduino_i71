/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	application/g29fromdualshock2					2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				"ofw_application_g29fromdualshock2.hpp"

//
//		using
//

using namespace ofw::application;

//
//		class:G29FROMDUALSHOCK2
//

//	public

VOID					G29FROMDUALSHOCK2::stNew(VOID){
	return;
}

VOID					G29FROMDUALSHOCK2::stDelete(VOID){
	return;
}

VOID					G29FROMDUALSHOCK2::stWrite(
	stub::USB_HID_G29PS4::LPWRITE	lpwritedestination,
	driver::PS::LPCREAD		lpcreadsource
){
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

	lpwritedestination->n4cPad=((LPGBYTE)argbcpad)[
		((lpcreadsource->DUALSHOCK2.biButtonUp!=0)?		1:0)|
		((lpcreadsource->DUALSHOCK2.biButtonRight!=0)?	2:0)|
		((lpcreadsource->DUALSHOCK2.biButtonDown!=0)?	4:0)|
		((lpcreadsource->DUALSHOCK2.biButtonLeft!=0)?	8:0)
	];
	lpwritedestination->eButtonSquare=		(lpcreadsource->DUALSHOCK2.biButtonSquare!=0);
	lpwritedestination->eButtonCross=		(lpcreadsource->DUALSHOCK2.biButtonCross!=0);
	lpwritedestination->eButtonCircle=		(lpcreadsource->DUALSHOCK2.biButtonCircle!=0);
	lpwritedestination->eButtonTriangle=	(lpcreadsource->DUALSHOCK2.biButtonTriangle!=0);
	lpwritedestination->eButtonL1=			(lpcreadsource->DUALSHOCK2.biButtonL1!=0);
	lpwritedestination->eButtonR1=			(lpcreadsource->DUALSHOCK2.biButtonR1!=0);
	lpwritedestination->eButtonL2=			(lpcreadsource->DUALSHOCK2.biButtonL2!=0);
	lpwritedestination->eButtonR2=			(lpcreadsource->DUALSHOCK2.biButtonR2!=0);
	lpwritedestination->eButtonShare=		!lpcreadsource->DUALSHOCK2.eButtonSelect;
	lpwritedestination->eButtonPS=			!lpcreadsource->DUALSHOCK2.eButtonStart;
	return;
}
