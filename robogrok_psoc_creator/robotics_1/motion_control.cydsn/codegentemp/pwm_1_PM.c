/*******************************************************************************
* File Name: pwm_1_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "pwm_1.h"

static pwm_1_backupStruct pwm_1_backup;


/*******************************************************************************
* Function Name: pwm_1_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  pwm_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void pwm_1_SaveConfig(void) 
{

    #if(!pwm_1_UsingFixedFunction)
        #if(!pwm_1_PWMModeIsCenterAligned)
            pwm_1_backup.PWMPeriod = pwm_1_ReadPeriod();
        #endif /* (!pwm_1_PWMModeIsCenterAligned) */
        pwm_1_backup.PWMUdb = pwm_1_ReadCounter();
        #if (pwm_1_UseStatus)
            pwm_1_backup.InterruptMaskValue = pwm_1_STATUS_MASK;
        #endif /* (pwm_1_UseStatus) */

        #if(pwm_1_DeadBandMode == pwm_1__B_PWM__DBM_256_CLOCKS || \
            pwm_1_DeadBandMode == pwm_1__B_PWM__DBM_2_4_CLOCKS)
            pwm_1_backup.PWMdeadBandValue = pwm_1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(pwm_1_KillModeMinTime)
             pwm_1_backup.PWMKillCounterPeriod = pwm_1_ReadKillTime();
        #endif /* (pwm_1_KillModeMinTime) */

        #if(pwm_1_UseControl)
            pwm_1_backup.PWMControlRegister = pwm_1_ReadControlRegister();
        #endif /* (pwm_1_UseControl) */
    #endif  /* (!pwm_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: pwm_1_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  pwm_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void pwm_1_RestoreConfig(void) 
{
        #if(!pwm_1_UsingFixedFunction)
            #if(!pwm_1_PWMModeIsCenterAligned)
                pwm_1_WritePeriod(pwm_1_backup.PWMPeriod);
            #endif /* (!pwm_1_PWMModeIsCenterAligned) */

            pwm_1_WriteCounter(pwm_1_backup.PWMUdb);

            #if (pwm_1_UseStatus)
                pwm_1_STATUS_MASK = pwm_1_backup.InterruptMaskValue;
            #endif /* (pwm_1_UseStatus) */

            #if(pwm_1_DeadBandMode == pwm_1__B_PWM__DBM_256_CLOCKS || \
                pwm_1_DeadBandMode == pwm_1__B_PWM__DBM_2_4_CLOCKS)
                pwm_1_WriteDeadTime(pwm_1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(pwm_1_KillModeMinTime)
                pwm_1_WriteKillTime(pwm_1_backup.PWMKillCounterPeriod);
            #endif /* (pwm_1_KillModeMinTime) */

            #if(pwm_1_UseControl)
                pwm_1_WriteControlRegister(pwm_1_backup.PWMControlRegister);
            #endif /* (pwm_1_UseControl) */
        #endif  /* (!pwm_1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: pwm_1_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  pwm_1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void pwm_1_Sleep(void) 
{
    #if(pwm_1_UseControl)
        if(pwm_1_CTRL_ENABLE == (pwm_1_CONTROL & pwm_1_CTRL_ENABLE))
        {
            /*Component is enabled */
            pwm_1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            pwm_1_backup.PWMEnableState = 0u;
        }
    #endif /* (pwm_1_UseControl) */

    /* Stop component */
    pwm_1_Stop();

    /* Save registers configuration */
    pwm_1_SaveConfig();
}


/*******************************************************************************
* Function Name: pwm_1_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  pwm_1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void pwm_1_Wakeup(void) 
{
     /* Restore registers values */
    pwm_1_RestoreConfig();

    if(pwm_1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        pwm_1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
