//	use "switch_org.bat"

void					setup(void){
	DDRB=0xff;
	DDRD=0xff;
	PORTB=0xff;
	PORTD=0xff;
	return;
}

void					loop(void){
	static unsigned char	uctemp=0;

	uctemp++;
	if(uctemp&1){
		PORTB=0x00;
	}else{
		PORTB=0x01;
	}
	delay(100);
	return;
}
