/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "game.h"
/*
* Function to check the reaction time of the user. If the time of 
* response between the seven segment display and button press is 
* over 1s, then Too slow will be displayed
* @param uint16_t reactionTime : [IN] time between the seven segment
*                                    display and button press
* @returns RC_ERROR : [OUT] if Reaction speed is too slow (>1s)
* @returns RC_SUCCESS:[OUT] if Reaction speed is within 1s
*/
RC_t reactionSpeed(uint16_t reactionTime ){
    if(reactionTime > 1000){
        UART_LOG_PutString("Too slow \n");
        return RC_ERROR;
    }
    return RC_SUCCESS;
}


uint16_t startTime = 0;
uint16_t counterTimer = 0;

/*
* Function to initialize the reaction test program
*/
void startGame() {
    srand(counterTimer);
    UART_LOG_PutString("=======================================================\n");
    UART_LOG_PutString("Reaction test program\n");
    UART_LOG_PutString("Press one of the two buttons to start... \n");
}

/*
* Function to generate a random delay and display a random number on the 7-segment displays
* It also captures the current counter timing in startTime variable
*/
void generateRandomDelayAndDisplay() {
    uint8_t randomDelay = (rand() % 2000) + 1000;
    CyDelay(randomDelay);
    srand(counterTimer);
    uint8_t currentNumOnSeg = (rand() % 2) + 1;

    SEVEN_Set(SEVEN_1, currentNumOnSeg);
    SEVEN_Set(SEVEN_0, currentNumOnSeg);
    
    startTime = counterTimer;
}

/*
* tsk_button is an extended task that waits for a button 3 or 4 to be pressed
* to start/reset the game. The ISR2 isr_Reset checks if button 3 or 4 is 
* pressed and sets the event for this task. 
* This task also generates a random delay between 1s to 3s before displaying 
* a random number 1 or 2 on the 7-segment display which is done by calling
* generateRandomDelayAndDisplay() function
*/
TASK(tsk_button) {
    while (1) {
        EventMaskType ev = 0;
        srand(counterTimer);
        startGame();

        WaitEvent(ev_Button_3 | ev_Button_4);
        GetEvent(tsk_button, &ev);
        ClearEvent(ev);
        // rand seed  insert here, so the randomness is created by the user
        generateRandomDelayAndDisplay();
        ActivateTask(tsk_event);
    }
    TerminateTask();
}

/*
* tsk_timer is a basic task called by the alrm_Tick1ms which is called
* every 1ms. Here a variable counterTimer is incremented
*/
TASK(tsk_timer)
{
    counterTimer++;  
    TerminateTask();
}

/*
* tsk_event is an extended task that waits for a button 1 or 2 press.
* Initially, the game waits for a button to be pressed and if an event
* occurs, will measure the current counter timer and calculate the difference,
* which is the reaction time of the player.
* If the reaction time is within 1s, then further check is done if right button
* is pressed when 2 is displayed and left button is pressed when 1 is displayed
* Paralelly the score and reaction time are noted and the later is stored in an array
* Finally after 10 rounds of the game, the Total time, score and the average reaction
* time is displayed and Game is over
*/
TASK(tsk_event)
{  
    uint8_t gameRound =0;
    static int score = 0;
    static float avgTime = 0.0;
    static int reactionTimeArray[10];

    while(1)
    {
    EventMaskType ev = 0;
    uint16_t endTime =0;
        
    uint16_t reactionTime = 0;    

    if(gameRound<10)
    {  
        WaitEvent (ev_Button_1 | ev_Button_2);
        GetEvent(tsk_event, &ev);
        ClearEvent(ev);
        endTime = counterTimer;
        reactionTime = endTime-startTime;
        if (reactionSpeed(reactionTime) != RC_ERROR){
            if (ev & ev_Button_1){
                if(SEVEN_Ret(SEVEN_0) == 2){
                    score++;
                    reactionTimeArray[gameRound] = reactionTime;
                    char buffer[20];
                    sprintf(buffer,"Great - correct button pressed \nReaction time in ms: %d \n",reactionTime);
                    UART_LOG_PutString(buffer);
                }
                else{
                    UART_LOG_PutString("Error: Incorrect button pressed\n");       
                }  
            }
            if (ev & ev_Button_2){
                if(SEVEN_Ret(SEVEN_1) == 1){
                    score++;
                    reactionTimeArray[gameRound] = reactionTime;
                    char buffer[20];
                    sprintf(buffer,"Great - correct button pressed \nReaction time in ms: %d \n",reactionTime);
                    UART_LOG_PutString(buffer);
                }
                else{
                    UART_LOG_PutString("Error: Incorrect button pressed\n");       
                }
            }
            gameRound++;

        }
            SEVEN_Clear(SEVEN_1);
            SEVEN_Clear(SEVEN_0);
    }
    else if(gameRound == 10){
        static int sumTime = 0;
        for (int i = 0; i < gameRound; i++) {
            sumTime += reactionTimeArray[i];
            }
        avgTime = (float)sumTime / 10.0;
        char buffer[40];
        sprintf(buffer,"Game score: %d \nTotal time : %d\nAverage reaction time in ms: %.2f \nGame Over!\n",score,sumTime, avgTime);
        UART_LOG_PutString(buffer);
        break;        
        }
    }
    
    TerminateTask();
}

/* [] END OF FILE */
