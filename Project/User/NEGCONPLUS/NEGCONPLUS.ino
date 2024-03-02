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

//	<PSプロトコル仕様(互換モード)>
//	+----------+----+----+----+----+----+----+----+----+
//	|  バイト  | b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
//	+==========+====+====+====+====+====+====+====+====+
//	|１バイト目|               -----                   |  不定でよい
//	+----------+---------------------------------------+
//	|２バイト目|                0x23                   |
//	+----------+---------------------------------------+
//	|３バイト目|                0x5a                   |  'Z'
//	+----------+----+----+----+----+----+----+----+----+
//	|４バイト目| 左 | 下 | 右 | 上 |ｽﾀｰﾄ| １ | １ | １ |
//	+----------+----+----+----+----+----+----+----+----+
//	|５バイト目| １ | １ | Ａ | Ｂ | Ｒ | １ | １ | １ |
//	+----------+----+----+----+----+----+----+----+----+
//	|６バイト目| ねじり ADCデータ                      |  最左:0x00, 中心:0x80
//	+----------+---------------------------------------+
//	|７バイト目| I ボタン ADCデータ                    |  00h ～ FFh
//	+----------+---------------------------------------+
//	|８バイト目| II ボタン ADCデータ                   |  00h ～ FFh
//	+----------+---------------------------------------+
//	|９バイト目| L ボタン ADCデータ                    |  00h ～ FFh
//	+----------+---------------------------------------+

//	<PSプロトコル仕様(独自拡張モード)>
//	+----------+----+----+----+----+----+----+----+----+
//	|  バイト  | b7 | b6 | b5 | b4 | b3 | b2 | b1 | b0 |
//	+==========+====+====+====+====+====+====+====+====+
//	|１バイト目|               -----                   |  不定でよい
//	+----------+---------------------------------------+
//	|２バイト目|                0xa5                   |
//	+----------+---------------------------------------+
//	|３バイト目|                0x5a                   |  'Z'
//	+----------+----+----+----+----+----+----+----+----+
//	|４バイト目| 左 | 下 | 右 | 上 |ｽﾀｰﾄ| １ | １ | １ |
//	+----------+----+----+----+----+----+----+----+----+
//	|５バイト目| １ | １ | Ａ | Ｂ | Ｒ | １ | １ | １ |
//	+----------+----+----+----+----+----+----+----+----+
//	|６バイト目| ねじり ADCデータ(下位8bit)            |  最左:0x0000, 中心:0x8000
//	+----------+---------------------------------------+
//	|７バイト目| ねじり ADCデータ(上位8bit)            |
//	+----------+---------------------------------------+
//	|８バイト目| I ボタン ADCデータ(下位8bit)          |  0000h ～ FFFFh
//	+----------+---------------------------------------+
//	|９バイト目| I ボタン ADCデータ(上位8bit)          |
//	+----------+---------------------------------------+
//	|10バイト目| II ボタン ADCデータ(下位8bit)         |  0000h ～ FFFFh
//	+----------+---------------------------------------+
//	|11バイト目| II ボタン ADCデータ(上位8bit)         |
//	+----------+---------------------------------------+
//	|12バイト目| L ボタン ADCデータ(下位8bit)          |  0000h ～ FFFFh
//	+----------+---------------------------------------+
//	|13バイト目| L ボタン ADCデータ(上位8bit)          |
//	+----------+---------------------------------------+

#include				<ofw.hpp>
#include				<ofw_device_analog.hpp>
#include				<ofw_stub_ps.hpp>
using namespace ofw::device;
using namespace ofw::stub;
BOOL					ePlus;

INT						main(VOID){
	OFW::stNew();
	ANALOG::stNew();
	PS::stNew();
    DDRB=0xe0;PORTB=0x1f;
    DDRC=0xf0;PORTC=0x00;
    ePlus=FALSE;
	while(TRUE)stSend();
	return 0;
}

VOID					stSend(VOID){
	ATOMIC					atomic;
	WORD					wi0,wi1,wi2,wi3;

	while(!steTrytoOpen(&wi0,&wi1,&wi2,&wi3));
	do{
		//	|１バイト目|               -----                   |  不定でよい
		if(PS::stbWriteBYTEHS(0xff)!=0x01)break;
		PS::stWriteACK();
		if(ePlus){
			//	|２バイト目|                0xa5                   |
			CBYTE					cbccommand=PS::stbWriteBYTEHS(0xa5);

			PS::stWriteACK();
			if((cbccommand!=0x42)&&(cbccommand!=0x45))break;
			//	|３バイト目|                0x5a                   |  'Z'
			if(PS::stbWriteBYTEHS(0x5a)!=0x00)break;
			PS::stWriteACK();
			//	|４バイト目| 左 | 下 | 右 | 上 |ｽﾀｰﾄ| １ | １ | １ |
			if(PS::stbWriteBYTEHS((PINB<<3)|0x07)!=0x00)break;
			PS::stWriteACK();
			//	|５バイト目| １ | １ | Ａ | Ｂ | Ｒ | １ | １ | １ |
			if(PS::stbWriteBYTEHS(PIND|0xc7)!=0x00)break;
			PS::stWriteACK();
			//	|６バイト目| ねじり ADCデータ(下位8bit)            |  最左:0x0000, 中心:0x8000
			if(PS::stbWriteBYTEHS(BYTE(wi0&0xff))!=0x00)break;
			PS::stWriteACK();
			//	|７バイト目| ねじり ADCデータ(上位8bit)            |
			if(PS::stbWriteBYTEHS(BYTE(wi0>>8))!=0x00)break;
			PS::stWriteACK();
			//	|８バイト目| I ボタン ADCデータ(下位8bit)          |  0000h ～ FFFFh
			if(PS::stbWriteBYTEHS(BYTE(wi1&0xff))!=0x00)break;
			PS::stWriteACK();
			//	|９バイト目| I ボタン ADCデータ(上位8bit)          |
			if(PS::stbWriteBYTEHS(BYTE(wi1>>8))!=0x00)break;
			PS::stWriteACK();
			//	|10バイト目| II ボタン ADCデータ(下位8bit)         |  0000h ～ FFFFh
			if(PS::stbWriteBYTEHS(BYTE(wi2&0xff))!=0x00)break;
			PS::stWriteACK();
			//	|11バイト目| II ボタン ADCデータ(上位8bit)         |
			if(PS::stbWriteBYTEHS(BYTE(wi2>>8))!=0x00)break;
			PS::stWriteACK();
			//	|12バイト目| L ボタン ADCデータ(下位8bit)          |  0000h ～ FFFFh
			if(PS::stbWriteBYTEHS(BYTE(wi3&0xff))!=0x00)break;
			PS::stWriteACK();
			//	|13バイト目| L ボタン ADCデータ(上位8bit)          |
			if(PS::stbWriteBYTEHS(BYTE(wi3>>8))!=0x00)break;
			PS::stWriteACK();
			PS::stClose();
			return;
		}else{
			//	|２バイト目|                0x23                   |
			CBYTE					cbccommand=PS::stbWriteBYTEHS(0x23);

			PS::stWriteACK();
			if(cbccommand==0x42){
				//	|３バイト目|                0x5a                   |  'Z'
				if(PS::stbWriteBYTEHS(0x5a)!=0x00)break;
				PS::stWriteACK();
				//	|４バイト目| 左 | 下 | 右 | 上 |ｽﾀｰﾄ| １ | １ | １ |
				if(PS::stbWriteBYTEHS((PINB<<3)|0x07)!=0x00)break;
				PS::stWriteACK();
				//	|５バイト目| １ | １ | Ａ | Ｂ | Ｒ | １ | １ | １ |
				if(PS::stbWriteBYTEHS(PIND|0xc7)!=0x00)break;
				PS::stWriteACK();
				//	|６バイト目| ねじり ADCデータ                      |  最左:0x00, 中心:0x80
				if(PS::stbWriteBYTEHS(BYTE(wi0>>8))!=0x00)break;
				PS::stWriteACK();
				//	|７バイト目| I ボタン ADCデータ                    |  00h ～ FFh
				if(PS::stbWriteBYTEHS(BYTE(wi1>>8))!=0x00)break;
				PS::stWriteACK();
				//	|８バイト目| II ボタン ADCデータ                   |  00h ～ FFh
				if(PS::stbWriteBYTEHS(BYTE(wi2>>8))!=0x00)break;
				PS::stWriteACK();
				//	|９バイト目| L ボタン ADCデータ                    |  00h ～ FFh
				if(PS::stbWriteBYTEHS(BYTE(wi3>>8))!=0x00)break;
				PS::stWriteACK();
				PS::stClose();
				return;
			}else if(cbccommand==0x43){
				//	|３バイト目|                0x5a                   |  'Z'
				if(PS::stbWriteBYTEHS(0x5a)!=0x00)break;
				PS::stWriteACK();
				if(PS::stbWriteBYTEHS(0xff)!=0x01)break;
				PS::stWriteACK();
				for(BYTE i=0;i<5;++i){
					if(PS::stbWriteBYTEHS(0xff)!=0x00)break;
					PS::stWriteACK();
				}
				ePlus=TRUE;
				PS::stClose();
				return;
			}
		}
	}while(FALSE);
	PS::stClose();
	ePlus=FALSE;
	return;
}

BOOL					steTrytoOpen(
	LPWORD					lpwi0,
	LPWORD					lpwi1,
	LPWORD					lpwi2,
	LPWORD					lpwi3
){
	WORD					wi00,wi10,wi20,wi30;
	WORD					wi01,wi11,wi21,wi31;
	
	ANALOG::stSelect(0x00);	//	ねじ
	if(steTrytoOpen(&wi00))return TRUE;
	ANALOG::stSelect(0x01);	//	I
	wi00=(wi00<<5)|(wi00>>5);
	if(steTrytoOpen(&wi10))return TRUE;
	ANALOG::stSelect(0x02);	//	II
	wi10=(wi10<<5)|(wi10>>5);
	if(steTrytoOpen(&wi20))return TRUE;
	ANALOG::stSelect(0x03);	//	L
	wi20=(wi20<<5)|(wi20>>5);
	if(steTrytoOpen(&wi30))return TRUE;
	ANALOG::stSelect(0x00);	//	ねじ
	wi30=(wi30<<5)|(wi30>>5);
	if(steTrytoOpen(&wi01))return TRUE;
	ANALOG::stSelect(0x01);	//	I
	wi01=(wi01<<5)|(wi01>>5);
	wi00+=wi01;
	if(steTrytoOpen(&wi11))return TRUE;
	ANALOG::stSelect(0x02);	//	II
	wi11=(wi11<<5)|(wi11>>5);
	wi10+=wi11;
	if(steTrytoOpen(&wi21))return TRUE;
	ANALOG::stSelect(0x03);	//	L
	wi21=(wi21<<5)|(wi21>>5);
	wi20+=wi21;
	if(steTrytoOpen(&wi31))return TRUE;
	wi31=(wi31<<5)|(wi31>>5);
	wi30+=wi31;
	*lpwi0=wi00;
	*lpwi1=wi10;
	*lpwi2=wi20;
	*lpwi3=wi30;
	return FALSE;
}

BOOL					steTrytoOpen(
	LPWORD					lpwivalue
){
	while(!ANALOG::steIsReady())if(PS::steTrytoOpen())return TRUE;
	*lpwivalue=ANALOG::stwRead();
	return FALSE;
}
