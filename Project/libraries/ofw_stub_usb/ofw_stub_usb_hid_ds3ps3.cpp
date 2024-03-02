/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb_hid_ds3ps3								2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				<ofw_driver_serial0.hpp>
#include				<ofw_stub_usb_hid_ds3ps3.hpp>

//
//		using
//

using namespace ofw::stub;

//
//		class:USB_HID_DS3PS3::WRITE
//

//	public

VOID					USB_HID_DS3PS3::WRITE::Clear(VOID){
	eButtonSelect=			FALSE;
	eButtonL3=				FALSE;
	eButtonR3=				FALSE;
	eButtonStart=			FALSE;
	eButtonUp=				FALSE;
	eButtonRight=			FALSE;
	eButtonDown=			FALSE;
	eButtonLeft=			FALSE;
	eButtonL2=				FALSE;
	eButtonR2=				FALSE;
	eButtonL1=				FALSE;
	eButtonR1=				FALSE;
	eButtonTriangle=		FALSE;
	eButtonCircle=			FALSE;
	eButtonCross=			FALSE;
	eButtonSquare=			FALSE;
	eButtonPS=				FALSE;
	biAxisLX=				0x80;
	biAxisLY=				0x80;
	biAxisRX=				0x80;
	biAxisRY=				0x80;
	biButtonUp=				0x00;
	biButtonRight=			0x00;
	biButtonDown=			0x00;
	biButtonLeft=			0x00;
	biButtonL2=				0x00;
	biButtonR2=				0x00;
	biButtonL1=				0x00;
	biButtonR1=				0x00;
	biButtonTriangle=		0x00;
	biButtonCircle=			0x00;
	biButtonCross=			0x00;
	biButtonSquare=			0x00;
	niAccelX=				0x0000;
	niAccelY=				0x0000;
	niAccelZ=				0x0000;
	niGyro=					0x0000;
	return;
}

//
//		class:USB_HID_DS3PS3
//

//	private

VOID					USB_HID_DS3PS3::Main_Self(VOID){
//	driver::SERIAL0::stPrint(ARGSTR("0:"));
	if(EP_Main_stsznRead(IDEndPoint_Read0,&readThis,sizeof(readThis))==sizeof(readThis))eReadValid=TRUE;
//	driver::SERIAL0::stPrint(ARGSTR("1:"));
	EP_Main_stWrite(IDEndPoint_Write0,&writeThis,sizeof(writeThis));
//	driver::SERIAL0::stPrint(ARGSTR("2\r\n"));
	writeThis.Clear();
	return;
}

GBYTE					argbReportDescriptor[]={
	0x05,0x01,				//	Usage Page(Generic Desktop)
	0x09,0x04,				//	Usage(Joystick)
	0xa1,0x01,				//	Collection(Physical)
	0xa1,0x02,				//		Collection(Application)
							//										Report
	0x85,0x01,				//			Report ID(1)				-  0~ 0/Report ID(1B)
	0x75,0x08,				//			Report Size(8)
	0x95,0x01,				//			Report Count(1)
	0x15,0x00,				//			Logical Minimum(0)
	0x26,0xff,0x00,			//			Logical Maximum(255)
	0x81,0x03,				//			Input(Const)				-  1~ 1/Reserved(1B)
	0x75,0x01,				//			Report Size(1)
	0x95,0x13,				//			Report Count(19)
	0x15,0x00,				//			Logical Minimum(0)
	0x25,0x01,				//			Logical Maximum(1)
	0x35,0x00,				//			Physical Minimum(0)
	0x45,0x01,				//			Physical Maximum(1)
	0x05,0x09,				//			Usage Page(Button)
	0x19,0x01,				//			Usage Minimum(0x01)
	0x29,0x13,				//			Usage Maximum(0x13)
	0x81,0x02,				//			Input(Data)					-  2~--/Digital button(19b)
	0x75,0x01,				//			Report Size(1)
	0x95,0x0d,				//			Report Count(13)
	0x06,0x00,0xff,			//			Usage Page(Vendor-defined)
	0x81,0x03,				//			Input(Const)				- --~ 5/Reserved(13b)
	0x15,0x00,				//			Logical Minimum(0)
	0x26,0xff,0x00,			//			Logical Maximum(255)
	0x05,0x01,				//			Usage Page(Generic Desktop)
	0x09,0x01,				//			Usage(Pointer)
	0xa1,0x00,				//			Collection(Undefined)
	0x75,0x08,				//				Report Size(8)
	0x95,0x04,				//				Report Count(4)
	0x35,0x00,				//				Physical Minimum(0)
	0x46,0xff,0x00,			//				Physical Maximum(255)
	0x09,0x30,				//				Usage(X)
	0x09,0x31,				//				Usage(Y)
	0x09,0x32,				//				Usage(Z)
	0x09,0x35,				//				Usage(Rz)
	0x81,0x02,				//				Input(Data)					-  6~ 9/Axis(4B)
	0xc0,					//			End Collection
	0x05,0x01,				//			Usage Page(Generic Desktop)
	0x75,0x08,				//			Report Size(8)
	0x95,0x27,				//			Report Count(39)
	0x09,0x01,				//			Usage(Pointer)
	0x81,0x02,				//			Input(Data)					- 10~48/Analog button,Gyro(39B)
							//										Feedback
	0x75,0x08,				//			Report Size(8)
	0x95,0x30,				//			Report Count(48)
	0x09,0x01,				//			Usage(Pointer)
	0x91,0x02,				//			Output(Data)				-  0~47/Reserved(48B)
	0x75,0x08,				//			Report Size(8)
	0x95,0x30,				//			Report Count(48)
	0x09,0x01,				//			Usage(Pointer)
	0xb1,0x02,				//			Feature(Data)
	0xc0,					//		End Collection
	0xa1,0x02,				//		Collection (Application)
	0x85,0x02,				//			Report ID(2)
	0x75,0x08,				//			Report Size(8)
	0x95,0x30,				//			Report Count(48)
	0x09,0x01,				//			Usage(Pointer)
	0xb1,0x02,				//			Feature(Data)
	0xc0,					//		End Collection
	0xa1,0x02,				//		Collection (Application)
	0x85,0xee,				//			Report ID(238)
	0x75,0x08,				//			Report Size(8)
	0x95,0x30,				//			Report Count(48)
	0x09,0x01,				//			Usage(Pointer)
	0xb1,0x02,				//			Feature(Data)
	0xc0,					//		End Collection
	0xa1,0x02,				//		Collection (Application)
	0x85,0xef,				//			Report ID(239)
	0x75,0x08,				//			Report Size(8)
	0x95,0x30,				//			Report Count(48)
	0x09,0x01,				//			Usage(Pointer)
	0xb1,0x02,				//			Feature(Data)
	0xc0,					//		End Collection
	0xc0					//	End Collection
};

BYTE					USB_HID_DS3PS3::EP_Initialize_bcConfigType(
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

VOID					USB_HID_DS3PS3::VECTOR_Request_Standard_Descriptor_Device(VOID){
	CTRL_stWrite(ARGDEVICEDESC({
		sizeof(DEVICEDESC),		//	bnLength
		IDDescriptorType_Device,	//	bcDescriptorType
		OFW_stwEndianL(0x0200),	//	wcUSB
		0x00,					//	bcDeviceClass
		0x00,					//	bcDeviceSubClass
		0x00,					//	bcDeviceProtocol
		0x40,					//	bnMaxPacketSize
		OFW_stwEndianL(0x054c),	//	wcVendor
		OFW_stwEndianL(0x0268),	//	wcProduct
		OFW_stwEndianL(0x0100),	//	wcDevice
		IDStringDesc_Manufacturer,	//	biManufacturer
		IDStringDesc_Product,	//	biProduct
		IDStringDesc_Serial,	//	biSerialNumber
		0x01					//	bnConfiguration
	}),sizeof(DEVICEDESC));
	return;
}

VOID					USB_HID_DS3PS3::VECTOR_Request_Standard_Descriptor_Configuration(VOID){
	CTRL_stWrite(ARGUSERDESC({
		{
			sizeof(CONFIGDESC),		//	bnLength
			IDDescriptorType_Configuration,	//	bcDescriptorType
			OFW_stwEndianL(sizeof(USERDESC)),	//	wnTotalLength
			0x01,					//	bnInterface
			0x01,					//	bnConfiguration
			0x00,					//	biConfiguration
			stcbcAttributeBusPowered,	//	bcAttibute
			500>>1					//	bcMaxPower
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
			OFW_stwEndianL(0x0111),	//	wcHID
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
			1						//	bnInterval
		},						//	epdescRead0
		{
			sizeof(ENDPOINTDESC),	//	bnLength
			IDDescriptorType_EndPoint,	//	bcDescriptorType
			IDEndPoint_Write0|EP_stcbcDirectionWrite,	//	bcEndpointAddress
			EP_stcbcDescriptorTypeInterrupt,	//	bcAttribute
			OFW_stwEndianL(EP_stcsznBuffer),	//	wnMaxPacketSize
			1						//	bnInterval
		}						//	epdescWrite0
	}),sizeof(USERDESC));
	return;
}

VOID					USB_HID_DS3PS3::VECTOR_Request_Standard_Descriptor_String(
	BYTE					bithis
){
	switch(bithis){
	case IDStringDesc_Language:
		CTRL_stWriteStringLanguageDesc(0x0409);
		break;
	case IDStringDesc_Product:
		CTRL_stWriteStringDesc(ARGSTR("PLAYSTATION(R)3 Controller"));
		break;
	case IDStringDesc_Manufacturer:
		CTRL_stWriteStringDesc(ARGSTR("Sony"));
		break;
	}
	return;
}

VOID					USB_HID_DS3PS3::New_Self2(VOID){
	driver::SERIAL0::stNew(230400);
	driver::SERIAL0::stPrintClear();
	readThis.New();
	writeThis.New();
	OFW::stCopy(arbcAddress,ARGBYTE(0xaa,0xaa,0xaa,0xaa,0xaa,0xaa),6);
	eReadValid=FALSE;
	return;
}

VOID					USB_HID_DS3PS3::Delete_Self2(VOID){
	return;
}

VOID					USB_HID_DS3PS3::VECTOR_Request_Standard_Descriptor_Report(VOID){
	CTRL_stWrite((LPGBYTE)argbReportDescriptor,sizeof(argbReportDescriptor));
	return;
}

VOID					USB_HID_DS3PS3::VECTOR_Request_Class_Interface_Read(
	LPREQUEST				lpreqsource,
	LPCBYTE					lpcbsource,
	SIZE					sznsource
){
	switch(lpreqsource->bValueLSB){
	case 0xf5:
		OFW::stCopy(arbcAddress,lpcbsource+2,6);
		break;
	case 0xef:
		bcEF=lpcbsource[6];
		break;
	}
driver::SERIAL0::stPrint(ARGSTR("READ ("));
driver::SERIAL0::stPrintHEX(lpreqsource->bValueLSB);
driver::SERIAL0::stPrint(ARGSTR(")\r\n"));
	return;
}

SIZE					USB_HID_DS3PS3::VECTOR_Request_Class_Interface_sznWrite(
	LPREQUEST				lpreqsource,
	LPBYTE					lpbdestination
){
	switch(lpreqsource->bValueLSB){
	case 0x01:
		OFW::stCopy(lpbdestination,ARGBYTE(
			0x00,0x01,0x04,0x00,0x07,0x0c,0x01,0x02,0x18,0x18,0x18,0x18,0x09,0x0a,0x10,0x11,
			0x12,0x13,0x00,0x00,0x00,0x00,0x04,0x00,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x04,
			0x04,0x04,0x04,0x00,0x00,0x04,0x00,0x01,0x02,0x07,0x00,0x17,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		),0x40);
		break;
	case 0xf2:
		OFW::stCopy(lpbdestination,ARGBYTE(
			0xf2,0xff,0xff,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x00,0x03,0x50,0x81,0xd8,0x01,
			0x8a,0x13,0x00,0x00,0x00,0x00,0x04,0x00,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x04,
			0x04,0x04,0x04,0x00,0x00,0x04,0x00,0x01,0x02,0x07,0x00,0x17,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		),0x40);
		break;
	case 0xf5:
		OFW::stCopy(lpbdestination+0x00,ARGBYTE(
			0x01,0x00
		),0x02);
		OFW::stCopy(lpbdestination+0x02,arbcAddress,0x06);
		OFW::stCopy(lpbdestination+0x08,ARGBYTE(
			                                        0xff,0xf7,0x00,0x03,0x50,0x81,0xd8,0x01,
			0x8a,0x13,0x00,0x00,0x00,0x00,0x04,0x00,0x02,0x02,0x02,0x02,0x00,0x00,0x00,0x04,
			0x04,0x04,0x04,0x00,0x00,0x04,0x00,0x01,0x02,0x07,0x00,0x17,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		),0x38);
	case 0xf7:
		OFW::stCopy(lpbdestination,ARGBYTE(
			0x01,0x04,0xc4,0x02,0xd6,0x01,0xee,0xff,0x14,0x13,0x01,0x02,0xc4,0x01,0xd6,0x00,
			0x00,0x02,0x02,0x02,0x00,0x03,0x00,0x00,0x02,0x00,0x00,0x02,0x62,0x01,0x02,0x01,
			0x5e,0x00,0x32,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		),0x40);
		break;
	case 0xf8:
		OFW::stCopy(lpbdestination+0x00,ARGBYTE(
			0x00,0x01,0x00,0x00,0x07,0x03,0x01
		),0x07);
		lpbdestination[0x07]=bcEF;
		OFW::stCopy(lpbdestination,ARGBYTE(
			                                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x02,0x6b,0x02,0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		),0x38);
		break;
	case 0xef:
		OFW::stCopy(lpbdestination+0x00,ARGBYTE(
			0x00,0xef,0x04,0x00,0x07,0x03,0x01
		),0x07);
		lpbdestination[0x07]=bcEF;
		OFW::stCopy(lpbdestination+0x08,ARGBYTE(
			                                        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x02,0x6b,0x02,0x68,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
			0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
		),0x38);
		break;
	}
driver::SERIAL0::stPrint(ARGSTR("WRITE("));
driver::SERIAL0::stPrintHEX(lpreqsource->bValueLSB);
driver::SERIAL0::stPrint(ARGSTR(")\r\n"));
	return lpreqsource->wnLength;
}
