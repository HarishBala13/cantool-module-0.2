/******************************************************************************
[COPYRIGHT INFORMATION]
* COMPANY: VARROC ENGINEERING LTD.
* FILE NAME: CAN_IF_CFG.c
* AUTHOR: ANANDHAN T
* CURRENT VERSION: V1.00.00
*(HERE VERSION IS MAINTAINED AS MAJOR.MINOR.PATCH - REFER VERSION CONTROL 
DOCUMENT FOR FURTHER DETAILS)
* DATE: 29-MAR-2023
* OPERATING ENVIRONMENT: C
* DESCRIPTION:  CAN IF CONFIGURATION SOURCE FILE. (THIS FILE CONTAINS THE
 MESSAGE INFORMATION OF COM AND TP MESSAGES)
* CAUTION NOTE: CAUTION RELATED TO FILE                    

THIS FILE/CODE CONTAINS INFORMATION THAT IS PROPRIETARY TO VARROC ENGINEERING 
LTD.NO PART OF THIS DOCUMENT/CODE MAY BE REPRODUCED OR USED IN WHOLE OR PART 
IN ANY FORM OR BY ANY MEANS - GRAPHIC, ELECTRONIC OR MECHANICAL WITHOUT THE 
WRITTEN PERMISSION OF VARROC ENGINEERING LTD.
******************************************************************************/

/******************************************************************************
[I N C L U D E  F I L E S]
******************************************************************************/

#include "CAN_IF_CFG.h"

/*************************** END OF INCLUDE FILES ****************************/

/******************************************************************************
[T Y P E  D E F I N I T I O N]
******************************************************************************/
/*************************** END OF TYPE DEFINITION***************************/

/******************************************************************************
[M A C R O S]
******************************************************************************/

#define TXQ1_BUFF_SIZE 	5U
#define TXQ1_TYPE 		CAN_PRIORITYQUEUE
#define TXQ2_BUFF_SIZE 	5U
#define TXQ2_TYPE 		CAN_FIFOQUEUE
#define TXQ3_BUFF_SIZE 	5U
#define TXQ3_TYPE 		CAN_FIFOQUEUE
#define TXQ4_BUFF_SIZE 	5U
#define TXQ4_TYPE 		CAN_FIFOQUEUE

/*************************** END OF MACROS ***********************************/

/******************************************************************************
[S T A T I C  F U N C T I O N  P R O T O T Y P E S]
******************************************************************************/

static CAN_LLFRAME_ST* GetTxMsgHdl (pduHdl_t hdl);

/********************** END OF STATIC FUNCTION PROTOTYPE *********************/

/******************************************************************************
[C O N S T A N T  V A R I A B L E   D E F I N I T I O N]
******************************************************************************/
/********************** END OF CONST. VARIABLE DEFINITION ********************/

/******************************************************************************
[V A R I A B L E  D E F I N I T I O N]
******************************************************************************/

/* RX FIlter configuration :
CANID : CAN ID 
Mask : Mask value for the filter
*/
CANFILTERCFG_ST FilterCfgTable_st[FILTCFG_COUNT] = {
	{/*CANID*/0x600,/*Mask*/0x7C8}, /* BASIC CAN */
	{/*CANID*/0x300,/*Mask*/0x7C8}, /* BASIC CAN */
	{/*CANID*/0x1FFFFFFF,/*Mask*/0x1FFFFFFF},/* FULL CAN */
};

/* TX Buffer configuration 
buffType : Can_MB or CAN_FIFO
buffID : Buffer ID
buffStatus : Buffer initial status CAN_OBJ_IDLE or 
						CAN_OBJ_BUSY
*/
CANPDUBUFFINFO_ST TxBuffConfigTable_st[TXHWOBJ_COUNT] = {
	{/*buffType*/Can_MB,/*buffID*/0,/*buffStatus*/CAN_OBJ_IDLE},
	{/*buffType*/Can_MB,/*buffID*/1,/*buffStatus*/CAN_OBJ_IDLE},
	{/*buffType*/Can_MB,/*buffID*/2,/*buffStatus*/CAN_OBJ_IDLE},
	{/*buffType*/Can_MB,/*buffID*/(CAN_HW_BUFF_TX_MAX-1),/*buffStatus*/CAN_OBJ_IDLE},
};

/* RX Buffer configuration 
buffType : Can_MB or Can_RxFIFO
buffID : Buffer ID
FilterHandle : Filter Handle configured in above Rx filter 
configuration   (index of FilterCfgTable_st)
*/
CANRXBUFFINFO_ST RxBuffConfigTable_st[CAN_RXBUFF_COUNT] = {
	{/*buffType*/Can_RxFIFO,/*buffID*/0,/*FilterHandle*/1},
	{/*buffType*/Can_RxFIFO,/*buffID*/1,/*FilterHandle*/0},
	{/*buffType*/Can_MB,/*buffID*/1,/*FilterHandle*/2},
};

/* TX PDU to Buffer Mapping
[Each index if this array correcponds to TX Message 
that configured in TxMsgPduInfo_st]

buffID - give buffer ID for the particuler message
 */
IFTXPDUCONFIGTYPE_ST TxInfoTable_st[CAN_TXMSGMAX] = {
	{/*buffID*/0},
	{/*buffID*/1},
	{/*buffID*/2},
	{/*buffID*/3}
};

/*Creating software Queue*/
pduHdl_t IfQueue_Buff1[TXQ1_BUFF_SIZE] = {0};

pduHdl_t IfQueue_Buff2[TXQ2_BUFF_SIZE] = {0};

pduHdl_t IfQueue_Buff3[TXQ3_BUFF_SIZE] = {0};

pduHdl_t IfQueue_Buff4[TXQ4_BUFF_SIZE] = {0};

/* Tx Queue configuration */
CANMSGQ_ST TxQueue_st[TXQCFG_COUNT] = {
	{{0,0,TXQ1_BUFF_SIZE},IfQueue_Buff1,TXQ1_TYPE,GetTxMsgHdl},
	{{0,0,TXQ2_BUFF_SIZE},IfQueue_Buff2,TXQ2_TYPE,GetTxMsgHdl},
	{{0,0,TXQ3_BUFF_SIZE},IfQueue_Buff3,TXQ3_TYPE,GetTxMsgHdl},
	{{0,0,TXQ4_BUFF_SIZE},IfQueue_Buff4,TXQ4_TYPE,GetTxMsgHdl},
};

/* Tx Queue to Buffer configuration */
/* One Tx Queue instance should be mapped to one tx HW buffer*/
IFTXCFGS_ST IfTxCfgs_st[TXHWOBJ_COUNT] = {
	{/*Queue ID*/0}, /*For buffer 0*/
	{/*Queue ID*/1}, /*For buffer 1*/
	{/*Queue ID*/2}, /*For buffer 2*/
	{/*Queue ID*/3}  /*For buffer 3*/
};

/*Note :  CONFIGURING TX FOR COM AND TP
[CAUTION : MSGID shall be in ascending order]
TxMsgID - message ID (both standard end extended supported)
type - mention type of message (com or tp)
*/
MsgIdPduInfo_ST TxMsgPduInfo_st[CAN_TXMSGMAX] = 
                    { {/*COM TxMsgID*/0x605, /*type*/ COM_TYPE},
											{/*COM TxMsgID*/0x607, /*type*/ COM_TYPE},
                      {/*TP TxMsgID*/ 0x612, /*type*/ TP_TYPE }, 
											{/*COM TxMsgID*/0x1FFFFFFF, /*type*/ COM_TYPE},
										};

/*Note :  CONFIGURING RX FOR COM AND TP
[CAUTION : MSGID shall be in ascending order]
RxMsgID - message ID (both standard end extended supported)
type - mention type of message (com or tp)
*/
MsgIdPduInfo_ST RxMsgPduInfo_st[CAN_RXMSGMAX] =  
                    { {/*COM RxMsgID*/0x301, /*type*/ COM_TYPE},
                      {/*COM RxMsgID*/0x302, /*type*/ COM_TYPE},
                      {/*COM RxMsgID*/0x304, /*type*/ COM_TYPE},
                      {/*TP RxMsgID*/ 0x607, /*type*/ COM_TYPE},
											{/*COM TxMsgID*/ 0x610, /*type*/ TP_TYPE},
											{/*COM RxMsgID*/0x1FFFFFFF, /*type*/ COM_TYPE},
										};   

/********************** END OF GLOBAL VARIABLE DEFINITION ********************/

/******************************************************************************
[F U N C T I O N  D E F I N I T I O N]
*******************************************************************************
* FUNCTION NAME     :	GetTxMsgHdl	
* DESCRIPTION       :	Gets Tx msg	            
* ARGUMENTS         :	hdl_u8       
* RETURN TYPE       :	CAN_LLFRAME_ST	         
* CALLED FUNCTIONS  :   Its a callback function       
* GLOBAL DATA       :
* EVENT OF CALLING  :
  CAUTION           :                             
******************************************************************************/

static CAN_LLFRAME_ST* GetTxMsgHdl (pduHdl_t hdl_u8)
{
	if (CAN_TXMSGMAX <= hdl_u8) 
	{
		hdl_u8 = 0;
		DET_ERR_REPORT(CANIF_MODULE_ID,DET_APIID_GENERIC,DET_ERR_PDUINVALID);
	}
	else 
	{
		/*Nothing to do*/
	}
	return &TxInfoTable_st[hdl_u8].ll_pdu;
}

/*********************** END OF FUNCTION DEFINITION **************************/

/******************************************************************************
[C H A N G E  H I S T O R Y]
*******************************************************************************
VERSION 	DATE        		AUTHOR     			DESCRIPTION
V1.1		07-JAN-2021		FIRSTNAME LASTNAME		INITIAL VERSION
******** *********** ********** **********************************************/

/**************************END OF FILE INFO***********************************/
