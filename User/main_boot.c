#include "main.h"
/*
*********************************************************************************************************
*                                      main
*********************************************************************************************************
*/
#define g_JumpInit *(uint32_t *)0x20000000

int main()
{
    if (g_JumpInit == 0x12345678)
    {
        g_JumpInit = 0;
        BSP_JumpToApp();  
    }

    BSP_MPUConfig();
    BSP_CPUCacheEnable();
    HAL_Init();
    BSP_SystemClockConfig();
    BSP_Usart1Init();       
    while(1)
    {
        HAL_Delay(100);         // HAL_Delay : OK!
        g_JumpInit = 0x12345678;
//        BSP_JumpToApp();  
        NVIC_SystemReset();     // RESET CPU 
    }
}

