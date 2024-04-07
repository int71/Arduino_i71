/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	driver/ps										2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw_device_pin.hpp>

//
//		namespace:ofw
//

namespace ofw{

	//
	//		namespace:driver
	//

	namespace driver{

		//
		//		class
		//

		class PS;
		typedef const PS		CPS;
		typedef PS*				LPPS;
		typedef CPS*			LPCPS;

		//
		//		class:PS
		//

		class PS{
		public:

			//
			//		const
			//

			//	TRANSITION
			enum IDTRANSITION{
				IDTransition_None,
				IDTransition_CheckSpeed,
				IDTransition_NS_Initialize,
				IDTransition_NS_SetAnalog0,
				IDTransition_NS_SetAnalog1,
				IDTransition_NS_SetAnalog2,
				IDTransition_NS_SetAnalog3_0,
				IDTransition_NS_SetAnalog3_1,
				IDTransition_NS_SetAnalog3_2,
				IDTransition_NS_SetAnalog3_3,
				IDTransition_NS_SetAnalog4,
				IDTransition_NS_Digital,
				IDTransition_NS_neGcon,
				IDTransition_NS_DUALSHOCK,
				IDTransition_HS_Initialize,
				IDTransition_HS_SetAnalog0,
				IDTransition_HS_SetAnalog1,
				IDTransition_HS_SetAnalog2,
				IDTransition_HS_SetAnalog3_0,
				IDTransition_HS_SetAnalog3_1,
				IDTransition_HS_SetAnalog3_2,
				IDTransition_HS_SetAnalog3_3,
				IDTransition_HS_SetAnalog4_0,
				IDTransition_HS_SetAnalog4_1,
				IDTransition_HS_SetAnalog4_2,
				IDTransition_HS_SetAnalog4_3,
				IDTransition_HS_SetAnalog5,
				IDTransition_HS_Digital,
				IDTransition_HS_neGconPlus,
				IDTransition_HS_DUALSHOCK2
			};
			//	DEVICE
			enum IDDEVICE{
				IDDevice_None			=0x00,
				IDDevice_NS_Initialize	=0x01,
				IDDevice_NS_Digital		=0x02,
				IDDevice_NS_neGcon		=0x03,
				IDDevice_NS_DUALSHOCK	=0x04,
				IDDevice_HS_Initialize	=0x08+0x01,
				IDDevice_HS_Digital		=0x08+0x02,
				IDDevice_HS_neGconPlus	=0x08+0x03,
				IDDevice_HS_DUALSHOCK2	=0x08+0x04
			};
			//	REGISTER
			#define OFW_DRIVER_PS_REGISTER_DDR	DDRF
			#define OFW_DRIVER_PS_REGISTER_PORT	PORTF
			#define OFW_DRIVER_PS_REGISTER_PIN	PINF
			static CBYTE			REGISTER_stcbiBitDAT=7;
			static CBYTE			REGISTER_stcbcMaskDAT=1<<REGISTER_stcbiBitDAT;
			static CBYTE			REGISTER_stcbiBitCMD=6;
			static CBYTE			REGISTER_stcbcMaskCMD=1<<REGISTER_stcbiBitCMD;
			static CBYTE			REGISTER_stcbiBitSEL=5;
			static CBYTE			REGISTER_stcbcMaskSEL=1<<REGISTER_stcbiBitSEL;
			static CBYTE			REGISTER_stcbiBitCLK=4;
			static CBYTE			REGISTER_stcbcMaskCLK=1<<REGISTER_stcbiBitCLK;
			static CBYTE			REGISTER_stcbcPORTDefault=0x00;

			//
			//		class
			//

			//	READ
			class READ;
			typedef const READ		CREAD;
			typedef READ*			LPREAD;
			typedef CREAD*			LPCREAD;
			//	ST
			class ST;
			typedef const ST		CST;
			typedef ST*				LPST;
			typedef CST*			LPCST;

			//
			//		class:READ
			//

			class READ{
			public:
				BYTE					bUnknown;
				union{
					struct{
						BYTE					bcType;
						BYTE					bcCheck;
					};
					WORD					wcID;
				};
				union{
					struct{
						BYTE					arbcData[32];
					}UNKNOWN;
					struct{
						BYTE					eButtonSelect:1;
						BYTE					_padding0:2;
						BYTE					eButtonStart:1;
						BYTE					eButtonUp:1;
						BYTE					eButtonRight:1;
						BYTE					eButtonDown:1;
						BYTE					eButtonLeft:1;
						BYTE					eButtonL2:1;
						BYTE					eButtonR2:1;
						BYTE					eButtonL1:1;
						BYTE					eButtonR1:1;
						BYTE					eButtonTriangle:1;
						BYTE					eButtonCircle:1;
						BYTE					eButtonCross:1;
						BYTE					eButtonSquare:1;
					}DIGITAL;
					struct{
						BYTE					_padding0:3;
						BYTE					eButtonStart:1;
						BYTE					eButtonUp:1;
						BYTE					eButtonRight:1;
						BYTE					eButtonDown:1;
						BYTE					eButtonLeft:1;
						BYTE					_padding1:3;
						BYTE					eButtonR:1;
						BYTE					eButtonB:1;
						BYTE					eButtonA:1;
						BYTE					_padding2:2;
						BYTE					biAxisSteering;
						BYTE					biButtonI;
						BYTE					biButtonII;
						BYTE					biButtonL;
					}NEGCON;
					struct{
						BYTE					_padding0:3;
						BYTE					eButtonStart:1;
						BYTE					eButtonUp:1;
						BYTE					eButtonRight:1;
						BYTE					eButtonDown:1;
						BYTE					eButtonLeft:1;
						BYTE					_padding1:3;
						BYTE					eButtonR:1;
						BYTE					eButtonB:1;
						BYTE					eButtonA:1;
						BYTE					_padding2:2;
						WORD					wiAxisSteering;
						WORD					wiButtonI;
						WORD					wiButtonII;
						WORD					wiButtonL;
					}NEGCONPLUS;
					struct{
						BYTE					eButtonSelect:1;
						BYTE					eButtonL3:1;
						BYTE					eButtonR3:1;
						BYTE					eButtonStart:1;
						BYTE					eButtonUp:1;
						BYTE					eButtonRight:1;
						BYTE					eButtonDown:1;
						BYTE					eButtonLeft:1;
						BYTE					eButtonL2:1;
						BYTE					eButtonR2:1;
						BYTE					eButtonL1:1;
						BYTE					eButtonR1:1;
						BYTE					eButtonTriangle:1;
						BYTE					eButtonCircle:1;
						BYTE					eButtonCross:1;
						BYTE					eButtonSquare:1;
						BYTE					biAxisRX;
						BYTE					biAxisRY;
						BYTE					biAxisLX;
						BYTE					biAxisLY;
					}DUALSHOCK;
					struct{
						BYTE					eButtonSelect:1;
						BYTE					eButtonL3:1;
						BYTE					eButtonR3:1;
						BYTE					eButtonStart:1;
						BYTE					eButtonUp:1;
						BYTE					eButtonRight:1;
						BYTE					eButtonDown:1;
						BYTE					eButtonLeft:1;
						BYTE					eButtonL2:1;
						BYTE					eButtonR2:1;
						BYTE					eButtonL1:1;
						BYTE					eButtonR1:1;
						BYTE					eButtonTriangle:1;
						BYTE					eButtonCircle:1;
						BYTE					eButtonCross:1;
						BYTE					eButtonSquare:1;
						BYTE					biAxisRX;
						BYTE					biAxisRY;
						BYTE					biAxisLX;
						BYTE					biAxisLY;
						BYTE					biButtonRight;
						BYTE					biButtonLeft;
						BYTE					biButtonUp;
						BYTE					biButtonDown;
						BYTE					biButtonTriangle;
						BYTE					biButtonCircle;
						BYTE					biButtonCross;
						BYTE					biButtonSquare;
						BYTE					biButtonL1;
						BYTE					biButtonR1;
						BYTE					biButtonL2;
						BYTE					biButtonR2;
					}DUALSHOCK2;
				};
			};

			//
			//		class:ST
			//

			class ST{
			public:
				BYTE					bnInstance;
				BYTE					eHighSpeed:1;
			public:
				/* VOID */				ST(VOID):
					bnInstance(0)
				{}
			};

			//
			//		body:PS
			//

		private:
			static ST				st;
			IDTRANSITION			idTransition;
			IDDEVICE				idDevice;
			BYTE					arbcCommand[4];
			READ					readThis;
			BYTE					biMotorSLength;
			BYTE					biMotorLLength;
		public:
			VOID					New(VOID);
			VOID					Delete(VOID);
			VOID					Main(VOID);
			INLINE IDTRANSITION		idGetTransition(VOID){
				return idTransition;
			}
			INLINE IDDEVICE			idGetDevice(VOID){
				return idDevice;
			}
			INLINE CREAD&			creadDelegateThis(VOID){
				return readThis;
			}
			INLINE VOID				SetRumbleS(BYTE bnstrength,BYTE bnlength){	//	bnstrength:0~1
				arbcCommand[2]=bnstrength;
				biMotorSLength=bnlength;
				return;
			}
			INLINE VOID				SetRumbleL(BYTE bnstrength,BYTE bnlength){	//	bnstrength:0~255
				arbcCommand[3]=bnstrength;
				biMotorLLength=bnlength;
				return;
			}
		private:
			static VOID				stNew_Local(VOID);
			static VOID				stDelete_Local(VOID);
			static INLINE VOID		stSetHS(BOOL ehighspeed){
				st.eHighSpeed=ehighspeed;
				return;
			}
			static VOID				stRead(LPBYTE lpbreturn,LPCBYTE lpcbcommand,BYTE bncommand);
			static BYTE				stbReadBYTE(BYTE bccommand);
			static BYTE				stbReadBYTE_NoACK(BYTE bccommand);
			static BYTE				stbReadBYTE_Body(BYTE bccommand);
			static BYTE				stbReadBYTE_BodyHS(BYTE bccommand);
			static INLINE VOID		stWaitUp(VOID){
				OFW::stWaitFine(24);
				return;
			}
			static INLINE VOID		stWaitUpHS(VOID){
				OFW::stWaitFine(12);
				return;
			}
			static VOID				stWaitClockAdjust(VOID);
			static VOID				stWaitClock(VOID);
			static INLINE VOID		stWaitClockHS(VOID){
				return;
			}
			static INLINE VOID		stWaitACK(VOID){
				OFW::stWaitFine(20);
				return;
			}
			static INLINE VOID		stWaitACKHS(VOID){
				OFW::stWaitFine(8);
				return;
			}
			VOID					New_Local(VOID);
			VOID					Delete_Local(VOID);
			INLINE VOID				Read(LPCBYTE lpcbcommand,BYTE bncommand){
				stRead((LPBYTE)&readThis,lpcbcommand,bncommand);
				return;
			}
		};
	}
}
