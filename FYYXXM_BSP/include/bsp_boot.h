#ifndef __BSP_BOOT_H
#define __BSP_BOOT_H

#include "bsp.h"

/* STM32H750， FALASH 扇区大小为128KB， boot区需要占用128KB  */
#define APPLICATION_ADDRESS		ADDR_FLASH_SECTOR_2_BANK1 		// 选择128K以后的区域作为APP程序区（2MB-128KB)

#define BSP_Enable_IRQ()  __set_PRIMASK(0)  /*  使能全局中断 */

#define BSP_Disable_IRQ() __set_PRIMASK(1)  /* 禁止全局中断*/

void BSP_JumpToApp(void);

uint8_t CheckAppOk(void);
    
#endif
