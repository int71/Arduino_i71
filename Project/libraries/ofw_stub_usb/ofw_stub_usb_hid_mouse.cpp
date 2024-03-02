/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb_hid_mouse								2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				<ofw_stub_usb_hid_mouse.hpp>

//
//		using
//

using namespace ofw::stub;

//	private

GBYTE					argbReportDescriptor[]={
	0x05,0x01,				//	USAGE_PAGE (Generic Desktop)
	0x09,0x02,				//	USAGE (Mouse)
	0xa1,0x01,				//	COLLECTION (Application)
	0x09,0x01,				//		USAGE (Pointer)
	0xa1,0x00,				//		COLLECTION (Physical)
	0x85,0x01,				//			REPORT_ID (1)
	0x05,0x09,				//				USAGE_PAGE (Button)
	0x19,0x01,				//				USAGE_MINIMUM (Button 1)
	0x29,0x03,				//				USAGE_MAXIMUM (Button 3)
	0x15,0x00,				//				LOGICAL_MINIMUM (0)
	0x25,0x01,				//				LOGICAL_MAXIMUM (1)
	0x95,0x03,				//				REPORT_COUNT (3)
	0x75,0x01,				//				REPORT_SIZE (1)
	0x81,0x02,				//				INPUT (Data,Var,Abs)
	0x95,0x01,				//				REPORT_COUNT (1)
	0x75,0x05,				//				REPORT_SIZE (5)
	0x81,0x03,				//				INPUT (Cnst,Var,Abs)
	0x05,0x01,				//				USAGE_PAGE (Generic Desktop)
	0x09,0x30,				//				USAGE (X)
	0x09,0x31,				//				USAGE (Y)
	0x09,0x38,				//				USAGE (Wheel)
	0x15,0x81,				//				LOGICAL_MINIMUM (-127)
	0x25,0x7f,				//				LOGICAL_MAXIMUM (127)
	0x75,0x08,				//				REPORT_SIZE (8)
	0x95,0x03,				//				REPORT_COUNT (3)
	0x81,0x06,				//				INPUT (Data,Var,Rel)
	0xc0,					//		END_COLLECTION
	0xc0,					//	END_COLLECTION
};

BYTE					USB_HID_MOUSE::EP_Initialize_bcConfigType(
	BYTE					biep
){
	switch(biep){
	case IDEndPoint_Write0:
		return EP_stcbcConfigTypeInterruptWrite;
	}
	return 0;
}

VOID					USB_HID_MOUSE::VECTOR_Request_Standard_Descriptor_Device(VOID){
	CTRL_stWrite(ARGDEVICEDESC({
		sizeof(DEVICEDESC),		//	bnLength
		IDDescriptorType_Device,	//	bcDescriptorType
		OFW_stwEndianL(0x0200),	//	wcUSB
		0xef,					//	bcDeviceClass
		0x02,					//	bcDeviceSubClass
		0x01,					//	bcDeviceProtocol
		0x40,					//	bnMaxPacketSize
		OFW_stwEndianL(0x1111),	//	wcVendor
		OFW_stwEndianL(0x2222),	//	wcProduct
		OFW_stwEndianL(0x0100),	//	wcDevice
		IDStringDesc_Manufacturer,	//	biManufacturer
		IDStringDesc_Product,	//	biProduct
		IDStringDesc_Serial,	//	biSerialNumber
		0x01					//	bnConfiguration
	}),sizeof(DEVICEDESC));
	return;
}

VOID					USB_HID_MOUSE::VECTOR_Request_Standard_Descriptor_Configuration(VOID){
	CTRL_stWrite(ARGUSERDESC({
		{
			sizeof(CONFIGDESC),		//	bnLength
			IDDescriptorType_Configuration,	//	bcDescriptorType
			OFW_stwEndianL(sizeof(USERDESC)),	//	wnTotalLength
			1,						//	bnInterface
			1,						//	bnConfiguration
			0,						//	biConfiguration
			stcbcAttributeBusPowered|stcbcAttributeRemoteWakeUp,	//	bcAttibute
			500>>1					//	bcMaxPower
		},						//	cfgdescThis
		{
			sizeof(INTERFACEDESC),	//	bnLength
			IDDescriptorType_Interface,	//	bcDescriptorType
			0,						//	bnInterface
			0,						//	bcAlternateSetting
			1,						//	bnEndpoint
			IDDeviceClass_HID,		//	bcInterfaceClass
			IDDeviceClassHID_None,	//	bcInterfaceSubClass
			IDProtocolHID_None,		//	bcInterfaceProtocol
			0						//	biInterface
		},						//	ifdescThis
		{
			sizeof(HIDDESC),		//	bnLength
			IDDescriptorType_HID,	//	bcDescriptorType
			OFW_stwEndianL(0x0101),	//	wcHID
			0,						//	bcCountryCode
			1,						//	bnDescriptor
			IDDescriptorTypeHID_Report,	//	bcDescriptorTypeHID
			OFW_stwEndianL(sizeof(argbReportDescriptor))	//	wnDescriptorLength
		},						//	hiddescThis
		{
			sizeof(ENDPOINTDESC),	//	bnLength
			IDDescriptorType_EndPoint,	//	bcDescriptorType
			EP_stcbcDirectionWrite|IDEndPoint_Write0,	//	bcEndpointAddress
			EP_stcbcDescriptorTypeInterrupt,	//	bcAttribute
			OFW_stwEndianL(EP_stcsznBuffer),	//	wnMaxPacketSize
			1						//	bnInterval
		}						//	epdescWrite0
	}),sizeof(USERDESC));
	return;
}

VOID					USB_HID_MOUSE::VECTOR_Request_Standard_Descriptor_String(
	BYTE					bithis
){
	switch(bithis){
	case IDStringDesc_Language:
		CTRL_stWriteStringLanguageDesc(0x0409);
		break;
	case IDStringDesc_Product:
		CTRL_stWriteStringDesc(ARGSTR("USB IO Board"));
		break;
	case IDStringDesc_Manufacturer:
		CTRL_stWriteStringDesc(ARGSTR("SparkFun"));
		break;
	case IDStringDesc_Serial:
		CTRL_stWriteStringDesc(ARGSTR("HID"));
		break;
	}
	return;
}

VOID					USB_HID_MOUSE::New_Self2(VOID){
	return;
}

VOID					USB_HID_MOUSE::Delete_Self2(VOID){
	return;
}

VOID					USB_HID_MOUSE::Main_ReportWrite(VOID){
	static BYTE				stbiprogress=0;
	BYTES m[5];

	stbiprogress++;
	m[0] = 1;
	m[1] = 0;// buttons
	if((stbiprogress&0x80)==0)m[2] = 1;//	x
	else m[2] = -1;//	x
	m[3] = 0;//	y
	m[4] = 0;//	wheel
	EP_stWrite(IDEndPoint_Write0,m,sizeof(m));
}

VOID					USB_HID_MOUSE::VECTOR_Request_Standard_Descriptor_Report(VOID){
	CTRL_stWrite((LPGBYTE)argbReportDescriptor,sizeof(argbReportDescriptor));
	return;
}
