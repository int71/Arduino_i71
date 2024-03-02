/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb_hid									2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw_stub_usb.hpp>

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

		class USB_HID;
		typedef const USB_HID	CUSB_HID;
		typedef USB_HID*		LPUSB_HID;
		typedef CUSB_HID*		LPCUSB_HID;

		//
		//		class:USB_HID
		//

		class USB_HID:public USB{
		public:

			//
			//		const
			//

			//	IDDESCRIPTORTYPEHID
			enum IDDESCRIPTORTYPEHID{
				IDDescriptorTypeHID_Report=0x22,
				IDDescriptorTypeHID_Physical=0x23
			};
			//	IDDEVICECLASSHID
			enum IDDEVICECLASSHID{
				IDDeviceClassHID_None=0,
				IDDeviceClassHID_BootInterface=1
			};
			//	IDPROTOCOLHID
			enum IDPROTOCOLHID{
				IDProtocolHID_None=0,
				IDProtocolHID_Keyboard=1,
				IDProtocolHID_Mouse=2
			};

			//
			//		class
			//

			//	HIDDESC
			class HIDDESC;
			typedef const HIDDESC	CHIDDESC;
			typedef HIDDESC*		LPHIDDESC;
			typedef CHIDDESC*		LPCHIDDESC;
			#define GHIDDESC		static PROGMEM CHIDDESC
			typedef LPG<HIDDESC>	LPGHIDDESC;
			typedef const LPGHIDDESC	CLPGHIDDESC;
			#define ARGHIDDESC(...)	(LPGHIDDESC)({GHIDDESC starghiddesctemp[]={__VA_ARGS__};starghiddesctemp;})

			//
			//		class:HIDDESC
			//

			class HIDDESC{
			public:
				BYTE					bnLength;
				BYTE					bcDescriptorType;
				WORD					wcHID;
				BYTE					bcCountryCode;
				BYTE					bnDescriptor;
				BYTE					bcDescriptorTypeHID;
				WORD					wnDescriptorLength;
			};

			//
			//		body:USB_HID
			//

		protected:
			virtual VOID			New_Self2(VOID);
			virtual VOID			Delete_Self2(VOID);
			virtual VOID			VECTOR_Request_Standard_Descriptor_Report(VOID)=0;
			virtual VOID			VECTOR_Request_Class_Interface_Read(LPREQUEST lpreqsource,LPCBYTE lpcbsource,SIZE sznsource);
			virtual SIZE			VECTOR_Request_Class_Interface_sznWrite(LPREQUEST lpreqsource,LPBYTE lpbdestination);
		private:
			VOID					New_Self(VOID);
			VOID					Delete_Self(VOID);
			VOID					VECTOR_Request_Standard_Descriptor_Other(LPREQUEST lpreqsource);
			VOID					VECTOR_Request_Class_Interface(LPREQUEST lpreqsource);
		};
	}
}
