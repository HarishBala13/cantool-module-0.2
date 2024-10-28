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
/**        \file  CAN_StackCfg.c
 *        \brief  CAN User configuration Source file.
 *
 *      \details  This file contains the declaration and initializationConfig variables
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/

#include "CAN_StackCfg.h"

/**********************************************************************************************************************
*  LOCAL CONSTANT MACROS / LOCAL FUNCTION MACROS
*********************************************************************************************************************/

#define TXQ1_BUFF_SIZE 5
#define TXQ1_TYPE Can_PriorityQueue

#define TXQ2_BUFF_SIZE 3
#define TXQ2_TYPE Can_FifoQueue

/**********************************************************************************************************************
*  GLOBAL DATA
**********************************************************************************************************************/

/* RX FIlter configuration */
CanFilterCfg_t FilterCfgTable[FILTCFG_COUNT] = {
	{0x500,0xFFFF}, /* FULL CAN */
	{0x400,0x7CF}, /* BASIC CAN */
	{0x200,0x3CF}, /* BASIC CAN */
};

/* TX Buffer configuration */
CanPduBuffInfo_t TxBuffConfigTable[TXHWOBJ_COUNT] = {
	{Can_MB,0,CAN_OBJ_IDLE},
	{Can_MB,1,CAN_OBJ_IDLE},
	{Can_MB,2,CAN_OBJ_IDLE},
	{Can_MB,CAN_HW_BUFF_TX_MAX,CAN_OBJ_IDLE},
};

/* RX Buffer configuration */
CanRxBuffInfo_t RxBuffConfigTable[CAN_RXBUFF_COUNT] = {
	{Can_MB,0,0},
	{Can_RxFIFO,0,1},
	{Can_RxFIFO,1,2},
};

/* TX PDU to Buffer Mapping */
If_TxPduConfigType_t xTxInfoTable[CAN_TXMESSAGE_MAX] = {
	{0},
	{1},
	{2},
	{2},
};

pduHdl IfQueue_Buff1[TXQ1_BUFF_SIZE] = {0};
pduHdl IfQueue_Buff2[TXQ2_BUFF_SIZE] = {0};

Can_LLFrame_t* GetTxMsgHdl (pduHdl hdl);

/* Tx Queue configuration */
CanMsgQ_t TxQueue[TXQCFG_COUNT] = {
	{{0,0,TXQ1_BUFF_SIZE},TXQ1_TYPE,IfQueue_Buff1,GetTxMsgHdl},
	{{0,0,TXQ2_BUFF_SIZE},TXQ2_TYPE,IfQueue_Buff2,GetTxMsgHdl},
};

Can_LLFrame_t* GetTxMsgHdl (pduHdl hdl)
{
	if (CAN_TXMESSAGE_MAX <= hdl) {
		hdl = 0;
		DET_ERR_REPORT(CANIF_MODULE_ID,DET_APIID_GENERIC,DET_ERR_PDUINVALID);
	}
	return &xTxInfoTable[hdl].ll_pdu;
}

/* Tx Queue to Buffer configuration */
/* One Tx Queue instance should be mapped to one tx HW buffer*/
If_TxCfgs_t If_TxCfgs[TXHWOBJ_COUNT] = {
	{0},
	{HW_HDL_INV_U8},
	{1},
	{HW_HDL_INV_U8}
};

/**********************************************************************************************************************
*  END OF FILE: CAN_StackCfg.c
*********************************************************************************************************************/

