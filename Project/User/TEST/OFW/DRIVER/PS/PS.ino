#include				<ofw_driver_serial0.hpp>
#include				<ofw_driver_ps.hpp>
using namespace driver;

PS						psThis;
PS::IDDEVICE			idDevicePrevious;
BOOL					eRefreshed;

INT						main(VOID){
	OFW::stNew();
	SERIAL0::stNew(230400);
	SERIAL0::stPrintClear();
	psThis.New();
	idDevicePrevious=PS::IDDevice_None-1;
	for(;;){
		PS::IDDEVICE			iddevicecurrent;
		BOOL					erefresh;

		psThis.Main();
		iddevicecurrent=psThis.idGetDevice();
		erefresh=FALSE;
		if(iddevicecurrent!=idDevicePrevious){
			idDevicePrevious=iddevicecurrent;
			SERIAL0::stPrintClear();
			SERIAL0::stPrintSetForeColor(6);
			SERIAL0::stPrintSetPosition( 0, 0);SERIAL0::stPrint(ARGSTR("DEVICE:"));
			SERIAL0::stPrintSetForeColor(9);
			erefresh=TRUE;
		}
		switch(iddevicecurrent){
		case PS::IDDevice_NS_Initialize:
		case PS::IDDevice_HS_Initialize:
			if(erefresh)show_initializing_base();
			show_initializing();
			break;
		case PS::IDDevice_NS_Digital:
			if(erefresh)show_digital_base();
			show_digital();
			break;
		case PS::IDDevice_NS_neGcon:
			if(erefresh)show_negcon_base();
			show_negcon();
			break;
		case PS::IDDevice_NS_DUALSHOCK:
			if(erefresh)show_dualshock_base();
			show_dualshock();
			break;
		case PS::IDDevice_HS_DUALSHOCK2:
			if(erefresh)show_dualshock2_base();
			show_dualshock2();
			break;
		default:
			if(erefresh)show_none_base();
			show_none();
			break;
		}
		OFW::stWait(20);
	}
	return 0;
}

VOID					show_none_base(VOID){
	SERIAL0::stPrintSetPosition( 8, 0);SERIAL0::stPrint(ARGSTR("-"));
	return;
}

VOID					show_none(VOID){
	return;
}

VOID					show_initializing_base(VOID){
	SERIAL0::stPrintSetPosition( 8, 0);SERIAL0::stPrint(ARGSTR("(DETECTING)"));
	return;
}

VOID					show_initializing(VOID){
	return;
}

VOID					show_digital_base(VOID){
	SERIAL0::stPrintSetForeColor(6);
	SERIAL0::stPrintSetPosition( 8, 2);SERIAL0::stPrint(ARGSTR("L2:"));
	SERIAL0::stPrintSetPosition(60, 2);SERIAL0::stPrint(ARGSTR("R2:"));
	SERIAL0::stPrintSetPosition( 8, 3);SERIAL0::stPrint(ARGSTR("L1:"));
	SERIAL0::stPrintSetPosition(60, 3);SERIAL0::stPrint(ARGSTR("R1:"));
	SERIAL0::stPrintSetPosition( 8, 5);SERIAL0::stPrint(ARGSTR("↑:"));
	SERIAL0::stPrintSetPosition( 4, 7);SERIAL0::stPrint(ARGSTR("←:"));
	SERIAL0::stPrintSetPosition(12, 7);SERIAL0::stPrint(ARGSTR("→:"));
	SERIAL0::stPrintSetPosition( 8, 9);SERIAL0::stPrint(ARGSTR("↓:"));
	SERIAL0::stPrintSetPosition(24, 7);SERIAL0::stPrint(ARGSTR("SELECT:"));
	SERIAL0::stPrintSetPosition(40, 7);SERIAL0::stPrint(ARGSTR("START:"));
	SERIAL0::stPrintSetPosition(60, 5);SERIAL0::stPrint(ARGSTR("△:"));
	SERIAL0::stPrintSetPosition(56, 7);SERIAL0::stPrint(ARGSTR("□:"));
	SERIAL0::stPrintSetPosition(64, 7);SERIAL0::stPrint(ARGSTR("〇:"));
	SERIAL0::stPrintSetPosition(60, 9);SERIAL0::stPrint(ARGSTR("×:"));
	SERIAL0::stPrintSetForeColor(9);
	SERIAL0::stPrintSetPosition( 8, 0);SERIAL0::stPrint(ARGSTR("DIGITAL PAD"));
	return;
}

VOID					show_digital(VOID){
	SERIAL0::stPrintSetPosition(12, 2);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonL2));
	SERIAL0::stPrintSetPosition(64, 2);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonR2));
	SERIAL0::stPrintSetPosition(12, 3);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonL1));
	SERIAL0::stPrintSetPosition(64, 3);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonR1));
	SERIAL0::stPrintSetPosition(12, 5);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonUp));
	SERIAL0::stPrintSetPosition( 8, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonLeft));
	SERIAL0::stPrintSetPosition(16, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonRight));
	SERIAL0::stPrintSetPosition(12, 9);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonDown));
	SERIAL0::stPrintSetPosition(32, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonSelect));
	SERIAL0::stPrintSetPosition(48, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonStart));
	SERIAL0::stPrintSetPosition(64, 5);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonTriangle));
	SERIAL0::stPrintSetPosition(60, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonSquare));
	SERIAL0::stPrintSetPosition(68, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonCircle));
	SERIAL0::stPrintSetPosition(64, 9);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DIGITAL.eButtonCross));
	return;
}

VOID					show_negcon_base(VOID){
	BYTE					i;

	SERIAL0::stPrintSetForeColor(6);
	SERIAL0::stPrintSetPosition( 8, 2);SERIAL0::stPrint(ARGSTR("Ｌ:"));
	SERIAL0::stPrintSetPosition(60, 2);SERIAL0::stPrint(ARGSTR("Ｒ:"));
	SERIAL0::stPrintSetPosition( 8, 4);SERIAL0::stPrint(ARGSTR("↑:"));
	SERIAL0::stPrintSetPosition( 4, 6);SERIAL0::stPrint(ARGSTR("←:"));
	SERIAL0::stPrintSetPosition(12, 6);SERIAL0::stPrint(ARGSTR("→:"));
	SERIAL0::stPrintSetPosition( 8, 8);SERIAL0::stPrint(ARGSTR("↓:"));
	SERIAL0::stPrintSetPosition(24, 6);SERIAL0::stPrint(ARGSTR("START:"));
	SERIAL0::stPrintSetPosition(60, 4);SERIAL0::stPrint(ARGSTR("Ｂ:"));
	SERIAL0::stPrintSetPosition(56, 6);SERIAL0::stPrint(ARGSTR("Ⅱ:"));
	SERIAL0::stPrintSetPosition(64, 6);SERIAL0::stPrint(ARGSTR("Ａ:"));
	SERIAL0::stPrintSetPosition(60, 8);SERIAL0::stPrint(ARGSTR("Ⅰ:"));
	for(i=2;i<9;i++){
		SERIAL0::stPrintSetPosition(34, i);SERIAL0::stPrint(ARGSTR("||"));
	}
	SERIAL0::stPrintSetForeColor(9);
	SERIAL0::stPrintSetPosition( 8, 0);SERIAL0::stPrint(ARGSTR("neGcon"));
	return;
}

VOID					show_negcon(VOID){
	SERIAL0::stPrintSetPosition(12, 2);SERIAL0::stPrintHEX(psThis.creadDelegateThis().NEGCON.biButtonL);
	SERIAL0::stPrintSetPosition(64, 2);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().NEGCON.eButtonR));
	SERIAL0::stPrintSetPosition(12, 4);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().NEGCON.eButtonUp));
	SERIAL0::stPrintSetPosition( 8, 6);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().NEGCON.eButtonLeft));
	SERIAL0::stPrintSetPosition(16, 6);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().NEGCON.eButtonRight));
	SERIAL0::stPrintSetPosition(12, 8);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().NEGCON.eButtonDown));
	SERIAL0::stPrintSetPosition(32, 6);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().NEGCON.eButtonStart));
	SERIAL0::stPrintSetPosition(64, 4);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().NEGCON.eButtonB));
	SERIAL0::stPrintSetPosition(60, 6);SERIAL0::stPrintHEX(psThis.creadDelegateThis().NEGCON.biButtonII);
	SERIAL0::stPrintSetPosition(68, 6);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().NEGCON.eButtonA));
	SERIAL0::stPrintSetPosition(64, 8);SERIAL0::stPrintHEX(psThis.creadDelegateThis().NEGCON.biButtonI);
	SERIAL0::stPrintSetPosition(34, 9);SERIAL0::stPrintHEX(psThis.creadDelegateThis().NEGCON.biAxisSteering);
	return;
}

VOID					show_dualshock_base(VOID){
	SERIAL0::stPrintSetForeColor(6);
	SERIAL0::stPrintSetPosition( 8, 2);SERIAL0::stPrint(ARGSTR("L2:"));
	SERIAL0::stPrintSetPosition(60, 2);SERIAL0::stPrint(ARGSTR("R2:"));
	SERIAL0::stPrintSetPosition( 8, 3);SERIAL0::stPrint(ARGSTR("L1:"));
	SERIAL0::stPrintSetPosition(60, 3);SERIAL0::stPrint(ARGSTR("R1:"));
	SERIAL0::stPrintSetPosition( 8, 5);SERIAL0::stPrint(ARGSTR("↑:"));
	SERIAL0::stPrintSetPosition( 4, 7);SERIAL0::stPrint(ARGSTR("←:"));
	SERIAL0::stPrintSetPosition(12, 7);SERIAL0::stPrint(ARGSTR("→:"));
	SERIAL0::stPrintSetPosition( 8, 9);SERIAL0::stPrint(ARGSTR("↓:"));
	SERIAL0::stPrintSetPosition(24, 7);SERIAL0::stPrint(ARGSTR("SELECT:"));
	SERIAL0::stPrintSetPosition(40, 7);SERIAL0::stPrint(ARGSTR("START:"));
	SERIAL0::stPrintSetPosition(60, 5);SERIAL0::stPrint(ARGSTR("△:"));
	SERIAL0::stPrintSetPosition(56, 7);SERIAL0::stPrint(ARGSTR("□:"));
	SERIAL0::stPrintSetPosition(64, 7);SERIAL0::stPrint(ARGSTR("〇:"));
	SERIAL0::stPrintSetPosition(60, 9);SERIAL0::stPrint(ARGSTR("×:"));
	SERIAL0::stPrintSetPosition(22, 9);SERIAL0::stPrint(ARGSTR("↑"));
	SERIAL0::stPrintSetPosition(20,10);SERIAL0::stPrint(ARGSTR("←  →"));
	SERIAL0::stPrintSetPosition(22,11);SERIAL0::stPrint(ARGSTR("↓"));
	SERIAL0::stPrintSetPosition(46, 9);SERIAL0::stPrint(ARGSTR("↑"));
	SERIAL0::stPrintSetPosition(44,10);SERIAL0::stPrint(ARGSTR("←  →"));
	SERIAL0::stPrintSetPosition(46,11);SERIAL0::stPrint(ARGSTR("↓"));
	SERIAL0::stPrintSetForeColor(9);
	SERIAL0::stPrintSetPosition( 8, 0);SERIAL0::stPrint(ARGSTR("DUALSHOCK"));
	return;
}

VOID					show_dualshock(VOID){
	SERIAL0::stPrintSetPosition(12, 2);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonL2));
	SERIAL0::stPrintSetPosition(64, 2);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonR2));
	SERIAL0::stPrintSetPosition(12, 3);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonL1));
	SERIAL0::stPrintSetPosition(64, 3);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonR1));
	SERIAL0::stPrintSetPosition(12, 5);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonUp));
	SERIAL0::stPrintSetPosition( 8, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonLeft));
	SERIAL0::stPrintSetPosition(16, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonRight));
	SERIAL0::stPrintSetPosition(12, 9);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonDown));
	SERIAL0::stPrintSetPosition(32, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonSelect));
	SERIAL0::stPrintSetPosition(48, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonStart));
	SERIAL0::stPrintSetPosition(64, 5);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonTriangle));
	SERIAL0::stPrintSetPosition(60, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonSquare));
	SERIAL0::stPrintSetPosition(68, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonCircle));
	SERIAL0::stPrintSetPosition(64, 9);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonCross));
	SERIAL0::stPrintSetPosition(22,10);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonL3));
	SERIAL0::stPrintSetPosition(28,10);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK.biAxisLX);
	SERIAL0::stPrintSetPosition(22,12);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK.biAxisLY);
	SERIAL0::stPrintSetPosition(46,10);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK.eButtonR3));
	SERIAL0::stPrintSetPosition(52,10);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK.biAxisRX);
	SERIAL0::stPrintSetPosition(46,12);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK.biAxisRY);
	return;
}

VOID					show_dualshock2_base(VOID){
	SERIAL0::stPrintSetForeColor(6);
	SERIAL0::stPrintSetPosition( 8, 2);SERIAL0::stPrint(ARGSTR("L2:"));
	SERIAL0::stPrintSetPosition(60, 2);SERIAL0::stPrint(ARGSTR("R2:"));
	SERIAL0::stPrintSetPosition( 8, 3);SERIAL0::stPrint(ARGSTR("L1:"));
	SERIAL0::stPrintSetPosition(60, 3);SERIAL0::stPrint(ARGSTR("R1:"));
	SERIAL0::stPrintSetPosition( 8, 5);SERIAL0::stPrint(ARGSTR("↑:"));
	SERIAL0::stPrintSetPosition( 4, 7);SERIAL0::stPrint(ARGSTR("←:"));
	SERIAL0::stPrintSetPosition(12, 7);SERIAL0::stPrint(ARGSTR("→:"));
	SERIAL0::stPrintSetPosition( 8, 9);SERIAL0::stPrint(ARGSTR("↓:"));
	SERIAL0::stPrintSetPosition(24, 7);SERIAL0::stPrint(ARGSTR("SELECT:"));
	SERIAL0::stPrintSetPosition(40, 7);SERIAL0::stPrint(ARGSTR("START:"));
	SERIAL0::stPrintSetPosition(60, 5);SERIAL0::stPrint(ARGSTR("△:"));
	SERIAL0::stPrintSetPosition(56, 7);SERIAL0::stPrint(ARGSTR("□:"));
	SERIAL0::stPrintSetPosition(64, 7);SERIAL0::stPrint(ARGSTR("〇:"));
	SERIAL0::stPrintSetPosition(60, 9);SERIAL0::stPrint(ARGSTR("×:"));
	SERIAL0::stPrintSetPosition(22, 9);SERIAL0::stPrint(ARGSTR("↑"));
	SERIAL0::stPrintSetPosition(20,10);SERIAL0::stPrint(ARGSTR("←  →"));
	SERIAL0::stPrintSetPosition(22,11);SERIAL0::stPrint(ARGSTR("↓"));
	SERIAL0::stPrintSetPosition(46, 9);SERIAL0::stPrint(ARGSTR("↑"));
	SERIAL0::stPrintSetPosition(44,10);SERIAL0::stPrint(ARGSTR("←  →"));
	SERIAL0::stPrintSetPosition(46,11);SERIAL0::stPrint(ARGSTR("↓"));
	SERIAL0::stPrintSetForeColor(9);
	SERIAL0::stPrintSetPosition( 8, 0);SERIAL0::stPrint(ARGSTR("DUALSHOCK2"));
	return;
}

VOID					show_dualshock2(VOID){
	SERIAL0::stPrintSetPosition(12, 2);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonL2);
	SERIAL0::stPrintSetPosition(64, 2);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonR2);
	SERIAL0::stPrintSetPosition(12, 3);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonL1);
	SERIAL0::stPrintSetPosition(64, 3);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonR1);
	SERIAL0::stPrintSetPosition(12, 5);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonUp);
	SERIAL0::stPrintSetPosition( 8, 7);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonLeft);
	SERIAL0::stPrintSetPosition(16, 7);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonRight);
	SERIAL0::stPrintSetPosition(12, 9);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonDown);
	SERIAL0::stPrintSetPosition(32, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK2.eButtonSelect));
	SERIAL0::stPrintSetPosition(48, 7);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK2.eButtonStart));
	SERIAL0::stPrintSetPosition(64, 5);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonTriangle);
	SERIAL0::stPrintSetPosition(60, 7);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonSquare);
	SERIAL0::stPrintSetPosition(68, 7);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonCircle);
	SERIAL0::stPrintSetPosition(64, 9);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biButtonCross);
	SERIAL0::stPrintSetPosition(22,10);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK2.eButtonL3));
	SERIAL0::stPrintSetPosition(28,10);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biAxisLX);
	SERIAL0::stPrintSetPosition(22,12);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biAxisLY);
	SERIAL0::stPrintSetPosition(46,10);SERIAL0::stPrintHEX((BYTE)(1-(BYTE)psThis.creadDelegateThis().DUALSHOCK2.eButtonR3));
	SERIAL0::stPrintSetPosition(52,10);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biAxisRX);
	SERIAL0::stPrintSetPosition(46,12);SERIAL0::stPrintHEX(psThis.creadDelegateThis().DUALSHOCK2.biAxisRY);
	return;
}
