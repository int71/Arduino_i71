//	use "switch_i71.bat"
//         TX   RX
//         UART UART
//     +---PD3  PD2  GND  GND  PD1  PD0  PD4  PC6  PD7  PE6  PB4  PB5 -+
//     |    〇   〇   〇   〇   〇   〇   〇   〇   〇   〇   〇   〇  |
//     |                                                               |
//     |                                                 PB0           |
//     |                                                 ■TX LED(表)  |
//    +|                                                               |
//    ||                                                               |
//    +|                                                               |
//     |                                                 ■RX LED(表)  |
//     |                                                 PD5           |
//     |                                                               |
//     |    〇   〇   〇   〇   〇   〇   〇   〇   〇   〇   〇   〇  |
//     +---RAW  GND  RST  VCC  PF4  PF5  PF6  PF7  PB1  PB3  PB2  PB6 -+
//                             PS   PS   PS   PS   SPI  SPI  SPI  SPI
//                             CLK  SEL  CMD  DAT  SCLK MISO MOSI SS
//	「ofw_stub_usb_hid_ds3.cpp」は下記のように
//		_DEBUG_PIN:ON

#include				<ofw_driver_timer.hpp>
#include				<ofw_driver_usb_hid.hpp>
#include				<ofw_stub_usb_hid_ds3.hpp>
#include				<ofw_driver_ps.hpp>
#include				<ofw_application_ds3fromdualshock2.hpp>

driver::USB_HID			dusbThis;	//	自動変数領域だと「はみ出る」模様
stub::USB_HID_DS3		susbThis;
driver::PS				psThis;

INT						main(VOID){
	OFW::stNew();
	driver::TIMER::stNew(driver::TIMER::IDClock_Division8);
	if(dusbThis.eNew()){
		constexpr WORD			cwieiend=0x0200;
		constexpr WORD			cwiperiodicstart=cwieiend+0x0080;

		susbThis.New();
		psThis.New();
		application::DS3FROMDUALSHOCK2::stNew();
		driver::TIMER::stSet(cwieiend);
		while(TRUE){
			{
				ATOMIC					atomic;

				if(susbThis.eIsReadable()){
					if(susbThis.bcGetReportID()==0x01){
						psThis.SetRumbleS(
							susbThis.cread1DelegateThis().eMotorS,
							susbThis.cread1DelegateThis().bnMotorSLength
						);
						psThis.SetRumbleL(
							susbThis.cread1DelegateThis().nMotorLStrength*0x55,
							susbThis.cread1DelegateThis().bnMotorLLength
						);
					}
				}
				driver::TIMER::stWaitUntil(cwiperiodicstart);
				psThis.Main();
				dusbThis.GPIO_Write(psThis.idGetDevice());
				if(psThis.idGetDevice()==driver::PS::IDDevice_HS_DUALSHOCK2){
					application::DS3FROMDUALSHOCK2::stWrite(&susbThis.writeDelegateThis(),&psThis.creadDelegateThis());
				}
			}
			stub::USB::stMain();driver::TIMER::stSet(0);	//	ここをタイミング測定の起点に
			dusbThis.Main();
			driver::TIMER::stWaitUntil(cwieiend);
		}
	}else{
		//	USBホストシールド使用不能の場合
		DDRB|=0x01;
		while(TRUE){
			PORTB|=0x01;
			OFW::stWait(500);
			PORTB&=~0x01;
			OFW::stWait(500);
		}
	}
	return 0;
}
