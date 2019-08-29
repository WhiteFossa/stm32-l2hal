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

#include <l2hal_systick_private.h>

void L2HAL_SysTick_Init(void)
{
	L2HAL_SysTick_Context.Handlers = malloc(0);
}

void L2HAL_SysTick_RegisterHandler(void (*handler)(void))
{
	/* Allocating memory for new hanlder */
	L2HAL_SysTick_Context.Handlers = realloc(L2HAL_SysTick_Context.Handlers, (L2HAL_SysTick_Context.HandlersCount + 1) * sizeof(void*));
	if (NULL == L2HAL_SysTick_Context.Handlers)
	{
		/* Realloc failed */
		L2HAL_Error(Generic);
	}

	L2HAL_SysTick_Context.Handlers[L2HAL_SysTick_Context.HandlersCount] = handler;
	L2HAL_SysTick_Context.HandlersCount ++;
}

void L2HAL_SysTick_Callback(void)
{
	for (uint16_t handlerIndex = 0; handlerIndex < L2HAL_SysTick_Context.HandlersCount; handlerIndex ++)
	{
		L2HAL_SysTick_Context.Handlers[handlerIndex]();
	}
}

