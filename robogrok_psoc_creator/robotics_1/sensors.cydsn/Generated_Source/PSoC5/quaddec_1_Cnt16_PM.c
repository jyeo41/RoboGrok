/*******************************************************************************
* File Name: quaddec_1_Cnt16_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "quaddec_1_Cnt16.h"

static quaddec_1_Cnt16_backupStruct quaddec_1_Cnt16_backup;


/*******************************************************************************
* Function Name: quaddec_1_Cnt16_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  quaddec_1_Cnt16_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void quaddec_1_Cnt16_SaveConfig(void) 
{
    #if (!quaddec_1_Cnt16_UsingFixedFunction)

        quaddec_1_Cnt16_backup.CounterUdb = quaddec_1_Cnt16_ReadCounter();

        #if(!quaddec_1_Cnt16_ControlRegRemoved)
            quaddec_1_Cnt16_backup.CounterControlRegister = quaddec_1_Cnt16_ReadControlRegister();
        #endif /* (!quaddec_1_Cnt16_ControlRegRemoved) */

    #endif /* (!quaddec_1_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: quaddec_1_Cnt16_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  quaddec_1_Cnt16_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void quaddec_1_Cnt16_RestoreConfig(void) 
{      
    #if (!quaddec_1_Cnt16_UsingFixedFunction)

       quaddec_1_Cnt16_WriteCounter(quaddec_1_Cnt16_backup.CounterUdb);

        #if(!quaddec_1_Cnt16_ControlRegRemoved)
            quaddec_1_Cnt16_WriteControlRegister(quaddec_1_Cnt16_backup.CounterControlRegister);
        #endif /* (!quaddec_1_Cnt16_ControlRegRemoved) */

    #endif /* (!quaddec_1_Cnt16_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: quaddec_1_Cnt16_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  quaddec_1_Cnt16_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void quaddec_1_Cnt16_Sleep(void) 
{
    #if(!quaddec_1_Cnt16_ControlRegRemoved)
        /* Save Counter's enable state */
        if(quaddec_1_Cnt16_CTRL_ENABLE == (quaddec_1_Cnt16_CONTROL & quaddec_1_Cnt16_CTRL_ENABLE))
        {
            /* Counter is enabled */
            quaddec_1_Cnt16_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            quaddec_1_Cnt16_backup.CounterEnableState = 0u;
        }
    #else
        quaddec_1_Cnt16_backup.CounterEnableState = 1u;
        if(quaddec_1_Cnt16_backup.CounterEnableState != 0u)
        {
            quaddec_1_Cnt16_backup.CounterEnableState = 0u;
        }
    #endif /* (!quaddec_1_Cnt16_ControlRegRemoved) */
    
    quaddec_1_Cnt16_Stop();
    quaddec_1_Cnt16_SaveConfig();
}


/*******************************************************************************
* Function Name: quaddec_1_Cnt16_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  quaddec_1_Cnt16_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void quaddec_1_Cnt16_Wakeup(void) 
{
    quaddec_1_Cnt16_RestoreConfig();
    #if(!quaddec_1_Cnt16_ControlRegRemoved)
        if(quaddec_1_Cnt16_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            quaddec_1_Cnt16_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!quaddec_1_Cnt16_ControlRegRemoved) */
    
}


/* [] END OF FILE */
