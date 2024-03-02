#include				<ofw.hpp>

VOID					Print(WORD wsource);
VOID					Print(BYTE bsource);
VOID					PrintDigit(BYTE bsource);

void					setup(void){
	Serial.begin(115200);
	while(!Serial);
	return;
}

void					loop(void){
	for(;;){
		Serial.print(F("> "));Print(SREG);Serial.print(F("\r\n"));
		{
			ATOMIC					atomic;

			Serial.print(F("    > "));Print(SREG);Serial.print(F("\r\n"));
		}
		Serial.print(F("> "));Print(SREG);Serial.print(F("\r\n"));
		delay(1000);
	}
	return 0;
}

VOID					Print(
	WORD					wsource
){
	Print((BYTE)(wsource>>8));
	Print((BYTE)wsource);
	return;
}

VOID					Print(
	BYTE					bsource
){
	PrintDigit(bsource>>4);
	PrintDigit(bsource&0xf);
	return;
}

VOID					PrintDigit(
	BYTE					bsource
){
	if(bsource<10)Serial.print((char)('0'+bsource));
	else Serial.print((char)('a'-10+bsource));
	return;
}
