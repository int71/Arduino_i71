//	use "switch_i71.bat"
#include				<ofw_driver_serial0.hpp>
#include				<ofw_driver_ps.hpp>
using namespace driver;

PS						psThis;
PS::IDTRANSITION		idTransitionPrevious;
BOOL					eRefreshed;

INT						main(VOID){
	OFW::stNew();
	SERIAL0::stNew(115200);
	SERIAL0::stPrintClear();
	psThis.New();
	idTransitionPrevious=PS::IDDevice_None-1;
	while(TRUE){
		PS::IDTRANSITION		idtransitioncurrent;

		psThis.Main();
		idtransitioncurrent=psThis.idGetTransition();
		if(idtransitioncurrent!=idTransitionPrevious){
			LPGSTR					arlpgstrtransition[]={
				ARGSTR("None"),
				ARGSTR("CheckSpeed"),
				ARGSTR("NS_Initialize"),
				ARGSTR("NS_SetAnalog0"),
				ARGSTR("NS_SetAnalog1"),
				ARGSTR("NS_SetAnalog2"),
				ARGSTR("NS_SetAnalog3_0"),
				ARGSTR("NS_SetAnalog3_1"),
				ARGSTR("NS_SetAnalog3_2"),
				ARGSTR("NS_SetAnalog3_3"),
				ARGSTR("NS_SetAnalog4"),
				ARGSTR("NS_Digital"),
				ARGSTR("NS_neGcon"),
				ARGSTR("NS_DUALSHOCK"),
				ARGSTR("HS_Initialize"),
				ARGSTR("HS_SetAnalog0"),
				ARGSTR("HS_SetAnalog1"),
				ARGSTR("HS_SetAnalog2"),
				ARGSTR("HS_SetAnalog3_0"),
				ARGSTR("HS_SetAnalog3_1"),
				ARGSTR("HS_SetAnalog3_2"),
				ARGSTR("HS_SetAnalog3_3"),
				ARGSTR("HS_SetAnalog4_0"),
				ARGSTR("HS_SetAnalog4_1"),
				ARGSTR("HS_SetAnalog4_2"),
				ARGSTR("HS_SetAnalog4_3"),
				ARGSTR("HS_SetAnalog5"),
				ARGSTR("HS_Digital"),
				ARGSTR("HS_neGconPlus"),
				ARGSTR("HS_DUALSHOCK2")
			};

			idTransitionPrevious=idtransitioncurrent;
			SERIAL0::stPrint(arlpgstrtransition[INT(idTransitionPrevious)]);
			SERIAL0::stPrint(ARGSTR("\r\n"));
		}
		OFW::stWait(1);
	}
	return 0;
}
