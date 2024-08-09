/*******************************************************************************
* File Name: c1.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_c1_ALIASES_H) /* Pins c1_ALIASES_H */
#define CY_PINS_c1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define c1_0			(c1__0__PC)
#define c1_0_INTR	((uint16)((uint16)0x0001u << c1__0__SHIFT))

#define c1_INTR_ALL	 ((uint16)(c1_0_INTR))

#endif /* End Pins c1_ALIASES_H */


/* [] END OF FILE */
