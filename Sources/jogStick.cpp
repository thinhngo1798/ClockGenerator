/*
  * clockControl.cpp
 *
 *  Created on: Sep 29, 2019
 *      Author: PLH
 */

#include <jogStick.h>

void deBouncer()
{
   static int switchCounter = 0;
   static int lastSwitch    = false;

   // Encode all switch values as a single binary number
   int currentSwitch =
	  (EastSwitch::read()<<eastSwitch)|
	  (SouthSwitch::read()<<southSwitch)|
	  (WestSwitch::read()<<westSwitch)|
	  (CentreSwitch::read()<<centreSwitch)|
	  (NorthSwitch::read()<<northSwitch);

   console.writeln(currentSwitch);

   if (currentSwitch == lastSwitch)
   {
	   ++switchCounter;
   }
   else
   {
	   switchCounter = 0;
   }

   if (switchCounter == DEBOUNCE_SAMPLES)
   {
	   switch(currentSwitch)
	   {
	   	   case (1<<eastSwitch):
			   switchValue = eastSwitch;
	   	   	   break;
	   	   case (1<<northSwitch):
			   switchValue = northSwitch;
			   break;
	   	   case (1<<southSwitch):
	   			switchValue = southSwitch;
	   	   	   	break;
	   	   case (1<<westSwitch):
				switchValue = westSwitch;
				break;
	   	   case (1<<centreSwitch):
			   switchValue = centreSwitch;
			   break;
	   	   default:
			   switchValue = noSwitch;
			   break;
	   }
   }
   lastSwitch = currentSwitch;
}


void initialiseClockControl()
{
	   EastSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_Passive);
	   SouthSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_Passive);
	   WestSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_Passive);
	   CentreSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_Passive);
	   NorthSwitch::setInput(PinPull_Up, PinAction_None, PinFilter_Passive);

	   // PIT configure
	   Timer::configure(PitDebugMode_Stop);

	   // Set handler for PIT channel programmatically
	   TimerChannel::setCallback(deBouncer);

	   // Setup de-bouncer to execute @DEBOUNCE_SAMPLE_TIME interval
	   TimerChannel::configure(DEBOUNCE_SAMPLE_TIME, PitChannelIrq_Enabled);

	   // Enable interrupts via NVIC for the PIT channel
	   TimerChannel::enableNvicInterrupts(NvicPriority_Normal);
	   checkError();
}

SwitchValue getJogswitchValue()
{
	TimerChannel::disableNvicInterrupts();
	SwitchValue saveSwitch = switchValue;
	switchValue = noSwitch;
	TimerChannel::enableNvicInterrupts();
	return saveSwitch;
}
