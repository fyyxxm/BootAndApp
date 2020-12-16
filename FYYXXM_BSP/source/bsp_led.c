#include "bsp.h"

void BSP_LedInit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOA_CLK_ENABLE();

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);

    /*Configure GPIO pin : PA1 */
    GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void BSP_LedOn(_ENUM_LED_FLAG led_flag)
{
    switch (led_flag)
    {
    case LED_PSD_FLAG:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
        break;
    case LED_PCM_FLAG:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
        break;
    case LED_PLAY_FLAG:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
        break;
    default:
        BSP_LedErrorHandler();
        break;
    }
}

void BSP_LedOff(_ENUM_LED_FLAG led_flag)
{
    switch (led_flag)
    {
    case LED_PSD_FLAG:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
        break;
    case LED_PCM_FLAG:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
        break;
    case LED_PLAY_FLAG:
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET);
        break;
    default:
        BSP_LedErrorHandler();
        break;
    }   
}

void BSP_LedToggle(_ENUM_LED_FLAG led_flag)
{
    switch (led_flag)
    {
    case LED_PSD_FLAG:
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);
        break;
    case LED_PCM_FLAG:
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_2);
        break;
    case LED_PLAY_FLAG:
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_3);
        break;
    default:
        BSP_LedErrorHandler();
        break;
    }   
}

void BSP_LedErrorHandler(void)
{
    printf("this is led error\r\n");
}