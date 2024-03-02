/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	application/ds3fromdigital						2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw_driver_ps.hpp>
#include				<ofw_stub_usb_hid_ds3.hpp>

//
//		namespace:ofw
//

namespace ofw{

	//
	//		namespace:application
	//

	namespace application{

		//
		//		class
		//

		class DS3FROMDIGITAL;
		typedef const DS3FROMDIGITAL	CDS3FROMDIGITAL;
		typedef DS3FROMDIGITAL*	LPDS3FROMDIGITAL;
		typedef CDS3FROMDIGITAL*	LPCDS3FROMDIGITAL;

		//
		//		class:DS3FROMDIGITAL
		//

		class DS3FROMDIGITAL{
		public:
			static VOID				stNew(VOID);
			static VOID				stDelete(VOID);
			static VOID				stWrite(stub::USB_HID_DS3::LPWRITE lpwritedestination,driver::PS::LPCREAD lpcreadsource);
		};
	}
}
