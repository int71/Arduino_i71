#include				<ofw.hpp>
#include				<ofw_stub_ps.hpp>
using namespace ofw::stub;

INT						main(VOID){
	OFW::stNew();
	PS::stNew();
	while(TRUE){
		stSend();
	}
	return 0;
}

VOID					stSend(VOID){
	PS::stOpen();
	do{
		ATOMIC					atomic;

		//	|１バイト目|               -----                   |  不定でよい
		if(PS::stbWriteBYTE(0xaa)!=0x01)break;
		PS::stWriteACK();
		//	|２バイト目|                0x23                   |
		if(PS::stbWriteBYTE(0x23)!=0x42)break;
		PS::stWriteACK();
		//	|３バイト目|                0x5a                   | 'Z'
		if(PS::stbWriteBYTE(0x5a)!=0x00)break;
		PS::stWriteACK();
		//	|４バイト目| 左 | 下 | 右 | 上 |ｽﾀｰﾄ| １ | １ | １ |
		if(PS::stbWriteBYTE(0x7f)!=0x00)break;
		PS::stWriteACK();
		//	|５バイト目| １ | １ | Ａ | Ｂ | Ｒ | １ | １ | １ |
		if(PS::stbWriteBYTE(0xdf)!=0x00)break;
		PS::stWriteACK();
		//	|６バイト目| ねじり ADCデータ 最左:0x00, 中心:0x80 |
		if(PS::stbWriteBYTE(0x80)!=0x00)break;
		PS::stWriteACK();
		//	|７バイト目|  I ボタン ADCデータ(8bit unsigned)    |  00h ～ FFh
		if(PS::stbWriteBYTE(0xff)!=0x00)break;
		PS::stWriteACK();
		//	|８バイト目|       II ボタン ADCデータ             |  00h ～ FFh
		if(PS::stbWriteBYTE(0x00)!=0x00)break;
		PS::stWriteACK();
		//	|９バイト目|        Ｌボタン ADCデータ             |  00h ～ FFh
		if(PS::stbWriteBYTE(0x00)!=0x00)break;
		PS::stWriteACK();
	}while(FALSE);
	PS::stClose();
	return;
}
