/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	driver/usb_hid									2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				"ofw_driver_usb_hid.hpp"

//
//		using
//

using namespace ofw::driver;

//
//		class:USB_HID::READ_DS4
//

//	public

VOID					USB_HID::READ_DS4::Initialize(VOID){
	bcReportID=0x01;
	return;
}

VOID					USB_HID::READ_DS4::Clear(VOID){
	biAxisLX=0x80;
	biAxisLY=0x80;
	biAxisRX=0x80;
	biAxisRY=0x80;
	n4cPad=8;
	eButtonSquare=FALSE;
	eButtonCross=FALSE;
	eButtonCircle=FALSE;
	eButtonTriangle=FALSE;
	eButtonL1=FALSE;
	eButtonR1=FALSE;
	eButtonL2=FALSE;
	eButtonR2=FALSE;
	eButtonShare=FALSE;
	eButtonOption=FALSE;
	eButtonL3=FALSE;
	eButtonR3=FALSE;
	eButtonPS=FALSE;
	eTrackClick=FALSE;
	n6iCounter=0;
	biButtonL2=0;
	biButtonR2=0;
	biBattery=0;
	wsiAccelZ=0;
	wsiAccelY=0;
	wsiAccelX=0;
	wsiGyroX=0;
	wsiGyroY=0;
	wsiGyroZ=0;
	bcExternal=0x05;
	biTrackCounter=0;
	biTrack0Number=0;
	eTrack0Released=TRUE;
	n12Track0X=0;
	n12Track0Y=0;
	biTrack1Number=0;
	eTrack1Released=TRUE;
	n12Track1X=0;
	n12Track1Y=0;
	biTrackPreviousCounter=0;
	biTrackPrevious0Number=0;
	eTrackPrevious0Released=TRUE;
	n12TrackPrevious0X=0;
	n12TrackPrevious0Y=0;
	biTrackPrevious1Number=0;
	eTrackPrevious1Released=TRUE;
	n12TrackPrevious1X=0;
	n12TrackPrevious1Y=0;
	return;
}

//
//		class:USB_HID::READ_G29
//

//	public

VOID					USB_HID::READ_G29::Initialize(VOID){
	OFW::stFill(this,sizeof(*this),0x00);
	bcReportID=0x01;
	arbFixed0[0]=0x80;
	arbFixed0[1]=0x80;
	arbFixed0[2]=0x80;
	arbFixed0[3]=0x80;
	arbFixed3[0]=0xff;
	arbFixed3[1]=0xff;
	return;
}

VOID					USB_HID::READ_G29::Clear(VOID){
	n4cPad=8;
	eButtonSquare=FALSE;
	eButtonCross=FALSE;
	eButtonCircle=FALSE;
	eButtonTriangle=FALSE;
	eButtonL1=FALSE;
	eButtonR1=FALSE;
	eButtonL2=FALSE;
	eButtonR2=FALSE;
	eButtonShare=FALSE;
	eButtonOption=FALSE;
	eButtonL3=FALSE;
	eButtonR3=FALSE;
	eButtonPS=FALSE;
	wiSteering=0x8000;
	wiPedalAccel=0xffff;
	wiPedalBrake=0xffff;
	wiPedalClutch=0xffff;
	eShift1=FALSE;
	eShift2=FALSE;
	eShift3=FALSE;
	eShift4=FALSE;
	eShift5=FALSE;
	eShift6=FALSE;
	eShiftR=FALSE;
	eDialEnter=FALSE;
	eDialL=FALSE;
	eDialR=FALSE;
	eAdjusterMinus=FALSE;
	eAdjusterPlus=FALSE;
	return;
}

//
//		class:USB_HID
//

//	public

VOID					USB_HID::New(VOID){
	if(usbThis.Init()==-1)while(TRUE);
	return;
}

VOID					USB_HID::Delete(VOID){
	return;
}

VOID					USB_HID::Main(VOID){
	ATOMIC					atomic;

	usbThis.Task();
	return;
}

BOOL					USB_HID::eIsConnected(VOID){
	ATOMIC					atomic;

	return HIDUniversal::isReady();
}

VOID					USB_HID::ReadControlReport(
	BYTE					bcreportid,
	LPVOID					lpreport,
	BYTE					bnsize
){
	ATOMIC					atomic;

	GetReport(0,0x00,0x03,bcreportid,bnsize,(LPBYTE)lpreport);
	return;
}

VOID					USB_HID::WriteControlReport(
	BYTE					bcreportid,
	LPCVOID					lpcreport,
	BYTE					bnsize
){
	ATOMIC					atomic;

	SetReport(0,0x00,0x03,bcreportid,bnsize,(LPCBYTE)lpcreport);
	return;
}

VOID					USB_HID::GPIO_Write(
	BYTE					bsource
){
	ATOMIC					atomic;

	usbThis.regWr(rIOPINS1,bsource&0x0f);
	usbThis.regWr(rIOPINS2,(bsource>>4)&0x0f);
	return;
}

BYTE					USB_HID::GPIO_bRead(VOID){
	ATOMIC					atomic;

	return ((usbThis.regRd(rIOPINS1)&0xf0)>>4)|(usbThis.regRd(rIOPINS2)&0xf0);
}

//	private

VOID					USB_HID::ParseHIDData(
	USBHID*					hid,
	BOOL					is_rpt_id,
	uint8_t					len,
	uint8_t*				buf
){
	BYTE					i;

	for(i=0;i<len;i++)readThis.arbcThis[i]=buf[i];
	return;
}

uint8_t					USB_HID::OnInitSuccessful(VOID){
	return 0;
}

VOID					USB_HID::sendOutputReport(
	LPBYTE					lpbreport,
	BYTE					bnsize
){
	pUsb->outTransfer(bAddress,epInfo[hidInterfaces[0].epIndex[epInterruptOutIndex]].epAddr,bnsize,lpbreport);
	return;
}

BOOL					USB_HID::VIDPIDOK(
	uint16_t				vid,
	uint16_t				pid
){
	return TRUE;
}
