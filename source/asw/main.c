/**
* \file main
*
* \brief Demonstrator for Reaction Game with Arcadian lights
*
* The code written is for a reaction game which waits for a button to be pressed and
* measures the reaction time of the player.
* A random delay is generated before displaying 
* a random number 1 or 2 on the 7-segment display.
* If the reaction time is within 1s, then further check is done if right button
* is pressed when 2 is displayed and left button is pressed when 1 is displayed
* Paralelly the score and reaction time are noted.
* Finally after 10 rounds of the game, the Total time, score and the average reaction
* time is displayed and Game is over.
* At the same time, a basic task with the least priority that produces a
* knightrider effect from the fader function and the glower function
* produces a pattern of rise and fall of LED brightness on the RGB LED
* is also fired.
*/

#include "game.h"

#undef TRC_SYSTICK

//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
#ifdef TRC_SYSTICK
    vTraceStoreISRBegin(TRC_SystickHandle);
#endif   
    
    CounterTick(cnt_systick);

#ifdef TRC_SYSTICK
    vTraceStoreISREnd(0);
#endif   

}

int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
   
    // Start Operating System
    for(;;)	    
    	StartOS(OSDEFAULTAPPMODE);
}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    __asm("bkpt");
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_init)
{
    
    //Init MCAL Drivers
    UART_LOG_Start();
    
    LED_Init();
    SEVEN_Init();
  
    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
    
	
    //Start SysTick
	//Must be done here, because otherwise the isr vector is not overwritten yet
    EE_systick_start();

        
    UART_LOG_PutString("Welcome\n");

    //Start the cyclic alarms 
    SetRelAlarm(alrm_Tick1ms,1,1);
    SetRelAlarm(alrm_arcadian,10,10);
    
    //Activate all extended and the background task
    ActivateTask(tsk_button);
    ActivateTask(tsk_background);

    TerminateTask();
    
}


TASK(tsk_background)
{
    while(1)
    {
        //do something with low prioroty
        __asm("nop");
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/


ISR2(isr_Button)
{
    if (BUTTON_1_Read() == 1) SetEvent(tsk_event,ev_Button_1);   
    if (BUTTON_2_Read() == 1) SetEvent(tsk_event,ev_Button_2);
    
}

ISR2(isr_Reset)
{
    if (BUTTON_3_Read() == 1) SetEvent(tsk_button,ev_Button_3);   
    if (BUTTON_4_Read() == 1) SetEvent(tsk_button,ev_Button_4);
}



/* [] END OF FILE */
