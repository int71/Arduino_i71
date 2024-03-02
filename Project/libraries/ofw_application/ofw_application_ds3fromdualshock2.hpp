/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	application/ds3fromdualshock2					2024 written by int71	**
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

		class DS3FROMDUALSHOCK2;
		typedef const DS3FROMDUALSHOCK2	CDS3FROMDUALSHOCK2;
		typedef DS3FROMDUALSHOCK2*	LPDS3FROMDUALSHOCK2;
		typedef CDS3FROMDUALSHOCK2*	LPCDS3FROMDUALSHOCK2;

		//
		//		class:DS3FROMDUALSHOCK2
		//

		class DS3FROMDUALSHOCK2{
		public:
			static VOID				stNew(VOID);
			static VOID				stDelete(VOID);
			static VOID				stWrite(stub::USB_HID_DS3::LPWRITE lpwritedestination,driver::PS::LPCREAD lpcreadsource);
		};
	}
}
