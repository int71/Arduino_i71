//	use "switch_i71.bat"
#include				<ofw_driver_serial0.hpp>

INT						main(VOID){
	constexpr WORD			cwitemp0=0x3fff;
	constexpr WORD			cwitemp1=0x7fff;
	constexpr WORD			cwitemp2=0xbfff;
	constexpr WORD			cwitemp3=0xffff;

	OFW::stNew();
	driver::SERIAL0::stNew(115200);
	driver::SERIAL0::stPrintClear();
	driver::SERIAL0::stPrintHEX(BYTE(cwitemp0<cwitemp1));driver::SERIAL0::stPrint(ARGSTR("\r\n"));
	driver::SERIAL0::stPrintHEX(BYTE(cwitemp1<cwitemp2));driver::SERIAL0::stPrint(ARGSTR("\r\n"));
	driver::SERIAL0::stPrintHEX(BYTE(cwitemp2<cwitemp3));driver::SERIAL0::stPrint(ARGSTR("\r\n"));
	while(TRUE){
	}
	return 0;
}
