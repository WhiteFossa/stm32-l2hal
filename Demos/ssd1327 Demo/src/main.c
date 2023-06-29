/*
	This file is part of Fossa's MCU Graphics Library (FMGL).

	FMGL is free software:
	you can redistribute it and/or modify it under the terms of the
	GNU General Public License as published by the Free Software
	Foundation, either version 3 of the License, or (at your option)
	any later version.

	FMGL is distributed in the hope
	that it will be useful, but WITHOUT ANY WARRANTY; without even
	the implied warranty of MERCHANTABILITY or FITNESS FOR A
	PARTICULAR PURPOSE.  See the GNU General Public License for more
	details.

	You should have received a copy of the GNU General Public License
	along with FMGL.

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


// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#include "main.h"

int main(int argc, char* argv[])
{
	/* Setting up hardware */
	L2HAL_Init();

	HAL_Delay(100);

	/* Detecting display */
	L2HAL_SSD1327_Context = L2HAL_SSD1327_DetectDisplay(&I2CHandle);
	L2HAL_SSD1327_InitDisplay(&L2HAL_SSD1327_Context);

	/* Colors */
	FMGL_API_ColorStruct OffColor;
	OffColor.R = 0;
	OffColor.G = 0;
	OffColor.B = 0;

	FMGL_API_ColorStruct ColorGS1;
	ColorGS1.R = 32;
	ColorGS1.G = 32;
	ColorGS1.B = 32;

	FMGL_API_ColorStruct ColorGS2;
	ColorGS2.R = 64;
	ColorGS2.G = 64;
	ColorGS2.B = 64;

	FMGL_API_ColorStruct ColorGS3;
	ColorGS3.R = 96;
	ColorGS3.G = 96;
	ColorGS3.B = 96;

	FMGL_API_ColorStruct ColorGS4;
	ColorGS4.R = 128;
	ColorGS4.G = 128;
	ColorGS4.B = 128;

	FMGL_API_ColorStruct ColorGS5;
	ColorGS5.R = 160;
	ColorGS5.G = 160;
	ColorGS5.B = 160;

	FMGL_API_ColorStruct ColorGS6;
	ColorGS6.R = 192;
	ColorGS6.G = 192;
	ColorGS6.B = 192;

	FMGL_API_ColorStruct ColorGS7;
	ColorGS7.R = 224;
	ColorGS7.G = 224;
	ColorGS7.B = 224;

	FMGL_API_ColorStruct ColorGS8;
	ColorGS8.R = 255;
	ColorGS8.G = 255;
	ColorGS8.B = 255;

	/* Attaching FMGL to display */
	fmglContext = FMGL_API_AttachToDriver(&L2HAL_SSD1327_Context, &L2HAL_SSD1327_GetWidth, &L2HAL_SSD1327_GetHeight, &L2HAL_SSD1327_SetActiveColor,
			&L2HAL_SSD1327_DrawPixel, &L2HAL_SSD1327_GetPixel, &L2HAL_SSD1327_PushFramebuffer, OffColor);

	/* Initializing font */
	FMGL_API_Font font= FMGL_FontTerminusRegular12Init();

	FMGL_API_XBMTransparencyMode transparencyMode = FMGL_XBMTransparencyModeNormal;

	/* Font settings */
	fontSettings.Font = &font;
	fontSettings.Scale = 1;
	fontSettings.CharactersSpacing = 0;
	fontSettings.LinesSpacing = 0;
	fontSettings.BackgroundColor = &OffColor;
	fontSettings.Transparency = &transparencyMode;

	/* Clearing display */
	FMGL_API_ClearScreen(&fmglContext);
	FMGL_API_PushFramebuffer(&fmglContext);

	/* Test message */
	FMGL_API_ClearScreen(&fmglContext);
	char buffer[32];


	sprintf(buffer, "Yiff!");
	fontSettings.FontColor = &ColorGS1;
	FMGL_API_RenderTextWithLineBreaks(&fmglContext, &fontSettings, 0, 0, NULL, NULL, false, buffer); /* Actual drawing */

	sprintf(buffer, "Yerf!");
	fontSettings.FontColor = &ColorGS2;
	FMGL_API_RenderTextWithLineBreaks(&fmglContext, &fontSettings, 0, 16, NULL, NULL, false, buffer);

	sprintf(buffer, "Yipp!");
	fontSettings.FontColor = &ColorGS3;
	FMGL_API_RenderTextWithLineBreaks(&fmglContext, &fontSettings, 0, 32, NULL, NULL, false, buffer);

	sprintf(buffer, "Yuff!");
	fontSettings.FontColor = &ColorGS4;
	FMGL_API_RenderTextWithLineBreaks(&fmglContext, &fontSettings, 0, 48, NULL, NULL, false, buffer);

	sprintf(buffer, "OwO");
	fontSettings.FontColor = &ColorGS5;
	FMGL_API_RenderTextWithLineBreaks(&fmglContext, &fontSettings, 0, 64, NULL, NULL, false, buffer);

	sprintf(buffer, "What's this?");
	fontSettings.FontColor = &ColorGS6;
	FMGL_API_RenderTextWithLineBreaks(&fmglContext, &fontSettings, 0, 80, NULL, NULL, false, buffer);

	sprintf(buffer, "*notices the bulge*");
	fontSettings.FontColor = &ColorGS7;
	FMGL_API_RenderTextWithLineBreaks(&fmglContext, &fontSettings, 0, 96, NULL, NULL, false, buffer);

	sprintf(buffer, "Grrh }=");
	fontSettings.FontColor = &ColorGS8;
	FMGL_API_RenderTextWithLineBreaks(&fmglContext, &fontSettings, 0, 112, NULL, NULL, false, buffer);

	FMGL_API_PushFramebuffer(&fmglContext);

	while(true)
	{
	}

	return 0;
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
