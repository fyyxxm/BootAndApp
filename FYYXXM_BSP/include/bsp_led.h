#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "bsp.h"

typedef enum
{
    LED_PSD_FLAG = 0,
    LED_PCM_FLAG,
    LED_PLAY_FLAG
}_ENUM_LED_FLAG;

void BSP_LedInit(void);
void BSP_LedOn(_ENUM_LED_FLAG led_flag);
void BSP_LedOff(_ENUM_LED_FLAG led_flag);
void BSP_LedToggle(_ENUM_LED_FLAG led_flag);
void BSP_LedErrorHandler(void);

#endif