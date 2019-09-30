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

#include "indicator.h"
#include "clockControl.h"

// Access to USBDM name-space
using namespace USBDM;


//is there any conflict with the instruction
using North_Switch = GpioC<0,ActiveLow>;

using South_Switch = GpioD<6,ActiveLow>;
using Centre_Switch = GpioD<5,ActiveLow>;
//using West_Switch = GpioB<1,ActiveLow>;
//using East_Switch = GpioC<1,ActiveLow>;

static constexpr bool ON = true;
static constexpr bool OFF = false;

static int currentStatus = OFF;

static int frequency_index = 0;

static constexpr int MAX_INDEX = 19;

const int frequency[20] = 	{
								1, 2, 5,
								10, 20, 50,
								100, 200, 500,
								1000, 2000, 5000,
								10000, 20000, 50000,
								100000, 200000, 500000,
								1000000, 2000000
							};

/* **************************************************
 *  Globally shared objects representing hardware
 * ************************************************ */

//// SPI interface
//Spi0 spi;
//
//// LCD interface using SPI
//Lcd lcd(spi);
//
///* ************************************************** */
//
//// LCD derived dimensions
////static constexpr unsigned LCD_WIDTH  = (LCD_X_MAX-LCD_X_MIN);
////static constexpr unsigned LCD_HEIGHT = (LCD_Y_MAX-LCD_Y_MIN);
////static constexpr unsigned CENTRE_X   = ((LCD_X_MAX-LCD_X_MIN)/2);
////static constexpr unsigned CENTRE_Y   = ((LCD_Y_MAX-LCD_Y_MIN)/2);
//
//// Colour for LCD background
//static constexpr Colour BACKGROUND_COLOUR = (RED);
//
//// Colour for LCD foreground
//static constexpr Colour FOREGROUND_COLOUR = (WHITE);
//
//// Radius used for the moving circle
//static constexpr unsigned CIRCLE_RADIUS = (20);
//
///*
// * Draws a cursor on the lcd screen
// *
// * @param x       x position
// * @param y       y position
// * @param colour  Colour of cursor
// *
// * @note Done this way so a more sophisticated cursor can be added
// */
//void drawCursor(unsigned x, unsigned y, Colour colour) {
//   lcd.drawCircle(x, y, CIRCLE_RADIUS, colour);
////   lcd.drawRect(x-CIRCLE_RADIUS/2, y-1, x+CIRCLE_RADIUS/2, y+1, false, colour);
////   lcd.drawRect(x-1, y-CIRCLE_RADIUS/2, x+1, y+CIRCLE_RADIUS/2, false, colour);
//}

void incrementIndex()
{
	++frequency_index;
	if (frequency_index > MAX_INDEX)
	{
		frequency_index = 0;
	}
}

void decrementIndex()
{
	--frequency_index;
	if (frequency_index < 0)
	{
		frequency_index = MAX_INDEX;
	}
}

void toggleStatus()
{
	currentStatus = ~currentStatus;
}

int main()
{
	int lastFrequency = 0;
	Indicator lcdIndicator = Indicator();
	initialiseClockControl();
	for (;;)
	{
		Smc::enterWaitMode();

		if (getNorthPress())
		{
			incrementIndex();
		}

		if (getSouthPress())
		{
			decrementIndex();
		}

		if (getCentrePress())
		{
			toggleStatus();
		}

		int currentFrequency = 	frequency[frequency_index];

		if (currentFrequency != lastFrequency)
		{
			lcdIndicator.display(currentFrequency);
		}
		lastFrequency = currentFrequency;
	}
	return 0;
}


//int main() {
//
//	//
////	//Set input for switches:
////	North_Switch::setInput(
////			  PinPull_Up,
////			  PinAction_None,
////			  PinFilter_Passive);
////	 East_Switch::setInput(
////		      PinPull_Up,
////		      PinAction_None,
////		      PinFilter_Passive);
////	 West_Switch::setInput(
////		      PinPull_Up,
////		      PinAction_None,
////		      PinFilter_Passive);
////	 South_Switch::setInput(
////		      PinPull_Up,
////		      PinAction_None,
////		      PinFilter_Passive);
////	 Centre_Switch::setInput(
////		      PinPull_Up,
////		      PinAction_None,
////		      PinFilter_Passive);
////
////   // Draw pretty pattern
////   lcd.clear(BACKGROUND_COLOUR);
////   //lcd.drawCircle(CENTRE_X, CENTRE_Y, 20, WHITE);
////   //lcd.drawCircle(CENTRE_X, CENTRE_Y, 30, WHITE);
////   //lcd.drawCircle(CENTRE_X, CENTRE_Y, 40, WHITE);
////
////   // Set LCD defaults
////   lcd.setFont(fontSmall).setForeground(FOREGROUND_COLOUR).setBackground(BACKGROUND_COLOUR);
////
////   // Simple text with position and default font and colours
////   lcd.putStr("Some Circles", 30, 10);
////
////   // Change LCD defaults
////   lcd.setFont(fontLarge).setForeground(BLUE).setBackground(WHITE);
////
////   // Formatted write to LCD using current defaults
////   lcd.moveXY(10, LCD_Y_MAX-fontLarge.height-1)
////      .write("max-X=").write(LCD_X_MAX).write(" ");
////
////   // Cursor position on screen
////   unsigned x=0, y=0;
////   unsigned xOld=50, yOld=50;
//
//   //SevenSegment s1 = SevenSegment(50, 50);
//   //SevenSegment s2 = SevenSegment(90, 50);
//   //SevenSegment s3 = SevenSegment(130, 50);
////   int i = 0;
////   for(;;) {
////      x = LCD_X_MIN + CIRCLE_RADIUS + rand() % (LCD_WIDTH-2*CIRCLE_RADIUS);
////      y = LCD_Y_MIN + CIRCLE_RADIUS + rand() % (LCD_HEIGHT-2*CIRCLE_RADIUS);
////      waitMS(50);
////      drawCursor(xOld, yOld, BACKGROUND_COLOUR);
////      drawCursor(x, y, FOREGROUND_COLOUR);
////      xOld = x;
////      yOld = y;
//
//// After experiment, The North_Switch is the one that is the nearest to the screen. Then you can figure out other direction.
//
////	   if (North_Switch::isPressed())
////	   {
////		   console.writeln("north switch");
////	   }
////
////	   //s1.drawNum(lcd, i, FOREGROUND_COLOUR, BACKGROUND_COLOUR);
////	   ++i;
////	   if (i == 10) i=0;
////	   waitMS(500);
//   }
//   return 0;
//}
