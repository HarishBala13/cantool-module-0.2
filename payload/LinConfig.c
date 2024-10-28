
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
/**        \file  Can_UserCfg.c
 *        \brief  CAN User configuration Source file.
 *
 *      \details  This file contains the declaration and initializationConfig variables
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
*  INCLUDES
*********************************************************************************************************************/

#include "CAN_UserCfg.h"

/**********************************************************************************************************************
*  GLOBAL CONSTANT MACROS
*********************************************************************************************************************/

#define MSGA_SIG_COUNT 2
#define MSGB_SIG_COUNT 3

/**********************************************************************************************************************
*  GLOBAL DATA
**********************************************************************************************************************/
Com_SigInfo_t MsgA_SigDef[MSGA_SIG_COUNT] = {
	{ /*start_bit*/ 0,  /*len*/ 8 }
	{ /*start_bit*/ 8,  /*len*/ 8 }
};

Com_SigInfo_t MsgB_SigDef[MSGB_SIG_COUNT] = {
	{ /*start_bit*/ 0,  /*len*/ 8 }
	{ /*start_bit*/ 8,  /*len*/ 8 }
	{ /*start_bit*/ 16,  /*len*/ 16 }
};

Com_MessageInfo_t Com_TxMessageInfo_Table[CAN_TXMESSAGE_MAX] = {
    { /*siginfo*/ MsgA_SigDef, /*sig_count*/ MSGA_SIG_COUNT, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x30, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ MsgB_SigDef, /*sig_count*/ MSGB_SIG_COUNT, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x31, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ 0, /*sig_count*/ 0, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x32, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ 0, /*sig_count*/ 0, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x33, /*len*/ CAN_STD_FRAME_SIZE} }
};

Com_MessageInfo_t Com_RxMessageInfo_Table[CAN_RXMESSAGE_MAX] = {
    { /*siginfo*/ MsgA_SigDef, /*sig_count*/ MSGA_SIG_COUNT, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x200, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ MsgB_SigDef, /*sig_count*/ MSGB_SIG_COUNT, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x400, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ 0, /*sig_count*/ 0, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x410, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ 0, /*sig_count*/ 0, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x420, /*len*/ CAN_STD_FRAME_SIZE} },
    { /*siginfo*/ 0, /*sig_count*/ 0, /*period*/ 0, /*pdu*/ {/*MsgID*/ 0x500, /*len*/ CAN_STD_FRAME_SIZE} }
};

/**********************************************************************************************************************
*  END OF FILE: Can_UserCfg.c
*********************************************************************************************************************/
