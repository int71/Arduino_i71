/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	application/ds3fromdualshock2					2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				"ofw_application_ds3fromdualshock2.hpp"

//
//		using
//

using namespace ofw::application;

//
//		class:DS3FROMDUALSHOCK2
//

//	public

VOID					DS3FROMDUALSHOCK2::stNew(VOID){
	return;
}

VOID					DS3FROMDUALSHOCK2::stDelete(VOID){
	return;
}

VOID					DS3FROMDUALSHOCK2::stWrite(
	stub::USB_HID_DS3::LPWRITE	lpwritedestination,
	driver::PS::LPCREAD		lpcreadsource
){
	lpwritedestination->eButtonSelect=		!lpcreadsource->DUALSHOCK2.eButtonSelect;
	lpwritedestination->eButtonL3=			!lpcreadsource->DUALSHOCK2.eButtonL3;
	lpwritedestination->eButtonR3=			!lpcreadsource->DUALSHOCK2.eButtonR3;
	lpwritedestination->eButtonStart=		!lpcreadsource->DUALSHOCK2.eButtonStart;
	lpwritedestination->eButtonUp=			(lpcreadsource->DUALSHOCK2.biButtonUp!=0);
	lpwritedestination->eButtonRight=		(lpcreadsource->DUALSHOCK2.biButtonRight!=0);
	lpwritedestination->eButtonDown=		(lpcreadsource->DUALSHOCK2.biButtonDown!=0);
	lpwritedestination->eButtonLeft=		(lpcreadsource->DUALSHOCK2.biButtonLeft!=0);
	lpwritedestination->eButtonL2=			(lpcreadsource->DUALSHOCK2.biButtonL2!=0);
	lpwritedestination->eButtonR2=			(lpcreadsource->DUALSHOCK2.biButtonR2!=0);
	lpwritedestination->eButtonL1=			(lpcreadsource->DUALSHOCK2.biButtonL1!=0);
	lpwritedestination->eButtonR1=			(lpcreadsource->DUALSHOCK2.biButtonR1!=0);
	lpwritedestination->eButtonTriangle=	(lpcreadsource->DUALSHOCK2.biButtonTriangle!=0);
	lpwritedestination->eButtonCircle=		(lpcreadsource->DUALSHOCK2.biButtonCircle!=0);
	lpwritedestination->eButtonCross=		(lpcreadsource->DUALSHOCK2.biButtonCross!=0);
	lpwritedestination->eButtonSquare=		(lpcreadsource->DUALSHOCK2.biButtonSquare!=0);
	lpwritedestination->biAxisLX=			lpcreadsource->DUALSHOCK2.biAxisLX;
	lpwritedestination->biAxisLY=			lpcreadsource->DUALSHOCK2.biAxisLY;
	lpwritedestination->biAxisRX=			lpcreadsource->DUALSHOCK2.biAxisRX;
	lpwritedestination->biAxisRY=			lpcreadsource->DUALSHOCK2.biAxisRY;
	lpwritedestination->biButtonUp=			lpcreadsource->DUALSHOCK2.biButtonUp;
	lpwritedestination->biButtonRight=		lpcreadsource->DUALSHOCK2.biButtonRight;
	lpwritedestination->biButtonDown=		lpcreadsource->DUALSHOCK2.biButtonDown;
	lpwritedestination->biButtonLeft=		lpcreadsource->DUALSHOCK2.biButtonLeft;
	lpwritedestination->biButtonL2=			lpcreadsource->DUALSHOCK2.biButtonL2;
	lpwritedestination->biButtonR2=			lpcreadsource->DUALSHOCK2.biButtonR2;
	lpwritedestination->biButtonL1=			lpcreadsource->DUALSHOCK2.biButtonL1;
	lpwritedestination->biButtonR1=			lpcreadsource->DUALSHOCK2.biButtonR1;
	lpwritedestination->biButtonTriangle=	lpcreadsource->DUALSHOCK2.biButtonTriangle;
	lpwritedestination->biButtonCircle=		lpcreadsource->DUALSHOCK2.biButtonCircle;
	lpwritedestination->biButtonCross=		lpcreadsource->DUALSHOCK2.biButtonCross;
	lpwritedestination->biButtonSquare=		lpcreadsource->DUALSHOCK2.biButtonSquare;
	return;
}
