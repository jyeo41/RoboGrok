/*******************************************************************************
* File Name: quaddec_1.c  
* Version 3.0
*
* Description:
*  This file provides the source code to the API for the Quadrature Decoder
*  component.
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

#if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
    #include "quaddec_1_PVT.h"
#endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT */

uint8 quaddec_1_initVar = 0u;


/*******************************************************************************
* Function Name: quaddec_1_Init
********************************************************************************
*
* Summary:
*  Inits/Restores default QuadDec configuration provided with customizer.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void quaddec_1_Init(void) 
{
    #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
        /* Disable Interrupt. */
        CyIntDisable(quaddec_1_ISR_NUMBER);
        /* Set the ISR to point to the quaddec_1_isr Interrupt. */
        (void) CyIntSetVector(quaddec_1_ISR_NUMBER, & quaddec_1_ISR);
        /* Set the priority. */
        CyIntSetPriority(quaddec_1_ISR_NUMBER, quaddec_1_ISR_PRIORITY);
    #endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: quaddec_1_Enable
********************************************************************************
*
* Summary:
*  This function enable interrupts from Component and also enable Component's
*  ISR in case of 32-bit counter.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void quaddec_1_Enable(void) 
{
    uint8 enableInterrupts;

    quaddec_1_SetInterruptMask(quaddec_1_INIT_INT_MASK);

    /* Clear pending interrupts. */
    (void) quaddec_1_GetEvents();
    
    enableInterrupts = CyEnterCriticalSection();

    /* Enable interrupts from Statusi register */
    quaddec_1_SR_AUX_CONTROL |= quaddec_1_INTERRUPTS_ENABLE;

    CyExitCriticalSection(enableInterrupts);        

    #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
        /* Enable Component interrupts */
        CyIntEnable(quaddec_1_ISR_NUMBER);
    #endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: quaddec_1_Start
********************************************************************************
*
* Summary:
*  Initializes UDBs and other relevant hardware.
*  Resets counter, enables or disables all relevant interrupts.
*  Starts monitoring the inputs and counting.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  quaddec_1_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void quaddec_1_Start(void) 
{
    #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT)
        quaddec_1_Cnt8_Start();
        quaddec_1_Cnt8_WriteCounter(quaddec_1_COUNTER_INIT_VALUE);
    #else
        /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT) || 
        *  (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT) 
        */
        quaddec_1_Cnt16_Start();
        quaddec_1_Cnt16_WriteCounter(quaddec_1_COUNTER_INIT_VALUE);
    #endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT */
    
    #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)        
       quaddec_1_count32SoftPart = 0;
    #endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT */

    if (quaddec_1_initVar == 0u)
    {
        quaddec_1_Init();
        quaddec_1_initVar = 1u;
    }

    quaddec_1_Enable();
}


/*******************************************************************************
* Function Name: quaddec_1_Stop
********************************************************************************
*
* Summary:
*  Turns off UDBs and other relevant hardware.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void quaddec_1_Stop(void) 
{
    uint8 enableInterrupts;

    #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT)
        quaddec_1_Cnt8_Stop();
    #else 
        /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT) ||
        *  (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
        */
        quaddec_1_Cnt16_Stop();    /* counter disable */
    #endif /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT) */
 
    enableInterrupts = CyEnterCriticalSection();

    /* Disable interrupts interrupts from Statusi register */
    quaddec_1_SR_AUX_CONTROL &= (uint8) (~quaddec_1_INTERRUPTS_ENABLE);

    CyExitCriticalSection(enableInterrupts);

    #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
        CyIntDisable(quaddec_1_ISR_NUMBER);    /* interrupt disable */
    #endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT */
}


/*******************************************************************************
* Function Name: quaddec_1_GetCounter
********************************************************************************
*
* Summary:
*  Reports the current value of the counter.
*
* Parameters:
*  None.
*
* Return:
*  The counter value. Return type is signed and per the counter size setting.
*  A positive value indicates clockwise movement (B before A).
*
* Global variables:
*  quaddec_1_count32SoftPart - used to get hi 16 bit for current value
*  of the 32-bit counter, when Counter size equal 32-bit.
*
*******************************************************************************/
int32 quaddec_1_GetCounter(void) 
{
    int32 count;
    uint16 tmpCnt;

    #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
        int16 hwCount;

        CyIntDisable(quaddec_1_ISR_NUMBER);

        tmpCnt = quaddec_1_Cnt16_ReadCounter();
        hwCount = (int16) ((int32) tmpCnt - (int32) quaddec_1_COUNTER_INIT_VALUE);
        count = quaddec_1_count32SoftPart + hwCount;

        CyIntEnable(quaddec_1_ISR_NUMBER);
    #else 
        /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT) || 
        *  (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT)
        */
        #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT)
            tmpCnt = quaddec_1_Cnt8_ReadCounter();
        #else /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT) */
            tmpCnt = quaddec_1_Cnt16_ReadCounter();
        #endif  /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT */

        count = (int32) ((int32) tmpCnt -
                (int32) quaddec_1_COUNTER_INIT_VALUE);

    #endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT */ 

    return (count);
}


/*******************************************************************************
* Function Name: quaddec_1_SetCounter
********************************************************************************
*
* Summary:
*  Sets the current value of the counter.
*
* Parameters:
*  value:  The new value. Parameter type is signed and per the counter size
*  setting.
*
* Return:
*  None.
*
* Global variables:
*  quaddec_1_count32SoftPart - modified to set hi 16 bit for current
*  value of the 32-bit counter, when Counter size equal 32-bit.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void quaddec_1_SetCounter(int32 value) 
{
    #if ((quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT) || \
         (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT))
        uint16 count;
        
        if (value >= 0)
        {
            count = (uint16) value + quaddec_1_COUNTER_INIT_VALUE;
        }
        else
        {
            count = quaddec_1_COUNTER_INIT_VALUE - (uint16)(-value);
        }
        #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT)
            quaddec_1_Cnt8_WriteCounter(count);
        #else /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT) */
            quaddec_1_Cnt16_WriteCounter(count);
        #endif  /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT */
    #else /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT) */
        CyIntDisable(quaddec_1_ISR_NUMBER);

        quaddec_1_Cnt16_WriteCounter(quaddec_1_COUNTER_INIT_VALUE);
        quaddec_1_count32SoftPart = value;

        CyIntEnable(quaddec_1_ISR_NUMBER);
    #endif  /* (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_8_BIT) ||
             * (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_16_BIT)
             */
}


/*******************************************************************************
* Function Name: quaddec_1_GetEvents
********************************************************************************
* 
* Summary:
*   Reports the current status of events. This function clears the bits of the 
*   status register.
*
* Parameters:
*  None.
*
* Return:
*  The events, as bits in an unsigned 8-bit value:
*    Bit      Description
*     0        Counter overflow.
*     1        Counter underflow.
*     2        Counter reset due to index, if index input is used.
*     3        Invalid A, B inputs state transition.
*
*******************************************************************************/
uint8 quaddec_1_GetEvents(void) 
{
    return (quaddec_1_STATUS_REG & quaddec_1_INIT_INT_MASK);
}


/*******************************************************************************
* Function Name: quaddec_1_SetInterruptMask
********************************************************************************
*
* Summary:
*  Enables / disables interrupts due to the events.
*  For the 32-bit counter, the overflow, underflow and reset interrupts cannot
*  be disabled, these bits are ignored.
*
* Parameters:
*  mask: Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*
* Return:
*  None.
*
*******************************************************************************/
void quaddec_1_SetInterruptMask(uint8 mask) 
{
    #if (quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT)
        /* Underflow, Overflow and Reset interrupts for 32-bit Counter are always enable */
        mask |= (quaddec_1_COUNTER_OVERFLOW | quaddec_1_COUNTER_UNDERFLOW |
                 quaddec_1_COUNTER_RESET);
    #endif /* quaddec_1_COUNTER_SIZE == quaddec_1_COUNTER_SIZE_32_BIT */

    quaddec_1_STATUS_MASK = mask;
}


/*******************************************************************************
* Function Name: quaddec_1_GetInterruptMask
********************************************************************************
*
* Summary:
*  Reports the current interrupt mask settings.
*
* Parameters:
*  None.
*
* Return:
*  Enable / disable bits in an 8-bit value, where 1 enables the interrupt.
*  For the 32-bit counter, the overflow, underflow and reset enable bits are
*  always set.
*
*******************************************************************************/
uint8 quaddec_1_GetInterruptMask(void) 
{
    return (quaddec_1_STATUS_MASK & quaddec_1_INIT_INT_MASK);
}


/* [] END OF FILE */
