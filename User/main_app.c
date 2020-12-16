#include "main.h"

/* adress 0x8040000 */
uint8_t g_AppFlag = 0;
int main()
{
    BSP_MPUConfig();
    BSP_CPUCacheEnable();
    HAL_Init();
    BSP_SystemClockConfig();
    
    BSP_Usart1Init();  //If the Usart is not initialized, HAL_Delay has no problem
    
    while (1)
    {
//        printf("APP OK\r\n");
        g_AppFlag++;
        HAL_Delay(100);     //HAL_Delay Stuck
        
        if (g_AppFlag == 5) 
        {
            g_AppFlag = g_AppFlag + 2;
        }
    }
}

