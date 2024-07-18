/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	ofw												2024 written by int71	**
 ****************************************************************************/

//
//		include
//

#include				"ofw.hpp"

//
//		class:OFW
//

VOID					OFW::stFill(
	LPVOID					lpthis,
	SIZE					sznthis,
	BYTE					bfill
){
	SIZE					szicurrent;

	for(szicurrent=0;szicurrent<sznthis;szicurrent++)((LPBYTE)lpthis)[szicurrent]=bfill;
	return;
}

VOID					OFW::stCopy(
	LPVOID					lpthis,
	LPCVOID					lpcsource,
	SIZE					sznsource
){
	SIZE					szicurrent;

	for(szicurrent=0;szicurrent<sznsource;szicurrent++)((LPBYTE)lpthis)[szicurrent]=((LPCBYTE)lpcsource)[szicurrent];
	return;
}

VOID					OFW::stCopy(
	LPVOID					lpthis,
	LPGVOID					lpgsource,
	SIZE					sznsource
){
	SIZE					szicurrent;

	for(szicurrent=0;szicurrent<sznsource;szicurrent++)((LPBYTE)lpthis)[szicurrent]=lpgsource[szicurrent];
	return;
}

VOID					OFW::stWait(
	WORD					wnmsec
){
   for(;wnmsec;wnmsec--){
		__volatile__ WORD		wicount;

		for(wicount=0;wicount<(
			+stcdwnClockKHz/20
			+stcdwnClockKHz/800
			+stcdwnClockKHz/1600
			+stcdwnClockKHz/3200
			+stcdwnClockKHz/3200
		);wicount++);
   }
   return;
}
