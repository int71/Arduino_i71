#include				<ofw_driver_serial0.hpp>

class TEST{
public:
	BYTE					bcTest0;
	BYTE					bcTest1;
	BYTE					bcTest2;
	BYTE					bcTest3;
};
typedef const TEST		CTEST;
typedef TEST*			LPTEST;
typedef CTEST*			LPCTEST;
#define GTEST			static PROGMEM CTEST
typedef LPG<TEST>		LPGTEST;
typedef const LPGTEST	CLPGTEST;
#define ARGTEST(...)	(LPGTEST)({GTEST argtesttemp[]={__VA_ARGS__};argtesttemp;})

class HOLDER{
public:
	TEST					testThis0;
	TEST					testThis1;
};
typedef const HOLDER	CHOLDER;
typedef HOLDER*			LPHOLDER;
typedef CHOLDER*		LPCHOLDER;
#define GHOLDER			static PROGMEM CHOLDER
typedef LPG<HOLDER>		LPGHOLDER;
typedef const LPGHOLDER	CLPGHOLDER;
#define ARGHOLDER(...)	(LPGHOLDER)({GHOLDER argtesttemp[]={__VA_ARGS__};argtesttemp;})

int main(void){
	OFW::stNew();
	driver::SERIAL0::stNew(230400);
	driver::SERIAL0::stPrintClear();
	for(;;){
		GHOLDER					ghldrtemp={{0x40,0x41,0x42,0x43},{0x40,0x0d,0x0a,0x00}};
		LPGHOLDER				lpghldrtemp=&ghldrtemp;
		GTEST					argtesttemp[]={{0x40,0x41,0x42,0x43},{0x40,0x0d,0x0a,0x00}};

		driver::SERIAL0::stPrint((LPGSTR)(((LPGVOID)argtesttemp).lpcGetThis()));
		OFW::stWait(1000);
		driver::SERIAL0::stPrint("TEST\r\n");
		OFW::stWait(1000);
	}
	return 0;
}
