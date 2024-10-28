/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  Copyright (c) 2022 by Ielektron Technologies Pvt Ltd.                                              All rights reserved.
 *
 *                This software is copyright protected and proprietary to Ielektron Technologies Pvt Ltd.
 *                Ielektron Technologies Pvt Ltd grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Ielektron Technologies Pvt Ltd.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  CAN_StackCfg.h
 *        \brief  CAN Stack configuration header file.
 *
 *      \details  This file contains the declaration of the Config types and Config variables
 *
 *********************************************************************************************************************/

#ifndef CAN_STACK_CFG_H
#define CAN_STACK_CFG_H

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/

#include "CAN_Common.h"

#include "Can_MessageQueue.h"
#include "CAN_UserCfg.h"

/**********************************************************************************************************************
*  GLOBAL CONSTANT MACROS / GLOBAL FUNCTION MACROS
*********************************************************************************************************************/

#define FILTCFG_COUNT 3
#define TXHWOBJ_COUNT 4
#define CAN_RXBUFF_COUNT 3
#define TXQCFG_COUNT 	2

/*CAN DRIVER COMPILE TIME CONFIGURATIONS*/

#define CANCFG_RXFIFO0_ENABLE     1
#define CANCFG_RXFIFO1_ENABLE     1
#define CANCFG_RXFIFO_ENABLE     CANCFG_RXFIFO0_ENABLE || CANCFG_RXFIFO1_ENABLE

#if CANCFG_RXFIFO_ENABLE
/*Valid Values 1(4buffer),2(8buffer),3(16buffer) */
/*NOTE: Sum of Rx Buffers should not exceed 16(Max Buff)*/
#define CANCFG_RXFIFO0_LEN            1 
#define CANCFG_RXFIFO1_LEN            1 /*Valid Values 1(4buffer),2(8buffer),3(16 buffer)  4,8,16*/
#endif

#define CANCFG_RXFIFO0_INT_ENABLE       1 /* 0-DISABLE, 1-ENABLE*/
#define CANCFG_RXFIFO1_INT_ENABLE       1 /* 0-DISABLE, 1-ENABLE*/

#define CAN_HW_BUFF_TX_MAX          4
#define CAN_FILT_CFG_MAX            4

#define CanIf_GetTxBuffConfigInst()							TxBuffConfigTable
#define CanIf_GetTxBuffConfig(index)						(CanIf_GetTxBuffConfigInst()[(index)])
#define CanIf_SetBuffSts(index, value)				(CanIf_GetTxBuffConfig(index).obj_sts = value)

#define CanIf_GetTxQueueInst()				TxQueue
#define CanIf_GetTxQueue(index)				(CanIf_GetTxQueueInst()[(index)])

#define CanIf_GetTxCfgInst()				If_TxCfgs
#define CanIf_GetTxCfg(index)				(CanIf_GetTxCfgInst()[(index)])

/**********************************************************************************************************************
*  GLOBAL DATA TYPES AND STRUCTURES
*********************************************************************************************************************/

typedef uint8_t FiltHdlType;
typedef uint8_t IF_QCfg_HdlType;

typedef enum
{
    Can_MB = 0,
    Can_TxFIFO = 1,
    Can_RxFIFO = 2
} CanBufType_t;

typedef enum
{
	CAN_OBJ_IDLE = 0,
	CAN_OBJ_BUSY = 1
} CanHwObjStatus_t;

typedef struct
{
    CanIDType Code;
    CanIDType Mask;
} CanFilterCfg_t;

typedef struct
{
    CanBufType_t type   : 2;
    uint8_t buff_id     : 6;
    CanHwObjStatus_t obj_sts;
} CanPduBuffInfo_t;

typedef struct
{
    CanBufType_t type   : 2;
    uint8_t buff_id     : 6;
    FiltHdlType fhdl; 
} CanRxBuffInfo_t;

typedef struct
{
	HwHandleType hth;
	Can_LLFrame_t ll_pdu;
} If_TxPduConfigType_t;

typedef struct 
{
	IF_QCfg_HdlType QCfg_hdl;
} If_TxCfgs_t;

/**********************************************************************************************************************
*  GLOBAL DATA
**********************************************************************************************************************/

extern CanFilterCfg_t FilterCfgTable[FILTCFG_COUNT];
extern CanPduBuffInfo_t TxBuffConfigTable[TXHWOBJ_COUNT];
extern CanRxBuffInfo_t RxBuffConfigTable[CAN_RXBUFF_COUNT];
extern If_TxPduConfigType_t xTxInfoTable[CAN_TXMESSAGE_MAX];
extern CanMsgQ_t TxQueue[TXQCFG_COUNT];
extern If_TxCfgs_t If_TxCfgs[TXHWOBJ_COUNT];

#endif /* CAN_STACK_CFG_H */


/**********************************************************************************************************************
*  END OF FILE: CAN_StackCfg.h
*********************************************************************************************************************/


