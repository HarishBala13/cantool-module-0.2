/******************************************************************************
[COPYRIGHT INFORMATION]
* COMPANY: VARROC ENGINEERING LTD.
* FILE NAME: CAN_TP_CFG.C
* AUTHOR: ANANDHAN T
* CURRENT VERSION: V1.00.00
*(HERE VERSION IS MAINTAINED AS MAJOR.MINOR.PATCH - REFER VERSION CONTROL 
DOCUMENT FOR FURTHER DETAILS)
* DATE: 29-MAY-2023
* OPERATING ENVIRONMENT: C
* DESCRIPTION:  THIS FILE CONTAINS CONIFIGURATIONS FOR CANTP
* CAUTION NOTE: CAUTION RELATED TO FILE                    

THIS FILE/CODE CONTAINS INFORMATION THAT IS PROPRIETARY TO VARROC ENGINEERING 
* LTD.NO PART OF THIS DOCUMENT/CODE MAY BE REPRODUCED OR USED IN WHOLE OR PART 
IN ANY FORM OR BY ANY MEANS - GRAPHIC, ELECTRONIC OR MECHANICAL WITHOUT THE 
WRITTEN PERMISSION OF VARROC ENGINEERING LTD.
******************************************************************************/

/******************************************************************************
[I N C L U D E  F I L E S]
******************************************************************************/

#include "CAN_TP_CFG.h"
#include "Dcm_cbk.h"

/**************************** END OF INCLUDE FILES ***************************/

/******************************************************************************
[T Y P E  D E F I N I T I O N]
******************************************************************************/


/**************************** END OF TYPE DEFINITION**************************/

/******************************************************************************
[M A C R O S]
******************************************************************************/


/**************************** END OF MACROS **********************************/

/******************************************************************************
[C O N S T A N T  V A R I A B L E   D E F I N I T I O N]
******************************************************************************/


/*********************** END OF CONST. VARIABLE DEFINITION *******************/

/******************************************************************************
[V A R I A B L E  D E F I N I T I O N]
******************************************************************************/
/*NOTE : SERVICES USED BY CAN TP
TP Tx Confirmation Callback : Confirmation callback to application 
                              for message transmission. 
TP Rx Indication Callback   : Indication callback to application 
                              for message reception. 
TP Copy Tx Data : Copies data to transmit from application. 
TP Copy Rx Data : Copies data received to application 
TP Start of Reception : Indicates application about new message 
                        reception about to start. 
*/
CANTP_APPCALLBACKS_ST CanTpAppCallBack_Handle = { 
                            /*TP_TxConfirmation callback*/Dcm_TpTxConfirmation,
                            /*TP_RxIndication callback*/  Dcm_TpRxIndication,
                            /*TP_CopyTxData*/ Dcm_CopyTxData,
                            /*TP_CopyRxData*/ Dcm_CopyRxData,
                            /*TP_StartOfReception*/ Dcm_StartOfReception
                            };

/*NOTE: CANTP TRANMISSION
[use this configuration only for configuring TP messages]
MsgID Type - Mention STANDARD CAN (CAN_STD_MSGID) 0 to 11 bit identifier. 
            or EXTENDED CAN (CAN_EXT_MSGID) 0 to 29 bit identifier.
MsgID	- Message ID shall be from 0x0 to 0x1FFFFFFF.
pduid -  shall be the index corresponding to the message configured in 
          (TxMsgPduInfo_st)CAN_IF_CFG.c
			-  pduid shall be from 0 to 127.
*/
CANTP_TXID_ST TpIdTx_st[CANTP_TXMESSAGE_MAX]  = 
              { /*MsgID Type*/ CAN_STD_MSGID, /*TxMsgID*/0x612, /*pduid*/ 2};

/*NOTE: CANTP RECEPTION
[use this configuration only for configuring TP messages]
MsgID Type - Mention STANDARD CAN (CAN_STD_MSGID) 0 to 11 bit identifier. 
            or EXTENDED CAN (CAN_EXT_MSGID) 0 to 29 bit identifier.
MsgID	- Message ID shall be from 0x0 to 0x1FFFFFFF.
pduid -  shall be the index corresponding to the message configured in 
          (TxMsgPduInfo_st)CAN_IF_CFG.c
			-  pduid shall be from 0 to 127.
*/
CANTP_RXID_ST TpIdRx_st[CANTP_RXMESSAGE_MAX]  = 
              { /*MsgID Type*/ CAN_STD_MSGID, /*RxMSgID*/0x610, /*pduid*/ 4};

/*********************** END OF GLOBAL VARIABLE DEFINITION *******************/

/******************************************************************************
[S T A T I C  F U N C T I O N  P R O T O T Y P E S]
******************************************************************************/


/*********************** END OF STATIC FUNCTION PROTOTYPE ********************/

/******************************************************************************
[C H A N G E  H I S T O R Y]
*******************************************************************************
VERSION 	DATE        		AUTHOR     			DESCRIPTION
V1.1		29-MAY-2023		ANANDHAN T    		INITIAL VERSION
******** *********** ********** **********************************************/

/*************************END OF FILE INFO************************************/
