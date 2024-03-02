/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb_hid_mouse								2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw_stub_usb_hid.hpp>

//
//		namespace:ofw
//

namespace ofw{

	//
	//		namespace:stub
	//

	namespace stub{

		//
		//		class
		//

		class USB_HID_MOUSE;
		typedef const USB_HID_MOUSE	CUSB_HID_MOUSE;
		typedef USB_HID_MOUSE*	LPUSB_HID_MOUSE;
		typedef CUSB_HID_MOUSE*	LPCUSB_HID_MOUSE;

		//
		//		class:USB_HID_MOUSE
		//

		class USB_HID_MOUSE:public USB_HID{
		public:

			//
			//		const
			//

			//	IDSTRINGDESC
			enum IDSTRINGDESC{
				IDStringDesc_Language=0,
				IDStringDesc_Manufacturer=1,
				IDStringDesc_Product=2,
				IDStringDesc_Serial=3
			};
			//	IDENDPOINT
			enum IDENDPOINT{
				IDEndPoint_Write0=1
			};

			//
			//		class
			//

			//	USERDESC
			class USERDESC;
			typedef const USERDESC	CUSERDESC;
			typedef USERDESC*		LPUSERDESC;
			typedef CUSERDESC*		LPCUSERDESC;
			#define GUSERDESC		static PROGMEM CUSERDESC
			typedef LPG<USERDESC>	LPGUSERDESC;
			typedef const LPGUSERDESC	CLPGUSERDESC;
			#define ARGUSERDESC(...)	(LPGUSERDESC)({GUSERDESC starguserdesctemp[]={__VA_ARGS__};starguserdesctemp;})

			//
			//		class:USERDESC
			//

			class USERDESC{
			public:
				CONFIGDESC				cfgdescThis;
				INTERFACEDESC			ifdescThis;
				HIDDESC					hiddescThis;
				ENDPOINTDESC			epdescWrite0;
			};

			//
			//		body:USB_HID_MOUSE
			//

		private:
			BYTE					EP_Initialize_bcConfigType(BYTE biep);
			VOID					VECTOR_Request_Standard_Descriptor_Device(VOID);
			VOID					VECTOR_Request_Standard_Descriptor_Configuration(VOID);
			VOID					VECTOR_Request_Standard_Descriptor_String(BYTE bithis);
			VOID					New_Self2(VOID);
			VOID					Delete_Self2(VOID);
//			VOID					Main_ReportRead(VOID);
			VOID					Main_ReportWrite(VOID);
			VOID					VECTOR_Request_Standard_Descriptor_Report(VOID);
		};
	}
}
