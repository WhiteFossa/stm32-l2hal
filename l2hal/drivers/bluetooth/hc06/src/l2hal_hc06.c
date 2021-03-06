/*
 * l2hal_hc06.c
 *
 *  Created on: May 3, 2021
 *      Author: fossa
 */

#include <l2hal_hc06.h>

L2HAL_HC06_ContextStruct L2HAL_HC06_AttachToDevice(UART_HandleTypeDef* uart)
{
	L2HAL_HC06_ContextStruct context;
	context.IsFound = false;
	context.UART_Handle = uart;

	char buffer[3]; /* 3, not 2, because sprintf will add null-termination */
	sprintf(buffer, "AT");

	if (HAL_UART_Transmit(context.UART_Handle, (uint8_t*)buffer, 2, L2HAL_HC06_UART_TIMEOUT) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	/* Immediately expecting an answer */
	HAL_StatusTypeDef receiveStatus = HAL_UART_Receive(context.UART_Handle, (uint8_t*)buffer, 2, L2HAL_HC06_UART_TIMEOUT);

	if (HAL_TIMEOUT == receiveStatus)
	{
		return context; /* Not found */
	}
	else if (HAL_OK == receiveStatus)
	{
		/* 3rd byte in buffer is 0x00, so we can use strcmp*/
		if (0 == strcmp("OK", buffer))
		{
			context.IsFound = true;
		}

		return context;
	}
	else
	{
		L2HAL_Error(Generic);
	}

	return context;
}

void L2HAL_HC06_SetName(L2HAL_HC06_ContextStruct* context, const char* name)
{
	if (strlen(name) > L2HAL_HC06_MAX_NAME_LENGTH)
	{
		L2HAL_Error(Generic);
	}

	char processedName[L2HAL_HC06_MAX_NAME_LENGTH + 1]; /* +1 for null termination */
	strcpy(processedName, name);

	for (uint8_t i = 0; i < L2HAL_HC06_MAX_NAME_LENGTH; i++)
	{
		if (0x00 == processedName[i])
		{
			break;
		}
		else if (0x20 == processedName[i]) /* Space */
		{
			processedName[i] = 0x5f;
		}
	}

	char buffer[32];
	sprintf(buffer, "AT+NAME%s", processedName);

	uint8_t sendLength = strlen(buffer);
	if (HAL_UART_Transmit(context->UART_Handle, (uint8_t*)buffer, sendLength , L2HAL_HC06_UART_TIMEOUT) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	/* Immediately expecting an answer */
	if (HAL_UART_Receive(context->UART_Handle, (uint8_t*)buffer, 9, L2HAL_HC06_UART_TIMEOUT) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	buffer[9] = 0x00; /* Null-terminating by paws */

	if (strcmp("OKsetname", buffer) != 0)
	{
		L2HAL_Error(Generic);
	}
}

void L2HAL_HC06_SetPIN(L2HAL_HC06_ContextStruct* context, const char pin[L2HAL_HC06_PIN_CODE_LENGTH])
{
	char buffer[16];
	sprintf(buffer, "AT+PIN%s", pin);

	uint8_t sendLength = strlen(buffer);
	if (HAL_UART_Transmit(context->UART_Handle, (uint8_t*)buffer, sendLength, L2HAL_HC06_UART_TIMEOUT) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	/* Immediately expecting an answer */
	if (HAL_UART_Receive(context->UART_Handle, (uint8_t*)buffer, 8, L2HAL_HC06_UART_TIMEOUT) != HAL_OK)
	{
		L2HAL_Error(Generic);
	}

	buffer[8] = 0x00; /* Null-terminating by paws */

	if (strcmp("OKsetPIN", buffer) != 0)
	{
		L2HAL_Error(Generic);
	}
}
