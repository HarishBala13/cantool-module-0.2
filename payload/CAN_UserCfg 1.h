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
/**        \file  Can_UserCfg.h
 *        \brief  CAN User configuration header file.
 *
 *      \details  This file contains the declaration of the Config types and Config variables
 *
 *********************************************************************************************************************/

#ifndef CAN_USER_CFG_H
#define CAN_USER_CFG_H

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/

#include "CAN_Common.h"

/**********************************************************************************************************************
*  GLOBAL CONSTANT MACROS
*********************************************************************************************************************/

#define MAX_MESSAGES 5
#define CAN_TXMESSAGE_MAX 4
#define CAN_RXMESSAGE_MAX 5

/**********************************************************************************************************************
*  GLOBAL DATA TYPES AND STRUCTURES
*********************************************************************************************************************/

typedef uint8_t MsgInfoHdl_Type;

typedef struct
{
    uint8_t start_bit;
    uint8_t len;
} Com_SigInfo_t;

typedef struct
{
    Com_SigInfo_t *siginfo;
    uint8_t sig_count; 
    uint16_t period;
    Can_PduType_t pdu;
} Com_MessageInfo_t;

typedef struct 
{
	uint8_t Sig1    : 4;
	uint8_t Sig2;
	uint16_t Sig3;
	uint8_t Sig4    : 4;
	uint8_t Sig5    : 7;
} MsgA_SigInfo_t;

typedef struct 
{
	uint8_t Sig1    : 4;
	uint8_t Sig2;
	uint16_t Sig3;
	uint8_t Sig4    : 4;
	uint8_t Sig5    : 7;
	uint8_t Sig6    : 2;
	uint16_t Sig7;
} MsgB_SigInfo_t;

/**********************************************************************************************************************
*  GLOBAL FUNCTION MACROS
*********************************************************************************************************************/

#define Com_GetTxMsgInst()				        Com_TxMessageInfo_Table
#define Com_GetTxMessageHdl(index)				(Com_GetTxMsgInst()[(index)])

#define Com_GetRxMsgInst()				        Com_RxMessageInfo_Table
#define Com_GetRxMessageHdl(index)				(Com_GetRxMsgInst()[(index)])

#define Com_GetRxMessageID(index)				(Com_GetRxMessageHdl(index).pdu.MsgID)

/**********************************************************************************************************************
*  GLOBAL DATA
**********************************************************************************************************************/

extern Com_MessageInfo_t Com_TxMessageInfo_Table[CAN_TXMESSAGE_MAX];
extern Com_MessageInfo_t Com_RxMessageInfo_Table[CAN_RXMESSAGE_MAX];

#endif /* CAN_USER_CFG_H */

/**********************************************************************************************************************
*  END OF FILE: Can_UserCfg.h
*********************************************************************************************************************/
