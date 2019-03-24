#include <l2hal_errors.h>

void L2HAL_Error(L2HAL_ErrorCode code)
{
	L2HAL_ERROR_CLOCK_SIGNAL_PORT();

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	GPIO_InitStruct.Pin = L2HAL_ERROR_SIGNAL_PIN;
	HAL_GPIO_Init(L2HAL_ERROR_SIGNAL_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(L2HAL_ERROR_SIGNAL_PORT, L2HAL_ERROR_SIGNAL_PIN, L2HAL_ERROR_SIGNAL_PIN_STATE);

	/* Halt */
	while(1) {}
}
