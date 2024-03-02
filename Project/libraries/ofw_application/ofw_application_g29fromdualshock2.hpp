/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	application/g29fromdualshock2					2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw_driver_ps.hpp>
#include				<ofw_stub_usb_hid_g29ps4.hpp>

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

		class G29FROMDUALSHOCK2;
		typedef const G29FROMDUALSHOCK2	CG29FROMDUALSHOCK2;
		typedef G29FROMDUALSHOCK2*	LPG29FROMDUALSHOCK2;
		typedef CG29FROMDUALSHOCK2*	LPCG29FROMDUALSHOCK2;

		//
		//		class:G29FROMDUALSHOCK2
		//

		class G29FROMDUALSHOCK2{
		public:
			static VOID				stNew(VOID);
			static VOID				stDelete(VOID);
			static VOID				stWrite(stub::USB_HID_G29PS4::LPWRITE lpwritedestination,driver::PS::LPCREAD lpcreadsource);
		};
	}
}
