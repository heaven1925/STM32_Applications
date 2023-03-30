/*********************************START OF FILE********************************/
/*******************************************************************************
  * @file    EEMProtocol_Config.h
  * @author	 Atakan ERTEKiN
  * @version V1.0.0
  * @date	 30.01.2023 - ...
  * @rev     V1.0.0
  * @brief	 Ege Elektromobil CAN Stack
********************************************************************************/

#ifndef __EEMPROCOTOL_CONFIG_H__
#define	__EEMPROCOTOL_CONFIG_H__

/********************************************************************************/

#include "EEMProtocol.h"

/*
* All protocol numarator has to define here!
* uncomment #undef macro depend to ecu or hw
*/

/*
 * Body Control module EEM_PERIODIC protocol macro
*/
#ifndef 	BCM_MODULE
#define		BCM_MODULE
#undef		BCM_MODULE
#endif
/* Node Addr = 0x11 */
#define		BCM_NODE			0x11UL

/*
 * Heating and Ventilation controller EEM_PERIODIC protocol macro
*/
#ifndef 	HVAC_MODULE
#define		HVAC_MODULE
#undef		HVAC_MODULE
#endif
/* Node Addr = 0x22 */
#define		HVAC_NODE			0x22UL

/*
 * Simple Computer EEM_PERIODIC protocol macro
*/
#ifndef 	SCB_MODULE
#define		SCB_MODULE
#undef		SCB_MODULE
#endif
/* Node Addr = 0x33 */
#define		SCB_NODE			0x33UL

/*
 * Battery management system EEM_PERIODIC protocol macro
*/
#ifndef		BMS_MODULE
#define		BMS_MODULE
#undef		BMS_MODULE
#endif
/* Node Addr = 0x44 */
#define		BMS_NODE			0x44UL

/*
 * Motor Driver - 1 EEM_PERIODIC protocol macro
*/
#ifndef		MS1_MODULE
#define		MS1_MODULE
#undef		MS1_MODULE
#endif
/* Node Addr = 0x55 */
#define		MS1_NODE			0x55UL

/*
 * Motor Driver - 2 EEM_PERIODIC protocol macro
*/
#ifndef		MS2_MODULE
#define		MS2_MODULE
#undef		MS2_MODULE
#endif
/* Node Addr = 0x66 */
#define		MS2_NODE			0x66UL

/*
 * Isolation Watching Device EEM_PERIODIC protocol macro
*/
#ifndef		ISO_MODULE
#define		ISO_MODULE
#undef		ISO_MODULE
#endif
/* Node Addr = 0x77 */
#define		ISO_NODE			0x77UL

/*
 * Telemetry Module EEM_PERIODIC protocol macro
*/
#ifndef		TLM_MODULE
#define		TLM_MODULE
#undef		TLM_MODULE
#endif
/* Node Addr = 0x88 */
#define		TLM_NODE			0x88UL

/*
 * Built-In Charging unit EEM_PERIODIC protocol macro
*/
#ifndef		YSB_MODULE
#define		YSB_MODULE
#undef		YSB_MODULE
#endif
/* Node Addr = 0x88 */
#define		YSB_NODE			0x99UL

/*
 * Message Specific ID's
 */
#define		MESSAGE01			0x01UL	/* HVAC -> BCM */
#define		MESSAGE02			0x02UL	/* HVAC -> BCM */
#define		MESSAGE03			0x03UL
#define		MESSAGE04			0x04UL
#define		MESSAGE05			0x05UL
#define		MESSAGE06			0x06UL
#define		MESSAGE07			0x07UL	/* MS1 -> BCM */
#define		MESSAGE08			0x08UL	/* MS1 -> BCM */
#define		MESSAGE09			0x09UL	/* MS2 -> BCM */
#define		MESSAGE10			0x10UL	/* MS2 -> BCM */
#define		MESSAGE11			0x11UL	/* ISO -> BCM */
#define		MESSAGE12			0x12UL	/* TLM -> BCM */
#define		MESSAGE13			0x13UL	/* YSB -> BCM */
#define		MESSAGE14			0x14UL
#define		MESSAGE15			0x15UL
#define		MESSAGE16			0x16UL	/* BMS -> BCM */
#define		MESSAGE17			0x17UL
#define		MESSAGE18			0x18UL	/* MS-1 -> BCM */
#define		MESSAGE19			0x19UL  /* MS-2 -> BCM */
#define		MESSAGE20			0x20UL	/* BCM -> MS-1 */
#define		MESSAGE21			0x21UL	/* BCM -> MS-1 */
#define		MESSAGE22			0x22UL	/* BCM -> MS-2 */
#define		MESSAGE23			0x23UL	/* BCM -> MS-2 */
#define		MESSAGE24			0x24UL	/* BCM -> BMS  */
#define		MESSAGE25			0x25UL	/* BCM -> YSB  */


#define		SIZE_OF_MSG			25

/* Fixed Message Definitions */
typedef struct
{
	EEM_U32  identifier;
	EEM_U8*  fixedMessage;
}EEM_FixedMessage_st;

typedef struct
{
	char* 				 name;
	EEM_FixedMessage_st* msg;
	EEM_U8				 repeit_count;
}EEM_FixedFormat_st;

/********************************************************************************/

void 	  EEM_SET_IDENTIFIERS(void);

#if defined( BCM_MODULE )
EEM_ERR_T EEM_FILTER_BCM( EEM_Protocol_obj_st* param );
#elif defined( HVAC_MODULE )
/* HVAC module has been written Cpp language in order to arduino framework */
#elif defined( SCB_MODULE )
/* Simple computer protocol has written pyhton language */
#elif defined( BMS_MODULE )
EEM_ERR_T EEM_FILTER_BMS( EEM_Protocol_obj_st* param );
#elif defined( MS1_MODULE )
EEM_ERR_T EEM_FILTER_MS1( EEM_Protocol_obj_st* param );
#elif defined( MS2_MODULE )
EEM_ERR_T EEM_FILTER_MS2( EEM_Protocol_obj_st* param );
#elif defined( ISO_MODULE )
EEM_ERR_T EEM_FILTER_ISO( EEM_Protocol_obj_st* param );
#elif defined( TLM_MODULE )
EEM_ERR_T EEM_FILTER_TLM( EEM_Protocol_obj_st* param );
#elif defined( YSB_MODULE )
EEM_ERR_T EEM_FILTER_YSB( EEM_Protocol_obj_st* param );
#endif



/********************************************************************************/

/*
 * Reserved Numarator
 * This numarator has to configurate u1 type !
 */
typedef enum
{
	NOT_RESERVED = 0,
	RESERVED	 = 1,
}EEMConfig_Reserved_et;

/*
 * Data Page Numarator
 * This numarator has to configurate u1 type !
 */
typedef enum
{
	DATAPAGE_0 = 0,
	DATAPAGE_1 = 1,
}EEMConfig_DataPage_et;

/*
 * Priortiy Numarator
 * This numarator has to configurate u3 type !
 */
typedef enum
{
	PRIORITY_000 = 0b00000000 ,
	PRIORITY_001 = 0b00000001 ,
	PRIORITY_010 = 0b00000010 ,
	PRIORITY_011 = 0b00000011 ,
	PRIORITY_100 = 0b00000100 ,
	PRIORITY_101 = 0b00000101 ,
	PRIORITY_110 = 0b00000110 ,
	PRIORITY_111 = 0b00000111 ,
}EEMConfig_Priority_et;

/*
 * Message Index
 */
typedef enum
{
	MSG01_INDEX = 0 ,
	MSG02_INDEX ,
	MSG03_INDEX ,
	MSG04_INDEX ,
	MSG05_INDEX ,
	MSG06_INDEX ,
	MSG07_INDEX ,
	MSG08_INDEX ,
	MSG09_INDEX ,
	MSG10_INDEX ,
	MSG11_INDEX ,
	MSG12_INDEX ,
	MSG13_INDEX ,
	MSG14_INDEX ,
	MSG15_INDEX ,
	MSG16_INDEX ,
	MSG17_INDEX ,
	MSG18_INDEX ,
	MSG19_INDEX ,
	MSG20_INDEX ,
	MSG21_INDEX ,
	MSG22_INDEX ,
	MSG23_INDEX ,
	MSG24_INDEX ,
	MSG25_INDEX ,
	MSG26_INDEX ,
	MSG27_INDEX ,
	//@...
}EEMConfig_MsgID_Index_et;



/*
* All protocol payload has to define here!
*/

/*
* HVAC Message Class
 */
typedef struct
{
	EEM_U32 Message01_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_BOOL_T 	HVAC_led01_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-01 durumu */
			EEM_BOOL_T 	HVAC_led02_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-02 durumu */
			EEM_BOOL_T 	HVAC_led03_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-03 durumu */
			EEM_BOOL_T 	HVAC_led04_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-04 durumu */
			EEM_BOOL_T 	HVAC_led05_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-05 durumu */
			EEM_BOOL_T 	HVAC_led06_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-06 durumu */
			EEM_BOOL_T 	HVAC_led07_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-07 durumu */
			EEM_BOOL_T 	HVAC_led08_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-08 durumu */
			EEM_BOOL_T 	HVAC_led09_u1           : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-09 durumu */
			EEM_BOOL_T 	HVAC_led10_u1 	        : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-10 durumu */
			EEM_BOOL_T 	HVAC_led11_u1 	        : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-11 durumu */
			EEM_BOOL_T 	HVAC_led12_u1 	        : 1 ; /* YAKS Donanımına bağlı araç içerisindeki led-12 durumu */
			EEM_U8 		HVAC_pressureVal_u8 	: 8 ; /* Koltuk Basınç sensörü analog 8bit değeri */
			EEM_U8 		HVAC_indoorTempVal_u8   : 8 ; /* Araç Kontrol Görev Birimi ( AKS-YAKS-RPI) Sıcaklık analog 8bit değeri */
			EEM_U8 		HVAC_indoorHumidVal_u8  : 8 ; /* Araç Kontrol Görev Birimi ( AKS-YAKS-RPI) Nem analog 8bit değeri */
			EEM_BOOL_T 	HVAC_rtcCalib_u1		: 1 ; /* YAKS tarafından RTC kalibrasyon yapılacağı bilgisi */
			EEM_BOOL_T 	HVAC_rtcNewSecond_u8	: 1 ;	/* YAKS RTC Saniye bilgisi  */
			EEM_BOOL_T 	HVAC_rtcNewMinutes_u8   : 1 ; /* YAKS RTC Dakika bilgisi	*/
			EEM_BOOL_T 	HVAC_rtcNewHour_u8	    : 1 ; /* YAKS RTC Saat bilgisi 	*/
			EEM_BOOL_T 	HVAC_rtcNewDay_u8	    : 1 ; /* YAKS RTC Saat bilgisi 	*/
			EEM_BOOL_T 	HVAC_rtcNewMonth_u8	    : 1 ; /* YAKS RTC Ay bilgisi		*/
			EEM_U32:22; /* RFU */
		}SPN;
	}Message01;

	EEM_U32 Message02_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8 HVAC_tempVal_u8            : 8 ; /* Araç Kontrol Görev Birimi ( AKS-YAKS-RPI) Sıcaklık analog 8bit değeri	*/
			EEM_U8 HVAC_humidityVal_u8		  : 8 ; /* Araç Kontrol Görev Birimi ( AKS-YAKS-RPI) Nem analog 8bit değeri					*/
			EEM_U8 HVAC_smokeVal_u4			  : 4 ; /* Duman Sensörünün analog  4bit degeri					*/
			EEM_U8 HVAC_windPressure1_u4      : 4 ; /* Sol havalandırma rüzgar basınc sensörünün analog  4bit değeri					*/
			EEM_U8 HVAC_windPressure2_u4      : 4 ; /* Sağ havalandırma rüzgar basınc sensörünün analog 4bit değeri					*/
			EEM_U8 HVAC_leftFrontWheel_xy_u8  : 8 ; /* Sol ön tekerleğin X-Y eksen pozisyonları yazılımsal diferansiyel geri beslemesi için					*/
			EEM_U8 HVAC_rightFrontWheel_xy_u8 : 8 ; /* Sağ ön tekerleğin X-Y eksen pozisyonları yazılımsal diferansiyel geri beslemesi için					*/
			EEM_U8 HVAC_status00_u1        	  : 1 ; /* YAKS'de denetlenen status biti 0 -> YAKS 'deki Sol ön teker açı sınırı durumunu tutar.					*/
			EEM_U8 HVAC_status01_u1           : 1 ; /* YAKS'de denetlenen status biti 1 -> YAKS 'deki Sağ ön teker açı sınırı durumunu tutar.					*/
			EEM_U8 HVAC_status02_u1           : 1 ; /* YAKS'de denetlenen status biti 2 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_status03_u1           : 1 ; /* YAKS'de denetlenen status biti 3 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_status04_u1           : 1 ; /* YAKS'de denetlenen status biti 4 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_status05_u1           : 1 ; /* YAKS'de denetlenen status biti 5 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_status06_u1           : 1 ; /* YAKS'de denetlenen status biti 6 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_status07_u1           : 1 ; /* YAKS'de denetlenen status biti 7 -> YAKS 'deki .......... durumunu tutar.					*/
			EEM_U8 HVAC_Hgear_cmd_u3	      : 3 ; /* H - Vites Durum bilgisi - 0,1,2,3,4,5,6 */
			EEM_U8 HVAC_Gear_cmd_u2	          : 2 ; /* Park - İleri- Geri Vites Durum Bilgisi							*/
			EEM_U8 HVAC_cmdbit05_u1	          : 1 ; /* YAKS'den AKS'ye gönderilen 5. komut -> ......... komutu	  	    */
			EEM_U8 HVAC_cmdbit06_u1	          : 1 ; /* YAKS'den AKS'ye gönderilen 6. komut -> ......... komutu	    	*/
			EEM_U8 HVAC_cmdbit07_u1	          : 1 ; /* YAKS'den AKS'ye gönderilen 7. komut -> ......... komutu					*/
			EEM_U8:4; /* RFU */
		}SPN;
	}Message02;

}HVAC_Module_st;

/*
 * BCM Message Class
 */
typedef struct
{
	EEM_U32	Message03_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U32 BCM_differantialSpeed_u64 ; /* Diferansiyel gerçekleştirilmiş hız bilgisi */
		}SPN;
	}Message03;

	EEM_U32	Message04_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_BOOL_T	BCM_SCB_startRecord_u1 		 : 1    ;  /* Kamera kaydını başlatacak biti tutar.	*/
			EEM_BOOL_T	BCM_SCB_stopRecord_u1		 : 1	;  /* Kamera kaydını durduracak biti tutar.	*/
			EEM_BOOL_T	BCM_SCB_deleteRecord_u1      : 1	;  /* Kamera kaydını iptal edecek biti tutar.	*/
			EEM_BOOL_T	BCM_SCB_sdCardErase_u1       : 1	;  /* Kamera kaydını sd karttan silecek biti tutar.	*/
			EEM_BOOL_T	BCM_SCB_sdCardSave_u1        : 1	;  /* Kamera kaydını sd karta kaydedecek biti tutar.	*/
			EEM_BOOL_T	BCM_SCB_dashBoardState_u1    : 1	;  /* Dashboard aktif pasif-durumunu tutar.	*/
			EEM_BOOL_T	BCM_SCB_dashBoardCmd01_u1    : 1	;  /* BCM'den SCB'ye gönderilen 1. komut -> ......... komutu	*/
			EEM_BOOL_T	BCM_SCB_dashBoardCmd02_u1    : 1	;  /* BCM'den SCB'ye gönderilen 2. komut -> ......... komutu*/
			EEM_BOOL_T	BCM_SCB_dashBoardCmd03_u1    : 1	;  /* BCM'den SCB'ye gönderilen 3. komut -> ......... komutu*/
			EEM_BOOL_T	BCM_SCB_dashBoardCmd04_u1    : 1	;  /* BCM'den SCB'ye gönderilen 4. komut -> ......... komutu*/
			EEM_U8		:1; /* RFU */
			EEM_BOOL_T	BCM_SCB_ignitionStatus_u1    : 1	;  /* Kontağın açık/kapalı bilgisini tutar. */
			EEM_U8		:1; /* RFU */
			EEM_BOOL_T	BCM_SCB_leftSignal_u1        : 1	;  /* Sol sinyalin açık/kapalı bilgisini tutar. */
			EEM_BOOL_T	BCM_SCB_rightSignal_u1       : 1	;  /* Sağ sinyalin açık/kapalı bilgisini tutar. */
			EEM_BOOL_T	BCM_SCB_frontLight_u1        : 1	;  /* Ön farların açık/kapalı bilgisini tutar.	*/
			EEM_BOOL_T	BCM_SCB_backLight_u1         : 1	;  /* Arka farların açık/kapalı bilgisini tutar.	*/
			EEM_BOOL_T	BCM_SCB_signalLight_u1       : 1	;  /* Dörtlü sinyallerin açık/kapalı bilgisini tutar. */
			EEM_U8		:1; /* RFU */
			EEM_U16		BCM_SCB_spinnerAngle_u16	 : 16	;  /* Direksiyonun açı bilgisini tutar. */
			EEM_U16		BCM_SCB_gasPedalAnalog_u16   : 16	;  /* Gaz pedalından okunan değeri tutar.		*/
			EEM_U16		BCM_SCB_brakePedalAnalog_u16 : 16	;  /* Fren pedalından okunan değeri tutar.		*/
			EEM_BOOL_T  BCM_SCB_leftDirection_u1 	 : 1    ; /*  Aracın sağa/sola gittiği bilgisini tutar.					*/
			EEM_BOOL_T  BCM_SCB_rightDirection_u1 	 : 1    ; /*  Aracın ileri/geri gittiği bilgisini tutar.					*/
		}SPN;
	}Message04;

	EEM_U32 Message05_ID;
	union{

			EEM_U8 payload[8];
			struct{
				EEM_U16 BCM_leftGyro_u16  	: 16  ; /* Sol motorun gyro bilgisini  tutar.					 */
				EEM_U16 BCM_leftAcc_u16  	: 16  ; /* Sol motorun ivme bilgisini tutar.					 */
				EEM_U16 BCM_rightGyro_u16   : 16  ; /* Sağ motorun gyro bilgisini  tutar. 					 */
				EEM_U16 BCM_rightAcc_u16  	: 16  ; /* Sağ motorun ivme bilgisini tutar.					 */
			}SPN;
		}Message05;

	EEM_U32 Message11_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U64 BCM_MS1_Speed     	: 64  ; /*  */
		}SPN;
	}Message11;

	EEM_U32 Message12_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U64 BCM_MS2_Speed     	 : 64  ; /*  */
		}SPN;
	}Message12;

	EEM_U32 Message19_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8  BCM_MS1_Mode	:8;
			EEM_U64 dummy :56;
		}SPN;
	}Message19;

	EEM_U32 Message20_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8 BCM_MS2_Mode: 8	 ;
			EEM_U64 dummy : 56;
			}SPN;
	    }Message20;


}BCM_Module_st;

/*
 * Simple Computer Message Class
 */
typedef struct
{
	EEM_U32	Message21_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_BOOL_T 	SCB_cameraStartACK_u1 			: 1 ;
			EEM_BOOL_T	SCB_cameraStartNACK_u1			: 1 ;
			EEM_BOOL_T	SCB_cameraStopACK_u1			: 1 ;
			EEM_BOOL_T	SCB_cameraStopNACK_u1			: 1 ;
			EEM_BOOL_T	SCB_sdCardErase_ACK_u1			: 1 ;
			EEM_BOOL_T	SCB_sdCardErase_NACK_u1			: 1 ;
			EEM_BOOL_T	SCB_sdCardSave_ACK_u1			: 1 ;
			EEM_BOOL_T	SCB_sdCardSave_NACK_u1			: 1 ;
			EEM_U8		SCB_loggerByte01 				: 8 ;
			EEM_U8		SCB_loggerByte02 				: 8 ;
			EEM_U8		SCB_loggerByte03 				: 8 ;
			EEM_U8		SCB_loggerByte04 				: 8 ;
			EEM_U8		SCB_loggerByte05 				: 8 ;
			EEM_U8		SCB_loggerByte06 				: 8 ;
		}SPN;
	}Message21;

}SCB_Module_st;

/*
 * BMS Message Class
 */
typedef struct
{
	EEM_U32 Message06_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U16 BMS_cell01Voltage_u16  	: 16  ; /* Batarya Grubu 1. Hücre Gerilimini tutar.	 */
			EEM_U16 BMS_cell02Voltage_u16  	: 16  ; /* Batarya Grubu 2. Hücre Gerilimini tutar.  */
			EEM_U16 BMS_cell03Voltage_u16   : 16  ; /* Batarya Grubu 3. Hücre Gerilimini tutar.  */
			EEM_U16 BMS_cell04Voltage_u16  	: 16  ; /* Batarya Grubu 4. Hücre Gerilimini tutar.  */
		}SPN;
	}Message06;

	EEM_U32 Message07_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U16 BMS_cell05Voltage_u16  	: 16  ; /* Batarya Grubu 5. Hücre Gerilimini tutar.	 */
			EEM_U16 BMS_cell06Voltage_u16  	: 16  ; /* Batarya Grubu 6. Hücre Gerilimini tutar.  */
			EEM_U16 BMS_cell07Voltage_u16   : 16  ; /* Batarya Grubu 7. Hücre Gerilimini tutar.  */
			EEM_U16 BMS_cell08Voltage_u16  	: 16  ; /* Batarya Grubu 8. Hücre Gerilimini tutar.  */
		}SPN;
	}Message07;

	EEM_U32 Message08_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U16 BMS_cell09Voltage_u16  	: 16  ; /* Batarya Grubu 9. Hücre Gerilimini tutar.	 */
			EEM_U16 BMS_cell10Voltage_u16  	: 16  ; /* Batarya Grubu 10. Hücre Gerilimini tutar. */
			EEM_U16 BMS_cell11Voltage_u16   : 16  ; /* Batarya Grubu 11. Hücre Gerilimini tutar. */
			EEM_U16 BMS_cell12Voltage_u16  	: 16  ; /* Batarya Grubu 12. Hücre Gerilimini tutar. */
		}SPN;
	}Message08;

	EEM_U32 Message09_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U16 BMS_cell13Voltage_u16  	: 16  ; /* Batarya Grubu 11. Hücre Gerilimini tutar.	*/
			EEM_U16 BMS_cell14Voltage_u16  	: 16  ; /* Batarya Grubu 12. Hücre Gerilimini tutar. 	*/
			EEM_U16 BMS_cell15Voltage_u16   : 16  ; /* Batarya Grubu 13. Hücre Gerilimini tutar. 	*/
			EEM_U16 BMS_cell16Voltage_u16  	: 16  ; /* Batarya Grubu 14. Hücre Gerilimini tutar. 	*/
		}SPN;
	}Message09;

	EEM_U32 Message10_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U16 BMS_cell17Voltage_u16  	: 16  ; /* Batarya Grubu 15. Hücre Gerilimini tutar.	 */
			EEM_U16 BMS_cell18Voltage_u16  	: 16  ; /* Batarya Grubu 16. Hücre Gerilimini tutar. 	 */
			EEM_U16 BMS_lineCurrent_u16   	: 16  ; /* Batarya Grubu hat akımını tutar. 			 */
			EEM_U16 BMS_temperatureVal_u16 	: 16  ; /* Batarya Grubu sıcaklık değerini tutar.		 */
		}SPN;
	}Message10;

}BMS_Module_st;

/*
 * Motor Driver - 1 Message Class
 */
typedef struct
{
	EEM_U32 Message13_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8  MS1_Mode			: 8	 ;
			EEM_U16 MS1_temperature		: 16 ;
			EEM_U8  MS1_warningFlag01   : 1  ;
			EEM_U8  MS1_warningFlag02	: 1  ;
			EEM_U8  MS1_warningFlag03	: 1  ;
			EEM_U8  MS1_warningFlag04	: 1  ;
			EEM_U8  MS1_warningFlag05	: 1  ;
			EEM_U8  MS1_warningFlag06	: 1  ;
			EEM_U8  MS1_warningFlag07	: 1  ;
			EEM_U8  MS1_warningFlag08	: 1  ;
			EEM_U8  MS1_errorFlag01		: 1  ;
			EEM_U8  MS1_errorFlag02		: 1  ;
			EEM_U8  MS1_errorFlag03		: 1  ;
			EEM_U8  MS1_errorFlag04		: 1  ;
			EEM_U8  MS1_errorFlag05		: 1  ;
			EEM_U8  MS1_errorFlag06		: 1  ;
			EEM_U8  MS1_errorFlag07		: 1  ;
			EEM_U8  MS1_errorFlag08		: 1  ;
			EEM_U8  MS1_statusBit01		: 1  ;
			EEM_U8  MS1_statusBit02		: 1  ;
			EEM_U8  MS1_statusBit03		: 1  ;
			EEM_U8  MS1_statusBit04		: 1  ;
			EEM_U8  MS1_statusBit05		: 1  ;
			EEM_U8  MS1_statusBit06		: 1  ;
			EEM_U8  MS1_statusBit07		: 1  ;
			EEM_U8  MS1_statusBit08		: 1  ;
			EEM_U8  MS1_dummyByte01		: 8	 ;
		}SPN;
	}Message13;

	EEM_U32 Message14_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U32 MS1_voltage       	 	: 16 ; /*  */
			EEM_U16 MS1_PhaseUCurrent       : 16 ; /*  */
			EEM_U16 MS1_PhaseVCurrent       : 16 ;
			EEM_U16 MS1_PhaseWCurrent       : 16 ;
		}SPN;
	}Message14; /* 0x07 */

	EEM_U32 Message15_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U64 MS1_SpeedVal : 64 ;
		}SPN;
	}Message15;

}MS1_Module_st;

/*
 * Motor Driver - 2 Message  Class
 */
typedef struct
{

	EEM_U32 Message16_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8  MS2_Mode			: 8	 ;
			EEM_U16 MS2_temperature		: 16 ;
			EEM_U8  MS2_warningFlag01   : 1  ;
			EEM_U8  MS2_warningFlag02	: 1  ;
			EEM_U8  MS2_warningFlag03	: 1  ;
			EEM_U8  MS2_warningFlag04	: 1  ;
			EEM_U8  MS2_warningFlag05	: 1  ;
			EEM_U8  MS2_warningFlag06	: 1  ;
			EEM_U8  MS2_warningFlag07	: 1  ;
			EEM_U8  MS2_warningFlag08	: 1  ;
			EEM_U8  MS2_errorFlag01		: 1  ;
			EEM_U8  MS2_errorFlag02		: 1  ;
			EEM_U8  MS2_errorFlag03		: 1  ;
			EEM_U8  MS2_errorFlag04		: 1  ;
			EEM_U8  MS2_errorFlag05		: 1  ;
			EEM_U8  MS2_errorFlag06		: 1  ;
			EEM_U8  MS2_errorFlag07		: 1  ;
			EEM_U8  MS2_errorFlag08		: 1  ;
			EEM_U8  MS2_statusBit01		: 1  ;
			EEM_U8  MS2_statusBit02		: 1  ;
			EEM_U8  MS2_statusBit03		: 1  ;
			EEM_U8  MS2_statusBit04		: 1  ;
			EEM_U8  MS2_statusBit05		: 1  ;
			EEM_U8  MS2_statusBit06		: 1  ;
			EEM_U8  MS2_statusBit07		: 1  ;
			EEM_U8  MS2_statusBit08		: 1  ;
			EEM_U8  MS2_dummyByte01		: 8	 ;
		}SPN;
	}Message16;

	EEM_U32 Message17_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U32 MS2_voltage       	 	: 16 ; /*  */
			EEM_U16 MS2_PhaseUCurrent       : 16 ; /*  */
			EEM_U16 MS2_PhaseVCurrent       : 16 ;
			EEM_U16 MS2_PhaseWCurrent       : 16 ;
		}SPN;
	}Message17;

	EEM_U32 Message18_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U64 MS2_SpeedVal : 64 ;
		}SPN;
	}Message18;

}MS2_Module_st;

/*
 * Isolation watch Message Class
 */
typedef struct
{
	//@LATER
}ISO_Module_st;

/*
 * Telemetry Hand Connection Message Class
 */
typedef struct
{
	EEM_U32	Message22_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8 TLM_wifiStatus_u8 : 8 ;
			EEM_U8 TLM_wifiCmd01_u8  : 8 ;
			EEM_U8 TLM_wifiCmd02_u8  : 8 ;
			EEM_U8 TLM_wifiCmd03_u8  : 8 ;
			EEM_U8 TLM_wifiCmd04_u8  : 8 ;
			EEM_U8 TLM_wifiCmd05_u8  : 8 ;
			EEM_U8 TLM_wifiCmd06_u8  : 8 ;
			EEM_U8 TLM_wifiCmd07_u8  : 8 ;
		}SPN;
	}Message22;

	EEM_U32	Message23_ID;
	union{
		EEM_U8 payload[8];
		struct{
			EEM_U8 TLM_rfStatus_u8 : 8 ;
			EEM_U8 TLM_rfCmd01_u8  : 8 ;
			EEM_U8 TLM_rfCmd02_u8  : 8 ;
			EEM_U8 TLM_rfCmd03_u8  : 8 ;
			EEM_U8 TLM_rfCmd04_u8  : 8 ;
			EEM_U8 TLM_rfCmd05_u8  : 8 ;
			EEM_U8 TLM_rfCmd06_u8  : 8 ;
			EEM_U8 TLM_rfCmd07_u8  : 8 ;
		}SPN;
	}Message23;

	//@LATER
}TLM_Module_st;

/*
 * Charging Unit Message Class
 */
typedef struct
{
	//@LATER
}YSB_Module_st;


#endif /* __EEMPROCOTOL_CONFIG_H__ */
/***********************************END OF FILE********************************/

