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

//#include "indicator.h"
//#include "clockControl.h"
#include "ClockGenerator.h"

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

static constexpr int REAL_MIN_FREQUENCY =1;
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
//	int lastFrequency = 0;
//	Indicator lcdIndicator = Indicator();
//	initialiseClockControl();
//	for (;;)
//	{
//		Smc::enterWaitMode();
//
//		if (getNorthPress())
//		{
//			incrementIndex();
//		}
//
//		if (getSouthPress())
//		{
//			decrementIndex();
//		}
//
//		if (getCentrePress())
//		{
//			toggleStatus();
//		}
//
//		int currentFrequency = 	frequency[frequency_index];
//
//		if (currentFrequency != lastFrequency)
//		{
//			lcdIndicator.display(currentFrequency);
//		}
//		lastFrequency = currentFrequency;
//	}
	//Testing middle range f
	console.writeln("\nStarting\n");
	   generatorInitialise();

	   for(;;) {
	      unsigned frequency;
	      console.write("Frequency[")
	            .write(MIN_FREQUENCY)
	            .write("..")
	            .write(MAX_FREQUENCY).write("]")
	            .readln(frequency);
	      if ((frequency<REAL_MIN_FREQUENCY) || (frequency>MAX_FREQUENCY)) {
	         console.writeln("Frequency out of range");
	         continue;
	      }
	      generatorSetFrequency(frequency);
	   }
	return 0;
}


