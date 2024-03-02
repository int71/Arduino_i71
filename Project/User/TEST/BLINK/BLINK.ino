//	use "switch_org.bat"

void					setup(void){
    DDRC=0xff;
	return;
}

void					loop(void){
	static unsigned char	uctemp=0;

	uctemp++;
	if(uctemp&1){
	    PORTC=0x00;
	}else{
	    PORTC=0x80;
	}
    delay(100);
	return;
}
