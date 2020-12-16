#include "bsp.h"

/* Private typedef -----------------------------------------------------------*/
typedef void (*pFunction)(void);
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
pFunction JumpToApplication;

/*
*********************************************************************************************************
*	函 数 名: BSP_JumpToApp
*	功能说明: 跳转到APP程序 0x0800 2000
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_JumpToApp(void)
{
    /* Disable CPU L1 cache before jumping to the QSPI code execution */
    BSP_CPUCacheDisable();
    /* Disable Systick interrupt */
    __disable_irq();
//    BSP_Disable_IRQ();
    SysTick->CTRL = 0;
    /* Initialize user application's Stack Pointer & Jump to user application */
    JumpToApplication = (pFunction)(*(__IO uint32_t *)(APPLICATION_ADDRESS + 4));

    __set_MSP(*(__IO uint32_t *)APPLICATION_ADDRESS);

    JumpToApplication();

    /* We should never get here as execution is now on user application */
    while (1)
    {

    }
}


/*
*********************************************************************************************************
*	函 数 名: CheckAppOk
*	功能说明: 检查APP程序是否有效。
*	形    参: 无
*	返 回 值: 返回1表示OK，0表示失败
*********************************************************************************************************
*/
uint8_t CheckAppOk(void)
{
#if 1	
	uint32_t StackAddr;

	StackAddr = *(__IO uint32_t*)APPLICATION_ADDRESS + 128 * 1024;
	
	// 0x2408EDF8   0x20020000
	if ((StackAddr & 0x2FF00000) == 0x24000000 || (StackAddr & 0x2FF00000) == 0x20000000)
	{
		return 1;
	}
	return 0;
#else		/* 检查APP校验（是否合法程序） 未启用 */
	uint32_t ProgLen = *(uint32_t *)0x08008010;		/* app程序有效长度 */
	uint32_t ProgCrc = *(uint32_t *)0x08008014;		/* app程序CRC校验 */
	uint16_t crc1, crc2;
	uint32_t flash_size;
	
	flash_size = bsp_GetFlashSize();	/* falsh 容量 */
	
	if (ProgLen > flash_size - 8 * 1024)
	{
		return 0;
	}
	
	crc1 = CRC16_Modbus((uint8_t *)(0x08002000 + 0x100), ProgLen / 2);
	crc2 = CRC16_Modbus((uint8_t *)(0x08002000 + ProgLen / 2), ProgLen / 2);
	
	if (crc1 == (ProgCrc >> 16) && crc2 == (ProgCrc & 0xFFFF))
	{
		return 1;
	}
	else
	{
		return 0;
	}
#endif
}