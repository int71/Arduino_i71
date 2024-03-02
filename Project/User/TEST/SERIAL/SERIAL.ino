//	use "switch_org.bat"

void					setup(void){
	Serial.begin(115200);
	while(!Serial);
	return;
}

void					loop(void){
	Serial.print(F("TEST\r\n"));
	delay(1000);
	return;
}
