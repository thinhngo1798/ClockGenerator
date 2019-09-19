/**
 ============================================================================
 * \section ElecfreaksLcd Elecfreaks Colour LCD shield demonstration
 * This is a example of the use of the C++ library routines for the Elecfreaks LCD shield displays.\n
 *
 * It may be necessary to change pin mappings to use this example.\n
 * Open <b>Configure.usbdmProject</b> to change these.\n\n
 *
 * Refer to the individual files for license conditions as they vary.
 *
 * @example elecfreaks-lcd-example.cpp
 *
 * <hr>
 * <b>Quick Links</b>
 *
 *   - @htmlonly <a href="http://www.elecfreaks.com/store/color-lcd-shield-shdcls-p-462.html"><b>Elecfreaks LCD shield (obsolete)</b></a> @endhtmlonly
 *
 ============================================================================
 */
#include <stdlib.h>
#include "lcd.h"
#include "spi.h"
#include "delay.h"




// Access to USBDM name-space
using namespace USBDM;

using North_Switch = GpioC<0>;
using East_Switch = GpioC<1>;
using South_Switch = GpioD<6>;
using Centre_Switch = GpioD<5>;
using West_Switch = GpioB<1>;

#define numSegment 7
#define horizontal_bar_width 20
#define horizontal_bar_height 5
#define vertical_bar_width 5
#define vertical_bar_height 20
#define space_height 5
#define space_width 5


class SevenSegment
{
	int startX[7];
	int startY[7];

	int barWidth[7];
	int barHeight[7];

	int x;
	int y;

	bool table[10][7] = {
							{1,1,1,0,1,1,1},
							{0,0,0,0,0,1,1},
							{0,1,1,1,1,1,0},
							{0,0,1,1,1,1,1},
							{1,0,0,1,0,1,1},
							{1,0,1,1,1,0,1},
							{1,1,1,1,1,0,1},
							{0,0,1,0,0,1,1},
							{1,1,1,1,1,1,1},
							{1,0,1,1,1,1,1}
						};

	public:
		SevenSegment(int aX, int aY)//, Lcd& aLcd);
	{
			x = aX;
			y = aY;

			startX[0] = startX[1] = x;
			startX[2] = startX[3] = startX[4] = x + space_width;
			startX[5] = startX[6] = x + space_width + horizontal_bar_width;

			startY[4] = y;
			startY[1] = startY[6] = y + space_height;
			startY[3] = y + vertical_bar_height;
			startY[0] = startY[5] = y + 2*space_height + vertical_bar_height;
			startY[2] = y + 2 * (space_height + vertical_bar_height);

			barWidth[0] = barWidth[1] = barWidth[5] = barWidth[6] = vertical_bar_width;
			barHeight[0] = barHeight[1] = barHeight[5] = barHeight[6] = vertical_bar_height;
			barWidth[2] = barWidth[3] = barWidth[4] = horizontal_bar_width;
			barHeight[2] = barHeight[3] = barHeight[4] = horizontal_bar_height;

	}
		void setXY(int new_x, int new_y)
		{
			x = new_x;
			y = new_y;
		}
		void drawNum(USBDM::Lcd & lcd, int num, Colour foregroundColor, Colour backgroundColor)
		{
			if (num > 9 || num < 0) return;



			for (int segmentIndex = 0; segmentIndex < numSegment; ++segmentIndex)
			{
				int TopLeftX, TopLeftY, BotRightX, BotRightY;
				TopLeftX = startX[segmentIndex];
				TopLeftY = startY[segmentIndex];

				BotRightX = TopLeftX + barWidth[segmentIndex];
				BotRightY = TopLeftY + barHeight[segmentIndex];

				lcd.drawRect(TopLeftX, TopLeftY, BotRightX, BotRightY, false, backgroundColor);

				if (table[num][segmentIndex])
				{
					lcd.drawRect(TopLeftX, TopLeftY, BotRightX, BotRightY, false, foregroundColor);
				}
			}
		}
};



/* **************************************************
 *  Globally shared objects representing hardware
 * ************************************************ */

// SPI interface
Spi0 spi;

// LCD interface using SPI
Lcd lcd(spi);

/* ************************************************** */

// LCD derived dimensions
static constexpr unsigned LCD_WIDTH  = (LCD_X_MAX-LCD_X_MIN);
static constexpr unsigned LCD_HEIGHT = (LCD_Y_MAX-LCD_Y_MIN);
static constexpr unsigned CENTRE_X   = ((LCD_X_MAX-LCD_X_MIN)/2);
static constexpr unsigned CENTRE_Y   = ((LCD_Y_MAX-LCD_Y_MIN)/2);

// Colour for LCD background
static constexpr Colour BACKGROUND_COLOUR = (RED);

// Colour for LCD foreground
static constexpr Colour FOREGROUND_COLOUR = (WHITE);

// Radius used for the moving circle
static constexpr unsigned CIRCLE_RADIUS = (20);

/*
 * Draws a cursor on the lcd screen
 *
 * @param x       x position
 * @param y       y position
 * @param colour  Colour of cursor
 *
 * @note Done this way so a more sophisticated cursor can be added
 */
void drawCursor(unsigned x, unsigned y, Colour colour) {
   lcd.drawCircle(x, y, CIRCLE_RADIUS, colour);
//   lcd.drawRect(x-CIRCLE_RADIUS/2, y-1, x+CIRCLE_RADIUS/2, y+1, false, colour);
//   lcd.drawRect(x-1, y-CIRCLE_RADIUS/2, x+1, y+CIRCLE_RADIUS/2, false, colour);
}

int main() {

   // Draw pretty pattern
   lcd.clear(BACKGROUND_COLOUR);
   //lcd.drawCircle(CENTRE_X, CENTRE_Y, 20, WHITE);
   //lcd.drawCircle(CENTRE_X, CENTRE_Y, 30, WHITE);
   //lcd.drawCircle(CENTRE_X, CENTRE_Y, 40, WHITE);

   // Set LCD defaults
   lcd.setFont(fontSmall).setForeground(FOREGROUND_COLOUR).setBackground(BACKGROUND_COLOUR);

   // Simple text with position and default font and colours
   lcd.putStr("Some Circles", 30, 10);

   // Change LCD defaults
   lcd.setFont(fontLarge).setForeground(BLUE).setBackground(WHITE);

   // Formatted write to LCD using current defaults
   lcd.moveXY(10, LCD_Y_MAX-fontLarge.height-1)
      .write("max-X=").write(LCD_X_MAX).write(" ");

   // Cursor position on screen
   unsigned x=0, y=0;
   unsigned xOld=50, yOld=50;

   SevenSegment s1 = SevenSegment(50, 50);

   int i = 0;
   for(;;) {
//      x = LCD_X_MIN + CIRCLE_RADIUS + rand() % (LCD_WIDTH-2*CIRCLE_RADIUS);
//      y = LCD_Y_MIN + CIRCLE_RADIUS + rand() % (LCD_HEIGHT-2*CIRCLE_RADIUS);
//      waitMS(50);
//      drawCursor(xOld, yOld, BACKGROUND_COLOUR);
//      drawCursor(x, y, FOREGROUND_COLOUR);
//      xOld = x;
//      yOld = y;

	   s1.drawNum(lcd, i, FOREGROUND_COLOUR, BACKGROUND_COLOUR);
	   ++i;
	   if (i == 10) i=0;
	   waitMS(1000);
   }
   return 0;
}
