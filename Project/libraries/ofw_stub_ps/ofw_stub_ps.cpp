/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/ps											2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				"ofw_stub_ps.hpp"

//
//		using
//

using namespace ofw::stub;

//
//		class:PS
//

//	public

VOID					PS::stNew(VOID){
	OFW_STUB_PS_REGISTER_DDR=0x03;
	OFW_STUB_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault;
	return;
}

VOID					PS::stDelete(VOID){
	return;
}

VOID					PS::stOpen(VOID){
	while((OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskSEL)!=0x00);
	return;
}

VOID					PS::stClose(VOID){
	OFW_STUB_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskDAT|REGISTER_stcbcMaskACK;
	while((OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskSEL)==0x00);
	return;
}

BYTE					PS::stbWriteBYTE(
	BYTE					bcdata
){
	BYTE					bccommand=0x00;

	if((OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskSEL)!=0x00)return 0xff;
	OFW_STUB_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskDAT|REGISTER_stcbcMaskACK;
	for(BYTE i=0;i<8;++i){
		while((OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskCLK)!=0x00);
		OFW_STUB_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskACK|((bcdata&0x01)<<REGISTER_stcbiBitDAT);
		bcdata>>=1;
		bccommand>>=1;
		stWaitClock();
		while((OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskCLK)==0x00);
		bccommand|=(OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskCMD)<<(7-REGISTER_stcbiBitCMD);
		stWaitClockAdjust();
		stWaitClock();
	}
	OFW_STUB_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskDAT|REGISTER_stcbcMaskACK;
	return bccommand;
}

BYTE					PS::stbWriteBYTEHS(
	BYTE					bcdata
){
	BYTE					bccommand=0x00;

	if((OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskSEL)!=0x00)return 0xff;
	OFW_STUB_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskDAT|REGISTER_stcbcMaskACK;
	for(BYTE i=0;i<8;++i){
		while((OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskCLK)!=0x00);
		OFW_STUB_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskACK|((bcdata&0x01)<<REGISTER_stcbiBitDAT);
		bcdata>>=1;
		bccommand>>=1;
		stWaitClockHS();
		while((OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskCLK)==0x00);
		bccommand|=(OFW_STUB_PS_REGISTER_PIN&REGISTER_stcbcMaskCMD)<<(7-REGISTER_stcbiBitCMD);
		stWaitClockAdjust();
		stWaitClockHS();
	}
	OFW_STUB_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskDAT|REGISTER_stcbcMaskACK;
	return bccommand;
}

VOID					PS::stWriteACK(VOID){
	OFW_STUB_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskDAT;
	return;
}

//	private

VOID					PS::stWaitClockAdjust(VOID){
	OFW::stNOP();OFW::stNOP();
	return;
}

VOID					PS::stWaitClock(VOID){
	OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();
	OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();
	return;
}
