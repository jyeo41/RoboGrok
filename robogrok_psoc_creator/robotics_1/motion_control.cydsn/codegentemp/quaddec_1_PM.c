/*******************************************************************************
* File Name: quaddec_1_PM.c
* Version 3.0
*
* Description:
*  This file contains the setup, control and status commands to support 
*  component operations in low power mode.  
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

#include "quaddec_1.h"

static quaddec_1_BACKUP_STRUCT quaddec_1_backup = {0u};


/*******************************************************************************
* Function Name: quaddec_1_SaveConfig
********************************************************************************
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void quaddec_1_SaveConfig(void) 
{
    #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT)
        quaddec_1_Cnt8_SaveConfig();
    #else 
        /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT) || 
         * (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
         */
        quaddec_1_Cnt16_SaveConfig();
    #endif /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: quaddec_1_RestoreConfig
********************************************************************************
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void quaddec_1_RestoreConfig(void) 
{
    #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT)
        quaddec_1_Cnt8_RestoreConfig();
    #else 
        /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT) || 
         * (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT) 
         */
        quaddec_1_Cnt16_RestoreConfig();
    #endif /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT) */
}


/*******************************************************************************
* Function Name: quaddec_1_Sleep
********************************************************************************
* 
* Summary:
*  Prepare Quadrature Decoder Component goes to sleep.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  quaddec_1_backup - modified when non-retention registers are saved.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void quaddec_1_Sleep(void) 
{
    if (0u != (quaddec_1_SR_AUX_CONTROL & quaddec_1_INTERRUPTS_ENABLE))
    {
        quaddec_1_backup.enableState = 1u;
    }
    else /* The Quadrature Decoder Component is disabled */
    {
        quaddec_1_backup.enableState = 0u;
    }

    quaddec_1_Stop();
    quaddec_1_SaveConfig();
}


/*******************************************************************************
* Function Name: quaddec_1_Wakeup
********************************************************************************
*
* Summary:
*  Prepare Quadrature Decoder Component to wake up.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  quaddec_1_backup - used when non-retention registers are restored.
*
*******************************************************************************/
void quaddec_1_Wakeup(void) 
{
    quaddec_1_RestoreConfig();

    if (quaddec_1_backup.enableState != 0u)
    {
        #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT)
            quaddec_1_Cnt8_Enable();
        #else 
            /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT) || 
            *  (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT) 
            */
            quaddec_1_Cnt16_Enable();
        #endif /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT) */

        /* Enable component's operation */
        quaddec_1_Enable();
    } /* Do nothing if component's block was disabled before */
}


/* [] END OF FILE */

