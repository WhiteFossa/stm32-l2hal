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

/**
 * @file
 * @brief Polling buttons level 2 HAL driver.
 *
 * Driver for unlimited amount of buttons (polling, don't use interrupts).
 *
 * How to use it:
 *
 * 1) Declare driver context (l2hal_custom.h is good place for it):
 * L2HAL_Buttons_ContextStruct L2HAL_Buttons_Context;
 *
 * 2) Set up context:
 *
 * 	L2HAL_Buttons_Context.SkipPinsInitialization = false;
 *	L2HAL_Buttons_Context.CustomPinInitializer = NULL;
 *
 *	Read comments to L2HAL_Buttons_ContextStruct to know more about pins initialization.
 *
 *	3) Initialize driver:
 *
 *	L2HAL_Buttons_Init(&L2HAL_Buttons_Context);
 *
 *	4) Declare button(s) event handler(s):
 *
 *	void Button1Callback(L2HAL_Buttons_ButtonStruct* button, GPIO_PinState newPinState, uint16_t* portData);
 *
 *	5) Add new button(s) to driver:
 *
 *	L2HAL_Buttons_AddButton(&L2HAL_Buttons_Context, GPIOA, GPIO_PIN_0, &Button1Callback);
 *
 *	6) Start to poll ports (in main loop or in interrupt):
 *
 *	while(true)
 *	{
 *		L2HAL_Buttons_Poll(&L2HAL_Buttons_Context);
 *	}
 */

#ifndef L2HAL_DRIVERS_INPUT_BUTTONS_INCLUDE_L2HAL_BUTTONS_H_
#define L2HAL_DRIVERS_INPUT_BUTTONS_INCLUDE_L2HAL_BUTTONS_H_

#include <stm32f1xx_hal.h>
#include <l2hal_aux.h>
#include <l2hal_errors.h>

/**
 * Maximal ports count for given device. A-D for STM32F103
 */
#define L2HAL_BUTTONS_MAX_PORTS_COUNT 4

/**
 * Indexes to ports, i.e. 0 -> GPIOA, 1 -> GPIOB etc.
 */
static const GPIO_TypeDef* L2HAL_Buttons_IndexesToPorts[L2HAL_BUTTONS_MAX_PORTS_COUNT] = { GPIOA, GPIOB, GPIOC, GPIOD/*, GPIOE, GPIOF, GPIOG*/ };

/**
 * Button-defining struct.
 */
typedef struct
{
	/**
	 * Button connected to port with this index.
	 */
	uint8_t portIndex;

	/**
	 * Button connected to this pin.
	 */
	uint16_t pin;

	/**
	 * Button events callback function (aka handler). Being called when button is pressed or released.
	 * Parameters are fed with pointer to changed button struct (i.e. L2HAL_Buttons_ButtonStruct), new button state and pointer
	 * to ports data at the moment of button state change.
	 * Button struct and ports data are READONLY (changing it will change data for all consequent handlers). Ports data could change at any time
	 * after last handler exit. So if you plan to use it outside of handler, you need to copy data by hands.
	 *
	 * If callback pointer is NULL, nothing will be called during processing buttons events. It is useful if you need just to initialize a button,
	 * and want to check it state in other handler via L2HAL_Buttons_GetButtonState().
	 */
	void (*ButtonEventsCallback)(void*, GPIO_PinState, uint16_t*);

	/**
	 * Button previous state.
	 */
	GPIO_PinState previousState;

} L2HAL_Buttons_ButtonStruct;

/**
 * Driver context.
 */
typedef struct
{
	/**
	 * If set to true before L2HAL_Buttons_Init(), then pins initialization code wouldn't be called. In this case it's your
	 * responsibility to correctly initialize pins.
	 */
	bool SkipPinsInitialization;

	/**
	 * Custom pin initialization function. Set it before calling L2HAL_Buttons_Init(). If set to null, then
	 * on L2HAL_Buttons_Init() call pointer to default initializer will be set here.
	 */
	void (*CustomPinInitializer)(GPIO_TypeDef*, uint32_t);

	/**
	 * Array with buttons.
	 */
	L2HAL_Buttons_ButtonStruct* Buttons;

	/**
	 * Buttons count.
	 */
	uint8_t ButtonsCount;

	/**
	 * If false then some handler is running and we couldn't update ports data.
	 */
	bool IsPortDataCanBeUpdated;

	/**
	 * Ports data. Guarnteed to be valid during handlers calls.
	 */
	uint16_t PortsData[L2HAL_BUTTONS_MAX_PORTS_COUNT];

} L2HAL_Buttons_ContextStruct;


/**
 * Call this function to initialize driver. Feed it with pointer to driver context.
 * @param context Pointer to driver context.
 */
void L2HAL_Buttons_Init(L2HAL_Buttons_ContextStruct* context);

/**
 * Call this function to add new button.
 * @param context Pointer to driver context.
 * @param port Pointer to port, to what button is attached.
 * @param pin Pin, to what button is attached.
 * @param ButtonEventsCallback Pointer to function, which will be called in case of button state change (aka handler). READ THE L2HAL_Buttons_ButtonStruct CAREFULLY
 * to understand nature of the function parameters.
 * @
 */
L2HAL_Buttons_ButtonStruct* L2HAL_Buttons_AddButton(L2HAL_Buttons_ContextStruct* context,
		GPIO_TypeDef* port,
		uint16_t pin,
		void (*buttonEventsCallback)(void*, GPIO_PinState, uint16_t*));

/**
 * Gets button state using data from ports. Usually you need to call this function from button events callback to determine
 * together pressed buttons.
 * @param button Pointer to button, for what we want to determine state.
 * @param portsData Pointer to ports data. Could be data from callback parameters or from context (if you need just to examine button state).
 * @return Button state.
 */
GPIO_PinState L2HAL_Buttons_GetButtonState(L2HAL_Buttons_ButtonStruct* button, uint16_t* portsData);

/**
 * Call this to poll ports and generate buttons events. Note, that if you call it from interrupt and buttons events handlers are still running,
 * then function will block and wait until last handler completion.
 * @param context Pointer to driver context.
 */
void L2HAL_Buttons_Poll(L2HAL_Buttons_ContextStruct* context);

#endif /* L2HAL_DRIVERS_INPUT_BUTTONS_INCLUDE_L2HAL_BUTTONS_H_ */
