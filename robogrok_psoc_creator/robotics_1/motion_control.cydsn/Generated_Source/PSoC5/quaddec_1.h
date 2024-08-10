/*******************************************************************************
* File Name: quaddec_1.h  
* Version 3.0
*
* Description:
*  This file provides constants and parameter values for the Quadrature
*  Decoder component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_QUADRATURE_DECODER_quaddec_1_H)
#define CY_QUADRATURE_DECODER_quaddec_1_H

#include "cyfitter.h"
#include "CyLib.h"
#include "cytypes.h"

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component QuadDec_v3_0 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#define quaddec_1_COUNTER_SIZE               (32u)
#define quaddec_1_COUNTER_SIZE_8_BIT         (8u)
#define quaddec_1_COUNTER_SIZE_16_BIT        (16u)
#define quaddec_1_COUNTER_SIZE_32_BIT        (32u)

#if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT)
    #include "quaddec_1_Cnt8.h"
#else 
    /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT) || 
    *  (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT) 
    */
    #include "quaddec_1_Cnt16.h"
#endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT */

extern uint8 quaddec_1_initVar;


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define quaddec_1_COUNTER_RESOLUTION         (4u)


/***************************************
*       Data Struct Definition
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;
} quaddec_1_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  quaddec_1_Init(void) ;
void  quaddec_1_Start(void) ;
void  quaddec_1_Stop(void) ;
void  quaddec_1_Enable(void) ;
uint8 quaddec_1_GetEvents(void) ;
void  quaddec_1_SetInterruptMask(uint8 mask) ;
uint8 quaddec_1_GetInterruptMask(void) ;
int32 quaddec_1_GetCounter(void) ;
void  quaddec_1_SetCounter(int32 value)
;
void  quaddec_1_Sleep(void) ;
void  quaddec_1_Wakeup(void) ;
void  quaddec_1_SaveConfig(void) ;
void  quaddec_1_RestoreConfig(void) ;

#if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
    CY_ISR_PROTO(quaddec_1_ISR);
#endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT */


/***************************************
*           API Constants
***************************************/

#if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
    #define quaddec_1_ISR_NUMBER             ((uint8) quaddec_1_isr__INTC_NUMBER)
    #define quaddec_1_ISR_PRIORITY           ((uint8) quaddec_1_isr__INTC_PRIOR_NUM)
#endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT */


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define quaddec_1_GLITCH_FILTERING           (1u)
#define quaddec_1_INDEX_INPUT                (0u)


/***************************************
*    Initial Parameter Constants
***************************************/

#if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT)
    #define quaddec_1_COUNTER_INIT_VALUE    (0x80u)
#else 
    /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT) ||
    *  (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
    */
    #define quaddec_1_COUNTER_INIT_VALUE    (0x8000u)
    #define quaddec_1_COUNTER_MAX_VALUE     (0x7FFFu)
#endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT */


/***************************************
*             Registers
***************************************/

#define quaddec_1_STATUS_REG                 (* (reg8 *) quaddec_1_bQuadDec_Stsreg__STATUS_REG)
#define quaddec_1_STATUS_PTR                 (  (reg8 *) quaddec_1_bQuadDec_Stsreg__STATUS_REG)
#define quaddec_1_STATUS_MASK                (* (reg8 *) quaddec_1_bQuadDec_Stsreg__MASK_REG)
#define quaddec_1_STATUS_MASK_PTR            (  (reg8 *) quaddec_1_bQuadDec_Stsreg__MASK_REG)
#define quaddec_1_SR_AUX_CONTROL             (* (reg8 *) quaddec_1_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)
#define quaddec_1_SR_AUX_CONTROL_PTR         (  (reg8 *) quaddec_1_bQuadDec_Stsreg__STATUS_AUX_CTL_REG)


/***************************************
*        Register Constants
***************************************/

#define quaddec_1_COUNTER_OVERFLOW_SHIFT     (0x00u)
#define quaddec_1_COUNTER_UNDERFLOW_SHIFT    (0x01u)
#define quaddec_1_COUNTER_RESET_SHIFT        (0x02u)
#define quaddec_1_INVALID_IN_SHIFT           (0x03u)
#define quaddec_1_COUNTER_OVERFLOW           ((uint8) (0x01u << quaddec_1_COUNTER_OVERFLOW_SHIFT))
#define quaddec_1_COUNTER_UNDERFLOW          ((uint8) (0x01u << quaddec_1_COUNTER_UNDERFLOW_SHIFT))
#define quaddec_1_COUNTER_RESET              ((uint8) (0x01u << quaddec_1_COUNTER_RESET_SHIFT))
#define quaddec_1_INVALID_IN                 ((uint8) (0x01u << quaddec_1_INVALID_IN_SHIFT))

#define quaddec_1_INTERRUPTS_ENABLE_SHIFT    (0x04u)
#define quaddec_1_INTERRUPTS_ENABLE          ((uint8)(0x01u << quaddec_1_INTERRUPTS_ENABLE_SHIFT))
#define quaddec_1_INIT_INT_MASK              (0x0Fu)


/******************************************************************************************
* Following code are OBSOLETE and must not be used starting from Quadrature Decoder 2.20
******************************************************************************************/
#define quaddec_1_DISABLE                    (0x00u)


#endif /* CY_QUADRATURE_DECODER_quaddec_1_H */


/* [] END OF FILE */
