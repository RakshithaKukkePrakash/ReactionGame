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
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "project.h"
#include "global.h"
#include "seven.h"
#include "button.h"
#include "led.h"

/*
* Function to initialize the reaction test program
*/
void startGame();

/*
* Function to generate a random delay and display a random number on the 7-segment displays
*/
void generateRandomDelayAndDisplay();

/*
* Function to check the reaction time of the user. If the time of 
* response between the seven segment display and button press is 
* over 1s, then Too slow will be displayed
* @param uint16_t reactionTime : [IN] time between the seven segment
*                                    display and button press
* @returns RC_ERROR : [OUT] if Reaction speed is too slow (>1s)
* @returns RC_SUCCESS:[OUT] if Reaction speed is within 1s
*/
RC_t reactionSpeed(uint16_t reactionTime);

/* [] END OF FILE */
