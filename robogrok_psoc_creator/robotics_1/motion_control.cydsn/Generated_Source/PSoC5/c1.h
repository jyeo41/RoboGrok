/*******************************************************************************
* File Name: c1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_c1_H) /* Pins c1_H */
#define CY_PINS_c1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "c1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 c1__PORT == 15 && ((c1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    c1_Write(uint8 value);
void    c1_SetDriveMode(uint8 mode);
uint8   c1_ReadDataReg(void);
uint8   c1_Read(void);
void    c1_SetInterruptMode(uint16 position, uint16 mode);
uint8   c1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the c1_SetDriveMode() function.
     *  @{
     */
        #define c1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define c1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define c1_DM_RES_UP          PIN_DM_RES_UP
        #define c1_DM_RES_DWN         PIN_DM_RES_DWN
        #define c1_DM_OD_LO           PIN_DM_OD_LO
        #define c1_DM_OD_HI           PIN_DM_OD_HI
        #define c1_DM_STRONG          PIN_DM_STRONG
        #define c1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define c1_MASK               c1__MASK
#define c1_SHIFT              c1__SHIFT
#define c1_WIDTH              1u

/* Interrupt constants */
#if defined(c1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in c1_SetInterruptMode() function.
     *  @{
     */
        #define c1_INTR_NONE      (uint16)(0x0000u)
        #define c1_INTR_RISING    (uint16)(0x0001u)
        #define c1_INTR_FALLING   (uint16)(0x0002u)
        #define c1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define c1_INTR_MASK      (0x01u) 
#endif /* (c1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define c1_PS                     (* (reg8 *) c1__PS)
/* Data Register */
#define c1_DR                     (* (reg8 *) c1__DR)
/* Port Number */
#define c1_PRT_NUM                (* (reg8 *) c1__PRT) 
/* Connect to Analog Globals */                                                  
#define c1_AG                     (* (reg8 *) c1__AG)                       
/* Analog MUX bux enable */
#define c1_AMUX                   (* (reg8 *) c1__AMUX) 
/* Bidirectional Enable */                                                        
#define c1_BIE                    (* (reg8 *) c1__BIE)
/* Bit-mask for Aliased Register Access */
#define c1_BIT_MASK               (* (reg8 *) c1__BIT_MASK)
/* Bypass Enable */
#define c1_BYP                    (* (reg8 *) c1__BYP)
/* Port wide control signals */                                                   
#define c1_CTL                    (* (reg8 *) c1__CTL)
/* Drive Modes */
#define c1_DM0                    (* (reg8 *) c1__DM0) 
#define c1_DM1                    (* (reg8 *) c1__DM1)
#define c1_DM2                    (* (reg8 *) c1__DM2) 
/* Input Buffer Disable Override */
#define c1_INP_DIS                (* (reg8 *) c1__INP_DIS)
/* LCD Common or Segment Drive */
#define c1_LCD_COM_SEG            (* (reg8 *) c1__LCD_COM_SEG)
/* Enable Segment LCD */
#define c1_LCD_EN                 (* (reg8 *) c1__LCD_EN)
/* Slew Rate Control */
#define c1_SLW                    (* (reg8 *) c1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define c1_PRTDSI__CAPS_SEL       (* (reg8 *) c1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define c1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) c1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define c1_PRTDSI__OE_SEL0        (* (reg8 *) c1__PRTDSI__OE_SEL0) 
#define c1_PRTDSI__OE_SEL1        (* (reg8 *) c1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define c1_PRTDSI__OUT_SEL0       (* (reg8 *) c1__PRTDSI__OUT_SEL0) 
#define c1_PRTDSI__OUT_SEL1       (* (reg8 *) c1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define c1_PRTDSI__SYNC_OUT       (* (reg8 *) c1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(c1__SIO_CFG)
    #define c1_SIO_HYST_EN        (* (reg8 *) c1__SIO_HYST_EN)
    #define c1_SIO_REG_HIFREQ     (* (reg8 *) c1__SIO_REG_HIFREQ)
    #define c1_SIO_CFG            (* (reg8 *) c1__SIO_CFG)
    #define c1_SIO_DIFF           (* (reg8 *) c1__SIO_DIFF)
#endif /* (c1__SIO_CFG) */

/* Interrupt Registers */
#if defined(c1__INTSTAT)
    #define c1_INTSTAT            (* (reg8 *) c1__INTSTAT)
    #define c1_SNAP               (* (reg8 *) c1__SNAP)
    
	#define c1_0_INTTYPE_REG 		(* (reg8 *) c1__0__INTTYPE)
#endif /* (c1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_c1_H */


/* [] END OF FILE */
