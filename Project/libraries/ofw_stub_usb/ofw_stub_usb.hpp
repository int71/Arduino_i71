/****************************************************************************
**																			**
**																			**
**									ofw										**
**																			**
**	stub/usb										2024 written by int71	**
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
	//		namespace:stub
	//

	namespace stub{

		//
		//		class
		//

		class USB;
		typedef const USB		CUSB;
		typedef USB*			LPUSB;
		typedef CUSB*			LPCUSB;

		//
		//		class:USB
		//

		class USB{
		public:

			//
			//		const
			//

			//	IDREQUEST
			enum IDREQUEST{
				IDRequest_GetStatus=0,
				IDRequest_ClearFeature=1,
				IDRequest_SetFeature=3,
				IDRequest_SetAddress=5,
				IDRequest_GetDescriptor=6,
				IDRequest_SetDescriptor=7,
				IDRequest_GetConfiguration=8,
				IDRequest_SetConfiguration=9,
				IDRequest_GetInterface=10,
				IDRequest_SetInterface=11
			};
			//	IDDESCRIPTORTYPE
			enum IDDESCRIPTORTYPE{
				IDDescriptorType_Device=1,
				IDDescriptorType_Configuration=2,
				IDDescriptorType_String=3,
				IDDescriptorType_Interface=4,
				IDDescriptorType_EndPoint=5,
				IDDescriptorType_HID=0x21
			};
			//	IDFEATURETYPE
			enum IDFEATURETYPE{
				IDFeatureType_RemoteWakeUp=1,
				IDFeatureType_EndPointHalt=2,
				IDFeatureType_TestMode=3
			};
			//	IDDEVICECLASS
			enum IDDEVICECLASS{
				IDDeviceClass_Communications=0x02,
				IDDeviceClass_HID=0x03,
				IDDeviceClass_Storage=0x08,
				IDDeviceClass_VendorSpecific=0xff
			};
			//	EP_IDSIZE
			enum EP_IDSIZE{
				EP_IDSize_Single16=0x12,
				EP_IDSize_Single64=0x32,
				EP_IDSize_Double64=0x36
			};
			static CBYTE			stcbcRequestTarget=0x03;
			static CBYTE			stcbcRequestTargetDevice=0x00;
			static CBYTE			stcbcRequestTargetInterface=0x01;
			static CBYTE			stcbcRequestTargetEndPoint=0x02;
			static CBYTE			stcbcRequestTargetOther=0x03;
			static CBYTE			stcbcRequestType=0x60;
			static CBYTE			stcbcRequestTypeStandard=0x00;
			static CBYTE			stcbcRequestTypeClass=0x20;
			static CBYTE			stcbcRequestTypeVendor=0x40;
			static CBYTE			stcbcRequestDirection=0x80;
			static CBYTE			stcbcRequestDirectionHosttoDevice=0x00;
			static CBYTE			stcbcRequestDirectionDevicetoHost=0x80;
			static CBYTE			stcbcRequestDevicetoHostClassInterface=stcbcRequestDirectionDevicetoHost|stcbcRequestTypeClass|stcbcRequestTargetInterface;
			static CBYTE			stcbcRequestHosttoDeviceClassInterface=stcbcRequestDirectionHosttoDevice|stcbcRequestTypeClass|stcbcRequestTargetInterface;
			static CBYTE			stcbcRequestDevicetoHostStandardInterface=stcbcRequestDirectionDevicetoHost|stcbcRequestTypeStandard|stcbcRequestTargetInterface;
			static CBYTE			stcbcStatusSelfPoweredEnabled=(1<<0);
			static CBYTE			stcbcStatusRemoteWakeUpEnabled=(1<<1);
			static CBYTE			stcbcAttributeRemoteWakeUp=0x20;
			static CBYTE			stcbcAttributePoweredMask=0x40;
			static CBYTE			stcbcAttributeBusPowered=0x80;
			static CBYTE			stcbcAttributeSelfPowered=0xc0;
			static CSIZE			EP_stcsznBuffer=64;
#if defined(EPRST6)
			static CBYTE			EP_stcbnPort=7;	//	AtMegaxxU4
#else
			static CBYTE			EP_stcbnPort=5;	//	AtMegaxxU2
#endif
			static CBYTE			EP_stcbcDirection=0x80;
			static CBYTE			EP_stcbcDirectionRead=0x00;
			static CBYTE			EP_stcbcDirectionWrite=0x80;
			static CBYTE			EP_stcbcType=0x03;
			static CBYTE			EP_stcbcDescriptorTypeControl=0x00;
			static CBYTE			EP_stcbcDescriptorTypeIsochronous=0x01;
			static CBYTE			EP_stcbcDescriptorTypeBulk=0x02;
			static CBYTE			EP_stcbcDescriptorTypeInterrupt=0x03;
			static CBYTE			EP_stcbcConfigTypeControl=0x00;
			static CBYTE			EP_stcbcConfigTypeBulkRead=1<<EPTYPE1;
			static CBYTE			EP_stcbcConfigTypeBulkWrite=(1<<EPTYPE1)|(1<<EPDIR);
			static CBYTE			EP_stcbcConfigTypeInterruptRead=(1<<EPTYPE1)|(1<<EPTYPE0);
			static CBYTE			EP_stcbcConfigTypeInterruptWrite=(1<<EPTYPE1)|(1<<EPTYPE0)|(1<<EPDIR);
			static CBYTE			EP_stcbcConfigTypeIsochronousRead=1<<EPTYPE0;
			static CBYTE			EP_stcbcConfigTypeIsochronousWrite=(1<<EPTYPE0)|(1<<EPDIR);

			//
			//		class
			//

			//	DEVICEDESC
			class DEVICEDESC;
			typedef const DEVICEDESC	CDEVICEDESC;
			typedef DEVICEDESC*		LPDEVICEDESC;
			typedef CDEVICEDESC*	LPCDEVICEDESC;
			#define GDEVICEDESC		static PROGMEM CDEVICEDESC
			typedef LPG<DEVICEDESC>	LPGDEVICEDESC;
			typedef const LPGDEVICEDESC	CLPGDEVICEDESC;
			#define ARGDEVICEDESC(...)	(LPGDEVICEDESC)({GDEVICEDESC stargdvcdesctemp[]={__VA_ARGS__};stargdvcdesctemp;})
			//	CONFIGDESC
			class CONFIGDESC;
			typedef const CONFIGDESC	CCONFIGDESC;
			typedef CONFIGDESC*		LPCONFIGDESC;
			typedef CCONFIGDESC*	LPCCONFIGDESC;
			#define GCONFIGDESC		static PROGMEM CCONFIGDESC
			typedef LPG<CONFIGDESC>	LPGCONFIGDESC;
			typedef const LPGCONFIGDESC	CLPGCONFIGDESC;
			#define ARGCONFIGDESC(...)	(LPGCONFIGDESC)({GCONFIGDESC stargcfgdesctemp[]={__VA_ARGS__};stargcfgdesctemp;})
			//	INTERFACEDESC
			class INTERFACEDESC;
			typedef const INTERFACEDESC	CINTERFACEDESC;
			typedef INTERFACEDESC*	LPINTERFACEDESC;
			typedef CINTERFACEDESC*	LPCINTERFACEDESC;
			#define GINTERFACEDESC	static PROGMEM CINTERFACEDESC
			typedef LPG<INTERFACEDESC>	LPGINTERFACEDESC;
			typedef const LPGINTERFACEDESC	CLPGINTERFACEDESC;
			#define ARGINTERFACEDESC(...)	(LPGINTERFACEDESC)({GINTERFACEDESC stargifdesctemp[]={__VA_ARGS__};stargifdesctemp;})
			//	ENDPOINTDESC
			class ENDPOINTDESC;
			typedef const ENDPOINTDESC	CENDPOINTDESC;
			typedef ENDPOINTDESC*	LPENDPOINTDESC;
			typedef CENDPOINTDESC*	LPCENDPOINTDESC;
			#define GENDPOINTDESC	static PROGMEM CENDPOINTDESC
			typedef LPG<ENDPOINTDESC>	LPGENDPOINTDESC;
			typedef const LPGENDPOINTDESC	CLPGENDPOINTDESC;
			#define ARGENDPOINTDESC(...)	(LPGENDPOINTDESC)({GENDPOINTDESC stargepdesctemp[]={__VA_ARGS__};stargepdesctemp;})
			//	REQUEST
			class REQUEST;
			typedef const REQUEST	CREQUEST;
			typedef REQUEST*		LPREQUEST;
			typedef CREQUEST*		LPCREQUEST;
			//	ST
			class ST;
			typedef const ST		CST;
			typedef ST*				LPST;
			typedef CST*			LPCST;

			//
			//		class:DEVICEDESC
			//

			class DEVICEDESC{
			public:
				BYTE					bnLength;
				BYTE					bcDescriptorType;
				WORD					wcUSB;
				BYTE					bcDeviceClass;
				BYTE					bcDeviceSubClass;
				BYTE					bcDeviceProtocol;
				BYTE					bnMaxPacketSize;
				WORD					wcVendor;
				WORD					wcProduct;
				WORD					wcDevice;
				BYTE					biManufacturer;
				BYTE					biProduct;
				BYTE					biSerialNumber;
				BYTE					bnConfiguration;
			};

			//
			//		class:CONFIGDESC
			//

			class CONFIGDESC{
			public:
				BYTE					bnLength;
				BYTE					bcDescriptorType;
				WORD					wnTotalLength;
				BYTE					bnInterface;
				BYTE					bnConfiguration;
				BYTE					biConfiguration;
				BYTE					bcAttibute;
				BYTE					bcMaxPower;
			};

			//
			//		class:INTERFACEDESC
			//

			class INTERFACEDESC{
			public:
				BYTE					bnLength;
				BYTE					bcDescriptorType;
				BYTE					bnInterface;
				BYTE					bcAlternateSetting;
				BYTE					bnEndpoint;
				BYTE					bcInterfaceClass;
				BYTE					bcInterfaceSubClass;
				BYTE					bcInterfaceProtocol;
				BYTE					biInterface;
			};

			//
			//		class:ENDPOINTDESC
			//

			class ENDPOINTDESC{
			public:
				BYTE					bnLength;
				BYTE					bcDescriptorType;
				BYTE					bcEndpointAddress;
				BYTE					bcAttribute;
				WORD					wnMaxPacketSize;
				BYTE					bnInterval;
			};

			//
			//		class:REQUEST
			//

			class REQUEST{
			public:
				BYTE					bcRequestType;
				BYTE					bcRequest;
				BYTE					bValueLSB;	//	ReportID
				BYTE					bValueMSB;	//	ReportType
				WORD					wiIndex;
				WORD					wnLength;
			};

			//
			//		class:ST
			//

			class ST{
			public:
				BYTE					bnInstance;
				LPUSB					lpusbRoot;
				BYTE					biNOATOMIC;
				BOOL					eInitialized:1;
				BOOL					eSuspended:1;
				BOOL					eRemoteWakeUp:1;
				SIZE					CTRL_sziWriteCurrent;
				SIZE					CTRL_sznWriteLimit;
			public:
				/* VOID */				ST(VOID):
					bnInstance(0)
				{}
			};

			//
			//		body:USB
			//

		private:
			static ST				st;
		public:
			virtual /* VOID */		~USB(VOID){}
			static VOID				stMain(VOID);
			static INLINE VOID		VECTOR_stRequest(VOID){
				REQUEST					reqsource;

				EP_stOpen(0);
				if(!EP_steIsReadInterrupted())return;
				EP_stRead(&reqsource,8);
				EP_stClearInterrupt();
				switch(reqsource.bcRequestType&stcbcRequestDirection){
				case stcbcRequestDirectionHosttoDevice:
					EP_stClearWrite();
					EP_stWaitforDone();
					break;
				case stcbcRequestDirectionDevicetoHost:
					EP_stWaitforWritten();
					break;
				}
				switch(reqsource.bcRequestType&stcbcRequestType){
				case stcbcRequestTypeStandard:
					VECTOR_Request_stStandard(&reqsource);
					break;
				case stcbcRequestTypeClass:
					VECTOR_Request_stClass(&reqsource);
					break;
				case stcbcRequestTypeVendor:
					VECTOR_Request_stVendor(&reqsource);
					break;
				}
				EP_stClearWrite();
				return;
			}
			static INLINE VOID		VECTOR_stGeneral(VOID){
				BYTE					bcinterruptrequest=UDINT;

				UDINT&=~((1<<EORSTI)|(1<<SOFI));	// clear the IRQ flags for the IRQs which are handled here, except WAKEUPI and SUSPI (see below)
				if(bcinterruptrequest&(1<<EORSTI)){
					//	End of Reset
					EP_stInitialize(0,EP_stcbcConfigTypeControl,EP_IDSize_Single64);	// init ep0
					st.eInitialized=FALSE;				// not configured yet
					UEIENX=1<<RXSTPE;					// Enable interrupts for ep0
				}
				if(bcinterruptrequest&(1<<WAKEUPI)){
					// the WAKEUPI interrupt is triggered as soon as there are non-idle patterns on the data
					// lines. Thus, the WAKEUPI interrupt can occur even if the controller is not in the "suspend" mode.
					// Therefore the we enable it only when USB is suspended
					UDIEN=(UDIEN&~(1<<WAKEUPE))|(1<<SUSPE);	// Disable interrupts for WAKEUP and enable interrupts for SUSPEND
					UDINT&=~(1<<WAKEUPI);
					st.eSuspended=FALSE;
				}else if(bcinterruptrequest&(1<<SUSPI)){
					//	only one of the WAKEUPI / SUSPI bits can be active at time
					UDIEN=(UDIEN&~(1<<SUSPE))|(1<<WAKEUPE);	// Disable interrupts for SUSPEND and enable interrupts for WAKEUP
					UDINT&=~((1<<WAKEUPI)|(1<<SUSPI));	// clear any already pending WAKEUP IRQs and the SUSPI request
					st.eSuspended=TRUE;
				}
				return;
			}
			VOID					New(VOID);
			VOID					Delete(VOID);
		protected:
			static VOID				CTRL_stWriteOpen(SIZE sznsource);
			static VOID				CTRL_stWrite(BYTE bsource);
			static VOID				CTRL_stWrite(LPCVOID lpcsource,SIZE sznsource);
			static VOID				CTRL_stWrite(LPGVOID lpgsource,SIZE sznsource);
			static VOID				CTRL_stWriteStringLanguageDesc(WORD wclanguage);
			static VOID				CTRL_stWriteStringDesc(LPCSTR lpcstrsource);
			static VOID				CTRL_stWriteStringDesc(LPGSTR lpgstrsource);
			static SIZE				EP_stsznRead(BYTE biep,LPVOID lpthis,SIZE sznthis);
			static VOID				EP_stWrite(BYTE biep,LPCVOID lpcsource,SIZE sznsource);
			static VOID				EP_stWrite(BYTE biep,LPGVOID lpgsource,SIZE sznsource);
			static BYTE				EP_Main_stbnGetReadable(BYTE biep);
			static BYTE				EP_Main_stbnGetWritable(BYTE biep);
			static SIZE				EP_Main_stsznRead(BYTE biep,LPVOID lpthis,SIZE sznthis);
			static VOID				EP_Main_stWrite(BYTE biep,LPCVOID lpcsource,SIZE sznsource);
			static VOID				EP_Main_stWrite(BYTE biep,LPGVOID lpgsource,SIZE sznsource);
			virtual VOID			New_Self(VOID);
			virtual VOID			Delete_Self(VOID);
			virtual VOID			Main_Self(VOID);
			virtual VOID			VECTOR_Request_Standard_Descriptor_Device(VOID)=0;
			virtual VOID			VECTOR_Request_Standard_Descriptor_Configuration(VOID)=0;
			virtual VOID			VECTOR_Request_Standard_Descriptor_String(BYTE bithis)=0;
			virtual VOID			VECTOR_Request_Standard_Descriptor_Other(LPREQUEST lpreqsource);
			virtual VOID			VECTOR_Request_Class_Device(LPREQUEST lpreqsource);
			virtual VOID			VECTOR_Request_Class_Interface(LPREQUEST lpreqsource);
			virtual VOID			VECTOR_Request_Class_EndPoint(LPREQUEST lpreqsource);
			virtual BYTE			EP_Initialize_bcConfigType(BYTE biep)=0;
		private:
			static VOID				stNew_Local(VOID);
			static VOID				stDelete_Local(VOID);
			static VOID				stNew_Clock(VOID);
			static VOID				stDelete_Clock(VOID);
			static INLINE VOID		stStall(VOID){
				UECONX=(1<<STALLRQ)|(1<<EPEN);
				return;
			}
			static INLINE VOID		VECTOR_Request_stStandard(LPREQUEST lpreqsource){
				WORD					wValue;

				wValue=((WORD)lpreqsource->bValueLSB)|(((WORD)lpreqsource->bValueMSB)<<8);
				switch(lpreqsource->bcRequest){
				case IDRequest_GetStatus:
					if (lpreqsource->bcRequestType==(stcbcRequestDirectionDevicetoHost|stcbcRequestTypeStandard|stcbcRequestTargetDevice)){
						if(st.eRemoteWakeUp)EP_stWrite(stcbcStatusRemoteWakeUpEnabled);
						else EP_stWrite(0);
						EP_stWrite(0);
					}else{
						// TODO: handle the HALT state of an endpoint here
						// see "Figure 9-6. Information Returned by a GetStatus() Request to an Endpoint" in usb_20.pdf for more information
						EP_stWrite(0);
						EP_stWrite(0);
					}
					break;
				case IDRequest_ClearFeature:
					if(lpreqsource->bcRequestType==(stcbcRequestDirectionHosttoDevice|stcbcRequestTypeStandard|stcbcRequestTargetDevice))switch(wValue){
					case IDFeatureType_RemoteWakeUp:
						st.eRemoteWakeUp=FALSE;
						break;
					}
					break;
				case IDRequest_SetFeature:
					if(lpreqsource->bcRequestType==(stcbcRequestDirectionHosttoDevice|stcbcRequestTypeStandard|stcbcRequestTargetDevice))switch(wValue){
					case IDFeatureType_RemoteWakeUp:
						st.eRemoteWakeUp=TRUE;
						break;
					}
					break;
				case IDRequest_SetAddress:
					EP_stWaitforWritten();
					UDADDR=lpreqsource->bValueLSB|(1<<ADDEN);
					break;
				case IDRequest_GetDescriptor:
					CTRL_stWriteOpen(lpreqsource->wnLength);
					VECTOR_Request_Standard_stDescriptor(lpreqsource);
					break;
				case IDRequest_GetConfiguration:
					EP_stWrite(1);
					break;
				case IDRequest_SetConfiguration:
					switch(lpreqsource->bcRequestType&stcbcRequestTarget){
					case stcbcRequestTargetDevice:
						EP_stInitialize();
						st.eInitialized=(lpreqsource->bValueLSB!=0);
						break;
					default:
						stStall();
						return;
					}
					break;
				case IDRequest_GetInterface:
					break;
				case IDRequest_SetInterface:
					break;
				default:
					stStall();
					return;
				}
				return;
			}
			static INLINE VOID		VECTOR_Request_stClass(LPREQUEST lpreqsource){
				switch(lpreqsource->bcRequestType&stcbcRequestTarget){
				case stcbcRequestTargetDevice:
					st.lpusbRoot->VECTOR_Request_Class_Device(lpreqsource);
					break;
				case stcbcRequestTargetInterface:
					//	for "HidD_GetFeature"
					st.lpusbRoot->VECTOR_Request_Class_Interface(lpreqsource);
					break;
				case stcbcRequestTargetEndPoint:
					st.lpusbRoot->VECTOR_Request_Class_EndPoint(lpreqsource);
					break;
				}
				return;
			}
			static INLINE VOID		VECTOR_Request_stVendor(LPREQUEST lpreqsource){
				return;
			}
			static INLINE VOID		VECTOR_Request_Standard_stDescriptor(LPREQUEST lpreqsource){
				switch(lpreqsource->bValueMSB){
				case IDDescriptorType_Device:
					st.lpusbRoot->VECTOR_Request_Standard_Descriptor_Device();
					break;
				case IDDescriptorType_Configuration:
					st.lpusbRoot->VECTOR_Request_Standard_Descriptor_Configuration();
					break;
				case IDDescriptorType_String:
					st.lpusbRoot->VECTOR_Request_Standard_Descriptor_String(lpreqsource->bValueLSB);
					break;
				default:
					st.lpusbRoot->VECTOR_Request_Standard_Descriptor_Other(lpreqsource);
					break;
				}
				return;
			}
			static VOID				EP_stInitialize(VOID);
			static VOID				EP_stInitialize(BYTE biep,BYTE bcconfigtype,BYTE bcsize);
			static INLINE VOID		EP_stOpen(BYTE biep){
				UENUM=biep;
				return;
			}
			static INLINE BYTE		EP_stbRead(VOID){
				return UEDATX;
			}
			static INLINE VOID		EP_stRead(LPVOID lpthis,SIZE sznthis){
				LPBYTE					lpbthis=(LPBYTE)lpthis;

				for(;sznthis;sznthis--){
					*lpbthis=EP_stbRead();
					lpbthis++;
				}
				return;
			}
			static INLINE VOID		EP_stWrite(BYTE bsource){
				UEDATX=bsource;
				return;
			}
			static INLINE VOID		EP_stWaitforDone(VOID){
				while(!(UEINTX&((1<<TXINI)|(1<<RXOUTI))));
				return;
			}
			static INLINE VOID		EP_stWaitforWritten(VOID){
				while(!(UEINTX&(1<<TXINI)));
				return;
			}
			static INLINE VOID		EP_stClearRead(VOID){
				UEINTX=~(1<<RXOUTI);
				return;
			}
			static INLINE VOID		EP_stClearWrite(VOID){
				UEINTX=~(1<<TXINI);
				return;
			}
			static INLINE VOID		EP_stClearInterrupt(VOID){
				UEINTX=~((1<<RXSTPI)|(1<<RXOUTI)|(1<<TXINI));
				return;
			}
			static INLINE VOID		EP_stReleaseRead(VOID){
				UEINTX=0x6b;	// FIFOCON=0 NAKINI=1 RWAL=1 NAKOUTI=0 RXSTPI=1 RXOUTI=0 STALLEDI=1 TXINI=1
				return;
			}
			static INLINE VOID		EP_stReleaseWrite(VOID){
				UEINTX=0x3a;	// FIFOCON=0 NAKINI=0 RWAL=1 NAKOUTI=1 RXSTPI=1 RXOUTI=0 STALLEDI=1 TXINI=0
				return;
			}
			static INLINE BOOL		EP_steIsReadInterrupted(VOID){
				return UEINTX&(1<<RXSTPI);
			}
			static INLINE BOOL		EP_steIsWritable(VOID){
				return UEINTX&(1<<RWAL);
			}
			static BYTE				EP_stbnGetWritable(VOID);
			static INLINE BYTE		EP_stbnGetRest(VOID){
				return UEBCLX;
			}
			VOID					New_Local(VOID);
			VOID					Delete_Local(VOID);
		};
	}
}
