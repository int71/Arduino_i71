/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	application/ds3fromdigital						2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				"ofw_application_ds3fromdigital.hpp"

//
//		using
//

using namespace ofw::application;

//
//		class:DS3FROMDIGITAL
//

//	public

VOID					DS3FROMDIGITAL::stNew(VOID){
	return;
}

VOID					DS3FROMDIGITAL::stDelete(VOID){
	return;
}

VOID					DS3FROMDIGITAL::stWrite(
	stub::USB_HID_DS3::LPWRITE	lpwritedestination,
	driver::PS::LPCREAD		lpcreadsource
){
	lpwritedestination->eButtonSelect=		!lpcreadsource->DIGITAL.eButtonSelect;
	lpwritedestination->eButtonStart=		!lpcreadsource->DIGITAL.eButtonStart;
	lpwritedestination->eButtonUp=			!lpcreadsource->DIGITAL.eButtonUp;
	lpwritedestination->eButtonRight=		!lpcreadsource->DIGITAL.eButtonRight;
	lpwritedestination->eButtonDown=		!lpcreadsource->DIGITAL.eButtonDown;
	lpwritedestination->eButtonLeft=		!lpcreadsource->DIGITAL.eButtonLeft;
	lpwritedestination->eButtonL2=			!lpcreadsource->DIGITAL.eButtonL2;
	lpwritedestination->eButtonR2=			!lpcreadsource->DIGITAL.eButtonR2;
	lpwritedestination->eButtonL1=			!lpcreadsource->DIGITAL.eButtonL1;
	lpwritedestination->eButtonR1=			!lpcreadsource->DIGITAL.eButtonR1;
	lpwritedestination->eButtonTriangle=	!lpcreadsource->DIGITAL.eButtonTriangle;
	lpwritedestination->eButtonCircle=		!lpcreadsource->DIGITAL.eButtonCircle;
	lpwritedestination->eButtonCross=		!lpcreadsource->DIGITAL.eButtonCross;
	lpwritedestination->eButtonSquare=		!lpcreadsource->DIGITAL.eButtonSquare;
	lpwritedestination->biButtonUp=			lpcreadsource->DIGITAL.eButtonUp?0x00:0xff;
	lpwritedestination->biButtonRight=		lpcreadsource->DIGITAL.eButtonRight?0x00:0xff;
	lpwritedestination->biButtonDown=		lpcreadsource->DIGITAL.eButtonDown?0x00:0xff;
	lpwritedestination->biButtonLeft=		lpcreadsource->DIGITAL.eButtonLeft?0x00:0xff;
	lpwritedestination->biButtonL2=			lpcreadsource->DIGITAL.eButtonL2?0x00:0xff;
	lpwritedestination->biButtonR2=			lpcreadsource->DIGITAL.eButtonR2?0x00:0xff;
	lpwritedestination->biButtonL1=			lpcreadsource->DIGITAL.eButtonL1?0x00:0xff;
	lpwritedestination->biButtonR1=			lpcreadsource->DIGITAL.eButtonR1?0x00:0xff;
	lpwritedestination->biButtonTriangle=	lpcreadsource->DIGITAL.eButtonTriangle?0x00:0xff;
	lpwritedestination->biButtonCircle=		lpcreadsource->DIGITAL.eButtonCircle?0x00:0xff;
	lpwritedestination->biButtonCross=		lpcreadsource->DIGITAL.eButtonCross?0x00:0xff;
	lpwritedestination->biButtonSquare=		lpcreadsource->DIGITAL.eButtonSquare?0x00:0xff;
	return;
}
