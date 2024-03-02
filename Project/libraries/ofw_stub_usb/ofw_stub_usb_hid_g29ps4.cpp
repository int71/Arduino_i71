/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb_hid_g29ps4								2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				<ofw_stub_usb_hid_g29ps4.hpp>

//
//		using
//

using namespace ofw::stub;

//
//		class:USB_HID_G29PS4::WRITE
//

//	public

VOID					USB_HID_G29PS4::WRITE::Clear(VOID){
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
	return;
}

//
//		class:USB_HID_G29PS4
//

//	private

VOID					USB_HID_G29PS4::Main_Self(VOID){
	while((EP_Main_stbnGetReadable(IDEndPoint_Read0)==0)&&(EP_Main_stbnGetWritable(IDEndPoint_Write0)==0))lpusbDS4->Main();
/*
	if(eDS4()){
		if(writeThis.n4cPad==8)writeThis.n4cPad=lpusbDS4->creadDelegateThis().readVID054CPID09CC.n4cPad;
		writeThis.eButtonSquare		|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonSquare;
		writeThis.eButtonCross		|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonCross;
		writeThis.eButtonCircle		|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonCircle;
		writeThis.eButtonTriangle	|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonTriangle;
		writeThis.eButtonL1			|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonL1;
		writeThis.eButtonR1			|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonR1;
		writeThis.eButtonL2			|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonL2;
		writeThis.eButtonR2			|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonR2;
		writeThis.eButtonShare		|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonShare;
		writeThis.eButtonOption		|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonOption;
		writeThis.eButtonL3			|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonL3;
		writeThis.eButtonR3			|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonR3;
		writeThis.eButtonPS			|=lpusbDS4->creadDelegateThis().readVID054CPID09CC.eButtonPS;
	}
*/
	if(EP_Main_stsznRead(IDEndPoint_Read0,&readThis,sizeof(readThis))!=sizeof(readThis))readThis.bcReportID=0x00;
	EP_Main_stWrite(IDEndPoint_Write0,&writeThis,sizeof(writeThis));
	writeThis.Clear();
	return;
}

GBYTE					argbReportDescriptor[]={
	0x05,0x01,				//	Usage Page(Generic Desktop)
	0x09,0x04,				//	Usage(Joystick)
	0xa1,0x01,				//	Collection(Application)
	0x85,0x01,				//		Report ID(1)
	0x09,0x30,				//			Usage(X)					+	BYTE					biXX;
	0x09,0x31,				//			Usage(Y)					|	x 4
	0x09,0x32,				//			Usage(Z)					|
	0x09,0x35,				//			Usage(Rz)					|
	0x15,0x00,				//			Logical Minimum(0)			|
	0x26,0xff,0x00,			//			Logical Maximum(255)		|
	0x75,0x08,				//			Report Size(8)				|
	0x95,0x04,				//			Report Count(4)				|
	0x81,0x02,				//			Input(Variable)				+
	0x09,0x39,				//			Usage(Hat switch)			+	BYTE					b4cPad:4;
	0x15,0x00,				//			Logical Minimum(0)			|
	0x25,0x07,				//			Logical Maximum(7)			|
	0x35,0x00,				//			Physical Minimum(0)			|
	0x46,0x3b,0x01,			//			Physical Maximum(315)		|
	0x65,0x14,				//			Unit(Degrees)				|
	0x75,0x04,				//			Report Size(4)				|
	0x95,0x01,				//			Report Count(1)				|
	0x81,0x42,				//			Input(Variable)				+
	0x65,0x00,				//			Unit(Default)				+	BYTE					eButtonXX:1;
	0x05,0x09,				//			Usage Page(Button)			|	x 14
	0x19,0x01,				//			Usage Minimum(1)			|
	0x29,0x0e,				//			Usage Maximum(14)			|
	0x15,0x00,				//			Logical Minimum(0)			|
	0x25,0x01,				//			Logical Maximum(1)			|
	0x75,0x01,				//			Report Size(1)				|
	0x95,0x0e,				//			Report Count(14)			|
	0x81,0x02,				//			Input(Variable)				+
	0x06,0x00,0xff,			//			Usage Page(Vendor-defined)	+	BYTE					eXX:6;
	0x09,0x20,				//			Usage(Hook Switch)			|
	0x75,0x06,				//			Report Size(6)				|
	0x95,0x01,				//			Report Count(1)				|
	0x81,0x02,				//			Input(Variable)				+
	0x05,0x01,				//			Usage Page(Generic Desktop)	+	BYTE					biXX;
	0x09,0x33,				//			Usage(Rx)					|	x 2
	0x09,0x34,				//			Usage(Ry)					|
	0x15,0x00,				//			Logical Minimum(0)			|
	0x26,0xff,0x00,			//			Logical Maximum(255)		|
	0x75,0x08,				//			Report Size(8)				|
	0x95,0x02,				//			Report Count(2)				|
	0x81,0x02,				//			Input(Variable)				+
	0x06,0x00,0xff,			//			Usage Page(Vendor-defined)	+	BYTE					biXX;
	0x09,0x21,				//			Usage(0x21)					|	x 54
	0x95,0x36,				//			Report Count(54)			|
	0x81,0x02,				//			Input(Variable)				+
	0x85,0x05,				//		Report ID(5)
	0x09,0x22,				//			Usage(0x22)
	0x95,0x1f,				//			Report Count(31)
	0x91,0x02,				//			Output(Variable)			- Feedback
	0x85,0x03,				//		Report ID(3)
	0x0a,0x21,0x27,			//			Usage(0x2721)
	0x95,0x2f,				//			Report Count(47)
	0xb1,0x02,				//			Feature(Data,Var,Abs)
	0xc0,					//	End Collection
	0x06,0xf0,0xff,			//	Usage Page(0xfff0)
	0x09,0x40,				//	Usage(0x40)
	0xa1,0x01,				//	Collection(Application)
	0x85,0xf0,				//		Report ID(240)
	0x09,0x47,				//			Usage(0x47)
	0x95,0x3f,				//			Report Count(63)
	0xb1,0x02,				//			Feature(Data,Var,Abs)
	0x85,0xf1,				//		Report ID(241)
	0x09,0x48,				//			Usage(0x48)
	0x95,0x3f,				//			Report Count(63)
	0xb1,0x02,				//			Feature(Data,Var,Abs)
	0x85,0xf2,				//		Report ID(242)
	0x09,0x49,				//			Usage(0x49)
	0x95,0x0f,				//			Report Count(15)
	0xb1,0x02,				//			Feature(Data,Var,Abs)
	0x85,0xf3,				//		Report ID(243)
	0x0a,0x01,0x47,			//			Usage(0x4701)
	0x95,0x07,				//			Report Count(7)
	0xb1,0x02,				//			Feature(Data,Var,Abs)
	0xc0					//	End Collection
};

BYTE					USB_HID_G29PS4::EP_Initialize_bcConfigType(
	BYTE					biep
){
	switch(biep){
	case IDEndPoint_Read0:
		return EP_stcbcConfigTypeInterruptRead;
	case IDEndPoint_Write0:
		return EP_stcbcConfigTypeInterruptWrite;
	}
	return 0;
}

VOID					USB_HID_G29PS4::VECTOR_Request_Standard_Descriptor_Device(VOID){
	CTRL_stWrite(ARGDEVICEDESC({
		sizeof(DEVICEDESC),		//	bnLength
		IDDescriptorType_Device,	//	bcDescriptorType
		OFW_stwEndianL(0x0100),	//	wcUSB
		0x00,					//	bcDeviceClass
		0x00,					//	bcDeviceSubClass
		0x00,					//	bcDeviceProtocol
		0x40,					//	bnMaxPacketSize
		OFW_stwEndianL(0x046d),	//	wcVendor
		OFW_stwEndianL(0xc260),	//	wcProduct
		OFW_stwEndianL(0x8900),	//	wcDevice
		IDStringDesc_Manufacturer,	//	biManufacturer
		IDStringDesc_Product,	//	biProduct
		IDStringDesc_Serial,	//	biSerialNumber
		0x01					//	bnConfiguration
	}),sizeof(DEVICEDESC));
	return;
}

VOID					USB_HID_G29PS4::VECTOR_Request_Standard_Descriptor_Configuration(VOID){
	CTRL_stWrite(ARGUSERDESC({
		{
			sizeof(CONFIGDESC),		//	bnLength
			IDDescriptorType_Configuration,	//	bcDescriptorType
			OFW_stwEndianL(sizeof(USERDESC)),	//	wnTotalLength
			0x01,					//	bnInterface
			0x01,					//	bnConfiguration
			0x00,					//	biConfiguration
			stcbcAttributeBusPowered,	//	bcAttibute
			200>>1					//	bcMaxPower
		},						//	cfgdescThis
		{
			sizeof(INTERFACEDESC),	//	bnLength
			IDDescriptorType_Interface,	//	bcDescriptorType
			0x00,					//	bnInterface
			0x00,					//	bcAlternateSetting
			stcbnEndPoint,			//	bnEndpoint
			IDDeviceClass_HID,		//	bcInterfaceClass
			IDDeviceClassHID_None,	//	bcInterfaceSubClass
			IDProtocolHID_None,		//	bcInterfaceProtocol
			0x00					//	biInterface
		},						//	ifdescThis
		{
			sizeof(HIDDESC),		//	bnLength
			IDDescriptorType_HID,	//	bcDescriptorType
			OFW_stwEndianL(0x0110),	//	wcHID
			0x00,					//	bcCountryCode
			0x01,					//	bnDescriptor
			IDDescriptorTypeHID_Report,	//	bcDescriptorTypeHID
			OFW_stwEndianL(sizeof(argbReportDescriptor))	//	wnDescriptorLength
		},						//	hiddescThis
		{
			sizeof(ENDPOINTDESC),	//	bnLength
			IDDescriptorType_EndPoint,	//	bcDescriptorType
			IDEndPoint_Read0|EP_stcbcDirectionRead,	//	bcEndpointAddress
			EP_stcbcDescriptorTypeInterrupt,	//	bcAttribute
			OFW_stwEndianL(EP_stcsznBuffer),	//	wnMaxPacketSize
			5						//	bnInterval
		},						//	epdescRead0
		{
			sizeof(ENDPOINTDESC),	//	bnLength
			IDDescriptorType_EndPoint,	//	bcDescriptorType
			IDEndPoint_Write0|EP_stcbcDirectionWrite,	//	bcEndpointAddress
			EP_stcbcDescriptorTypeInterrupt,	//	bcAttribute
			OFW_stwEndianL(EP_stcsznBuffer),	//	wnMaxPacketSize
			5						//	bnInterval
		}						//	epdescWrite0
	}),sizeof(USERDESC));
	return;
}

VOID					USB_HID_G29PS4::VECTOR_Request_Standard_Descriptor_String(
	BYTE					bithis
){
	switch(bithis){
	case IDStringDesc_Language:
		CTRL_stWriteStringLanguageDesc(0x0409);
		break;
	case IDStringDesc_Product:
		CTRL_stWriteStringDesc(ARGSTR("G29 Driving Force Racing Wheel"));
		break;
	}
	return;
}

VOID					USB_HID_G29PS4::New_Self2(VOID){
	readThis.New();
	writeThis.New();
	return;
}

VOID					USB_HID_G29PS4::Delete_Self2(VOID){
	writeThis.Delete();
	readThis.Delete();
	return;
}

VOID					USB_HID_G29PS4::VECTOR_Request_Standard_Descriptor_Report(VOID){
	CTRL_stWrite((LPGBYTE)argbReportDescriptor,sizeof(argbReportDescriptor));
	return;
}

VOID					USB_HID_G29PS4::VECTOR_Request_Class_Interface_Read(
	LPREQUEST				lpreqsource,
	LPCBYTE					lpcbsource,
	SIZE					sznsource
){
/*
	if(eDS4())switch(lpreqsource->bValueLSB){
	case 0xf0:
		lpusbDS4->WriteControlReport(0xf0,lpcbsource,sznsource);
		break;
	}
*/
	if(eDS4())lpusbDS4->WriteControlReport(lpreqsource->bValueLSB,lpcbsource,sznsource);
	return;
}

SIZE					USB_HID_G29PS4::VECTOR_Request_Class_Interface_sznWrite(
	LPREQUEST				lpreqsource,
	LPBYTE					lpbdestination
){
/*
	if(eDS4())switch(lpreqsource->bValueLSB){
	case 0x03:
		OFW::stCopy(lpbdestination,ARGBYTE(
			0x03,0x21,0x27,0x03,0x11,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x0d,0x0d,0x00,0x00,0x00,0x00,0x0d,0x84,0x03,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		),0x30);
		break;
	case 0xf1:
		lpusbDS4->ReadControlReport(0xf1,lpbdestination,lpreqsource->wnLength);
		break;
	case 0xf2:
		lpusbDS4->ReadControlReport(0xf2,lpbdestination,lpreqsource->wnLength);
		break;
	case 0xf3:
		OFW::stCopy(lpbdestination,ARGBYTE(
			0xf3,0x00,0x38,0x38,0x00,0x00,0x00,0x00
		),0x08);
		break;
	}
*/
	if(eDS4())lpusbDS4->ReadControlReport(lpreqsource->bValueLSB,lpbdestination,lpreqsource->wnLength);
	return lpreqsource->wnLength;
}

BOOL					USB_HID_G29PS4::eDS4(VOID){
	if(lpusbDS4->eIsConnected())if(
		((lpusbDS4->wGetVID()==0x054c)&&(lpusbDS4->wGetPID()==0x09cc))||	//	DS4
		((lpusbDS4->wGetVID()==0x046d)&&(lpusbDS4->wGetPID()==0xc260))		//	GT29
	)return TRUE;
	return FALSE;
}
