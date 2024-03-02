//	use "switch_org.bat"

void					setup(void){
	Serial.begin(115200);
	while(!Serial);
	return;
}

void					loop(void){
	Serial.print(F("TEST:"));
	Serial.print(analogRead(0));
	Serial.print(F("/"));
	Serial.print(analogRead(1));
	Serial.print(F("\r\n"));
	delay(1000);
	return;
}
