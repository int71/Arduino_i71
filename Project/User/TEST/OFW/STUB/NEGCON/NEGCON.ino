//	use "switch_org.bat"
//	<328Pアサイン>
//	| b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
//	+====+====+====+====+====+====+====+====+==
//	| － | － | － | 左 | 下 | 右 | 上 |ｽﾀｰﾄ|PB
//	|    |    |    | DR | DR | DR | DR | DR |
//	+----+----+----+----+----+----+----+----+--
//	| － | － |    |    | Ｌ | II | Ｉ |ねじ|PC
//	|    |    |    |    | AR | AR | AR | AR |
//	+----+----+----+----+----+----+----+----+--
//	|CMD |CLK | Ａ | Ｂ | Ｒ |SEL |ACK |DAT |PD
//	| DR | DR | DR | DR | DR | DR | DW | DW |
//	+----+----+----+----+----+----+----+----+--

//	〇   〇   〇   〇   〇   〇   〇   〇
//	GND  VCC  ACK  DAT  SEL  CLK  CMD  7V
//	黒   赤   緑   茶   黄   青   橙   白

//	<PSプロトコル仕様>
//	+----------+----+----+----+----+----+----+----+----+
//	|  バイト  | b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
//	+==========+====+====+====+====+====+====+====+====+
//	|１バイト目|               -----                   |  不定でよい
//	+----------+---------------------------------------+
//	|２バイト目|                0x23                   |
//	+----------+---------------------------------------+
//	|３バイト目|                0x5a                   | 'Z'
//	+----------+----+----+----+----+----+----+----+----+
//	|４バイト目| 左 | 下 | 右 | 上 |ｽﾀｰﾄ| １ | １ | １ |
//	+----------+----+----+----+----+----+----+----+----+
//	|５バイト目| １ | １ | Ａ | Ｂ | Ｒ | １ | １ | １ |
//	+----------+----+----+----+----+----+----+----+----+
//	|６バイト目| ねじり ADCデータ 最左:0x00, 中心:0x80 |
//	+----------+---------------------------------------+
//	|７バイト目|  I ボタン ADCデータ(8bit unsigned)    |  00h ～ FFh
//	+----------+---------------------------------------+
//	|８バイト目|       II ボタン ADCデータ             |  00h ～ FFh
//	+----------+---------------------------------------+
//	|９バイト目|        Ｌボタン ADCデータ             |  00h ～ FFh
//	+----------+---------------------------------------+

typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;
typedef void			VOID;
enum{
	FALSE=false,
	TRUE=true
};

void					setup(void){
	Serial.begin(115200);
	while(!Serial);
	PrintClear();
	show_negcon_base();
	//	| b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
	//	+====+====+====+====+====+====+====+====+==
	//	|    |    |    | DR | DR | DR | DR | DR |PB
	//	+----+----+----+----+----+----+----+----+--
	//	|    |    |    |    | AR | AR | AR | AR |PC
	//	+----+----+----+----+----+----+----+----+--
	//	|CMD |CLK | Ａ | Ｂ | Ｒ |SEL |ACK |DAT |PD
	//	| DR | DR | DR | DR | DR | DR | DW | DW |
	//	+----+----+----+----+----+----+----+----+--
    DDRB=0xe0;PORTB=0x1f;
    DDRC=0xf0;PORTC=0x00;
    DDRD=0x03;PORTD=0x38;
	return;
}

void					loop(void){
	while(TRUE){
		show_negcon();
		delay(100);
	}
	return 0;
}

VOID					StartReadAnalog(const BYTE cbiregister){
	BYTE					bilow, bihigh;

	ADMUX=0x40|cbiregister;
	ADCSRA|=1<<ADSC;
	return;
}

WORD					wReadAnalog(VOID){
	BYTE					bilow, bihigh;

	while(ADCSRA&(1<<ADSC));
	bilow=ADCL;
	bihigh=ADCH;
	return (WORD(bihigh)<<8)|WORD(bilow);
}

VOID					show_negcon_base(VOID){
	BYTE					i;

	PrintSetForeColor(6);
	PrintSetPosition( 8, 2);Serial.print(F("Ｌ:"));
	PrintSetPosition(60, 2);Serial.print(F("Ｒ:"));
	PrintSetPosition( 8, 4);Serial.print(F("↑:"));
	PrintSetPosition( 4, 6);Serial.print(F("←:"));
	PrintSetPosition(12, 6);Serial.print(F("→:"));
	PrintSetPosition( 8, 8);Serial.print(F("↓:"));
	PrintSetPosition(24, 6);Serial.print(F("START:"));
	PrintSetPosition(60, 4);Serial.print(F("Ｂ:"));
	PrintSetPosition(56, 6);Serial.print(F("Ⅱ:"));
	PrintSetPosition(64, 6);Serial.print(F("Ａ:"));
	PrintSetPosition(60, 8);Serial.print(F("Ⅰ:"));
	for(i=2;i<9;i++){
		PrintSetPosition(34, i);Serial.print(F("||"));
	}
	PrintSetForeColor(9);
	PrintSetPosition( 8, 0);Serial.print(F("neGcon"));
	return;
}

VOID					show_negcon(VOID){
	const BYTE				cbcb=PINB;
	const BYTE				cbcd=PIND;

	//	| b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
	//	+====+====+====+====+====+====+====+====+==
	//	| － | － | － | 左 | 下 | 右 | 上 |ｽﾀｰﾄ|PB
	//	+----+----+----+----+----+----+----+----+--
	//	| － | － |    |    | Ｌ | II | Ｉ |ねじ|PC
	//	+----+----+----+----+----+----+----+----+--
	//	|CMD |CLK | Ａ | Ｂ | Ｒ |SEL |ACK |DAT |PD
	//	+----+----+----+----+----+----+----+----+--
	StartReadAnalog(3);PrintSetPosition(12, 2);PrintHEX(wReadAnalog());	//	L
	PrintSetPosition(64, 2);PrintHEX(BYTE(cbcd&0x08?0x00:0xff));	//	R
	PrintSetPosition(12, 4);PrintHEX(BYTE(cbcb&0x02?0x00:0xff));	//	↑
	PrintSetPosition( 8, 6);PrintHEX(BYTE(cbcb&0x10?0x00:0xff));	//	←
	PrintSetPosition(16, 6);PrintHEX(BYTE(cbcb&0x04?0x00:0xff));	//	→
	PrintSetPosition(12, 8);PrintHEX(BYTE(cbcb&0x08?0x00:0xff));	//	↓
	PrintSetPosition(32, 6);PrintHEX(BYTE(cbcb&0x01?0x00:0xff));	//	START
	PrintSetPosition(64, 4);PrintHEX(BYTE(cbcd&0x10?0x00:0xff));	//	B
	StartReadAnalog(2);PrintSetPosition(60, 6);PrintHEX(wReadAnalog());	//	II
	PrintSetPosition(68, 6);PrintHEX(BYTE(cbcd&0x20?0x00:0xff));	//	A
	StartReadAnalog(1);PrintSetPosition(64, 8);PrintHEX(wReadAnalog());	//	I
	StartReadAnalog(0);PrintSetPosition(33, 9);PrintHEX(wReadAnalog());	//	STEERING
	return;
}

VOID					PrintHEX(
	BYTE					bsource
){
	PrintHEX_Half((bsource>> 4)&0x0f);
	PrintHEX_Half((bsource>> 0)&0x0f);
	return;
}

VOID					PrintHEX(
	WORD					wsource
){
	PrintHEX_Half((wsource>>12)&0x0f);
	PrintHEX_Half((wsource>> 8)&0x0f);
	PrintHEX_Half((wsource>> 4)&0x0f);
	PrintHEX_Half((wsource>> 0)&0x0f);
	return;
}

VOID					PrintHEX(
	DWORD					dwsource
){
	PrintHEX_Half((dwsource>>28)&0x0f);
	PrintHEX_Half((dwsource>>24)&0x0f);
	PrintHEX_Half((dwsource>>20)&0x0f);
	PrintHEX_Half((dwsource>>16)&0x0f);
	PrintHEX_Half((dwsource>>12)&0x0f);
	PrintHEX_Half((dwsource>> 8)&0x0f);
	PrintHEX_Half((dwsource>> 4)&0x0f);
	PrintHEX_Half((dwsource>> 0)&0x0f);
	return;
}

VOID					PrintClear(VOID){
	Serial.print(F("\x1b[2J"));
	PrintSetPosition(0,0);
	return;	
}

VOID					PrintSetPosition(
	BYTE					bix,
	BYTE					biy
){
	Serial.print(F("\x1b["));
	Serial.print(biy+1);
	Serial.print(F(";"));
	Serial.print(bix+1);
	Serial.print(F("H"));
	return;
}

VOID					PrintSetForeColor(
	BYTE					bccolor
){
	Serial.print(F("\x1b[3"));
	Serial.print(bccolor);
	Serial.print(F("m"));
	return;
}

VOID					PrintSetBackColor(
	BYTE					bccolor
){
	Serial.print(F("\x1b[4"));
	Serial.print(bccolor);
	Serial.print(F("m"));
	return;
}

VOID					PrintHEX_Half(
	BYTE					bsource
){
	const char* const		acpcstrhex[]={
		"0",	"1",	"2",	"3",
		"4",	"5",	"6",	"7",
		"8",	"9",	"A",	"B",
		"C",	"D",	"E",	"F"
	};

	Serial.print(acpcstrhex[bsource]);
	return;
}
