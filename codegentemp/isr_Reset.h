/*******************************************************************************
* File Name: isr_Reset.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_isr_Reset_H)
#define CY_ISR_isr_Reset_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_Reset_Start(void);
void isr_Reset_StartEx(cyisraddress address);
void isr_Reset_Stop(void);

CY_ISR_PROTO(isr_Reset_Interrupt);

void isr_Reset_SetVector(cyisraddress address);
cyisraddress isr_Reset_GetVector(void);

void isr_Reset_SetPriority(uint8 priority);
uint8 isr_Reset_GetPriority(void);

void isr_Reset_Enable(void);
uint8 isr_Reset_GetState(void);
void isr_Reset_Disable(void);

void isr_Reset_SetPending(void);
void isr_Reset_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_Reset ISR. */
#define isr_Reset_INTC_VECTOR            ((reg32 *) isr_Reset__INTC_VECT)

/* Address of the isr_Reset ISR priority. */
#define isr_Reset_INTC_PRIOR             ((reg8 *) isr_Reset__INTC_PRIOR_REG)

/* Priority of the isr_Reset interrupt. */
#define isr_Reset_INTC_PRIOR_NUMBER      isr_Reset__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_Reset interrupt. */
#define isr_Reset_INTC_SET_EN            ((reg32 *) isr_Reset__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_Reset interrupt. */
#define isr_Reset_INTC_CLR_EN            ((reg32 *) isr_Reset__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_Reset interrupt state to pending. */
#define isr_Reset_INTC_SET_PD            ((reg32 *) isr_Reset__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_Reset interrupt. */
#define isr_Reset_INTC_CLR_PD            ((reg32 *) isr_Reset__INTC_CLR_PD_REG)


#endif /* CY_ISR_isr_Reset_H */


/* [] END OF FILE */
