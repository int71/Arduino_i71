/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	driver/serial2									2024 written by int71	**
 ****************************************************************************/

#if defined(__AVR_ATmega1280__)||defined(__AVR_ATmega2560__)

//
//		include
//

#include				"ofw_driver_serial2.hpp"

//
//		using
//

using namespace ofw::driver;

//
//		interrupt
//

ISR(USARTx_RX_vect){
	SERIAL2::stVectorRead();
	return;
}

//
//		class:SERIAL2
//

//	static

SERIAL2::ST				SERIAL2::st;

//	public

VOID					SERIAL2::stNew(
	DWORD					dwnrate
){
	stNew(dwnrate,IDLength_8bits,IDParity_None,IDStopbit_1);
	return;
}

VOID					SERIAL2::stNew(
	DWORD					dwnrate,
	IDLENGTH				idlength,
	IDPARITY				idparity,
	IDSTOPBIT				idstopbit
){
	BYTE					bctemp;

	switch(idlength){
	case IDLength_5bits:
		bctemp=0<<UCSZ10;
		break;
	case IDLength_6bits:
		bctemp=1<<UCSZ10;
		break;
	case IDLength_7bits:
		bctemp=2<<UCSZ10;
		break;
	case IDLength_9bits:
		bctemp=7<<UCSZ10;
		break;
	default:
		bctemp=3<<UCSZ10;
		break;
	}
	switch(idparity){
	case IDParity_Even:
		bctemp|=2<<UPM10;
		break;
	case IDParity_Odd:
		bctemp|=3<<UPM10;
		break;
	default:
		bctemp|=0<<UPM10;
		break;
	}
	switch(idstopbit){
	case IDStopbit_2:
		bctemp|=1<<USBS1;
		break;
	default:
		bctemp|=0<<USBS1;
		break;
	}
	//	hardware initialize
	UCSRxA=(1<<U2X1);							//	always 2X mode
	UCSRxC=bctemp;
	DDRx&=~(1<<stcbiRXD);DDRx|=(1<<stcbiTXD);
	PORTx&=~(1<<stcbiTXD);PORTx|=(1<<stcbiRXD);
	UBRRx=((dwnrate/2+OFW::stcdwnClockHz/8)/dwnrate)-1;	//	1/2 speed(always 2X mode)
	UCSRxB=((1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1));
	OFW::stWait(2);
	stReset();
	return;
}

VOID					SERIAL2::stDelete(VOID){
	return;
}

VOID					SERIAL2::stReset(VOID){
	st.biReadDone=0;
	st.biReadCurrent=0;
	return;
}

BYTE					SERIAL2::stbRead(VOID){
	BYTE					breturn;

	while(!steRead());
	breturn=st.arbRead[st.biReadCurrent];
	stIncrementCurrent();
	return breturn;
}

BYTE					SERIAL2::stbRead(
	WORDS&					wsnusectimeout
){
	static CWORDS			stcwsuseconce=(CWORDS)(3*16/OFW::stcdwnClockMHz);

	while(0<=wsnusectimeout)if(steRead()){
		BYTE					breturn;

		breturn=st.arbRead[st.biReadCurrent];
		stIncrementCurrent();
		return breturn;
	}else{
		OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();
		OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();
		OFW::stNOP();OFW::stNOP();
		wsnusectimeout-=stcwsuseconce;
	}
	return 0x00;
}

VOID					SERIAL2::stRead(
	LPVOID					lpdestination,
	BYTE					bnsize
){
	LPBYTE					lpbdestination=(LPBYTE)lpdestination;

	while(bnsize){
		while(!steRead());
		*lpbdestination=st.arbRead[st.biReadCurrent];lpbdestination++;bnsize--;
		stIncrementCurrent();
	}
	return;
}

VOID					SERIAL2::stRead(
	LPVOID					lpdestination,
	BYTE&					bnsize,
	WORDS&					wsnusectimeout
){
	LPBYTE					lpbdestination=(LPBYTE)lpdestination;
	static CWORDS			stcwsuseconce=(CWORDS)(3*16/OFW::stcdwnClockMHz);

	while((0<=wsnusectimeout)&&bnsize)if(steRead()){
		*lpbdestination=st.arbRead[st.biReadCurrent];lpbdestination++;bnsize--;
		stIncrementCurrent();
	}else{
		OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();
		OFW::stNOP();
		wsnusectimeout-=stcwsuseconce;
	}
	return;
}

VOID					SERIAL2::stWrite(
	BYTE					bsource
){
	while(!(UCSRxA&(1<<UDRE1)));
	UDRx=bsource;
	return;
}

VOID					SERIAL2::stWrite(
	LPCVOID					lpcsource,
	BYTE					bnsize
){
	LPCBYTE					lpcbsource=(LPCBYTE)lpcsource;
	BYTE					i;

	for(i=0;i<bnsize;i++)stWrite(lpcbsource[i]);
	return;
}

VOID					SERIAL2::stWrite(
	LPGVOID					lpgsource,
	BYTE					bnsize
){
	BYTE					i;

	for(i=0;i<bnsize;i++)stWrite(lpgsource[i]);
	return;
}

BOOL					SERIAL2::steRequestRead(
	BYTE					bccode,
	LPVOID					lpdestination,
	BYTE					bnsize,
	WORDS					wsnusectimeout
){
	LPBYTE					lpbdestination=(LPBYTE)lpdestination;
	BYTE					bin;

	stReset();
	stWrite(bccode);									//	->Request IN
	bin=stbRead(wsnusectimeout);						//	<-ACK
	if((bin!=0x80)||(wsnusectimeout<0))return FALSE;
	bin=stbRead(wsnusectimeout);						//	<-SIZE
	if((bin!=bnsize)||(wsnusectimeout<0))return FALSE;
	for(;stcbnPacketSize<bnsize;bnsize-=stcbnPacketSize,lpbdestination+=stcbnPacketSize){
		BYTE					bntemp;

		bntemp=stcbnPacketSize;
		stRead(lpbdestination,bntemp,wsnusectimeout);	//	<-DATA
		if(wsnusectimeout<0)return FALSE;
		stWrite(0x00);								//	->ACK
	}
	stRead(lpbdestination,bnsize,wsnusectimeout);		//	<-DATA
	if(wsnusectimeout<0)return FALSE;
	return TRUE;
}

BOOL					SERIAL2::steRequestWrite(
	BYTE					bccode,
	LPCVOID					lpcsource,
	BYTE					bnsize,
	WORDS					wsnusectimeout
){
	LPCBYTE					lpcbsource=(LPCBYTE)lpcsource;
	BYTE					bin;

	stReset();
	stWrite(bccode);									//	->Request OUT
	bin=stbRead(wsnusectimeout);						//	<-ACK
	if((bin!=0x00)||(wsnusectimeout<0))return FALSE;
	stWrite(bnsize);									//	->SIZE
	for(;stcbnPacketSize<bnsize;bnsize-=stcbnPacketSize,lpcbsource+=stcbnPacketSize){
		stWrite(lpcbsource,stcbnPacketSize);			//	->DATA
		bin=stbRead(wsnusectimeout);					//	<-ACK
		if((bin!=0x00)||(wsnusectimeout<0))return FALSE;
	}
	stWrite(lpcbsource,bnsize);						//	->DATA
	return TRUE;
}

BOOL					SERIAL2::steRequestWrite(
	BYTE					bccode,
	LPGVOID					lpgsource,
	BYTE					bnsize,
	WORDS					wsnusectimeout
){
	BYTE					bin;

	stReset();
	stWrite(bccode);									//	->Request OUT
	bin=stbRead(wsnusectimeout);						//	<-ACK
	if((bin!=0x00)||(wsnusectimeout<0))return FALSE;
	stWrite(bnsize);									//	->SIZE
	for(;stcbnPacketSize<bnsize;bnsize-=stcbnPacketSize,lpgsource+=stcbnPacketSize){
		stWrite(lpgsource,stcbnPacketSize);		//	->DATA
		bin=stbRead(wsnusectimeout);					//	<-ACK
		if((bin!=0x00)||(wsnusectimeout<0))return FALSE;
	}
	stWrite(lpgsource,bnsize);					//	->DATA
	return TRUE;
}

BYTE					SERIAL2::stbnReplyRead(
	LPCVOID					lpcsource,
	BYTE					bnsize,
	WORDS					wsnusectimeout
){
	LPCBYTE					lpcbsource=(LPCBYTE)lpcsource;
	BYTE					bnsource;

	stWrite(0x80);									//	->ACK
	stWrite(bnsize);									//	->SIZE
	bnsource=bnsize;
	for(;stcbnPacketSize<bnsize;bnsize-=stcbnPacketSize,lpcbsource+=stcbnPacketSize){
		BYTE					bin;

		stWrite(lpcbsource,stcbnPacketSize);			//	->DATA
		bin=stbRead(wsnusectimeout);					//	<-ACK
		if(bin!=0x00)return bnsource-bnsize;
	}
	stWrite(lpcbsource,bnsize);						//	->DATA
	return bnsource;
}

BYTE					SERIAL2::stbnReplyRead(
	LPGVOID					lpgsource,
	BYTE					bnsize,
	WORDS					wsnusectimeout
){
	BYTE					bnsource;

	stWrite(0x80);									//	->ACK
	stWrite(bnsize);									//	->SIZE
	bnsource=bnsize;
	for(;stcbnPacketSize<bnsize;bnsize-=stcbnPacketSize,lpgsource+=stcbnPacketSize){
		BYTE					bin;

		stWrite(lpgsource,stcbnPacketSize);		//	->DATA
		bin=stbRead(wsnusectimeout);					//	<-ACK
		if(bin!=0x00)return bnsource-bnsize;
	}
	stWrite(lpgsource,bnsize);					//	->DATA
	return bnsource;
}

BYTE					SERIAL2::stbnReplyWrite(
	LPVOID					lpdestination,
	BYTE					bnsize,
	WORDS					wsnusectimeout
){
	LPBYTE					lpbdestination=(LPBYTE)lpdestination;
	BYTE					bnsource;

	stWrite(0x00);									//	->ACK
	bnsource=stbRead(wsnusectimeout);					//	<-SIZE
	if(bnsource<bnsize)bnsize=bnsource;
	bnsource=bnsize;
	for(;stcbnPacketSize<bnsize;bnsize-=stcbnPacketSize,lpbdestination+=stcbnPacketSize){
		BYTE					bntemp;

		bntemp=stcbnPacketSize;
		stRead(lpbdestination,bntemp,wsnusectimeout);	//	<-DATA
		if(wsnusectimeout<0)return bnsource-bnsize;
		stWrite(0x00);								//	->ACK
	}
	stRead(lpbdestination,bnsize,wsnusectimeout);		//	<-DATA
	return bnsource;
}

VOID					SERIAL2::stPrint(
	LPCSTR					lpcstrsource
){
	for(;*lpcstrsource;lpcstrsource++)stWrite((BYTE)*lpcstrsource);
	return;
}

VOID					SERIAL2::stPrint(
	LPGSTR					lpgstrsource
){
	STR						strtemp;

	for(;strtemp=*lpgstrsource;lpgstrsource++)stWrite((BYTE)strtemp);
	return;
}

VOID					SERIAL2::stPrint(
	LONG					lsource
){
	LONG					ldecimal;
	BOOL					eshow;

	if(lsource<0){
		stWrite('-');
		lsource=-lsource;
	}
	eshow=FALSE;
	for(ldecimal=1000000000;1<ldecimal;ldecimal/=10){
		BYTE					bdigit;

		bdigit=(BYTE)(lsource/ldecimal);
		lsource-=((LONG)bdigit)*ldecimal;
		if(bdigit)eshow=TRUE;
		if(eshow)stWrite('0'+bdigit);
	}
	stWrite('0'+(BYTE)lsource);
	return;
}

VOID					SERIAL2::stPrintHEX(
	BYTE					bsource
){
	stPrintHEX_Half((bsource>> 4)&0x0f);
	stPrintHEX_Half((bsource>> 0)&0x0f);
	return;
}

VOID					SERIAL2::stPrintHEX(
	WORD					wsource
){
	stPrintHEX_Half((wsource>>12)&0x0f);
	stPrintHEX_Half((wsource>> 8)&0x0f);
	stPrintHEX_Half((wsource>> 4)&0x0f);
	stPrintHEX_Half((wsource>> 0)&0x0f);
	return;
}

VOID					SERIAL2::stPrintHEX(
	DWORD					dwsource
){
	stPrintHEX_Half((dwsource>>28)&0x0f);
	stPrintHEX_Half((dwsource>>24)&0x0f);
	stPrintHEX_Half((dwsource>>20)&0x0f);
	stPrintHEX_Half((dwsource>>16)&0x0f);
	stPrintHEX_Half((dwsource>>12)&0x0f);
	stPrintHEX_Half((dwsource>> 8)&0x0f);
	stPrintHEX_Half((dwsource>> 4)&0x0f);
	stPrintHEX_Half((dwsource>> 0)&0x0f);
	return;
}

VOID					SERIAL2::stPrintClear(VOID){
	stPrint(ARGSTR("\x1b[2J"));
	stPrintSetPosition(0,0);
	return;	
}

VOID					SERIAL2::stPrintSetPosition(
	BYTE					bix,
	BYTE					biy
){
	stPrint(ARGSTR("\x1b["));
	stPrint(biy+1);
	stWrite(';');
	stPrint(bix+1);
	stWrite('H');
	return;
}

VOID					SERIAL2::stPrintSetForeColor(
	BYTE					bccolor
){
	stPrint(ARGSTR("\x1b[3"));
	stPrint(bccolor);
	stWrite('m');
	return;
}

VOID					SERIAL2::stPrintSetBackColor(
	BYTE					bccolor
){
	stPrint(ARGSTR("\x1b[4"));
	stPrint(bccolor);
	stWrite('m');
	return;
}

VOID					SERIAL2::stPrintHEX_Half(
	BYTE					bsource
){
	if(bsource<10)stWrite('0'+bsource);
	else stWrite('A'+bsource-10);
	return;
}

#endif
