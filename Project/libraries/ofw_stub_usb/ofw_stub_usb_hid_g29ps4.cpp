/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb_hid_g29ps4								2024 written by int71	**
 ****************************************************************************/

//	_DEBUG_PIN
//		デバッグ用PIN出力
//		・「stub::USB_HID_G29PS4」FEATURE読み書き期間:PD0
//		・「stub::USB_HID_G29PS4::EP_Main_stWrite」実行期間:PD1
//	_DEBUG_SERIAL
//		シリアル初期化、文字出力ON
//	_DEBUG_NOG29
//		タイミング把握用USBホストシールド無し動作

//#define _DEBUG_PIN
//#define _DEBUG_SERIAL
//#define _DEBUG_NOG29

//
//		include
//

#include				<ofw_stub_usb_hid_g29ps4.hpp>
#ifdef _DEBUG_SERIAL
#include				<ofw_driver_serial0.hpp>
#endif

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

//	public

BOOL					USB_HID_G29PS4::eIsReadable(VOID){
	if(EP_Main_stbnGetReadable(IDEndPoint_Read0)){
		if(EP_Main_stsznRead(IDEndPoint_Read0,&readThis,sizeof(readThis))<sizeof(readThis))return FALSE;
		return TRUE;
	}
	return FALSE;
}

//	private

VOID					USB_HID_G29PS4::Main_Self(VOID){
	{
		ATOMIC					atomic;

		writeFeature=writeThis;
	}
	while(TRUE){
		ATOMIC					atomic;
		const auto				cbnwritable=EP_Main_stbnGetWritable(IDEndPoint_Write0);

		if(sizeof(writeThis)<=cbnwritable){
#ifdef _DEBUG_PIN
			PORTD|=0x02;
#endif
			EP_Main_stWrite(IDEndPoint_Write0,&writeThis,sizeof(writeThis));
			writeThis.Clear();
#ifdef _DEBUG_PIN
			PORTD&=~0x02;
#endif
			break;
		}
	}
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
#ifdef _DEBUG_PIN
	DDRD|=0x93;
#endif
#ifdef _DEBUG_SERIAL
	driver::SERIAL0::stNew(115200);
	driver::SERIAL0::stPrintClear();
	driver::SERIAL0::stPrint(ARGSTR("START\r\n"));
#endif
	return;
}

VOID					USB_HID_G29PS4::Delete_Self2(VOID){
#ifdef _DEBUG_SERIAL
	driver::SERIAL0::stDelete();
#endif
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
#ifdef _DEBUG_SERIAL
	driver::SERIAL0::stPrint(ARGSTR("WRITE("));
	driver::SERIAL0::stPrintHEX(lpreqsource->bValueLSB);
	driver::SERIAL0::stPrint(ARGSTR("):"));
	for(SIZE szisource=0;szisource<sznsource;++szisource){
		driver::SERIAL0::stPrintHEX(lpcbsource[szisource]);
		if(szisource+1<sznsource)driver::SERIAL0::stPrint(ARGSTR(" "));
	}
	driver::SERIAL0::stPrint(ARGSTR("\r\n"));
#endif
#ifndef _DEBUG_NOG29
#ifdef _DEBUG_PIN
	PORTD|=0x01;
#endif
	if(ePSKey())lpdusbPSKey->WriteControlReport(lpreqsource->bValueLSB,lpcbsource,sznsource);
#ifdef _DEBUG_PIN
	PORTD&=~0x01;
#endif
#endif
	return;
}

SIZE					USB_HID_G29PS4::VECTOR_Request_Class_Interface_sznWrite(
	LPREQUEST				lpreqsource,
	LPBYTE					lpbdestination
){
#ifdef _DEBUG_PIN
	PORTD|=0x01;
#endif
	if(ePSKey())lpdusbPSKey->ReadControlReport(lpreqsource->bValueLSB,lpbdestination,lpreqsource->wnLength);
	else lpbdestination[0]=0x00;
	if(lpbdestination[0]!=lpreqsource->bValueLSB)switch(lpreqsource->bValueLSB){
	case 0x03:
		OFW::stCopy(lpbdestination,ARGBYTE(
			0x03,0x21,0x27,0x03,0x11,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x0d,0x0d,0x00,0x00,0x00,0x00,0x0d,0x84,0x03,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		),0x30);
		break;
	case 0xf1:
		OFW::stCopy(lpbdestination,ARGBYTE(
			0xf1,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		),0x40);
		break;
	case 0xf2:
		OFW::stCopy(lpbdestination,ARGBYTE(
			0xf2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		),0x10);
		break;
	case 0xf3:
		OFW::stCopy(lpbdestination,ARGBYTE(
			0xf3,0x00,0x38,0x38,0x00,0x00,0x00,0x00
		),0x08);
		break;
	default:
		lpbdestination[0]=lpreqsource->bValueLSB;
		for(SIZE szidestination=1;szidestination<lpreqsource->wnLength;++szidestination)lpbdestination[szidestination]=0x00;
		break;
	}
#ifdef _DEBUG_PIN
	PORTD&=~0x01;
#endif
#ifdef _DEBUG_SERIAL
	driver::SERIAL0::stPrint(ARGSTR("READ("));
	driver::SERIAL0::stPrintHEX(lpreqsource->bValueLSB);
	driver::SERIAL0::stPrint(ARGSTR("):"));
	for(SIZE szidestination=0;szidestination<lpreqsource->wnLength;++szidestination){
		driver::SERIAL0::stPrintHEX(lpbdestination[szidestination]);
		if(szidestination+1<lpreqsource->wnLength)driver::SERIAL0::stPrint(ARGSTR(" "));
	}
	driver::SERIAL0::stPrint(ARGSTR("\r\n"));
#endif
	return lpreqsource->wnLength;
}

BOOL					USB_HID_G29PS4::ePSKey(VOID){
#ifndef _DEBUG_NOG29
	if(lpdusbPSKey->eIsConnected())if(
		((lpdusbPSKey->wGetVID()==0x046d)&&(lpdusbPSKey->wGetPID()==0xc260))		//	GT29
	)return TRUE;
#endif
	return FALSE;
}
