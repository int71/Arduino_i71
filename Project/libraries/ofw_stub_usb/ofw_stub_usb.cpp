/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb										2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				<ofw_stub_usb.hpp>

//
//		using
//

using namespace ofw::stub;

//
//		interrupt
//

ISR(USB_COM_vect){
	USB::VECTOR_stRequest();
	return;
}

ISR(USB_GEN_vect){
	USB::VECTOR_stGeneral();
	return;
}

//
//		class:USB
//

//	static

USB::ST					USB::st;

//	public

VOID					USB::stMain(VOID){
	st.lpusbRoot->Main_Self();
	return;
}

VOID					USB::New(VOID){
	st.bnInstance++;
	if(st.bnInstance==1)stNew_Local();
	New_Local();
	return;
}

VOID					USB::Delete(VOID){
	Delete_Local();
	if(st.bnInstance==1)stDelete_Local();
	st.bnInstance--;
	return;
}

//	protected

VOID					USB::CTRL_stWriteOpen(
	SIZE					sznsource
){
	EP_stOpen(0);
	st.CTRL_sziWriteCurrent=0;
	st.CTRL_sznWriteLimit=sznsource;
	return;
}

VOID					USB::CTRL_stWrite(
	BYTE					bsource
){
	if(st.CTRL_sziWriteCurrent<st.CTRL_sznWriteLimit){
		EP_stWaitforDone();
		EP_stWrite(bsource);
		st.CTRL_sziWriteCurrent++;
		if((st.CTRL_sziWriteCurrent&(EP_stcsznBuffer-1))==0)EP_stClearWrite();
	}
	return;
}

VOID					USB::CTRL_stWrite(
	LPCVOID					lpcsource,
	SIZE					sznsource
){
	LPCBYTE					lpcbsource=(LPCBYTE)lpcsource;

	for(;sznsource;sznsource--){
		CTRL_stWrite(*lpcbsource);
		lpcbsource++;
	}
	return;
}

VOID					USB::CTRL_stWrite(
	LPGVOID					lpgsource,
	SIZE					sznsource
){
	for(;sznsource;sznsource--){
		CTRL_stWrite(*lpgsource);
		lpgsource++;
	}
	return;
}

VOID					USB::CTRL_stWriteStringLanguageDesc(
	WORD					wclanguage
){
	CTRL_stWrite(2+1*2);
	CTRL_stWrite(IDDescriptorType_String);
	CTRL_stWrite(OFW_stbLSB(wclanguage));
	CTRL_stWrite(OFW_stbMSB(wclanguage));
	return;
}

VOID					USB::CTRL_stWriteStringDesc(
	LPCSTR					lpcstrsource
){
	SIZE					i;
	BYTE					bcurrent;

	for(i=0;lpcstrsource[i];i++);
	CTRL_stWrite(2+i*2);
	CTRL_stWrite(IDDescriptorType_String);
	for(i=0;bcurrent=(BYTE)lpcstrsource[i];i++){
		CTRL_stWrite(bcurrent);
		CTRL_stWrite(0);
	}
	return;
}

VOID					USB::CTRL_stWriteStringDesc(
	LPGSTR					lpgstrsource
){
	SIZE					i;
	BYTE					bcurrent;

	for(i=0;lpgstrsource[i];i++);
	CTRL_stWrite(2+i*2);
	CTRL_stWrite(IDDescriptorType_String);
	for(i=0;bcurrent=(BYTE)lpgstrsource[i];i++){
		CTRL_stWrite(bcurrent);
		CTRL_stWrite(0);
	}
	return;
}

SIZE					USB::EP_stsznRead(
	BYTE					biep,
	LPVOID					lpthis,
	SIZE					sznthis
){
	if(!st.eInitialized)return 0;
	{
		LPBYTE					lpbthis=(LPBYTE)lpthis;
		BYTE					bnrest;

		EP_stOpen(biep);
		bnrest=EP_stbnGetRest();
		if(bnrest<sznthis)sznthis=bnrest;
		else bnrest=sznthis;
		for(;bnrest;bnrest--){
			*lpbthis=EP_stbRead();
			lpbthis++;
		}
		EP_stReleaseRead();
	}
	return sznthis;
}

VOID					USB::EP_stWrite(
	BYTE					biep,
	LPCVOID					lpcsource,
	SIZE					sznsource
){
	LPCBYTE					lpcbsource=(LPCBYTE)lpcsource;

	if(!st.eInitialized)return;
	if(st.eSuspended)UDCON|=(1<<RMWKUP);
	EP_stOpen(biep);
	while(sznsource){
		BYTE					bnwritable;

		bnwritable=EP_stbnGetWritable();
		if(bnwritable){
			if(sznsource<bnwritable)bnwritable=sznsource;
			if(!EP_steIsWritable())continue;
			sznsource-=bnwritable;
			for(;bnwritable;bnwritable--){
				EP_stWrite(*lpcbsource);
				lpcbsource++;
			}
		}
	}
	EP_stReleaseWrite();
	return;
}

VOID					USB::EP_stWrite(
	BYTE					biep,
	LPGVOID					lpgsource,
	SIZE					sznsource
){
	if(!st.eInitialized)return;
	if(st.eSuspended)UDCON|=(1<<RMWKUP);
	EP_stOpen(biep);
	while(sznsource){
		BYTE					bnwritable;

		bnwritable=EP_stbnGetWritable();
		if(bnwritable){
			if(sznsource<bnwritable)bnwritable=sznsource;
			if(!EP_steIsWritable())continue;
			sznsource-=bnwritable;
			for(;bnwritable;bnwritable--){
				EP_stWrite(*lpgsource);
				lpgsource++;
			}
		}
	}
	EP_stReleaseWrite();
	return;
}

BYTE					USB::EP_Main_stbnGetReadable(
	BYTE					biep
){
	ATOMIC					atomic;

	EP_stOpen(biep);
	return EP_stbnGetRest();
}

BYTE					USB::EP_Main_stbnGetWritable(
	BYTE					biep
){
	ATOMIC					atomic;

	EP_stOpen(biep);
	return EP_stbnGetWritable();
}

SIZE					USB::EP_Main_stsznRead(
	BYTE					biep,
	LPVOID					lpthis,
	SIZE					sznthis
){
	ATOMIC					atomic;

	return EP_stsznRead(biep,lpthis,sznthis);
}

VOID					USB::EP_Main_stWrite(
	BYTE					biep,
	LPCVOID					lpcsource,
	SIZE					sznsource
){
	ATOMIC					atomic;

	EP_stWrite(biep,lpcsource,sznsource);
	if(EP_stbnGetRest())EP_stReleaseWrite();
	return;
}

VOID					USB::EP_Main_stWrite(
	BYTE					biep,
	LPGVOID					lpgsource,
	SIZE					sznsource
){
	ATOMIC					atomic;

	EP_stWrite(biep,lpgsource,sznsource);
	if(EP_stbnGetRest())EP_stReleaseWrite();
	return;
}

VOID					USB::New_Self(VOID){
	return;
}

VOID					USB::Delete_Self(VOID){
	return;
}

VOID					USB::Main_Self(VOID){
	return;
}

VOID					USB::VECTOR_Request_Standard_Descriptor_Other(
	LPREQUEST				lpreqsource
){
	return;
}

VOID					USB::VECTOR_Request_Class_Device(
	LPREQUEST				lpreqsource
){
	return;
}

VOID					USB::VECTOR_Request_Class_Interface(
	LPREQUEST				lpreqsource
){
	return;
}

VOID					USB::VECTOR_Request_Class_EndPoint(
	LPREQUEST				lpreqsource
){
	return;
}

//	private

VOID					USB::stNew_Local(VOID){
	st.eInitialized=FALSE;
	st.eSuspended=FALSE;
	st.eRemoteWakeUp=FALSE;
	stNew_Clock();
	UDINT&=~((1<<WAKEUPI)|(1<<SUSPI));		// clear already pending WAKEUP / SUSPEND requests
	UDIEN=(1<<EORSTE)|(1<<SOFE)|(1<<SUSPE);	// Enable interrupts for EOR (End of Reset), SOF (start of frame) and SUSPEND
	return;
}

VOID					USB::stDelete_Local(VOID){
	stDelete_Clock();
	return;
}

VOID					USB::stNew_Clock(VOID){
#if defined(UHWCON)		// power internal reg
	UHWCON|=(1<<UVREGE);
#endif					// clock frozen, usb enabled
	USBCON=(1<<USBE)|(1<<FRZCLK);
#if defined(PINDIV)		// ATmega32U4
#if F_CPU==16000000UL
	PLLCSR|=(1<<PINDIV);
#elif F_CPU==8000000UL
	PLLCSR &= ~(1<<PINDIV);
#else
#error "Clock rate of F_CPU not supported"
#endif
#elif defined(__AVR_AT90USB82__)||defined(__AVR_AT90USB162__)||defined(__AVR_ATmega32U2__)||defined(__AVR_ATmega16U2__)||defined(__AVR_ATmega8U2__)
#if F_CPU==16000000UL
	PLLCSR|=(1<<PLLP0);
#elif F_CPU==8000000UL
	PLLCSR&=~(1<<PLLP0);
#endif
#elif defined(PLLP2)	// AT90USB646, AT90USB647, AT90USB1286, AT90USB1287
#if F_CPU==16000000UL
#if defined(__AVR_AT90USB1286__)||defined(__AVR_AT90USB1287__)	// For Atmel AT90USB128x only. Do not use with Atmel AT90USB64x.
	PLLCSR=(PLLCSR&~(1<<PLLP1))|((1<<PLLP2)|(1<<PLLP0));	// Need 16 MHz xtal
#elif defined(__AVR_AT90USB646__)||defined(__AVR_AT90USB647__)	// For AT90USB64x only. Do not use with AT90USB128x.
	PLLCSR=(PLLCSR&~(1<<PLLP0))|((1<<PLLP2)|(1<<PLLP1));	// Need 16 MHz xtal
#else
#error "USB Chip not supported, please defined method of USB PLL initialization"
#endif
#elif F_CPU==8000000UL	// for Atmel AT90USB128x and AT90USB64x
	PLLCSR=(PLLCSR&~(1<<PLLP2))|((1<<PLLP1)|(1<<PLLP0));	// Need 8 MHz xtal
#else
#error "Clock rate of F_CPU not supported"
#endif
#else
#error "USB Chip not supported, please defined method of USB PLL initialization"
#endif
	PLLCSR|=(1<<PLLE);
	while(!(PLLCSR&(1<<PLOCK)));	// wait for lock pll
	delay(1);
#if defined(OTGPADE)	// start USB clock, enable VBUS Pad
	USBCON=(USBCON&~(1<<FRZCLK))|(1<<OTGPADE);
#else					// start USB clock
	USBCON&=~(1<<FRZCLK);
#endif
#if defined(RSTCPU)
	// enable attach resistor, set full speed mode
#if defined(LSM)
	UDCON&=~((1<<RSTCPU)|(1<<LSM)|(1<<RMWKUP)|(1<<DETACH));
#else					// u2 Series
	UDCON&=~((1<<RSTCPU)|(1<<RMWKUP)|(1<<DETACH));
#endif
#else					// AT90USB64x and AT90USB128x don't have RSTCPU
	UDCON&=~((1<<LSM)|(1<<RMWKUP)|(1<<DETACH));
#endif
	return;
}

VOID					USB::stDelete_Clock(VOID){
#if defined(OTGPADE)
	USBCON=(USBCON&~(1<<OTGPADE))|(1<<FRZCLK);	// freeze clock and disable VBUS Pad
#else					// u2 Series
	USBCON=(1<<FRZCLK);		// freeze clock
#endif
	PLLCSR&=~(1<<PLLE);		// stop PLL
	return;
}

VOID					USB::EP_stInitialize(VOID){
	BYTE					biep;

	for(biep=1;biep<EP_stcbnPort;biep++){
		BYTE					bcconfigtype;

		bcconfigtype=st.lpusbRoot->EP_Initialize_bcConfigType(biep);
		if(bcconfigtype)EP_stInitialize(biep,bcconfigtype,EP_IDSize_Double64);
	}
	UERST=0x7e;	// And reset them
	UERST=0;
	return;
}

VOID					USB::EP_stInitialize(
	BYTE					biep,
	BYTE					bcconfigtype,
	BYTE					bcsize
){
	UENUM=biep;
	UECONX=(1<<EPEN);
	UECFG0X=bcconfigtype;
	UECFG1X=bcsize;
	return;
}

BYTE					USB::EP_stbnGetWritable(VOID){
	if(!EP_steIsWritable())return 0;
	return EP_stcsznBuffer-EP_stbnGetRest();
}

void					USB::New_Local(void){
	st.lpusbRoot=this;
	New_Self();
	return;
}

void					USB::Delete_Local(void){
	Delete_Self();
	return;
}
