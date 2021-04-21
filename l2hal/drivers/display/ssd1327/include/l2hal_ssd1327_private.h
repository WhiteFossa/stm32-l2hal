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

#ifndef L2HAL_DRIVERS_DISPLAY_SSD1327_INCLUDE_L2HAL_SSD1327_PRIVATE_H_
#define L2HAL_DRIVERS_DISPLAY_SSD1327_INCLUDE_L2HAL_SSD1327_PRIVATE_H_

#include <l2hal_ssd1327.h>

/**
 * Display I/O timeout in milliseconds.
 */
#define L2HAL_SSD1327_IO_TIMEOUT 100U

/**
 * Display can have one of this two addresses. Addresses already shifted.
 */
#define L2HAL_SSD1327_POSSIBLE_ADDRESS1 0x78U
#define L2HAL_SSD1327_POSSIBLE_ADDRESS2 0x7AU

/**
 * Possible values of control byte (sent after device address).
 */
#define L2HAL_SSD1327_CONTROL_BYTE_COMMAND 0b00000000 /* Next byte is command */
#define L2HAL_SSD1327_CONTROL_BYTE_DATA 0b01000000 /* Next byte is data */

/**
 * Factors for brightness calculation, max brightness = 0x0F.
 * Br = 0.2126 * R + 0.7152 * G + 0.0722 * B
 */
#define L2HAL_SSD1327_BRIGHTNESS_DIV_FACTOR 4095U
#define L2HAL_SSD1327_BRIGHTNESS_MUL_R_FACTOR 54U
#define L2HAL_SSD1327_BRIGHTNESS_MUL_G_FACTOR 182U
#define L2HAL_SSD1327_BRIGHTNESS_MUL_B_FACTOR 18U

/**
 * Maximal pixel brightness
 */
#define L2HAL_SSD1327_MAX_BRIGHTNESS 0x0FU

/**
 * Multiply grayscale code [0-15] to this value, to get RGB [0-255] codes
 */
#define L2HAL_SSD1327_GET_PIXEL_MULTIPLIER 17U

/**
 * Causes L2HAL error if display not found.
 * @param context Pointer to driver context.
 */
void L2HAL_SSD1327_CheckIfFound(L2HAL_SSD1327_ContextStruct* context);

/**
 * Call this function to check if data transfer undergoing. If so, function will hang until it completed.
 * @param context Pointer to driver context.
 */
void L2HAL_SSD1327_WaitForTransferCompletion(L2HAL_SSD1327_ContextStruct* context);

/**
 * Send command to display.
 * @param context Pointer to driver context.
 * @param command Command to send.
 */
void L2HAL_SSD1327_WriteCommand(L2HAL_SSD1327_ContextStruct* context, uint8_t command);

/**
 * Send data to videomemory.
 * @param context Pointer to driver context.
 * @param data Pointer to data, data must not change during transfer (until L2HAL_SSD1327_WaitForTransferCompletion() is called).
 */
void L2HAL_SSD1327_WriteData(L2HAL_SSD1327_ContextStruct* context, uint8_t* data, uint16_t length);

/**
 * Get framebuffer's index and nibble for given pixel coordinates.
 * @param x X coordinate of pixel
 * @param y Y coordinate of pixel
 * @param index Pointer to variable where framebuffer index will be stored
 * @param isMostSignificantNibble Pointer to variable where marker of most significant nibble will be stored
 * @return True if coordinates are correct, false otherwise
 */
bool L2HAL_SSD1327_GetPixelAddress(uint16_t x, uint16_t y, uint16_t* index, bool* isMostSignificantNibble);

#endif /* L2HAL_DRIVERS_DISPLAY_SSD1327_INCLUDE_L2HAL_SSD1327_PRIVATE_H_ */
