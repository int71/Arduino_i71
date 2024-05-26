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

#include				<ofw.hpp>
#include				<ofw_driver_timer.hpp>

int main(void){
	OFW::stNew();
	driver::TIMER::stNew(driver::TIMER::IDClock_Division1);
	DDRD|=0x01;
	while(TRUE){
		while(driver::TIMER::stwiGet()<0x1000);
		PORTD|=0x01;driver::TIMER::stSet(0);
		while(driver::TIMER::stwiGet()<0x1000);
		PORTD&=~0x01;driver::TIMER::stSet(0);
	}
	return 0;
}
