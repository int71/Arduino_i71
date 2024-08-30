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
	auto					eup=lpcreadsource->DIGITAL.eButtonUp;
	auto					eright=lpcreadsource->DIGITAL.eButtonRight;
	auto					edown=lpcreadsource->DIGITAL.eButtonDown;
	auto					eleft=lpcreadsource->DIGITAL.eButtonLeft;

	if((!eup)&&(!edown)){
		eup=TRUE;
		edown=TRUE;
	}
	if((!eright)&&(!eleft)){
		eright=TRUE;
		eleft=TRUE;
	}
	lpwritedestination->eButtonSelect=		!lpcreadsource->DIGITAL.eButtonSelect;
	lpwritedestination->eButtonStart=		!lpcreadsource->DIGITAL.eButtonStart;
	lpwritedestination->eButtonUp=			!eup;
	lpwritedestination->eButtonRight=		!eright;
	lpwritedestination->eButtonDown=		!edown;
	lpwritedestination->eButtonLeft=		!eleft;
	lpwritedestination->eButtonL2=			!lpcreadsource->DIGITAL.eButtonL2;
	lpwritedestination->eButtonR2=			!lpcreadsource->DIGITAL.eButtonR2;
	lpwritedestination->eButtonL1=			!lpcreadsource->DIGITAL.eButtonL1;
	lpwritedestination->eButtonR1=			!lpcreadsource->DIGITAL.eButtonR1;
	lpwritedestination->eButtonTriangle=	!lpcreadsource->DIGITAL.eButtonTriangle;
	lpwritedestination->eButtonCircle=		!lpcreadsource->DIGITAL.eButtonCircle;
	lpwritedestination->eButtonCross=		!lpcreadsource->DIGITAL.eButtonCross;
	lpwritedestination->eButtonSquare=		!lpcreadsource->DIGITAL.eButtonSquare;
	lpwritedestination->biButtonUp=			eup?0x00:0xff;
	lpwritedestination->biButtonRight=		eright?0x00:0xff;
	lpwritedestination->biButtonDown=		edown?0x00:0xff;
	lpwritedestination->biButtonLeft=		eleft?0x00:0xff;
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
