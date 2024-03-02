/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	device/pin										2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<ofw.hpp>

//
//		namespace:ofw
//

namespace ofw{

	//
	//		namespace:device
	//

	namespace device{

		//
		//		macro
		//

		#define OFW_DEVICE_PIN_SetIn(ddr,port,pin,biposition)	(ddr&=~(1<<biposition),port&=~(1<<biposition))
		#define OFW_DEVICE_PIN_SetInPU(ddr,port,pin,biposition)	(ddr&=~(1<<biposition),port|=(1<<biposition))
		#define OFW_DEVICE_PIN_SetOut(ddr,port,pin,biposition)	(ddr|=(1<<biposition))
		#define OFW_DEVICE_PIN_bIn(ddr,port,pin,biposition)	((pin>>biposition)&1)
		#define OFW_DEVICE_PIN_Out(ddr,port,pin,biposition,value)	(port=(port&~(1<<biposition))|(value<<biposition))
		#define OFW_DEVICE_PIN_OutH(ddr,port,pin,biposition)	(port|=(1<<biposition))
		#define OFW_DEVICE_PIN_OutL(ddr,port,pin,biposition)	(port&=~(1<<biposition))

		//
		//		class
		//

		//
		//		class:PIN
		//

		class PIN{
		public:
		#if defined(ARDUINO_AVR_MEGA2560)||defined(ARDUINO_AVR_MEGA)||defined(ARDUINO_AVR_ADK)
			static INLINE VOID		stSetIn_D0(VOID){		OFW_DEVICE_PIN_SetIn(DDRE,PORTE,PINE,0);return;}
			static INLINE VOID		stSetIn_D1(VOID){		OFW_DEVICE_PIN_SetIn(DDRE,PORTE,PINE,1);return;}
			static INLINE VOID		stSetIn_D2(VOID){		OFW_DEVICE_PIN_SetIn(DDRE,PORTE,PINE,4);return;}
			static INLINE VOID		stSetIn_D3(VOID){		OFW_DEVICE_PIN_SetIn(DDRE,PORTE,PINE,5);return;}
			static INLINE VOID		stSetIn_D4(VOID){		OFW_DEVICE_PIN_SetIn(DDRG,PORTG,PING,5);return;}
			static INLINE VOID		stSetIn_D5(VOID){		OFW_DEVICE_PIN_SetIn(DDRE,PORTE,PINE,3);return;}
			static INLINE VOID		stSetIn_D6(VOID){		OFW_DEVICE_PIN_SetIn(DDRH,PORTH,PINH,3);return;}
			static INLINE VOID		stSetIn_D7(VOID){		OFW_DEVICE_PIN_SetIn(DDRH,PORTH,PINH,4);return;}
			static INLINE VOID		stSetIn_D8(VOID){		OFW_DEVICE_PIN_SetIn(DDRH,PORTH,PINH,5);return;}
			static INLINE VOID		stSetIn_D9(VOID){		OFW_DEVICE_PIN_SetIn(DDRH,PORTH,PINH,6);return;}
			static INLINE VOID		stSetIn_D10(VOID){		OFW_DEVICE_PIN_SetIn(DDRB,PORTB,PINB,4);return;}
			static INLINE VOID		stSetIn_D11(VOID){		OFW_DEVICE_PIN_SetIn(DDRB,PORTB,PINB,5);return;}
			static INLINE VOID		stSetIn_D12(VOID){		OFW_DEVICE_PIN_SetIn(DDRB,PORTB,PINB,6);return;}
			static INLINE VOID		stSetIn_D13(VOID){		OFW_DEVICE_PIN_SetIn(DDRB,PORTB,PINB,7);return;}
			static INLINE VOID		stSetInPU_D0(VOID){		OFW_DEVICE_PIN_SetInPU(DDRE,PORTE,PINE,0);return;}
			static INLINE VOID		stSetInPU_D1(VOID){		OFW_DEVICE_PIN_SetInPU(DDRE,PORTE,PINE,1);return;}
			static INLINE VOID		stSetInPU_D2(VOID){		OFW_DEVICE_PIN_SetInPU(DDRE,PORTE,PINE,4);return;}
			static INLINE VOID		stSetInPU_D3(VOID){		OFW_DEVICE_PIN_SetInPU(DDRE,PORTE,PINE,5);return;}
			static INLINE VOID		stSetInPU_D4(VOID){		OFW_DEVICE_PIN_SetInPU(DDRG,PORTG,PING,5);return;}
			static INLINE VOID		stSetInPU_D5(VOID){		OFW_DEVICE_PIN_SetInPU(DDRE,PORTE,PINE,3);return;}
			static INLINE VOID		stSetInPU_D6(VOID){		OFW_DEVICE_PIN_SetInPU(DDRH,PORTH,PINH,3);return;}
			static INLINE VOID		stSetInPU_D7(VOID){		OFW_DEVICE_PIN_SetInPU(DDRH,PORTH,PINH,4);return;}
			static INLINE VOID		stSetInPU_D8(VOID){		OFW_DEVICE_PIN_SetInPU(DDRH,PORTH,PINH,5);return;}
			static INLINE VOID		stSetInPU_D9(VOID){		OFW_DEVICE_PIN_SetInPU(DDRH,PORTH,PINH,6);return;}
			static INLINE VOID		stSetInPU_D10(VOID){	OFW_DEVICE_PIN_SetInPU(DDRB,PORTB,PINB,4);return;}
			static INLINE VOID		stSetInPU_D11(VOID){	OFW_DEVICE_PIN_SetInPU(DDRB,PORTB,PINB,5);return;}
			static INLINE VOID		stSetInPU_D12(VOID){	OFW_DEVICE_PIN_SetInPU(DDRB,PORTB,PINB,6);return;}
			static INLINE VOID		stSetInPU_D13(VOID){	OFW_DEVICE_PIN_SetInPU(DDRB,PORTB,PINB,7);return;}
			static INLINE VOID		stSetOut_D0(VOID){		OFW_DEVICE_PIN_SetOut(DDRE,PORTE,PINE,0);return;}
			static INLINE VOID		stSetOut_D1(VOID){		OFW_DEVICE_PIN_SetOut(DDRE,PORTE,PINE,1);return;}
			static INLINE VOID		stSetOut_D2(VOID){		OFW_DEVICE_PIN_SetOut(DDRE,PORTE,PINE,4);return;}
			static INLINE VOID		stSetOut_D3(VOID){		OFW_DEVICE_PIN_SetOut(DDRE,PORTE,PINE,5);return;}
			static INLINE VOID		stSetOut_D4(VOID){		OFW_DEVICE_PIN_SetOut(DDRG,PORTG,PING,5);return;}
			static INLINE VOID		stSetOut_D5(VOID){		OFW_DEVICE_PIN_SetOut(DDRE,PORTE,PINE,3);return;}
			static INLINE VOID		stSetOut_D6(VOID){		OFW_DEVICE_PIN_SetOut(DDRH,PORTH,PINH,3);return;}
			static INLINE VOID		stSetOut_D7(VOID){		OFW_DEVICE_PIN_SetOut(DDRH,PORTH,PINH,4);return;}
			static INLINE VOID		stSetOut_D8(VOID){		OFW_DEVICE_PIN_SetOut(DDRH,PORTH,PINH,5);return;}
			static INLINE VOID		stSetOut_D9(VOID){		OFW_DEVICE_PIN_SetOut(DDRH,PORTH,PINH,6);return;}
			static INLINE VOID		stSetOut_D10(VOID){		OFW_DEVICE_PIN_SetOut(DDRB,PORTB,PINB,4);return;}
			static INLINE VOID		stSetOut_D11(VOID){		OFW_DEVICE_PIN_SetOut(DDRB,PORTB,PINB,5);return;}
			static INLINE VOID		stSetOut_D12(VOID){		OFW_DEVICE_PIN_SetOut(DDRB,PORTB,PINB,6);return;}
			static INLINE VOID		stSetOut_D13(VOID){		OFW_DEVICE_PIN_SetOut(DDRB,PORTB,PINB,7);return;}
			static INLINE BYTE		stbIn_D0(VOID){			return OFW_DEVICE_PIN_bIn(DDRE,PORTE,PINE,0);}
			static INLINE BYTE		stbIn_D1(VOID){			return OFW_DEVICE_PIN_bIn(DDRE,PORTE,PINE,1);}
			static INLINE BYTE		stbIn_D2(VOID){			return OFW_DEVICE_PIN_bIn(DDRE,PORTE,PINE,4);}
			static INLINE BYTE		stbIn_D3(VOID){			return OFW_DEVICE_PIN_bIn(DDRE,PORTE,PINE,5);}
			static INLINE BYTE		stbIn_D4(VOID){			return OFW_DEVICE_PIN_bIn(DDRG,PORTG,PING,5);}
			static INLINE BYTE		stbIn_D5(VOID){			return OFW_DEVICE_PIN_bIn(DDRE,PORTE,PINE,3);}
			static INLINE BYTE		stbIn_D6(VOID){			return OFW_DEVICE_PIN_bIn(DDRH,PORTH,PINH,3);}
			static INLINE BYTE		stbIn_D7(VOID){			return OFW_DEVICE_PIN_bIn(DDRH,PORTH,PINH,4);}
			static INLINE BYTE		stbIn_D8(VOID){			return OFW_DEVICE_PIN_bIn(DDRH,PORTH,PINH,5);}
			static INLINE BYTE		stbIn_D9(VOID){			return OFW_DEVICE_PIN_bIn(DDRH,PORTH,PINH,6);}
			static INLINE BYTE		stbIn_D10(VOID){		return OFW_DEVICE_PIN_bIn(DDRB,PORTB,PINB,4);}
			static INLINE BYTE		stbIn_D11(VOID){		return OFW_DEVICE_PIN_bIn(DDRB,PORTB,PINB,5);}
			static INLINE BYTE		stbIn_D12(VOID){		return OFW_DEVICE_PIN_bIn(DDRB,PORTB,PINB,6);}
			static INLINE BYTE		stbIn_D13(VOID){		return OFW_DEVICE_PIN_bIn(DDRB,PORTB,PINB,7);}
			static INLINE BYTE		stOut_D0(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRE,PORTE,PINE,0,bvalue);return;}
			static INLINE BYTE		stOut_D1(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRE,PORTE,PINE,1,bvalue);return;}
			static INLINE BYTE		stOut_D2(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRE,PORTE,PINE,4,bvalue);return;}
			static INLINE BYTE		stOut_D3(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRE,PORTE,PINE,5,bvalue);return;}
			static INLINE BYTE		stOut_D4(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRG,PORTG,PING,5,bvalue);return;}
			static INLINE BYTE		stOut_D5(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRE,PORTE,PINE,3,bvalue);return;}
			static INLINE BYTE		stOut_D6(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRH,PORTH,PINH,3,bvalue);return;}
			static INLINE BYTE		stOut_D7(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRH,PORTH,PINH,4,bvalue);return;}
			static INLINE BYTE		stOut_D8(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRH,PORTH,PINH,5,bvalue);return;}
			static INLINE BYTE		stOut_D9(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRH,PORTH,PINH,6,bvalue);return;}
			static INLINE BYTE		stOut_D10(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRB,PORTB,PINB,4,bvalue);return;}
			static INLINE BYTE		stOut_D11(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRB,PORTB,PINB,5,bvalue);return;}
			static INLINE BYTE		stOut_D12(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRB,PORTB,PINB,6,bvalue);return;}
			static INLINE BYTE		stOut_D13(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRB,PORTB,PINB,7,bvalue);return;}
			static INLINE BYTE		stOutH_D0(VOID){		OFW_DEVICE_PIN_OutH(DDRE,PORTE,PINE,0);return;}
			static INLINE BYTE		stOutH_D1(VOID){		OFW_DEVICE_PIN_OutH(DDRE,PORTE,PINE,1);return;}
			static INLINE BYTE		stOutH_D2(VOID){		OFW_DEVICE_PIN_OutH(DDRE,PORTE,PINE,4);return;}
			static INLINE BYTE		stOutH_D3(VOID){		OFW_DEVICE_PIN_OutH(DDRE,PORTE,PINE,5);return;}
			static INLINE BYTE		stOutH_D4(VOID){		OFW_DEVICE_PIN_OutH(DDRG,PORTG,PING,5);return;}
			static INLINE BYTE		stOutH_D5(VOID){		OFW_DEVICE_PIN_OutH(DDRE,PORTE,PINE,3);return;}
			static INLINE BYTE		stOutH_D6(VOID){		OFW_DEVICE_PIN_OutH(DDRH,PORTH,PINH,3);return;}
			static INLINE BYTE		stOutH_D7(VOID){		OFW_DEVICE_PIN_OutH(DDRH,PORTH,PINH,4);return;}
			static INLINE BYTE		stOutH_D8(VOID){		OFW_DEVICE_PIN_OutH(DDRH,PORTH,PINH,5);return;}
			static INLINE BYTE		stOutH_D9(VOID){		OFW_DEVICE_PIN_OutH(DDRH,PORTH,PINH,6);return;}
			static INLINE BYTE		stOutH_D10(VOID){		OFW_DEVICE_PIN_OutH(DDRB,PORTB,PINB,4);return;}
			static INLINE BYTE		stOutH_D11(VOID){		OFW_DEVICE_PIN_OutH(DDRB,PORTB,PINB,5);return;}
			static INLINE BYTE		stOutH_D12(VOID){		OFW_DEVICE_PIN_OutH(DDRB,PORTB,PINB,6);return;}
			static INLINE BYTE		stOutH_D13(VOID){		OFW_DEVICE_PIN_OutH(DDRB,PORTB,PINB,7);return;}
			static INLINE BYTE		stOutL_D0(VOID){		OFW_DEVICE_PIN_OutL(DDRE,PORTE,PINE,0);return;}
			static INLINE BYTE		stOutL_D1(VOID){		OFW_DEVICE_PIN_OutL(DDRE,PORTE,PINE,1);return;}
			static INLINE BYTE		stOutL_D2(VOID){		OFW_DEVICE_PIN_OutL(DDRE,PORTE,PINE,4);return;}
			static INLINE BYTE		stOutL_D3(VOID){		OFW_DEVICE_PIN_OutL(DDRE,PORTE,PINE,5);return;}
			static INLINE BYTE		stOutL_D4(VOID){		OFW_DEVICE_PIN_OutL(DDRG,PORTG,PING,5);return;}
			static INLINE BYTE		stOutL_D5(VOID){		OFW_DEVICE_PIN_OutL(DDRE,PORTE,PINE,3);return;}
			static INLINE BYTE		stOutL_D6(VOID){		OFW_DEVICE_PIN_OutL(DDRH,PORTH,PINH,3);return;}
			static INLINE BYTE		stOutL_D7(VOID){		OFW_DEVICE_PIN_OutL(DDRH,PORTH,PINH,4);return;}
			static INLINE BYTE		stOutL_D8(VOID){		OFW_DEVICE_PIN_OutL(DDRH,PORTH,PINH,5);return;}
			static INLINE BYTE		stOutL_D9(VOID){		OFW_DEVICE_PIN_OutL(DDRH,PORTH,PINH,6);return;}
			static INLINE BYTE		stOutL_D10(VOID){		OFW_DEVICE_PIN_OutL(DDRB,PORTB,PINB,4);return;}
			static INLINE BYTE		stOutL_D11(VOID){		OFW_DEVICE_PIN_OutL(DDRB,PORTB,PINB,5);return;}
			static INLINE BYTE		stOutL_D12(VOID){		OFW_DEVICE_PIN_OutL(DDRB,PORTB,PINB,6);return;}
			static INLINE BYTE		stOutL_D13(VOID){		OFW_DEVICE_PIN_OutL(DDRB,PORTB,PINB,7);return;}
		#else
			static INLINE VOID		stSetIn_D0(VOID){		OFW_DEVICE_PIN_SetIn(DDRD,PORTD,PIND,0);return;}
			static INLINE VOID		stSetIn_D1(VOID){		OFW_DEVICE_PIN_SetIn(DDRD,PORTD,PIND,1);return;}
			static INLINE VOID		stSetIn_D2(VOID){		OFW_DEVICE_PIN_SetIn(DDRD,PORTD,PIND,2);return;}
			static INLINE VOID		stSetIn_D3(VOID){		OFW_DEVICE_PIN_SetIn(DDRD,PORTD,PIND,3);return;}
			static INLINE VOID		stSetIn_D4(VOID){		OFW_DEVICE_PIN_SetIn(DDRD,PORTD,PIND,4);return;}
			static INLINE VOID		stSetIn_D5(VOID){		OFW_DEVICE_PIN_SetIn(DDRD,PORTD,PIND,5);return;}
			static INLINE VOID		stSetIn_D6(VOID){		OFW_DEVICE_PIN_SetIn(DDRD,PORTD,PIND,6);return;}
			static INLINE VOID		stSetIn_D7(VOID){		OFW_DEVICE_PIN_SetIn(DDRD,PORTD,PIND,7);return;}
			static INLINE VOID		stSetIn_D8(VOID){		OFW_DEVICE_PIN_SetIn(DDRB,PORTB,PINB,0);return;}
			static INLINE VOID		stSetIn_D9(VOID){		OFW_DEVICE_PIN_SetIn(DDRB,PORTB,PINB,1);return;}
			static INLINE VOID		stSetIn_D10(VOID){		OFW_DEVICE_PIN_SetIn(DDRB,PORTB,PINB,2);return;}
			static INLINE VOID		stSetIn_D11(VOID){		OFW_DEVICE_PIN_SetIn(DDRB,PORTB,PINB,3);return;}
			static INLINE VOID		stSetIn_D12(VOID){		OFW_DEVICE_PIN_SetIn(DDRB,PORTB,PINB,4);return;}
			static INLINE VOID		stSetIn_D13(VOID){		OFW_DEVICE_PIN_SetIn(DDRB,PORTB,PINB,5);return;}
			static INLINE VOID		stSetInPU_D0(VOID){		OFW_DEVICE_PIN_SetInPU(DDRD,PORTD,PIND,0);return;}
			static INLINE VOID		stSetInPU_D1(VOID){		OFW_DEVICE_PIN_SetInPU(DDRD,PORTD,PIND,1);return;}
			static INLINE VOID		stSetInPU_D2(VOID){		OFW_DEVICE_PIN_SetInPU(DDRD,PORTD,PIND,2);return;}
			static INLINE VOID		stSetInPU_D3(VOID){		OFW_DEVICE_PIN_SetInPU(DDRD,PORTD,PIND,3);return;}
			static INLINE VOID		stSetInPU_D4(VOID){		OFW_DEVICE_PIN_SetInPU(DDRD,PORTD,PIND,4);return;}
			static INLINE VOID		stSetInPU_D5(VOID){		OFW_DEVICE_PIN_SetInPU(DDRD,PORTD,PIND,5);return;}
			static INLINE VOID		stSetInPU_D6(VOID){		OFW_DEVICE_PIN_SetInPU(DDRD,PORTD,PIND,6);return;}
			static INLINE VOID		stSetInPU_D7(VOID){		OFW_DEVICE_PIN_SetInPU(DDRD,PORTD,PIND,7);return;}
			static INLINE VOID		stSetInPU_D8(VOID){		OFW_DEVICE_PIN_SetInPU(DDRB,PORTB,PINB,0);return;}
			static INLINE VOID		stSetInPU_D9(VOID){		OFW_DEVICE_PIN_SetInPU(DDRB,PORTB,PINB,1);return;}
			static INLINE VOID		stSetInPU_D10(VOID){	OFW_DEVICE_PIN_SetInPU(DDRB,PORTB,PINB,2);return;}
			static INLINE VOID		stSetInPU_D11(VOID){	OFW_DEVICE_PIN_SetInPU(DDRB,PORTB,PINB,3);return;}
			static INLINE VOID		stSetInPU_D12(VOID){	OFW_DEVICE_PIN_SetInPU(DDRB,PORTB,PINB,4);return;}
			static INLINE VOID		stSetInPU_D13(VOID){	OFW_DEVICE_PIN_SetInPU(DDRB,PORTB,PINB,5);return;}
			static INLINE VOID		stSetOut_D0(VOID){		OFW_DEVICE_PIN_SetOut(DDRD,PORTD,PIND,0);return;}
			static INLINE VOID		stSetOut_D1(VOID){		OFW_DEVICE_PIN_SetOut(DDRD,PORTD,PIND,1);return;}
			static INLINE VOID		stSetOut_D2(VOID){		OFW_DEVICE_PIN_SetOut(DDRD,PORTD,PIND,2);return;}
			static INLINE VOID		stSetOut_D3(VOID){		OFW_DEVICE_PIN_SetOut(DDRD,PORTD,PIND,3);return;}
			static INLINE VOID		stSetOut_D4(VOID){		OFW_DEVICE_PIN_SetOut(DDRD,PORTD,PIND,4);return;}
			static INLINE VOID		stSetOut_D5(VOID){		OFW_DEVICE_PIN_SetOut(DDRD,PORTD,PIND,5);return;}
			static INLINE VOID		stSetOut_D6(VOID){		OFW_DEVICE_PIN_SetOut(DDRD,PORTD,PIND,6);return;}
			static INLINE VOID		stSetOut_D7(VOID){		OFW_DEVICE_PIN_SetOut(DDRD,PORTD,PIND,7);return;}
			static INLINE VOID		stSetOut_D8(VOID){		OFW_DEVICE_PIN_SetOut(DDRB,PORTB,PINB,0);return;}
			static INLINE VOID		stSetOut_D9(VOID){		OFW_DEVICE_PIN_SetOut(DDRB,PORTB,PINB,1);return;}
			static INLINE VOID		stSetOut_D10(VOID){		OFW_DEVICE_PIN_SetOut(DDRB,PORTB,PINB,2);return;}
			static INLINE VOID		stSetOut_D11(VOID){		OFW_DEVICE_PIN_SetOut(DDRB,PORTB,PINB,3);return;}
			static INLINE VOID		stSetOut_D12(VOID){		OFW_DEVICE_PIN_SetOut(DDRB,PORTB,PINB,4);return;}
			static INLINE VOID		stSetOut_D13(VOID){		OFW_DEVICE_PIN_SetOut(DDRB,PORTB,PINB,5);return;}
			static INLINE BYTE		stbIn_D0(VOID){			return OFW_DEVICE_PIN_bIn(DDRD,PORTD,PIND,0);}
			static INLINE BYTE		stbIn_D1(VOID){			return OFW_DEVICE_PIN_bIn(DDRD,PORTD,PIND,1);}
			static INLINE BYTE		stbIn_D2(VOID){			return OFW_DEVICE_PIN_bIn(DDRD,PORTD,PIND,2);}
			static INLINE BYTE		stbIn_D3(VOID){			return OFW_DEVICE_PIN_bIn(DDRD,PORTD,PIND,3);}
			static INLINE BYTE		stbIn_D4(VOID){			return OFW_DEVICE_PIN_bIn(DDRD,PORTD,PIND,4);}
			static INLINE BYTE		stbIn_D5(VOID){			return OFW_DEVICE_PIN_bIn(DDRD,PORTD,PIND,5);}
			static INLINE BYTE		stbIn_D6(VOID){			return OFW_DEVICE_PIN_bIn(DDRD,PORTD,PIND,6);}
			static INLINE BYTE		stbIn_D7(VOID){			return OFW_DEVICE_PIN_bIn(DDRD,PORTD,PIND,7);}
			static INLINE BYTE		stbIn_D8(VOID){			return OFW_DEVICE_PIN_bIn(DDRB,PORTB,PINB,0);}
			static INLINE BYTE		stbIn_D9(VOID){			return OFW_DEVICE_PIN_bIn(DDRB,PORTB,PINB,1);}
			static INLINE BYTE		stbIn_D10(VOID){		return OFW_DEVICE_PIN_bIn(DDRB,PORTB,PINB,2);}
			static INLINE BYTE		stbIn_D11(VOID){		return OFW_DEVICE_PIN_bIn(DDRB,PORTB,PINB,3);}
			static INLINE BYTE		stbIn_D12(VOID){		return OFW_DEVICE_PIN_bIn(DDRB,PORTB,PINB,4);}
			static INLINE BYTE		stbIn_D13(VOID){		return OFW_DEVICE_PIN_bIn(DDRB,PORTB,PINB,5);}
			static INLINE BYTE		stOut_D0(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRD,PORTD,PIND,0,bvalue);return;}
			static INLINE BYTE		stOut_D1(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRD,PORTD,PIND,1,bvalue);return;}
			static INLINE BYTE		stOut_D2(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRD,PORTD,PIND,2,bvalue);return;}
			static INLINE BYTE		stOut_D3(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRD,PORTD,PIND,3,bvalue);return;}
			static INLINE BYTE		stOut_D4(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRD,PORTD,PIND,4,bvalue);return;}
			static INLINE BYTE		stOut_D5(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRD,PORTD,PIND,5,bvalue);return;}
			static INLINE BYTE		stOut_D6(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRD,PORTD,PIND,6,bvalue);return;}
			static INLINE BYTE		stOut_D7(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRD,PORTD,PIND,7,bvalue);return;}
			static INLINE BYTE		stOut_D8(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRB,PORTB,PINB,0,bvalue);return;}
			static INLINE BYTE		stOut_D9(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRB,PORTB,PINB,1,bvalue);return;}
			static INLINE BYTE		stOut_D10(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRB,PORTB,PINB,2,bvalue);return;}
			static INLINE BYTE		stOut_D11(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRB,PORTB,PINB,3,bvalue);return;}
			static INLINE BYTE		stOut_D12(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRB,PORTB,PINB,4,bvalue);return;}
			static INLINE BYTE		stOut_D13(BYTE bvalue){	OFW_DEVICE_PIN_Out(DDRB,PORTB,PINB,5,bvalue);return;}
			static INLINE BYTE		stOutH_D0(VOID){		OFW_DEVICE_PIN_OutH(DDRD,PORTD,PIND,0);return;}
			static INLINE BYTE		stOutH_D1(VOID){		OFW_DEVICE_PIN_OutH(DDRD,PORTD,PIND,1);return;}
			static INLINE BYTE		stOutH_D2(VOID){		OFW_DEVICE_PIN_OutH(DDRD,PORTD,PIND,2);return;}
			static INLINE BYTE		stOutH_D3(VOID){		OFW_DEVICE_PIN_OutH(DDRD,PORTD,PIND,3);return;}
			static INLINE BYTE		stOutH_D4(VOID){		OFW_DEVICE_PIN_OutH(DDRD,PORTD,PIND,4);return;}
			static INLINE BYTE		stOutH_D5(VOID){		OFW_DEVICE_PIN_OutH(DDRD,PORTD,PIND,5);return;}
			static INLINE BYTE		stOutH_D6(VOID){		OFW_DEVICE_PIN_OutH(DDRD,PORTD,PIND,6);return;}
			static INLINE BYTE		stOutH_D7(VOID){		OFW_DEVICE_PIN_OutH(DDRD,PORTD,PIND,7);return;}
			static INLINE BYTE		stOutH_D8(VOID){		OFW_DEVICE_PIN_OutH(DDRB,PORTB,PINB,0);return;}
			static INLINE BYTE		stOutH_D9(VOID){		OFW_DEVICE_PIN_OutH(DDRB,PORTB,PINB,1);return;}
			static INLINE BYTE		stOutH_D10(VOID){		OFW_DEVICE_PIN_OutH(DDRB,PORTB,PINB,2);return;}
			static INLINE BYTE		stOutH_D11(VOID){		OFW_DEVICE_PIN_OutH(DDRB,PORTB,PINB,3);return;}
			static INLINE BYTE		stOutH_D12(VOID){		OFW_DEVICE_PIN_OutH(DDRB,PORTB,PINB,4);return;}
			static INLINE BYTE		stOutH_D13(VOID){		OFW_DEVICE_PIN_OutH(DDRB,PORTB,PINB,5);return;}
			static INLINE BYTE		stOutL_D0(VOID){		OFW_DEVICE_PIN_OutL(DDRD,PORTD,PIND,0);return;}
			static INLINE BYTE		stOutL_D1(VOID){		OFW_DEVICE_PIN_OutL(DDRD,PORTD,PIND,1);return;}
			static INLINE BYTE		stOutL_D2(VOID){		OFW_DEVICE_PIN_OutL(DDRD,PORTD,PIND,2);return;}
			static INLINE BYTE		stOutL_D3(VOID){		OFW_DEVICE_PIN_OutL(DDRD,PORTD,PIND,3);return;}
			static INLINE BYTE		stOutL_D4(VOID){		OFW_DEVICE_PIN_OutL(DDRD,PORTD,PIND,4);return;}
			static INLINE BYTE		stOutL_D5(VOID){		OFW_DEVICE_PIN_OutL(DDRD,PORTD,PIND,5);return;}
			static INLINE BYTE		stOutL_D6(VOID){		OFW_DEVICE_PIN_OutL(DDRD,PORTD,PIND,6);return;}
			static INLINE BYTE		stOutL_D7(VOID){		OFW_DEVICE_PIN_OutL(DDRD,PORTD,PIND,7);return;}
			static INLINE BYTE		stOutL_D8(VOID){		OFW_DEVICE_PIN_OutL(DDRB,PORTB,PINB,0);return;}
			static INLINE BYTE		stOutL_D9(VOID){		OFW_DEVICE_PIN_OutL(DDRB,PORTB,PINB,1);return;}
			static INLINE BYTE		stOutL_D10(VOID){		OFW_DEVICE_PIN_OutL(DDRB,PORTB,PINB,2);return;}
			static INLINE BYTE		stOutL_D11(VOID){		OFW_DEVICE_PIN_OutL(DDRB,PORTB,PINB,3);return;}
			static INLINE BYTE		stOutL_D12(VOID){		OFW_DEVICE_PIN_OutL(DDRB,PORTB,PINB,4);return;}
			static INLINE BYTE		stOutL_D13(VOID){		OFW_DEVICE_PIN_OutL(DDRB,PORTB,PINB,5);return;}
		#endif
		};
	}
}
