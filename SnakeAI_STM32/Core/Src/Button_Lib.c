/*
 * Button_Lib.c
 *
 *  Created on: Aug 16, 2024
 *      Author: barte
 */
#include "Button_lib.h"
#include "spi.h"

/*Button_Status Status_Button(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin){
	static Button_Status statusButton = Ready2GO;
	static uint32_t pressStartTime = 0;

	switch (statusButton)
	{
	case Ready2GO: statusButton = (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET) ? Press_Test : Ready2GO; break;

	case Press_Test:  statusButton = ((HAL_GetTick() - pressStartTime) > 20) ? Press : Ready2GO; break;

	case Press: statusButton = ((HAL_GetTick()-pressStartTime) > 1000) ? Hold : Press; break;

	case Hold: statusButton = (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)==GPIO_PIN_SET) ? Ready2GO : Hold; break;

	default: statusButton = Ready2GO; break;
	}

	return statusButton;
}
*/
Button_Status Status_Button(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
    static Button_Status statusButton = Ready2GO;
    static uint32_t pressStartTime = 0;

    switch (statusButton) {
        case Ready2GO:
            statusButton = (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET) ? Press_Test : Ready2GO;
            if (statusButton == Press_Test) {
                pressStartTime = HAL_GetTick();
            }
            break;

        case Press_Test:
            statusButton = ((HAL_GetTick() - pressStartTime) > 20) ? Press : (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET ? Ready2GO : Press_Test);
            break;

        case Press:
            statusButton = ((HAL_GetTick() - pressStartTime) > 1500) ? Hold : (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin)==GPIO_PIN_SET ? Ready2GO : Press);
            break;

        case Hold:
            statusButton = (HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_SET) ? Ready2GO : Hold;
            break;



        default:
            statusButton = Ready2GO;
            break;
    }

    return statusButton;

}
