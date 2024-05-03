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
#include "arcadian.h"

/**
* Function Glower that changes intensity of red, green and blue LEDs
* which glows and fades at required intervals mentioned in the glow table
*/
void glower(){
    static  uint8_t glow = 0;

    if(glow<sizeof(RG_glowtable_1) / sizeof(RG__Glow_t)){
    int redValue = RG_glowtable_1[glow].intensity_red;
    int greenValue = RG_glowtable_1[glow].intensity_green;
    int blueValue = RG_glowtable_1[glow].intensity_blue;
    int timeInMS = RG_glowtable_1[glow].timeInMS;
    LED_RGB_Set(redValue,greenValue,blueValue);
    CyDelay(timeInMS);
    glow++;
    }
    else{  
    glow =0;
    }
}

/**
* Function Fader that changes intensity of red, yellow and green LED
* which glows and fades at required intervals 
*/
void fader(){
    static int i = 0;
    static int j = 0;
    static int k = 0;
    static int state = 0;
    switch (state) {
    case 0:
        PWM_Red_WriteCompare(i);
        PWM_Green_WriteCompare(255 - i);
        i += 15;

        if (PWM_Red_ReadCompare() == 255) {
            state = 1;
            i = 0;
        }
        break;

    case 1:
        PWM_Yellow_WriteCompare(j);
        PWM_Red_WriteCompare(255 - j);
        j += 15;

        if (PWM_Yellow_ReadCompare() == 255) {
            state = 2;
            j = 0;
        }
        break;

    case 2:
        PWM_Green_WriteCompare(k);
        PWM_Yellow_WriteCompare(255 - k);
        k += 15;

        if (PWM_Green_ReadCompare() == 255) {
            state = 0;
            k = 0;
        }
        break;
    }
}

/*
* tsk_arcadian is a basic task with the least priority that produces a
* knightrider effect from the fader function and the glower function
* produces a pattern of rise and fall of LED brightness on the RGB LED
*/
TASK(tsk_arcadian)
{
    glower();
    fader();
    TerminateTask();
}

/* [] END OF FILE */
