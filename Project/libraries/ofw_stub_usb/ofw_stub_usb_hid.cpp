/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb_hid									2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				<ofw_stub_usb_hid.hpp>

//
//		using
//

using namespace ofw::stub;

//	protected

VOID					USB_HID::New_Self2(VOID){
	return;
}

VOID					USB_HID::Delete_Self2(VOID){
	return;
}

VOID					USB_HID::VECTOR_Request_Class_Interface_Read(
	LPREQUEST				lpreqsource,
	LPCBYTE					lpcbsource,
	SIZE					sznsource
){
	return;
}

SIZE					USB_HID::VECTOR_Request_Class_Interface_sznWrite(
	LPREQUEST				lpreqsource,
	LPBYTE					lpbdestination
){
	return 0;
}

//	private

VOID					USB_HID::New_Self(VOID){
	New_Self2();
	return;
}

VOID					USB_HID::Delete_Self(VOID){
	Delete_Self2();
	return;
}

VOID					USB_HID::VECTOR_Request_Standard_Descriptor_Other(
	LPREQUEST				lpreqsource
){
	if(
		(lpreqsource->bcRequestType==stcbcRequestDevicetoHostStandardInterface)&&
		(lpreqsource->bValueMSB==IDDescriptorTypeHID_Report)
	)VECTOR_Request_Standard_Descriptor_Report();
	return;
}

VOID					USB_HID::VECTOR_Request_Class_Interface(
	LPREQUEST				lpreqsource
){
	BYTE					arbbuffer[64];
	SIZE					sznbuffer;

	switch(lpreqsource->bcRequestType&stcbcRequestDirection){
	case stcbcRequestDirectionHosttoDevice:
		switch(lpreqsource->bcRequest){
		case 0x09:	//	SETUP_HID_SET_REPORT
			switch(lpreqsource->bValueMSB){	//	ReportType
			case 0x01:	//	REPORT_TYPE_INPUT
				break;
			case 0x02:	//	REPORT_TYPE_OUTPUT
				break;
			case 0x03:	//	REPORT_TYPE_FEATURE
				sznbuffer=EP_stsznRead(0,arbbuffer,lpreqsource->wnLength);
				VECTOR_Request_Class_Interface_Read(lpreqsource,arbbuffer,sznbuffer);
				break;
			}
			break;
		case 0x0a:	//	SETUP_HID_SET_IDLE
			break;
		case 0x0b:	//	SETUP_HID_SET_PROTOCOL
			break;
		}
		break;
	case stcbcRequestDirectionDevicetoHost:
		switch(lpreqsource->bcRequest){
		case 0x01:	//	SETUP_HID_GET_REPORT
			switch(lpreqsource->bValueMSB){	//	ReportType
			case 0x01:	//	REPORT_TYPE_INPUT
				break;
			case 0x02:	//	REPORT_TYPE_OUTPUT
				break;
			case 0x03:	//	REPORT_TYPE_FEATURE
				sznbuffer=VECTOR_Request_Class_Interface_sznWrite(lpreqsource,arbbuffer);
				CTRL_stWriteOpen(sznbuffer);
				CTRL_stWrite(arbbuffer,sznbuffer);
				break;
			}
			break;
		case 0x02:	//	SETUP_HID_GET_IDLE
			break;
		case 0x03:	//	SETUP_HID_GET_PROTOCOL
			break;
		}
		break;
	}
	return;
}
