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
/**
* Structure that holds the intensity of the led components and the duration 
* of each step in milliseconds.
*/ 
typedef struct{
    uint8_t intensity_red;
    uint8_t intensity_green;
    uint8_t intensity_blue;
    uint16_t timeInMS;
}RG__Glow_t;

/**
* Look up table that represents the glow intensity of each of the red, 
* green and blue components of the RGB LED with the duration between each  
* glow given in ms
*/ 
const RG__Glow_t RG_glowtable_1[] = {
    //Red Green Blue TimeInMS
    {255, 0, 0, 500},
    {0,255, 0, 500},
    {0,0, 255, 500},
    {0,0, 0, 100},
    {255, 255, 255, 100},
    {0,0, 0, 100},
    {255, 255, 255, 100},
    {0,0, 0, 100},
    {255, 255, 255, 100}
    };


/**
* Function Glower that changes intensity of red, green and blue LEDs
* which glows and fades at required intervals mentioned in the glow table
*/
void glower();

/**
* Function Fader that changes intensity of red, yellow and green LED
* which glows and fades at required intervals 
*/
void fader();
/* [] END OF FILE */
