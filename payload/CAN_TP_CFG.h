/******************************************************************************
[COPYRIGHT INFORMATION]
* COMPANY: VARROC ENGINEERING LTD.
* FILE NAME: CAN_TP_CFG.h
* AUTHOR: ANANDHAN T
* CURRENT VERSION: V1.00.00
*(HERE VERSION IS MAINTAINED AS MAJOR.MINOR.PATCH - REFER VERSION CONTROL 
DOCUMENT FOR FURTHER DETAILS)
* DATE: 29-MAY-2023
* OPERATING ENVIRONMENT: C
* DESCRIPTION:  Configuration file for CANTP. 
* CAUTION NOTE: CAUTION RELATED TO FILE                    

THIS FILE/CODE CONTAINS INFORMATION THAT IS PROPRIETARY TO VARROC ENGINEERING 
LTD.NO PART OF THIS DOCUMENT/CODE MAY BE REPRODUCED OR USED IN WHOLE OR PART 
IN ANY FORM OR BY ANY MEANS - GRAPHIC, ELECTRONIC OR MECHANICAL WITHOUT THE 
WRITTEN PERMISSION OF VARROC ENGINEERING LTD.
******************************************************************************/

#ifndef CAN_TP_CFG_H
#define CAN_TP_CFG_H


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

#define CANTP_RXMESSAGE_MAX     (1U)
#define CANTP_TXMESSAGE_MAX     (1U)

#define DEFAULT_FC_BS           (0x04U)
#define DEFAULT_FC_STMIN        (30U)

#define TIMER_UNIT              (10U)  /*Timer unit in ms*/

#define STMIN_PERIOD_DEFAULT    (2U)    
#define N_AS_TIMEOUT_PERIOD     (100U)  
#define N_BS_TIMEOUT_PERIOD     (100U)
#define N_AR_TIMEOUT_PERIOD     (100U)
#define N_BR_TIMEOUT_PERIOD     (1U)
#define N_CR_TIMEOUT_PERIOD     (100U)

#define FLOWCONTROL_SDUID       (0U)

/****************************** END OF MACROS ********************************/

/******************************************************************************
 [E N U M E R A T O R S]
 *****************************************************************************/

/**************************** END OF ENUMERATORS *****************************/

/******************************************************************************
 [T Y P E D E F S]
 *****************************************************************************/

typedef struct
{
  uint8_t* SduDataPtr;
  uint8_t* MetaDataPtr;
  uint16_t SduLength;
}TP_SDUINFO_ST;

typedef struct
{
  uint8_t  state;
  uint16_t count;
}TP_RETRY_ST;


typedef uint16_t TpSduLength_t;

typedef uint8_t TpReturnType_t;

typedef void (*App_TxConf) (SduId_t,CANERRCODE_EN);

typedef void (*App_RxIndi) (SduId_t,CANERRCODE_EN);

typedef CANERRCODE_EN (*App_CpyTx) (SduId_t, const TP_SDUINFO_ST*,\
                                const TP_RETRY_ST*, TpSduLength_t*);

typedef CANERRCODE_EN (*App_CpyRx) (SduId_t,const TP_SDUINFO_ST*, \
                                    TpSduLength_t*);

typedef CANERRCODE_EN (*App_StOfRx) (SduId_t,const TP_SDUINFO_ST*, \
                                    TpSduLength_t, TpSduLength_t*);

typedef struct
{
	App_TxConf   TxCnf;
  App_RxIndi   RxInd;
  App_CpyTx    CpyTx;
  App_CpyRx    CpyRx;
  App_StOfRx   StOfRx;
}CANTP_APPCALLBACKS_ST;

typedef struct
{
  CAN_FRAMETYPE_EN  IdType;
  CanIDType_t TpRx_id; /*Request ID*/
	uint8_t 		pduid;
}CANTP_RXID_ST;

typedef struct
{
  CAN_FRAMETYPE_EN  IdType;
  CanIDType_t TpTx_id; /*Respose ID*/
	uint8_t 		pduid;
}CANTP_TXID_ST;

/****************************** END OF TYPEDEFS ******************************/

/******************************************************************************T
[F U N C T I O N  P R O T O T Y P E S] 
 *****************************************************************************/

/************************ END OF FUNCTION PROTOTYPES *************************/


/******************************************************************************
[E X T E R N  D E C L A R A T I O N
******************************************************************************/

extern CANTP_APPCALLBACKS_ST CanTpAppCallBack_Handle;

extern CANTP_RXID_ST TpIdRx_st[CANTP_RXMESSAGE_MAX];

extern CANTP_TXID_ST TpIdTx_st[CANTP_TXMESSAGE_MAX];

/************************ END OF EXTERN DECLARATIONS *************************/
#endif

/******************************************************************************
[C H A N G E  H I S T O R Y]
*******************************************************************************
VERSION 	DATE        		AUTHOR     			DESCRIPTION
V1.1		29-MAY-2023		ANANDHAN T				INITIAL VERSION
******** *********** ********** ***********************************************
******************************************************************************/

/**************************END OF FILE INFO***********************************/
