/******************************************************************************
[COPYRIGHT INFORMATION]
* COMPANY: VARROC ENGINEERING LTD.
* FILE NAME: CAN_IF_CFG.h
* AUTHOR: ANANDHAN T
* CURRENT VERSION: V1.00.00
*(HERE VERSION IS MAINTAINED AS MAJOR.MINOR.PATCH - REFER VERSION CONTROL 
DOCUMENT FOR FURTHER DETAILS)
* DATE: 29-MAR-2023
* OPERATING ENVIRONMENT: C
* DESCRIPTION:  CAN STACK CONFIGURATION HEADER FILE. (THIS FILE CONTAINS THE 
DECLARATION OF THE CONFIG TYPES AND CONFIG VARIABLES)
* CAUTION NOTE: CAUTION RELATED TO FILE                    

THIS FILE/CODE CONTAINS INFORMATION THAT IS PROPRIETARY TO VARROC ENGINEERING 
LTD.NO PART OF THIS DOCUMENT/CODE MAY BE REPRODUCED OR USED IN WHOLE OR PART 
IN ANY FORM OR BY ANY MEANS - GRAPHIC, ELECTRONIC OR MECHANICAL WITHOUT THE 
WRITTEN PERMISSION OF VARROC ENGINEERING LTD.
******************************************************************************/

/*****************************************************************************/

#ifndef CANIF_CFG_H
#define CANIF_CFG_H

/******************************************************************************
 [P R A G M A S]
 *****************************************************************************/
/****************************** END OF PRAGMAS *******************************/

/******************************************************************************
 [I N C L U D E  F I L E S]
 *****************************************************************************/

#include "CAN_Common.h"
#include "Can_MessageQueue.h"
#include "Com_CFG.h"
#include "CAN_TP_CFG.h"


/*************************** END OF INCLUDE FILES ****************************/

/******************************************************************************
 [M A C R O S]
 *****************************************************************************/

#define FILTCFG_COUNT                   3U
#define TXHWOBJ_COUNT                   4U
#define CAN_RXBUFF_COUNT                3U
#define TXQCFG_COUNT 	                  4U

/*CAN DRIVER COMPILE TIME CONFIGURATIONS*/

#define CANCFG_RXFIFO0_ENABLE      1U
#define CANCFG_RXFIFO1_ENABLE      1U
#define CANCFG_RXFIFO_ENABLE            CANCFG_RXFIFO0_ENABLE ||\
                                        CANCFG_RXFIFO1_ENABLE

#if CANCFG_RXFIFO_ENABLE
/*Valid Values 1(4buffer),2(8buffer),3(16buffer) */
/*NOTE: Sum of Rx Buffers should not exceed 16(Max Buff)*/
#define CANCFG_RXFIFO0_LEN         1U 
#define CANCFG_RXFIFO1_LEN         1U /*Valid Values 1(4buffer),2(8buffer),
                                            3(16 buffer)  4,8,16*/
#endif

#define CANCFG_RXFIFO0_INT_ENABLE  1U /* 0-DISABLE, 1-ENABLE*/
#define CANCFG_RXFIFO1_INT_ENABLE  1U /* 0-DISABLE, 1-ENABLE*/

#define CAN_HW_BUFF_TX_MAX         4U
#define CAN_FILT_CFG_MAX           4U

/*TX and RX Queue Configurations*/
#define RXQUEUE_ENABLE             1U

#if RXQUEUE_ENABLE
#define CAN_RXQ_LEN                6U
#endif

#define CanIf_GetTxBuffConfigInst()		  TxBuffConfigTable_st
#define CanIf_GetTxBuffConfig(index)	  (CanIf_GetTxBuffConfigInst()[(index)])
#define CanIf_SetBuffSts(index, value)	((CanIf_GetTxBuffConfig(index).obj_sts)\
                                        = (value))

#define CanIf_GetTxQueueInst()			    TxQueue_st
#define CanIf_GetTxQueue(index)			    (CanIf_GetTxQueueInst()[(index)])

#define CanIf_GetTxCfgInst()			      IfTxCfgs_st
#define CanIf_GetTxCfg(index)			      (CanIf_GetTxCfgInst()[(index)])

#define COMTXMSGMAX \
                sizeof(ComTxMsgInfoTable_st)/sizeof(ComTxMsgInfoTable_st[0])

#define TPTXMSGMAX \
                sizeof(TpIdTx_st)/sizeof(TpIdTx_st[0])

#define CAN_TXMSGMAX (COMTXMSGMAX + TPTXMSGMAX)

#define COM_GetTxMsgIDInst()			    ComTxMsgInfoTable_st
#define COM_GetTxMsgID(index)			    (COM_GetTxMsgIDInst()[(index)].pdu.MsgID)

#define TP_GetTxMsgIDInst()			      TpIdTx_st
#define TP_GetTxMsgID(index)			    (TP_GetTxMsgIDInst()[(index)].TpTx_id)


#define COMRXMSGMAX \
                sizeof(ComRxMsgInfoTable_st)/sizeof(ComRxMsgInfoTable_st[0])

#define TPRXMSGMAX \
                sizeof(TpIdRx_st)/sizeof(TpIdRx_st[0])

#define CAN_RXMSGMAX (COMRXMSGMAX + TPRXMSGMAX)

#define COM_GetRxMsgIDInst()			    ComTxMsgInfoTable_st
#define COM_GetRxMsgID(index)			    (COM_GetRxMsgIDInst()[(index)].pdu.MsgID)

#define TP_GetRxMsgIDInst()			      TpIdRx_st
#define TP_GetRxMsgID(index)			    (TP_GetRxMsgIDInst()[(index)].TpRx_id)

/****************************** END OF MACROS ********************************/

/******************************************************************************
 [E N U M E R A T O R S]
 *****************************************************************************/

typedef enum
{
  Can_MB      = 0,
  Can_TxFIFO  = 1,
  Can_RxFIFO  = 2
} CANBUFTYPE_EN;

typedef enum
{
	CAN_OBJ_IDLE = 0,
	CAN_OBJ_BUSY = 1
} CANHWOBJSTATUS_EN;

typedef enum
{
  COM_TYPE = 0,
  TP_TYPE  = 1,
}MSGTYPE_EN;


/**************************** END OF ENUMERATORS *****************************/

/******************************************************************************
 [T Y P E D E F S]
 *****************************************************************************/

typedef uint8_t FiltHdlType_t;

typedef uint8_t IFQCfgHdlType_t;

typedef struct
{
  CanIDType_t Code;
  CanIDType_t Mask;
} CANFILTERCFG_ST;

typedef struct
{
  CANBUFTYPE_EN     type;
  uint8_t           buff_id  : 6;
  CANHWOBJSTATUS_EN obj_sts;
} CANPDUBUFFINFO_ST;

typedef struct
{
  CANBUFTYPE_EN type;
  uint8_t       buff_id  : 6;
  FiltHdlType_t fhdl; 
} CANRXBUFFINFO_ST;

typedef struct
{
	HwHandleType_t hth;
	CAN_LLFRAME_ST ll_pdu;
} IFTXPDUCONFIGTYPE_ST;

typedef struct 
{
	IFQCfgHdlType_t QCfg_hdl;
} IFTXCFGS_ST;

typedef struct
{
  CanIDType_t    msgid;
  MSGTYPE_EN  type;
}MsgIdPduInfo_ST;

/****************************** END OF TYPEDEFS ******************************/

/******************************************************************************
[F U N C T I O N  P R O T O T Y P E S] 
 *****************************************************************************/
/************************ END OF FUNCTION PROTOTYPES *************************/

/******************************************************************************
[E X T E R N  D E C L A R A T I O N
******************************************************************************/

extern CANFILTERCFG_ST FilterCfgTable_st[FILTCFG_COUNT];

extern CANPDUBUFFINFO_ST TxBuffConfigTable_st[TXHWOBJ_COUNT];

extern CANRXBUFFINFO_ST RxBuffConfigTable_st[CAN_RXBUFF_COUNT];

extern IFTXPDUCONFIGTYPE_ST TxInfoTable_st[CAN_TXMSGMAX];

extern CANMSGQ_ST TxQueue_st[TXQCFG_COUNT];

extern IFTXCFGS_ST IfTxCfgs_st[TXHWOBJ_COUNT];

extern MsgIdPduInfo_ST TxMsgPduInfo_st[CAN_TXMSGMAX];
extern MsgIdPduInfo_ST RxMsgPduInfo_st[CAN_RXMSGMAX];

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
