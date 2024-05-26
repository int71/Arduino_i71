/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	ofw												2024 written by int71	**
 ****************************************************************************/
#pragma once

//
//		include
//

#include				<Arduino.h>
#include				<avr/wdt.h>
#include				<avr/pgmspace.h>
#include				<avr/interrupt.h>

//
//		namespace:ofw
//

namespace ofw{

	//
	//		macro
	//

	#define offsetof(CLASS,MEMBER)	((INT)&(((CLASS*)0)->MEMBER))
	#define INLINE			__attribute__((always_inline))
	#if __BYTE_ORDER__==__ORDER_LITTLE_ENDIAN__
	#define LITTLE_ENDIAN
	#else
	#define BIG_ENDIAN
	#endif

	//
	//		managed
	//

	//	LPG
	template<class CLASS>class LPG;

	//
	//		primitive
	//

	//	SIZE
	typedef unsigned int	SIZE;
	typedef const SIZE		CSIZE;
	typedef SIZE*			LPSIZE;
	typedef CSIZE*			LPCSIZE;
	#define GSIZE			static PROGMEM CSIZE
	typedef LPG<SIZE>		LPGSIZE;
	typedef const LPGSIZE	CLPGSIZE;
	#define ARGSIZE(...)	(LPGSIZE)({GSIZE stargbtemp[]={__VA_ARGS__};stargbtemp;})
	//	BYTE
	typedef unsigned char	BYTE;
	typedef const BYTE		CBYTE;
	typedef BYTE*			LPBYTE;
	typedef CBYTE*			LPCBYTE;
	#define GBYTE			static PROGMEM CBYTE
	typedef LPG<BYTE>		LPGBYTE;
	typedef const LPGBYTE	CLPGBYTE;
	#define ARGBYTE(...)	(LPGBYTE)({GBYTE stargbtemp[]={__VA_ARGS__};stargbtemp;})
	//	BYTES
	typedef signed char		BYTES;
	typedef const BYTES		CBYTES;
	typedef BYTES*			LPBYTES;
	typedef CBYTES*			LPCBYTES;
	#define GBYTES			static PROGMEM CBYTES
	typedef LPG<BYTES>		LPGBYTES;
	typedef const LPGBYTES	CLPGBYTES;
	#define ARGBYTES(...)	(LPGBYTES)({GBYTES stargbstemp[]={__VA_ARGS__};stargbstemp;})
	//	BOOL
	typedef bool			BOOL;
	typedef const BOOL		CBOOL;
	typedef BOOL*			LPBOOL;
	typedef CBOOL*			LPCBOOL;
	#define GBOOL			static PROGMEM CBOOL
	typedef LPG<BOOL>		LPGBOOL;
	typedef const LPGBOOL	CLPGBOOL;
	static CBOOL			TRUE=true;
	static CBOOL			FALSE=false;
	#define ARGBOOL(...)	(LPGBOOL)({GBOOL stargetemp[]={__VA_ARGS__};stargetemp;})
	//	STR
	typedef char			STR;
	typedef const STR		CSTR;
	typedef STR*			LPSTR;
	typedef CSTR*			LPCSTR;
	#define GSTR			static PROGMEM CSTR
	typedef LPG<STR>		LPGSTR;
	typedef const LPGSTR	CLPGSTR;
	#define ARGSTR(argstrsource)	(LPGSTR)({GSTR stargstrtemp[]=(argstrsource);stargstrtemp;})
	//	VOID
	#define VOID			void
	typedef const VOID		CVOID;
	typedef VOID*			LPVOID;
	typedef CVOID*			LPCVOID;
	class LPGVOID;
	typedef const LPGVOID	CLPGVOID;
	//	WORD
	typedef unsigned short	WORD;
	typedef const WORD		CWORD;
	typedef WORD*			LPWORD;
	typedef CWORD*			LPCWORD;
	#define GWORD			static PROGMEM CWORD
	typedef LPG<WORD>		LPGWORD;
	typedef const LPGWORD	CLPGWORD;
	#define ARGWORD(...)	(LPGWORD)({GWORD stargwtemp[]={__VA_ARGS__};stargwtemp;})
	//	WORDS
	typedef signed short	WORDS;
	typedef const WORDS		CWORDS;
	typedef WORDS*			LPWORDS;
	typedef CWORDS*			LPCWORDS;
	#define GWORDS			static PROGMEM CWORDS
	typedef LPG<WORDS>		LPGWORDS;
	typedef const LPGWORDS	CLPGWORDS;
	#define ARGWORDS(...)	(LPGWORDS)({GWORDS stargwstemp[]={__VA_ARGS__};stargwstemp;})
	//	SHORT
	typedef short			SHORT;
	typedef const SHORT		CSHORT;
	typedef SHORT*			LPSHORT;
	typedef CSHORT*			LPCSHORT;
	#define GSHORT			static PROGMEM CSHORT
	typedef LPG<SHORT>		LPGSHORT;
	typedef const LPGSHORT	CLPGSHORT;
	#define ARGSHORT(...)	(LPGSHORT)({GSHORT stargstemp[]={__VA_ARGS__};stargstemp;})
	//	INT
	typedef int				INT;
	typedef const INT		CINT;
	typedef INT*			LPINT;
	typedef CINT*			LPCINT;
	#define GINT			static PROGMEM CINT
	typedef LPG<INT>		LPGINT;
	typedef const LPGINT	CLPGINT;
	#define ARGINT(...)		(LPGINT)({GINT stargitemp[]={__VA_ARGS__};stargitemp;})
	//	UINT
	typedef unsigned int	UINT;
	typedef const UINT		CUINT;
	typedef UINT*			LPUINT;
	typedef CUINT*			LPCUINT;
	#define GUINT			static PROGMEM CUINT
	typedef LPG<UINT>		LPGUINT;
	typedef const LPGUINT	CLPGUINT;
	#define ARGUINT(...)	(LPGUINT)({GUINT starguitemp[]={__VA_ARGS__};starguitemp;})
	//	PTRINT
	typedef WORD			PTRINT;
	typedef const PTRINT	CPTRINT;
	typedef PTRINT*			LPPTRINT;
	typedef CPTRINT*		LPCPTRINT;
	#define GPTRINT			static PROGMEM CPTRINT
	typedef LPG<PTRINT>		LPGPTRINT;
	typedef const LPGPTRINT	CLPGPTRINT;
	#define ARGPTRINT(...)	(LPGPTRINT)({GPTRINT stargpitemp[]={__VA_ARGS__};stargpitemp;})
	//	DWORD
	typedef unsigned long	DWORD;
	typedef const DWORD		CDWORD;
	typedef DWORD*			LPDWORD;
	typedef CDWORD*			LPCDWORD;
	#define GDWORD			static PROGMEM CDWORD
	typedef LPG<DWORD>		LPGDWORD;
	typedef const LPGDWORD	CLPGDWORD;
	#define ARGDWORD(...)	(LPGDWORD)({GDWORD stargdwtemp[]={__VA_ARGS__};stargdwtemp;})
	//	DWORDS
	typedef signed long		DWORDS;
	typedef const DWORDS	CDWORDS;
	typedef DWORDS*			LPDWORDS;
	typedef CDWORDS*		LPCDWORDS;
	#define GDWORDS			static PROGMEM CDWORDS
	typedef LPG<DWORDS>		LPGDWORDS;
	typedef const LPGDWORDS	CLPGDWORDS;
	#define ARGDWORDS(...)	(LPGDWORDS)({GDWORDS stargdwstemp[]={__VA_ARGS__};stargdwstemp;})
	//	LONG
	typedef long			LONG;
	typedef const LONG		CLONG;
	typedef LONG*			LPLONG;
	typedef CLONG*			LPCLONG;
	#define GLONG			static PROGMEM CLONG
	typedef LPG<LONG>		LPGLONG;
	typedef const LPGLONG	CLPGLONG;
	#define ARGLONG(...)	(LPGLONG)({GLONG stargltemp[]={__VA_ARGS__};stargltemp;})
	//	FLOAT
	typedef float			FLOAT;
	typedef const FLOAT		CFLOAT;
	typedef FLOAT*			LPFLOAT;
	typedef CFLOAT*			LPCFLOAT;
	#define GFLOAT			static PROGMEM CFLOAT
	typedef LPG<FLOAT>		LPGFLOAT;
	typedef const LPGFLOAT	CLPGFLOAT;
	#define ARGFLOAT(...)	(LPGFLOAT)({GFLOAT stargftemp[]={__VA_ARGS__};stargftemp;})
	//	FPST_VOID_VOID
	typedef VOID			(*FPST_VOID_VOID)(VOID);
	typedef const FPST_VOID_VOID	CFPST_VOID_VOID;

	//
	//		cast
	//

	//	CAST8
	typedef union{
		BYTE					bThis;
		BYTES					bsThis;
		BOOL					eThis;
		STR						strThis;
	}CAST8;
	typedef const CAST8		CCAST8;
	typedef CAST8*			LPCAST8;
	typedef CCAST8*			LPCCAST8;
	//	CAST16
	typedef union{
		BYTE					bThis;
		BYTES					bsThis;
		BOOL					eThis;
		STR						strThis;
		WORD					wThis;
		WORDS					wsThis;
		SHORT					sThis;
		INT						iThis;
		UINT					uiThis;
		PTRINT					piThis;
	}CAST16;
	typedef const CAST16	CCAST16;
	typedef CAST16*			LPCAST16;
	typedef CCAST16*		LPCCAST16;
	//	CAST32
	typedef union{
		BYTE					bThis;
		BYTES					bsThis;
		BOOL					eThis;
		STR						strThis;
		WORD					wThis;
		WORDS					wsThis;
		SHORT					sThis;
		INT						iThis;
		UINT					uiThis;
		PTRINT					piThis;
		DWORD					dwThis;
		DWORDS					dwsThis;
		LONG					lThis;
		FLOAT					fThis;
	}CAST32;
	typedef const CAST32	CCAST32;
	typedef CAST32*			LPCAST32;
	typedef CCAST32*		LPCCAST32;

	//
	//		class:ATOMIC
	//

	class ATOMIC{
	private:
		BYTE					bSave;
	public:
		/* VOID */				ATOMIC(VOID):
			bSave(SREG)
		{
			__asm__ __volatile__("cli;");
			return;
		}
		/* VOID */				~ATOMIC(VOID){
			SREG=bSave;
			return;
		}
	};

	//
	//		class:NOATOMIC
	//

	class NOATOMIC{
	private:
		BYTE					bSave;
	public:
		/* VOID */				NOATOMIC(VOID):
			bSave(SREG)
		{
			__asm__ __volatile__("sei;");
			return;
		}
		/* VOID */				~NOATOMIC(VOID){
			SREG=bSave;
			return;
		}
	};

	//
	//		class:LPGVOID
	//

	class LPGVOID{
	private:
		LPCBYTE					lpcbThis;
	public:
		INLINE /* VOID */		LPGVOID(LPCVOID lpcsource){
			lpcbThis=(LPCBYTE)lpcsource;
			return;
		}
		INLINE LPCVOID			lpcGetThis(VOID)const{
			return (LPCVOID)lpcbThis;
		}
		INLINE LPGVOID&			operator =(LPGVOID& lpgsource){
			lpcbThis=lpgsource.lpcbThis;
			return *this;
		}
		INLINE LPGVOID&			operator +=(INT iithis){
			lpcbThis+=iithis;
			return *this;
		}
		INLINE LPGVOID&			operator -=(INT iithis){
			lpcbThis-=iithis;
			return *this;
		}
		INLINE BYTE				operator *(VOID)const{
			return (BYTE)pgm_read_byte(lpcbThis);
		}
		INLINE BYTE				operator [](INT iithis)const{
			return (BYTE)pgm_read_byte(lpcbThis+iithis);
		}
		INLINE LPGVOID			operator +(INT iithis)const{
			return (LPGVOID)(lpcbThis+iithis);
		}
		INLINE LPGVOID			operator -(INT iithis)const{
			return (LPGVOID)(lpcbThis-iithis);
		}
		INLINE LPGVOID&			operator ++(VOID){
			lpcbThis++;
			return *this;
		}
		INLINE LPGVOID			operator ++(INT){
			LPGVOID					lpgreturn=*this;

			lpcbThis++;
			return lpgreturn;
		}
	};

	//
	//		managed:LPG
	//

	template<class CLASS>class LPG{
	public:

		//
		//		primitive
		//

		//	CLASS
		typedef const CLASS		CCLASS;
		typedef CLASS*			LPCLASS;
		typedef CCLASS*			LPCCLASS;
		typedef LPG<CLASS>		LPGCLASS;
		typedef const LPGCLASS	CLPGCLASS;

		//
		//		body:LPG
		//

	private:
		LPCCLASS				lpcxThis;
	public:
		INLINE /* VOID */		LPG(LPCCLASS lpcxsource){
			lpcxThis=lpcxsource;
			return;
		}
		INLINE LPGCLASS&		operator =(LPGCLASS& lpgxsource){
			lpcxThis=lpgxsource.lpcxThis;
			return *this;
		}
		INLINE LPGCLASS&		operator +=(INT iithis){
			lpcxThis+=iithis;
			return *this;
		}
		INLINE LPGCLASS&		operator -=(INT iithis){
			lpcxThis-=iithis;
			return *this;
		}
		INLINE CLASS			operator *(VOID)const{
			CLASS					xreturn;
			BYTE					i;

			for(i=0;i<sizeof(CLASS);i++)((LPBYTE)&xreturn)[i]=(BYTE)pgm_read_byte((LPCBYTE)lpcxThis+i);
			return xreturn;
		}
		INLINE CLASS			operator [](INT iithis)const{
			CLASS					xreturn;
			BYTE					i;

			for(i=0;i<sizeof(CLASS);i++)((LPBYTE)&xreturn)[i]=(BYTE)pgm_read_byte((LPCBYTE)(lpcxThis+iithis)+i);
			return xreturn;
		}
		INLINE LPGCLASS			operator +(INT iithis)const{
			return (LPGCLASS)(lpcxThis+iithis);
		}
		INLINE LPGCLASS			operator -(INT iithis)const{
			return (LPGCLASS)(lpcxThis-iithis);
		}
		INLINE LPGCLASS&		operator ++(VOID){
			lpcxThis++;
			return *this;
		}
		INLINE LPGCLASS			operator ++(INT){
			LPGCLASS				lpgxreturn=*this;

			lpcxThis++;
			return lpgxreturn;
		}
		INLINE /* LPGVOID */	operator LPGVOID(VOID)const{
			return (LPGVOID)(LPCVOID)lpcxThis;
		}
	};

	//
	//		class:OFW
	//

	class OFW{
	public:

		//
		//		const
		//

		#define OFW_stclpcstrClass	"OFW"
		static CDWORD			stcdwnClockHz=F_CPU;
		static CDWORD			stcdwnClockKHz=F_CPU/1000;
		static CDWORD			stcdwnClockMHz=F_CPU/1000000;

		//
		//		body:OFW
		//

		static INLINE VOID		stNew(VOID){
			init();
			MCUSR=0;
			return;
		}
		static INLINE VOID		stDelete(VOID){
			return;
		}
		static INLINE VOID		stReset(VOID){
			wdt_disable();
			wdt_enable(WDTO_15MS);
			while(TRUE);
		}
		static INLINE VOID		stNOP(VOID){
			__asm__ __volatile__("nop;");
			return;
		}
		static VOID				stFill(LPVOID lpthis,SIZE sznthis,BYTE bfill);
		static VOID				stCopy(LPVOID lpthis,LPCVOID lpcsource,SIZE sznsource);
		static VOID				stCopy(LPVOID lpthis,LPGVOID lpgsource,SIZE sznsource);
		static VOID				stWait(WORD wnmsec);
		static INLINE VOID		stWaitFine(BYTE bncount){
			__volatile__ BYTE		i;

			for(i=0;i<bncount;i++);
			return;
		}
		#define OFW_stbLSB(wsource)	((BYTE)((wsource)&0xff))
		#define OFW_stbMSB(wsource)	((BYTE)((wsource)>>8))
		#define OFW_stwUnicode(strsource)	((WORD)(strsource))
		#ifdef LITTLE_ENDIAN
			#define OFW_stwEndianL(wsource)	(wsource)
			#define OFW_stdwEndianL(dwsource)	(dwsource)
			#define OFW_stwEndianB(wsource)	((((wsource)<<8)&0xff00)|(((wsource)>>8)&0x00ff))
			#define OFW_stdwEndianB(dwsource)	((((dwsource)<<24)&0xff000000)|(((dwsource)<<8)&0x00ff0000)|(((dwsource)>>8)&0x0000ff00)|(((dwsource)>>24)&0x000000ff))
		#else //BIG_ENDIAN
			#define OFW_stwEndianL(wsource)	((((wsource)<<8)&0xff00)|(((wsource)>>8)&0x00ff))
			#define OFW_stdwEndianL(dwsource)	((((dwsource)<<24)&0xff000000)|(((dwsource)<<8)&0x00ff0000)|(((dwsource)>>8)&0x0000ff00)|(((dwsource)>>24)&0x000000ff))
			#define OFW_stwEndianB(wsource)	(wsource)
			#define OFW_stdwEndianB(dwsource)	(dwsource)
		#endif
	};
}

//
//		using
//

using namespace ofw;
