/**

 * @file    generator.cpp (180.ARM_Peripherals/Snippets)
>>>>>>> master
 * @brief   Demo using Ftm class to implement a basic Output Compare system
 *
 *  An FTM output generates a square wave with 100ms period
 *
 *  Created on: 3/7/2017
 *      Author: podonoghue
 ============================================================================
 */


#include <ClockGenerator.h>
#include "hardware.h"
#include "smc.h"


using namespace USBDM;

/**
 * This example uses FTM interrupts.
 *
 * It is necessary to enable these in Configure.usbdmProject
 * under the "Peripheral Parameters"->FTM tab.
 * Select irqHandlingMethod option (Class Method - Software ...)
 */

/**
 * Timer being used - change as required
 * Could also access as TimerChannel::Ftm
 */
using Timer = Ftm1;

using generateGround = GpioA<2>;
/// Timer channel for output - change as required

using TimerChannel = Timer::Channel<1>;


int input1Hz=0;
int input2Hz=0;
int eventCounter=0;

/**
 * Half-period for timer in ticks.
 * This variable is shared with the interrupt routine
 */
static volatile uint16_t timerHalfPeriodInTicks;

/// Waveform period to generate
static constexpr float WAVEFORM_PERIOD = 1*ms;

/// Maximum OC interval - the OC interval should not exceed this value.
//static constexpr float MAX_OC_INTERVAL = (1.1 * WAVEFORM_PERIOD)/2;

/**
 * Interrupt handler for Timer interrupts
 * This sets the next interrupt/pin toggle for a half-period from the last event
 *
 * @param[in] status Flags indicating interrupt source channel(s)
 */
static void ftmCallback(uint8_t status) {

   // Check channel
   if (status & TimerChannel::CHANNEL_MASK) {
	  if (((input1Hz==1) || (input2Hz==1)) && (TimerChannel::getMode()==FtmChMode_OutputCompareToggle))
		  TimerChannel::setMode(FtmChMode_OutputCompareSet);
	  if ((input1Hz==0) && (input2Hz==0))
		  TimerChannel::setMode(FtmChMode_OutputCompareToggle);
	  switch (TimerChannel::getMode()) {
	  case FtmChMode_OutputCompareToggle:
		  TimerChannel::setDeltaEventTime(timerHalfPeriodInTicks);
		  break;
	  case FtmChMode_OutputCompareSet: {
		  eventCounter++;
		  if (eventCounter==10)
		  {
			  eventCounter=0;
			  TimerChannel::setMode(FtmChMode_OutputCompareClear);
		  }
		  TimerChannel::setDeltaEventTime(timerHalfPeriodInTicks);
		  break;
	  }
	  case FtmChMode_OutputCompareClear: {
		  eventCounter++;
		   if (eventCounter==10)
		   {
		   eventCounter=0;
		  TimerChannel::setMode(FtmChMode_OutputCompareSet);
		   }
		   TimerChannel::setDeltaEventTime(timerHalfPeriodInTicks);
		   break;
	  }
	  default:
	  __asm__("bkpt");
	  }
   }
}



void generatorInitialise(){

	//Generate a ground to use for Logic Analyser.
	generateGround::setOutput(PinDriveStrength_Low, PinDriveMode_PushPull, PinSlewRate_Slow);
	generateGround::write(0);
	/**
	    * FTM channel set as Output compare with pin Toggle mode and using a callback function
	*/
	// Configure base FTM (affects all channels)
	   Timer::configure(
	         FtmMode_LeftAlign,       // Left-aligned is required for OC/IC
	         FtmClockSource_System);  // Bus clock usually

	   // Set IC/OC measurement interval to longest interval needed.
	   // This adjusts the prescaler value but does not change the clock source

	   Timer::setMaximumInterval(1.1*0.5/MIN_FREQUENCY);


	   // Calculate half-period in timer ticks
	   // Must be done after timer clock configuration (above)
	   generatorSetFrequency(MIN_FREQUENCY);
	   // Enable interrupts for entire timer
	   Timer::enableNvicInterrupts(NvicPriority_Normal);

	   // Configure pin associated with channel
	   TimerChannel::setOutput(
	         PinDriveStrength_High,
	         PinDriveMode_PushPull,
	         PinSlewRate_Slow);

	   // Trigger 1st interrupt at now+100
	   TimerChannel::setRelativeEventTime(100);

	   // Set callback function (may be shared by multiple channels)
	   TimerChannel::setChannelCallback(ftmCallback);

	   // Configure the channel
	   TimerChannel::configure(
	         FtmChMode_OutputCompareToggle, //  Output Compare with pin toggle
	         FtmChannelAction_Irq);         //  + interrupts on events

	   // Check if configuration failed
	   USBDM::checkError();

}

/**
 * Set generator Frequency
 *
 * @param frequency [MIN_FREQUENCY ... MAX_FREQUENCY]
 */
void generatorSetFrequency(unsigned frequency){
	//Timer::setPeriod(frequency*us, true);
	int fakeFrequency;
	if (frequency == 1) {
	input1Hz=1;
	fakeFrequency=10;
	}
	else if (frequency == 2)
	{
	input2Hz=1;
	fakeFrequency=20;
	}
	else
	{
		input1Hz=0;
		input2Hz=0;
	fakeFrequency=frequency; // The frequency applies as normal.There is no fake frequency.
	}
	timerHalfPeriodInTicks=Timer::convertSecondsToTicks(0.5/fakeFrequency);
}


