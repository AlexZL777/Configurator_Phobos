#include "defines_HW.h"

#ifdef _DEFINES_HW_3_1_H_

void deinit_pin(GPIO_TypeDef *port, uint32_t pin, uint32_t state)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = state;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

void init_pin(GPIO_TypeDef *port, uint32_t pin, uint32_t state, uint32_t pull, uint32_t speed)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.Pin = pin;
    GPIO_InitStruct.Mode = state;
    GPIO_InitStruct.Pull = pull;
    GPIO_InitStruct.Speed = speed;
    HAL_GPIO_Init(port, &GPIO_InitStruct);
}

#endif // _DEFINES_HW_3_1_H_
