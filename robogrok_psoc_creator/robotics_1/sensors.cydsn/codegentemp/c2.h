/*******************************************************************************
* File Name: c2.h  
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

#if !defined(CY_PINS_c2_H) /* Pins c2_H */
#define CY_PINS_c2_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "c2_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 c2__PORT == 15 && ((c2__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    c2_Write(uint8 value);
void    c2_SetDriveMode(uint8 mode);
uint8   c2_ReadDataReg(void);
uint8   c2_Read(void);
void    c2_SetInterruptMode(uint16 position, uint16 mode);
uint8   c2_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the c2_SetDriveMode() function.
     *  @{
     */
        #define c2_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define c2_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define c2_DM_RES_UP          PIN_DM_RES_UP
        #define c2_DM_RES_DWN         PIN_DM_RES_DWN
        #define c2_DM_OD_LO           PIN_DM_OD_LO
        #define c2_DM_OD_HI           PIN_DM_OD_HI
        #define c2_DM_STRONG          PIN_DM_STRONG
        #define c2_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define c2_MASK               c2__MASK
#define c2_SHIFT              c2__SHIFT
#define c2_WIDTH              1u

/* Interrupt constants */
#if defined(c2__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in c2_SetInterruptMode() function.
     *  @{
     */
        #define c2_INTR_NONE      (uint16)(0x0000u)
        #define c2_INTR_RISING    (uint16)(0x0001u)
        #define c2_INTR_FALLING   (uint16)(0x0002u)
        #define c2_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define c2_INTR_MASK      (0x01u) 
#endif /* (c2__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define c2_PS                     (* (reg8 *) c2__PS)
/* Data Register */
#define c2_DR                     (* (reg8 *) c2__DR)
/* Port Number */
#define c2_PRT_NUM                (* (reg8 *) c2__PRT) 
/* Connect to Analog Globals */                                                  
#define c2_AG                     (* (reg8 *) c2__AG)                       
/* Analog MUX bux enable */
#define c2_AMUX                   (* (reg8 *) c2__AMUX) 
/* Bidirectional Enable */                                                        
#define c2_BIE                    (* (reg8 *) c2__BIE)
/* Bit-mask for Aliased Register Access */
#define c2_BIT_MASK               (* (reg8 *) c2__BIT_MASK)
/* Bypass Enable */
#define c2_BYP                    (* (reg8 *) c2__BYP)
/* Port wide control signals */                                                   
#define c2_CTL                    (* (reg8 *) c2__CTL)
/* Drive Modes */
#define c2_DM0                    (* (reg8 *) c2__DM0) 
#define c2_DM1                    (* (reg8 *) c2__DM1)
#define c2_DM2                    (* (reg8 *) c2__DM2) 
/* Input Buffer Disable Override */
#define c2_INP_DIS                (* (reg8 *) c2__INP_DIS)
/* LCD Common or Segment Drive */
#define c2_LCD_COM_SEG            (* (reg8 *) c2__LCD_COM_SEG)
/* Enable Segment LCD */
#define c2_LCD_EN                 (* (reg8 *) c2__LCD_EN)
/* Slew Rate Control */
#define c2_SLW                    (* (reg8 *) c2__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define c2_PRTDSI__CAPS_SEL       (* (reg8 *) c2__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define c2_PRTDSI__DBL_SYNC_IN    (* (reg8 *) c2__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define c2_PRTDSI__OE_SEL0        (* (reg8 *) c2__PRTDSI__OE_SEL0) 
#define c2_PRTDSI__OE_SEL1        (* (reg8 *) c2__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define c2_PRTDSI__OUT_SEL0       (* (reg8 *) c2__PRTDSI__OUT_SEL0) 
#define c2_PRTDSI__OUT_SEL1       (* (reg8 *) c2__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define c2_PRTDSI__SYNC_OUT       (* (reg8 *) c2__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(c2__SIO_CFG)
    #define c2_SIO_HYST_EN        (* (reg8 *) c2__SIO_HYST_EN)
    #define c2_SIO_REG_HIFREQ     (* (reg8 *) c2__SIO_REG_HIFREQ)
    #define c2_SIO_CFG            (* (reg8 *) c2__SIO_CFG)
    #define c2_SIO_DIFF           (* (reg8 *) c2__SIO_DIFF)
#endif /* (c2__SIO_CFG) */

/* Interrupt Registers */
#if defined(c2__INTSTAT)
    #define c2_INTSTAT            (* (reg8 *) c2__INTSTAT)
    #define c2_SNAP               (* (reg8 *) c2__SNAP)
    
	#define c2_0_INTTYPE_REG 		(* (reg8 *) c2__0__INTTYPE)
#endif /* (c2__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_c2_H */


/* [] END OF FILE */
