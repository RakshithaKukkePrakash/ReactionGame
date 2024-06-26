/*******************************************************************************
* File Name: PWM_Yellow_1_PM.c
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

#include "PWM_Yellow_1.h"

static PWM_Yellow_1_backupStruct PWM_Yellow_1_backup;


/*******************************************************************************
* Function Name: PWM_Yellow_1_SaveConfig
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
*  PWM_Yellow_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_Yellow_1_SaveConfig(void) 
{

    #if(!PWM_Yellow_1_UsingFixedFunction)
        #if(!PWM_Yellow_1_PWMModeIsCenterAligned)
            PWM_Yellow_1_backup.PWMPeriod = PWM_Yellow_1_ReadPeriod();
        #endif /* (!PWM_Yellow_1_PWMModeIsCenterAligned) */
        PWM_Yellow_1_backup.PWMUdb = PWM_Yellow_1_ReadCounter();
        #if (PWM_Yellow_1_UseStatus)
            PWM_Yellow_1_backup.InterruptMaskValue = PWM_Yellow_1_STATUS_MASK;
        #endif /* (PWM_Yellow_1_UseStatus) */

        #if(PWM_Yellow_1_DeadBandMode == PWM_Yellow_1__B_PWM__DBM_256_CLOCKS || \
            PWM_Yellow_1_DeadBandMode == PWM_Yellow_1__B_PWM__DBM_2_4_CLOCKS)
            PWM_Yellow_1_backup.PWMdeadBandValue = PWM_Yellow_1_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_Yellow_1_KillModeMinTime)
             PWM_Yellow_1_backup.PWMKillCounterPeriod = PWM_Yellow_1_ReadKillTime();
        #endif /* (PWM_Yellow_1_KillModeMinTime) */

        #if(PWM_Yellow_1_UseControl)
            PWM_Yellow_1_backup.PWMControlRegister = PWM_Yellow_1_ReadControlRegister();
        #endif /* (PWM_Yellow_1_UseControl) */
    #endif  /* (!PWM_Yellow_1_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_Yellow_1_RestoreConfig
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
*  PWM_Yellow_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Yellow_1_RestoreConfig(void) 
{
        #if(!PWM_Yellow_1_UsingFixedFunction)
            #if(!PWM_Yellow_1_PWMModeIsCenterAligned)
                PWM_Yellow_1_WritePeriod(PWM_Yellow_1_backup.PWMPeriod);
            #endif /* (!PWM_Yellow_1_PWMModeIsCenterAligned) */

            PWM_Yellow_1_WriteCounter(PWM_Yellow_1_backup.PWMUdb);

            #if (PWM_Yellow_1_UseStatus)
                PWM_Yellow_1_STATUS_MASK = PWM_Yellow_1_backup.InterruptMaskValue;
            #endif /* (PWM_Yellow_1_UseStatus) */

            #if(PWM_Yellow_1_DeadBandMode == PWM_Yellow_1__B_PWM__DBM_256_CLOCKS || \
                PWM_Yellow_1_DeadBandMode == PWM_Yellow_1__B_PWM__DBM_2_4_CLOCKS)
                PWM_Yellow_1_WriteDeadTime(PWM_Yellow_1_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_Yellow_1_KillModeMinTime)
                PWM_Yellow_1_WriteKillTime(PWM_Yellow_1_backup.PWMKillCounterPeriod);
            #endif /* (PWM_Yellow_1_KillModeMinTime) */

            #if(PWM_Yellow_1_UseControl)
                PWM_Yellow_1_WriteControlRegister(PWM_Yellow_1_backup.PWMControlRegister);
            #endif /* (PWM_Yellow_1_UseControl) */
        #endif  /* (!PWM_Yellow_1_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_Yellow_1_Sleep
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
*  PWM_Yellow_1_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_Yellow_1_Sleep(void) 
{
    #if(PWM_Yellow_1_UseControl)
        if(PWM_Yellow_1_CTRL_ENABLE == (PWM_Yellow_1_CONTROL & PWM_Yellow_1_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_Yellow_1_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_Yellow_1_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_Yellow_1_UseControl) */

    /* Stop component */
    PWM_Yellow_1_Stop();

    /* Save registers configuration */
    PWM_Yellow_1_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_Yellow_1_Wakeup
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
*  PWM_Yellow_1_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_Yellow_1_Wakeup(void) 
{
     /* Restore registers values */
    PWM_Yellow_1_RestoreConfig();

    if(PWM_Yellow_1_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_Yellow_1_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
