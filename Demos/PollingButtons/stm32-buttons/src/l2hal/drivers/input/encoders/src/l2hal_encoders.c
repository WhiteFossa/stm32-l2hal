/*
	This file is part of Fossa's STM32 level 2 HAL.

	STM32 level 2 HAL is free software:
	you can redistribute it and/or modify it under the terms of the
	GNU General Public License as published by the Free Software
	Foundation, either version 3 of the License, or (at your option)
	any later version.

	STM32 level 2 HAL is distributed in the hope
	that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A
	PARTICULAR PURPOSE.  See the GNU General Public License for more
	details.

	You should have received a copy of the GNU General Public License
	along with STM32 level 2 HAL.

	If not, see <http://www.gnu.org/licenses/>.

	-------------------------------------------------------------------------

	Created by White Fossa, also known as Artyom Vetrov.

	Feel free to contact: whitefossa@gmail.com

	Repository: https://github.com/WhiteFossa/stm32-l2hal

	If repository above is not available, try my LiveJournal:
	fossa-white.livejournal.com

	or as last measure try to search for #WhiteFossa hashtag.

	-------------------------------------------------------------------------
 */

#include <l2hal_encoders_private.h>

void L2HAL_Encoders_ButtonsCallback(L2HAL_Buttons_ButtonStruct* button, GPIO_PinState newPinState, uint16_t* portsData)
{
	/* Event happened in this encoder in leading channel */
	L2HAL_Encoders_EncoderStruct* encoderPtr = button->ArbitraryContextPointer;

	if (encoderPtr->ActiveState != newPinState)
	{
		return;
	}

	/* Leading channel is just activated, what's trailing state? */
	L2HAL_Encoders_Direction direction;
	GPIO_PinState trailingState = L2HAL_Buttons_GetButtonState(encoderPtr->TrailingChannel, portsData);
	if (encoderPtr->ActiveState != trailingState)
	{
		direction = Clockwise;
	}
	else
	{
		direction = CounterClockwise;
	}

	encoderPtr->EncoderEventsCallback(encoderPtr, direction);
}

void L2HAL_Encoders_Init(L2HAL_Encoders_ContextStruct* context)
{
	context->EncodersCount = 0;
	context->Encoders = malloc(0);
}

L2HAL_Encoders_EncoderStruct* L2HAL_Encoders_AddEncoder(L2HAL_Encoders_ContextStruct* context,
		GPIO_TypeDef* leadingPort,
		uint16_t leadingPin,
		GPIO_TypeDef* trailingPort,
		uint16_t trailingPin,
		GPIO_PinState activeState,
		void (*encoderEventsCallback)(void*, L2HAL_Encoders_Direction),
		void* arbitraryContextPointer)
{
	/* Allocating memory for new encoder */
	context->EncodersCount ++;
	context->Encoders = realloc(context->Encoders, context->EncodersCount * sizeof(L2HAL_Encoders_EncoderStruct));
	if (NULL == context->Encoders)
	{
		/* Realloc failed */
		L2HAL_Error(Generic);
	}

	/* Filling new encoder struct*/
	L2HAL_Encoders_EncoderStruct* newEncoder = &context->Encoders[context->EncodersCount - 1];

	/* Setting-up leading channel */
	newEncoder->LeadingChannel = L2HAL_Buttons_AddButton(context->ButtonsDriverContext,
			leadingPort,
			leadingPin,
			&L2HAL_Encoders_ButtonsCallback,
			newEncoder);

	/* And trailing */
	newEncoder->TrailingChannel = L2HAL_Buttons_AddButton(context->ButtonsDriverContext,
			trailingPort,
			trailingPin,
			NULL, /* We don't need handler for trailing channel */
			newEncoder);

	newEncoder->ActiveState = activeState;
	newEncoder->ArbitraryContextPointer = arbitraryContextPointer;
	newEncoder->EncoderEventsCallback = encoderEventsCallback;

	return newEncoder;
}


