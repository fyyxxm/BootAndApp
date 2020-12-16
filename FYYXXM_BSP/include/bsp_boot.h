#ifndef __BSP_BOOT_H
#define __BSP_BOOT_H

#include "bsp.h"

/* STM32H750�� FALASH ������СΪ128KB�� boot����Ҫռ��128KB  */
#define APPLICATION_ADDRESS		ADDR_FLASH_SECTOR_2_BANK1 		// ѡ��128K�Ժ��������ΪAPP��������2MB-128KB)

#define BSP_Enable_IRQ()  __set_PRIMASK(0)  /*  ʹ��ȫ���ж� */

#define BSP_Disable_IRQ() __set_PRIMASK(1)  /* ��ֹȫ���ж�*/

void BSP_JumpToApp(void);

uint8_t CheckAppOk(void);
    
#endif
