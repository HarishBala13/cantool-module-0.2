/******************************************************************************
[COPYRIGHT INFORMATION]
* COMPANY: VARROC ENGINEERING LTD.
* FILE NAME: Com_CFG.c
* AUTHOR: ANANDHAN T
* CURRENT VERSION: V1.00.00
*(HERE VERSION IS MAINTAINED AS MAJOR.MINOR.PATCH - REFER VERSION CONTROL 
DOCUMENT FOR FURTHER DETAILS)
* DATE: 29-MAR-2023
* OPERATING ENVIRONMENT: C
* DESCRIPTION:  COM USER CONFIGURATION SOURCE FILE. (THIS FILE CONTAINS THE
 MESSAGE RELATED INOFORMATIONS)
* CAUTION NOTE: CAUTION RELATED TO FILE                    

THIS FILE/CODE CONTAINS INFORMATION THAT IS PROPRIETARY TO VARROC ENGINEERING 
LTD.NO PART OF THIS DOCUMENT/CODE MAY BE REPRODUCED OR USED IN WHOLE OR PART 
IN ANY FORM OR BY ANY MEANS - GRAPHIC, ELECTRONIC OR MECHANICAL WITHOUT THE 
WRITTEN PERMISSION OF VARROC ENGINEERING LTD.
******************************************************************************/

/******************************************************************************
[I N C L U D E  F I L E S]
******************************************************************************/

#include "Com_CFG.h"
#include "CAN_AppCallbacks.h"

/*************************** END OF INCLUDE FILES ****************************/

/******************************************************************************
[T Y P E  D E F I N I T I O N]
******************************************************************************/
/*************************** END OF TYPE DEFINITION***************************/

/******************************************************************************
[M A C R O S]
******************************************************************************/

/*************************** END OF MACROS ***********************************/

/******************************************************************************
[C O N S T A N T  V A R I A B L E   D E F I N I T I O N]
******************************************************************************/
/********************** END OF CONST. VARIABLE DEFINITION ********************/

/******************************************************************************
[V A R I A B L E  D E F I N I T I O N]
******************************************************************************/

/*Message info with information of DBC*/
static COMSIGINFO_ST Msg_IDU1_st[IDU1_SIG_COUNT] = {
	{ /*start_bit*/ 0,  /*len*/ 2},
	{ /*start_bit*/ 2,  /*len*/ 2},
	{ /*start_bit*/ 6,  /*len*/ 2}
};

/*Message info with information of DBC*/
static COMSIGINFO_ST Msg_EMS1_st[EMS1_SIG_COUNT] = {
	{ /*start_bit*/ 0,  /*len*/ 8},
	{ /*start_bit*/ 14, /*len*/ 1},
	{ /*start_bit*/ 15, /*len*/ 1}
};

/*Message info with information of DBC*/
static COMSIGINFO_ST Msg_EMS2_st[EMS2_SIG_COUNT] = {
	{ /*start_bit*/ 8,  /*len*/ 16}
};

/*Message info with information of DBC*/
static COMSIGINFO_ST Msg_EMS4_st[EMS4_SIG_COUNT] = {
	{ /*start_bit*/ 31,  /*len*/ 1}
};

/*Message info with information of DBC*/
static COMSIGINFO_ST Msg_Mux_st[MUX_SIG_COUNT] = {
	/*--------Mulitplexor--------*/
	{ /*start_bit*/6,  /*len*/2  },  /*MULTIPLEXOR SIGNAL (MUX) */

	/*SIGNAL LAYOUT 1 : MUX : 0x01*/
	{ /*start_bit*/24, /*len*/30 },  /*MULTIPLEXED SIGNAL_1 : Mux value - 1*/
	{ /*start_bit*/32, /*len*/8  },  /*MULTIPLEXED SIGNAL_2 : Mux value - 1*/

	/*SIGNAL LAYOUT 2 : MUX : 0x02*/
	{ /*start_bit*/30, /*len*/24 },  /*MULTIPLEXED SIGNAL_3 : Mux value - 2*/
	{ /*start_bit*/52, /*len*/18 },  /*MULTIPLEXED SIGNAL_4 : Mux value - 2*/
	{ /*start_bit*/59, /*len*/5  },  /*MULTIPLEXED SIGNAL_5 : Mux value - 2*/

		/*SIGNAL LAYOUT 3 : MUX : 0x03*/
	{ /*start_bit*/34, /*len*/32  }, /*MULTIPLEXED SIGNAL_6 : Mux value - 3*/
};

/*Message info with information of DBC*/
static COMSIGINFO_ST Extd_Msg_st[EXTD_SIG_COUNT] = {
	{ /*start_bit*/ 9,  /*len*/ 15}
};

/* NOTE FOR CONFIGURING TRANSMISSION : 
[use only for configuring com messages for configuring tp message use CAN_TP_CFG.c]
pduid -  shall be the index corresponding to the message configured in (TxMsgPduInfo_st)CAN_IF_CFG.c
			-  pduid shall be from 0 to 127.
siginfo	- message info structure defined above.
sig_count - no of signals presents in the message (use the macro defined in Com_CFG.h).
period - one unit is 10ms. (1 for 10ms)
				- it shall be from 0 to 65535.
MsgID Type - Mention STANDARD CAN (CAN_STD_MSGID) 0 to 11 bit identifier. 
            or EXTENDED CAN (CAN_EXT_MSGID) 0 to 29 bit identifier.
MsgID	- Message ID shall be from 0x0 to 0x1FFFFFFF.
len - Message Length shall be from 0 to 8.
sdu - data need to transmit (we can put here default data need to transmit).

[CAUTION]Message configuration must be in ascending order of the message ID]
*/
COMMESSAGEINFO_ST ComTxMsgInfoTable_st[COM_TXMESSAGE_MAX] = {
  { /*pduid*/ 0, /*siginfo*/ Msg_IDU1_st, /*sig_count*/ IDU1_SIG_COUNT, /*period*/ 10, /*pdu*/ {/*MsgID Type*/ CAN_STD_MSGID, /*MsgID*/ 0x605, /*len*/ CAN_STD_FRAME_SIZE, /*sdu*/ {0,0,0,0,0,0,0,0}} },
  { /*pduid*/ 1, /*siginfo*/ Msg_Mux_st, /*sig_count*/ MUX_SIG_COUNT, /*period*/ 10, /*pdu*/ {/*MsgID Type*/ CAN_STD_MSGID, /*MsgID*/ 0x607, /*len*/ CAN_STD_FRAME_SIZE, /*sdu*/ {0,0,0,0,0,0,0,0} } },
  { /*pduid*/ 3, /*siginfo*/ Extd_Msg_st, /*sig_count*/ EXTD_SIG_COUNT, /*period*/ 10, /*pdu*/ {/*MsgID Type*/ CAN_EXT_MSGID, /*MsgID*/ 0x1FFFFFFF, /*len*/ CAN_STD_FRAME_SIZE, /*sdu*/ {0,0,0,0,0,0,0,0} } },
};


/* NOTE FOR CONFIGURING RECEPTION : 
[use only for configuring com messages for configuring tp message use CAN_TP_CFG.c]
pduid -  shall be the index corresponding to the message configured in (RxMsgPduInfo_st)CAN_IF_CFG.c
			-  pduid shall be from 0 to 127.
siginfo	- message info structure defined above.
sig_count - no of signals presents in the message (use the macro defined in Com_CFG.h).
period - one unit is 10ms. (1 for 10ms)
				- it shall be from 0 to 65535.
MsgID Type - Mention STANDARD CAN (CAN_STD_MSGID) or EXTENDED CAN (CAN_EXT_MSGID).
MsgID	- Message ID shall be from 0x0 to 0x1FFFFFFF.
len - Message Length shall be from 0 to 8.
sdu - received data will store here.
callback - application callback function will called whenever respective message received.
toutcallback - if period is defined then this callback function will call whenever the respective message
							 not received in that period of time.
Noti_type - RXNOTI_ONCHANGE – Reception Callback will be called only if there is a change in the received signal values.
						RXNOTI_ALWAYS – Reception Callback will be called irrespective of the change in signal values.

[CAUTION]Message configuration must be in ascending order of the message ID]
*/
COM_RXMESSAGEINFO_ST ComRxMsgInfoTable_st[COM_RXMESSAGE_MAX] = {
	{ /*pduid*/ 0, /*siginfo*/ Msg_EMS1_st, /*sig_count*/ EMS1_SIG_COUNT, /*period*/ 10, /*pdu*/ {/*MsgID Type*/ CAN_STD_MSGID, /*MsgID*/ 0x301, /*len*/ CAN_STD_FRAME_SIZE, {0,0,0,0,0,0,0,0} }, /*callback*/ APP_MessageEMS1_CB, /*toutcallback*/ APP_MessageA_TimeoutCB, /*noti_type*/ RXNOTI_ONCHANGE},
  { /*pduid*/ 1, /*siginfo*/ Msg_EMS2_st, /*sig_count*/ EMS2_SIG_COUNT, /*period*/ 10, /*pdu*/ {/*MsgID Type*/ CAN_STD_MSGID, /*MsgID*/ 0x302, /*len*/ CAN_STD_FRAME_SIZE, {0,0,0,0,0,0,0,0} }, /*callback*/ APP_MessageEMS2_CB, /*toutcallback*/ APP_MessageA_TimeoutCB, /*noti_type*/ RXNOTI_ALWAYS},
  { /*pduid*/ 2, /*siginfo*/ Msg_EMS4_st, /*sig_count*/ EMS4_SIG_COUNT, /*period*/ 10, /*pdu*/ {/*MsgID Type*/ CAN_STD_MSGID, /*MsgID*/ 0x304, /*len*/ CAN_STD_FRAME_SIZE, {0,0,0,0,0,0,0,0} }, /*callback*/ APP_MessageEMS4_CB, /*toutcallback*/ APP_MessageA_TimeoutCB, /*noti_type*/ RXNOTI_ALWAYS},
	{ /*pduid*/ 3, /*siginfo*/ Msg_Mux_st, /*sig_count*/ MUX_SIG_COUNT, /*period*/ 10, /*pdu*/ {/*MsgID Type*/ CAN_STD_MSGID, /*MsgID*/ 0x607, /*len*/ CAN_STD_FRAME_SIZE, {0,0,0,0,0,0,0,0} }, /*callback*/ APP_MessageMux_CB, /*toutcallback*/ APP_MessageA_TimeoutCB, /*noti_type*/ RXNOTI_ALWAYS},
	{ /*pduid*/ 5, /*siginfo*/ Extd_Msg_st, /*sig_count*/ EXTD_SIG_COUNT, /*period*/ 10, /*pdu*/ {/*MsgID Type*/ CAN_EXT_MSGID, /*MsgID*/ 0x1FFFFFFF, /*len*/ CAN_STD_FRAME_SIZE, {0,0,0,0,0,0,0,0} }, /*callback*/ APP_MessageExtd_CB, /*toutcallback*/ APP_MessageA_TimeoutCB, /*noti_type*/ RXNOTI_ALWAYS},
  };

/*Application callback for error notification*/
CANEVENT_CALLBACKS_ST CanEventCB_Handle = {APP_ErrorNotificationCB};


/********************** END OF GLOBAL VARIABLE DEFINITION ********************/

/******************************************************************************
[S T A T I C  F U N C T I O N  P R O T O T Y P E S]
******************************************************************************/
/********************** END OF STATIC FUNCTION PROTOTYPE *********************/

/******************************************************************************
[C H A N G E  H I S T O R Y]
*******************************************************************************
VERSION 	DATE        		AUTHOR     			DESCRIPTION
V1.1		07-JAN-2021		FIRSTNAME LASTNAME		INITIAL VERSION
******** *********** ********** **********************************************/

/**************************END OF FILE INFO***********************************/
