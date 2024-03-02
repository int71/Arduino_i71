/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	driver/ps										2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				"ofw_driver_ps.hpp"

//
//		using
//

using namespace ofw::driver;

//
//		class:PS
//

//	static

PS::ST					PS::st;

//	public

VOID					PS::New(VOID){
	st.bnInstance++;
	if(st.bnInstance==1)stNew_Local();
	New_Local();
	return;
}

VOID					PS::Delete(VOID){
	Delete_Local();
	if(st.bnInstance==1)stDelete_Local();
	st.bnInstance--;
	return;
}

VOID					PS::Main(VOID){
	if(biMotorSLength)biMotorSLength--;
	else arbcCommand[2]=0x00;
	if(biMotorLLength)biMotorLLength--;
	else arbcCommand[3]=0x00;
	stSetHS(FALSE);
	switch(idTransition){
	case IDTransition_None:
		{
			//	READ_DATA_AND_VIBRATE_EX
			//	CMD=01,42,00,WW,PP(,00,00,00,00)
			//	DAT=--,ID,SS,XX,XX(,XX,XX,XX,XX)
			BYTE					arbccommand[]={0x42};

			idDevice=IDDevice_None;
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a){
				idTransition=IDTransition_CheckSpeed;
				return;
			}
		}
		break;
	case IDTransition_CheckSpeed:
		{
			//	READ_DATA_AND_VIBRATE_EX
			//	CMD=01,42,00,WW,PP(,00,00,00,00)
			//	DAT=--,ID,SS,XX,XX(,XX,XX,XX,XX)
			BYTE					arbccommand[]={0x42};

			idDevice=IDDevice_NS_Initialize;
			stSetHS(TRUE);
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a)idTransition=IDTransition_HS_Initialize;
			else idTransition=IDTransition_NS_Initialize;
			return;
		}
		break;
	case IDTransition_NS_Initialize:
		{
			//	READ_DATA_AND_VIBRATE_EX
			//	CMD=01,42,00,WW,PP(,00,00,00,00)
			//	DAT=--,ID,SS,XX,XX(,XX,XX,XX,XX)
			BYTE					arbccommand[]={0x42};

			idDevice=IDDevice_NS_Initialize;
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a){
				if(readThis.bcType==0x23)idTransition=IDTransition_NS_neGcon;
				else idTransition=IDTransition_NS_SetAnalog0;
				return;
			}
		}
		break;
	case IDTransition_NS_SetAnalog0:
		{
			//	CONFIG_MODE_ENTER
			//	CMD=01,43,00,01,00(,00,00,00,00)
			//	DAT=--,ID,SS,XX,XX(,XX,XX,XX,XX)
			BYTE					arbccommand[]={0x43,0x00,0x01};

			idDevice=IDDevice_NS_Initialize;
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a)idTransition=idTransition+1;
			else idTransition=IDTransition_NS_Digital;
			return;
		}
		break;
	case IDTransition_NS_SetAnalog1:
		{
			//	QUERY_MODEL_AND_MODE
			//	CMD=01,45,00,00,00,00,00,00,00
			//	DAT=FF,F3,5A,01,02,MM,VV,01,00
			BYTE					arbccommand[]={0x45};

			idDevice=IDDevice_NS_Initialize;
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.wcID==0x5af3)idTransition=idTransition+1;
			else idTransition=IDTransition_NS_Digital;
			return;
		}
		break;
	case IDTransition_NS_SetAnalog2:
		{
			//	SET_MODE_AND_LOCK
			//	CMD=01,44,00,XX,YY,00,00,00,00
			//	DAT=--,F3,5A,00,00,00,00,00,00
			BYTE					arbccommand[]={0x44,0x00,0x01,0x03};

			idDevice=IDDevice_NS_Initialize;
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a){
				idTransition=idTransition+1;
				return;
			}
		}
		break;
	case IDTransition_NS_SetAnalog3_0:
	case IDTransition_NS_SetAnalog3_1:
	case IDTransition_NS_SetAnalog3_2:
	case IDTransition_NS_SetAnalog3_3:
		{
			//	VIBRATION_ENABLE
			//	CMD=01,4D,00,00,01,FF,FF,FF,FF
			//	DAT=--,F3,5A,FF,FF,FF,FF,FF,FF
			BYTE					arbccommand[]={0x4d,0x00,0x00,0x01,0xff,0xff,0xff,0xff};

			idDevice=IDDevice_NS_Initialize;
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a){
				idTransition=idTransition+1;
				return;
			}
		}
		break;
	case IDTransition_NS_SetAnalog4:
		{
			//	CONFIG_MODE_EXIT
			//	CMD=01,43,00,00,5A,5A,5A,5A,5A
			//	DAT=FF,F3,5A,00,00,00,00,00,00
			BYTE					arbccommand[]={0x43,0x00,0x00,0x5a,0x5a,0x5a,0x5a,0x5a};

			idDevice=IDDevice_NS_Initialize;
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a){
				idTransition=IDTransition_NS_DUALSHOCK;
				return;
			}
		}
		break;
	case IDTransition_NS_Digital:
		{
			//	READ_DATA
			//	CMD=01,42,00,00,00
			//	DAT=--,41,5A,XX,XX
			idDevice=IDDevice_NS_Digital;
			Read(nullptr,0);
			if(readThis.wcID==0x5a41)return;
		}
		break;
	case IDTransition_NS_neGcon:
		{
			//	READ_DATA
			//	CMD=01,42,00,00,00
			//	DAT=--,23,5A,XX,XX
			idDevice=IDDevice_NS_neGcon;
			Read(nullptr,0);
			if(readThis.wcID==0x5a23)return;
		}
		break;
	case IDTransition_NS_DUALSHOCK:
		{
			//	READ_DATA_AND_VIBRATE_EX
			//	CMD=01,42,00,WW,PP(,00,00,00,00)
			//	DAT=--,ID,SS,XX,XX(,XX,XX,XX,XX)
			idDevice=IDDevice_NS_DUALSHOCK;
			Read(arbcCommand,sizeof(arbcCommand));
			if(readThis.wcID==0x5a73)return;
		}
		break;
	case IDTransition_HS_Initialize:
		{
			//	READ_DATA_AND_VIBRATE_EX
			//	CMD=01,42,00,WW,PP(,00,00,00,00)
			//	DAT=--,ID,SS,XX,XX(,XX,XX,XX,XX)
			BYTE					arbccommand[]={0x42};

			idDevice=IDDevice_HS_Initialize;
			stSetHS(TRUE);
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a){
				idTransition=IDTransition_HS_SetAnalog0;
				return;
			}
		}
		break;
	case IDTransition_HS_SetAnalog0:
		{
			//	CONFIG_MODE_ENTER
			//	CMD=01,43,00,01,00(,00,00,00,00)
			//	DAT=--,ID,SS,XX,XX(,XX,XX,XX,XX)
			BYTE					arbccommand[]={0x43,0x00,0x01};

			idDevice=IDDevice_HS_Initialize;
			stSetHS(TRUE);
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a)idTransition=idTransition+1;
			else idTransition=IDTransition_NS_Digital;
			return;
		}
		break;
	case IDTransition_HS_SetAnalog1:
		{
			//	QUERY_MODEL_AND_MODE
			//	CMD=01,45,00,00,00,00,00,00,00
			//	DAT=FF,F3,5A,01,02,MM,VV,01,00
			BYTE					arbccommand[]={0x45};

			idDevice=IDDevice_HS_Initialize;
			stSetHS(TRUE);
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.wcID==0x5af3)idTransition=idTransition+1;
			else if(readThis.wcID==0x5aa5)idTransition=IDTransition_HS_neGconPlus;
			else idTransition=IDTransition_NS_Digital;
			return;
		}
		break;
	case IDTransition_HS_SetAnalog2:
		{
			//	SET_MODE_AND_LOCK
			//	CMD=01,44,00,XX,YY,00,00,00,00
			//	DAT=--,F3,5A,00,00,00,00,00,00
			BYTE					arbccommand[]={0x44,0x00,0x01,0x03};

			idDevice=IDDevice_HS_Initialize;
			stSetHS(TRUE);
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a){
				idTransition=idTransition+1;
				return;
			}
		}
		break;
	case IDTransition_HS_SetAnalog3_0:
	case IDTransition_HS_SetAnalog3_1:
	case IDTransition_HS_SetAnalog3_2:
	case IDTransition_HS_SetAnalog3_3:
		{
			//	PRESSURE_ENABLE
			//	CMD=01,4F,00,FF,FF,03,00,00,00
			//	DAT=FF,F3,5A,00,00,00,00,00,5A
			BYTE					arbccommand[]={0x4f,0x00,0xff,0xff,0x03};

			idDevice=IDDevice_HS_Initialize;
			stSetHS(TRUE);
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a){
				idTransition=idTransition+1;
				return;
			}
		}
		break;
	case IDTransition_HS_SetAnalog4_0:
	case IDTransition_HS_SetAnalog4_1:
	case IDTransition_HS_SetAnalog4_2:
	case IDTransition_HS_SetAnalog4_3:
		{
			//	VIBRATION_ENABLE
			//	CMD=01,4D,00,00,01,FF,FF,FF,FF
			//	DAT=--,F3,5A,FF,FF,FF,FF,FF,FF
			BYTE					arbccommand[]={0x4d,0x00,0x00,0x01,0xff,0xff,0xff,0xff};

			idDevice=IDDevice_HS_Initialize;
			stSetHS(TRUE);
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a){
				idTransition=idTransition+1;
				return;
			}
		}
		break;
	case IDTransition_HS_SetAnalog5:
		{
			//	CONFIG_MODE_EXIT
			//	CMD=01,43,00,00,5A,5A,5A,5A,5A
			//	DAT=FF,F3,5A,00,00,00,00,00,00
			BYTE					arbccommand[]={0x43,0x00,0x00,0x5a,0x5a,0x5a,0x5a,0x5a};

			idDevice=IDDevice_HS_Initialize;
			stSetHS(TRUE);
			Read(arbccommand,sizeof(arbccommand));
			if(readThis.bcCheck==0x5a){
				idTransition=IDTransition_HS_DUALSHOCK2;
				return;
			}
		}
		break;
	case IDTransition_HS_neGconPlus:
		{
			//	READ_DATA
			//	CMD=01,42,00,00,00
			//	DAT=--,23,5A,XX,XX
			idDevice=IDDevice_HS_neGconPlus;
			stSetHS(TRUE);
			Read(nullptr,0);
			if(readThis.wcID==0x5aa5)return;
		}
		break;
	case IDTransition_HS_DUALSHOCK2:
		{
			//	READ_DATA_AND_VIBRATE_EX
			//	CMD=01,42,00,WW,PP(,00,00,00,00)
			//	DAT=--,ID,SS,XX,XX(,XX,XX,XX,XX)
			idDevice=IDDevice_HS_DUALSHOCK2;
			stSetHS(TRUE);
			Read(arbcCommand,sizeof(arbcCommand));
			if(readThis.wcID==0x5a79)return;
		}
		break;
	}
	idTransition=IDTransition_None;
	idDevice=IDDevice_None;
	return;
}

//	private

VOID					PS::stNew_Local(VOID){
	st.eHighSpeed=FALSE;
	OFW_DRIVER_PS_REGISTER_DDR=REGISTER_stcbcMaskCMD|REGISTER_stcbcMaskSEL|REGISTER_stcbcMaskCLK;
	OFW_DRIVER_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskCMD|REGISTER_stcbcMaskSEL|REGISTER_stcbcMaskCLK;
	return;
}

VOID					PS::stDelete_Local(VOID){
	OFW_DRIVER_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault;
	return;
}

VOID					PS::stRead(
	LPBYTE					lpbreturn,
	LPCBYTE					lpcbcommand,
	BYTE					bncommand
){
	BYTE					bnsize;
	ATOMIC					atomic;

	//	Open
	OFW_DRIVER_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskCMD|REGISTER_stcbcMaskCLK;
	if(st.eHighSpeed)stWaitUpHS();
	else stWaitUp();
	//	0
	*lpbreturn=stbReadBYTE(0x01);
	OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();
	lpbreturn++;
	//	1
	if(bncommand){
		*lpbreturn=stbReadBYTE(*lpcbcommand);
		lpcbcommand++;
		bncommand--;
	}else{
		*lpbreturn=stbReadBYTE(0x42);
	}
	bnsize=(((*lpbreturn-1)&0x0f)<<1)+2;
	lpbreturn++;
	//	2
	if(bncommand){
		*lpbreturn=stbReadBYTE(*lpcbcommand);
		lpcbcommand++;
		bncommand--;
	}else{
		*lpbreturn=stbReadBYTE(0x00);
	}
	lpbreturn++;
	//	3~
	while(1<bnsize){
		if(bncommand){
			*lpbreturn=stbReadBYTE(*lpcbcommand);
			lpcbcommand++;
			bncommand--;
		}else{
			*lpbreturn=stbReadBYTE(0x00);
		}
		lpbreturn++;
		bnsize--;
	}
	OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();
	//	Last
	if(bncommand)*lpbreturn=stbReadBYTE_NoACK(*lpcbcommand);
	else *lpbreturn=stbReadBYTE_NoACK(0x00);
	//	Close
	OFW_DRIVER_PS_REGISTER_PORT=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskCMD|REGISTER_stcbcMaskSEL|REGISTER_stcbcMaskCLK;
	return;
}

BYTE					PS::stbReadBYTE(
	BYTE					bccommand
){
	BYTE					breturn;

	if(!st.eHighSpeed){
		breturn=stbReadBYTE_Body(bccommand);
		stWaitACK();
	}else{
		breturn=stbReadBYTE_BodyHS(bccommand);
		stWaitACKHS();
	}
	return breturn;
}

BYTE					PS::stbReadBYTE_NoACK(
	BYTE					bccommand
){
	if(!st.eHighSpeed)return stbReadBYTE_Body(bccommand);
	else return stbReadBYTE_BodyHS(bccommand);
}

BYTE					PS::stbReadBYTE_Body(
	BYTE					bccommand
){
	BYTE					breturn=0;

	stWaitClock();
	for(BYTE i=0;i<8;++i){
		BYTE					bcout;

		//	CLK:0
		if(bccommand&1)bcout=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskCMD;
		else bcout=REGISTER_stcbcPORTDefault;
		OFW_DRIVER_PS_REGISTER_PORT=bcout;
		bccommand>>=1;
		stWaitClockAdjust();
		//	CLK:1
		stWaitClock();
		OFW_DRIVER_PS_REGISTER_PORT=bcout|REGISTER_stcbcMaskCLK;
		breturn>>=1;
		stWaitClock();
		breturn|=(OFW_DRIVER_PS_REGISTER_PIN&REGISTER_stcbcMaskDAT)<<(7-REGISTER_stcbiBitDAT);
	}
	return breturn;
}

BYTE					PS::stbReadBYTE_BodyHS(
	BYTE					bccommand
){
	BYTE					breturn=0;

	stWaitClockHS();
	for(BYTE i=0;i<8;++i){
		BYTE					bcout;

		//	CLK:0
		if(bccommand&1)bcout=REGISTER_stcbcPORTDefault|REGISTER_stcbcMaskCMD;
		else bcout=REGISTER_stcbcPORTDefault;
		OFW_DRIVER_PS_REGISTER_PORT=bcout;
		bccommand>>=1;
		stWaitClockAdjust();
		//	CLK:1
		stWaitClockHS();
		OFW_DRIVER_PS_REGISTER_PORT=bcout|REGISTER_stcbcMaskCLK;
		breturn>>=1;
		stWaitClockHS();
		breturn|=(OFW_DRIVER_PS_REGISTER_PIN&REGISTER_stcbcMaskDAT)<<(7-REGISTER_stcbiBitDAT);
	}
	return breturn;
}

VOID					PS::stWaitClockAdjust(VOID){
	OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();
	return;
}

VOID					PS::stWaitClock(VOID){
	OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();OFW::stNOP();
	return;
}

VOID					PS::New_Local(VOID){
	idTransition=IDTransition_None;
	idDevice=IDDevice_None;
	//	READ_DATA_AND_VIBRATE_EX
	//	CMD=01,42,00,WW,PP(,00,00,00,00)
	//	DAT=--,ID,SS,XX,XX(,XX,XX,XX,XX)
	arbcCommand[0]=0x42;
	arbcCommand[1]=0x00;
	arbcCommand[2]=0x00;
	arbcCommand[3]=0x00;
	biMotorSLength=0x00;
	biMotorLLength=0x00;
	return;
}

VOID					PS::Delete_Local(VOID){
	return;
}
