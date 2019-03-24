#include <l2hal_custom.h>

void L2HAL_InitCustomHardware(void)
{
	/* Preparing I2C */
	L2HAL_SetupI2C();
}

void L2HAL_SetupI2C(void)
{
	/* Clocking I2C */
	__HAL_RCC_I2C1_CLK_ENABLE();

	/**
	 * Setting up I2C
	 */

	I2CHandle.Instance = I2C1;
	I2CHandle.Init.ClockSpeed = 400000; /* 400 KHz */
	I2CHandle.Init.DutyCycle = I2C_DUTYCYCLE_2;
	I2CHandle.Init.OwnAddress1 = 0x00;
	I2CHandle.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	I2CHandle.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	I2CHandle.Init.OwnAddress2 = 0x00;
	I2CHandle.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	I2CHandle.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	if(HAL_I2C_Init(&I2CHandle) != HAL_OK)
	{
		/* Initialization Error */
		L2HAL_Error(Generic);
	}
}

void HAL_I2C_MspInit(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->Instance == I2C1)
	{
		/**
		 * Setting up port
		 * I2C1 at PB6 (SCL) and PB7 (SDA)
		 */

		/* Clocking port */
		__HAL_RCC_GPIOB_CLK_ENABLE();

		GPIO_InitTypeDef GPIO_InitStruct;

		GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
		GPIO_InitStruct.Pull = GPIO_PULLUP;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

		HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

		/* Display driver uses I2C interrupts exchange */
		HAL_NVIC_SetPriority(I2C1_ER_IRQn, I2C1_ER_IRQN_PRIORITY, I2C1_ER_IRQN_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
		HAL_NVIC_SetPriority(I2C1_EV_IRQn, I2C1_EV_IRQN_PRIORITY, I2C1_EV_IRQN_SUBPRIORITY);
		HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
	}
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
	if (hi2c->Instance == I2C1)
	{
		HAL_NVIC_DisableIRQ(I2C1_ER_IRQn);
		HAL_NVIC_DisableIRQ(I2C1_EV_IRQn);

		__HAL_RCC_I2C1_CLK_DISABLE();
		HAL_GPIO_DeInit(GPIOB, GPIO_PIN_6 | GPIO_PIN_7);
	}
}

void I2C1_EV_IRQHandler(void)
{
	HAL_I2C_EV_IRQHandler(&I2CHandle);
}

void I2C1_ER_IRQHandler(void)
{
	HAL_I2C_ER_IRQHandler(&I2CHandle);
}

void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c)
{
	if (hi2c->Instance == I2C1)
	{
		L2HAL_SSD1306_InterruptTransferCompleted(&L2HAL_SSD1306_Context);
	}
}


