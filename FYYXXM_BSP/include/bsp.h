#ifndef __BSP_H
#define __BSP_H

/* C std lib */
#include "stdio.h"
#include "stdint.h"
#include "stdarg.h"
#include "string.h"

/* Hal/LL lib*/
#include "stm32h743xx.h"
#include "stm32h7xx.h"
#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_rcc.h"
#include "stm32h7xx_hal_pwr.h"
#include "stm32h7xx_hal_gpio.h"
#include "stm32h7xx_hal_uart.h"
#include "stm32h7xx_hal_usart.h"
#include "stm32h7xx_hal_tim.h"
#include "stm32h7xx_hal_sd.h"
#include "stm32h7xx_hal_mmc.h"
#include "stm32h7xx_hal_exti.h"
#include "stm32h7xx_hal_sai.h"
#include "stm32h7xx_hal_spi.h"

#include "bsp_system_clock.h"
#include "bsp_mpu_config.h"
#include "bsp_usart.h"
#include "bsp_led.h"
#include "bsp_boot.h"
#include "bsp_cpu_flash.h"

#endif