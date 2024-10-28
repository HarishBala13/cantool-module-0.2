/******************************************************************************
[COPYRIGHT INFORMATION]
* COMPANY: VARROC ENGINEERING LTD.
* FILE NAME: Com_CFG.h
* AUTHOR: ANANDHAN T
* CURRENT VERSION: V1.00.00
*(HERE VERSION IS MAINTAINED AS MAJOR.MINOR.PATCH - REFER VERSION CONTROL 
DOCUMENT FOR FURTHER DETAILS)
* DATE: 29-MAR-2023
* OPERATING ENVIRONMENT: C
* DESCRIPTION:  CAN USER CONFIGURATION HEADER FILE. (THIS FILE CONTAINS THE 
DECLARATION OF THE CONFIG TYPES AND CONFIG VARIABLES)
* CAUTION NOTE: CAUTION RELATED TO FILE                    

THIS FILE/CODE CONTAINS INFORMATION THAT IS PROPRIETARY TO VARROC ENGINEERING 
LTD.NO PART OF THIS DOCUMENT/CODE MAY BE REPRODUCED OR USED IN WHOLE OR PART 
IN ANY FORM OR BY ANY MEANS - GRAPHIC, ELECTRONIC OR MECHANICAL WITHOUT THE 
WRITTEN PERMISSION OF VARROC ENGINEERING LTD.
******************************************************************************/

/*****************************************************************************/

#ifndef COM_CFG_H
#define COM_CFG_H

/******************************************************************************
 [P R A G M A S]
 *****************************************************************************/
/****************************** END OF PRAGMAS *******************************/

/******************************************************************************
 [I N C L U D E  F I L E S]
 *****************************************************************************/

#include "CAN_Common.h"

/*************************** END OF INCLUDE FILES ****************************/

/******************************************************************************
 [M A C R O S]
 *****************************************************************************/

#define MAX_MESSAGES 	  	 5U

#define COM_TXMESSAGE_MAX  3U
#define COM_RXMESSAGE_MAX  5U

#define BIG_ENDIAN_SIGNALS 1U

#define COM_GETTXMSGINST()						ComTxMsgInfoTable_st
#define COM_GETTXMESSAGEHDL(index)		(COM_GETTXMSGINST()[(index)])

#define COM_GETRXMSGINST()						ComRxMsgInfoTable_st
#define COM_GETRXMESSAGEHDL(index)		(COM_GETRXMSGINST()[(index)])
#define COM_GET_RXMSGINFO_HDL(index)	(COM_GETRXMSGINST()[(index)].msg_info)
#define COM_GETRXMESSAGEID(index)			(COM_GET_RXMSGINFO_HDL(index).pdu.MsgID)

#define Can_GetEventCallbackHdl()			(CanEventCB_Handle)

#define COM_ZERO 	0U
#define COM_ONE  	1U
#define COM_TWO  	2U
#define COM_THREE 3U
#define COM_FOUR	4U
#define COM_FIVE  5U
#define COM_SIX		6U
#define COM_EIGHT	8U
#define COM_NULL 	0U

#define IDU1_SIG_COUNT 3U
#define EMS1_SIG_COUNT 3U
#define EMS2_SIG_COUNT 1U
#define EMS4_SIG_COUNT 1U
#define MUX_SIG_COUNT  7U
#define EXTD_SIG_COUNT 1U


/****************************** END OF MACROS ********************************/

/******************************************************************************
 [E N U M E R A T O R S]
 *****************************************************************************/
/**************************** END OF ENUMERATORS *****************************/

/******************************************************************************
 [T Y P E D E F S]
 *****************************************************************************/

typedef uint8_t MsgInfoHdlType_t;

typedef void (*ComMessageCmplCB_t) (PduId_t msgId);

typedef struct
{
  uint8_t start_bit;
  uint8_t len;
} COMSIGINFO_ST;

/*callback - If the message is Receive message then this callback is used to 
for RxNotification, or Tx Confirmation notification*/

/*toutcallback - If the message is Receive message then this callback is used 
to for Rxtimeout, or Tx timeout notification*/

typedef struct
{
	uint8_t 						pduid;
  COMSIGINFO_ST 			*siginfo;
  uint8_t        			sig_count; 
	uint16_t       			period;
  CAN_PDUTYPE_ST 			pdu;
} COMMESSAGEINFO_ST;

typedef struct
{
	COMMESSAGEINFO_ST  msg_info;
	ComMessageCmplCB_t callback;
	ComMessageCmplCB_t toutcallback;
	CAN_RXNOTI_TYPE_EN noti_type;
} COM_RXMESSAGEINFO_ST;

typedef struct 
{
	uint8_t  Sig_EngSovStatus_u2	: 2;
	uint8_t  Sig_TankSovStatus_u2 : 2;
	uint8_t  Sig_IDUFeedback_u2   : 2;
} CanMsg_IDU1_Info_t;

typedef struct 
{
	uint8_t  Sig_EngSpeed_u8;
	uint8_t  Sig_EngSov_u1    : 1;
	uint8_t  SigTnakSov_u1    : 1;
} CanMsg_EMS1_Info_t;

typedef struct 
{
	uint16_t Sig_EngTemperature_u16;
} CanMsg_EMS2_Info_t;

typedef struct 
{
	uint8_t  Sig_OverheatTempActive_u1    : 1;
} CanMsg_EMS4_Info_t;

typedef void (*CanErrorEventCB) (BUS_ERRORS_EN err, uint16_t err_flag);

typedef struct
{
	CanErrorEventCB bus_err_cb;
} CANEVENT_CALLBACKS_ST;


typedef struct 
{
	uint8_t 	SigMux 	: 2;
	union 
	{
		/*SIGNAL GROUP 1*/
		struct 
		{
			uint32_t 	Sig1		: 30;
			uint8_t 	Sig2;
		}sig_group1; 
		
    /*SIGNAL GROUP 2*/
		struct 
		{
			uint32_t 	Sig3	  : 24;
			uint32_t 	Sig4 		: 18;
			uint8_t   Sig5 		:  5;
		}sig_group2;

		/*SIGNAL GROUP 3*/
		struct 
		{
			uint32_t Sig6;
		}sig_group3;
		

	}signals;

} CanMsgMux_t;

typedef struct 
{
	uint16_t  TestSig  : 15;
} CanMsg_Extd_t;

/****************************** END OF TYPEDEFS ******************************/

/******************************************************************************
[F U N C T I O N  P R O T O T Y P E S] 
 *****************************************************************************/
/************************ END OF FUNCTION PROTOTYPES *************************/

/******************************************************************************
[E X T E R N  D E C L A R A T I O N
******************************************************************************/

extern COMMESSAGEINFO_ST ComTxMsgInfoTable_st[COM_TXMESSAGE_MAX];

extern COM_RXMESSAGEINFO_ST ComRxMsgInfoTable_st[COM_RXMESSAGE_MAX];

extern CANEVENT_CALLBACKS_ST CanEventCB_Handle;

/************************ END OF EXTERN DECLARATIONS *************************/
#endif

/******************************************************************************
[C H A N G E  H I S T O R Y]
*******************************************************************************
VERSION 	DATE        		AUTHOR     			DESCRIPTION
V1.1		29-MAR-2023		ANANDHAN T				INITIAL VERSION
******** *********** ********** ***********************************************
******************************************************************************/

/**************************END OF FILE INFO***********************************/
