#ifndef __BSP_DWT_H
#define __BSP_DWT_H

#include "bsp.h"

/* 宏定义 */
#define DWT_CYCCNT *(volatile unsigned int *)0xE0001004
#define DWT_CR *(volatile unsigned int *)0xE0001000
#define DEM_CR *(volatile unsigned int *)0xE000EDFC
#define DBGMCU_CR *(volatile unsigned int *)0xE0042004

/* 函数声明*/
void BSP_InitDWT(void);
void BSP_DelayDWT(uint32_t _ulDelayTime);
void BSP_DelayUS(uint32_t _ulDelayTime);
void BSP_DelayMS(uint32_t _ulDelayTime);

#endif