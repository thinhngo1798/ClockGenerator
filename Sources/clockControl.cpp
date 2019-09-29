/*
 * clockControl.cpp
 *
 *  Created on: Sep 29, 2019
 *      Author: PLH
 */
#include "clockControl.h"

void deBouncer()
{
	static int northCounter = 0;
	static int southCounter = 0;
	static int centreCounter = 0;

	static bool lastNorthValue = false;
	static bool lastSouthValue = false;
	static bool lastCentreValue = false;

	bool tempNorth = North_Switch::isPressed();
	bool tempSouth = South_Switch::isPressed();
	bool tempCentre = Centre_Switch::isPressed();

	if (tempNorth == lastNorthValue)
	{
		++northCounter;
	}
	else
	{
		northCounter = 0;
	}

	if (northCounter == DEBOUNCE_SAMPLES)
	{
		northValue = lastNorthValue;
	}

	lastNorthValue = tempNorth;

	if (tempSouth == lastSouthValue)
	{
		++southCounter;
	}
	else
	{
		southCounter = 0;
	}

	if (southCounter == DEBOUNCE_SAMPLES)
	{
		southValue = lastSouthValue;
	}

	lastSouthValue = tempSouth;

	if (tempCentre == lastCentreValue)
	{
		++centreCounter;
	}
	else
	{
		centreCounter = 0;
	}

	if (centreCounter == DEBOUNCE_SAMPLES)
	{
		centreValue = lastCentreValue;
	}

	lastCentreValue = tempCentre;
}


void initialiseClockControl()
{
	North_Switch::setInput(
			  PinPull_Up,
			  PinAction_None,
			  PinFilter_Passive);
	 South_Switch::setInput(
		      PinPull_Up,
		      PinAction_None,
		      PinFilter_Passive);
	 Centre_Switch::setInput(
		      PinPull_Up,
		      PinAction_None,
		      PinFilter_Passive);

	 Timer::configure(PitDebugMode_Stop);
	 Timer::setCallback(deBouncer);
	 TimerChannel::configure(DEBOUNCE_SAMPLE_TIME,  PitChannelIrq_Enabled);
	 TimerChannel::enableNvicInterrupts(NvicPriority_Normal);
	 checkError();
}


bool getNorthPress()
{
   TimerChannel::enableInterrupts(false);
   bool tempNorth = northValue;
   northValue = false;
   TimerChannel::enableInterrupts(true);
   return tempNorth;
}

bool getSouthPress()
{
   TimerChannel::enableInterrupts(false);
   bool tempSouth = southValue;
   southValue = false;
   TimerChannel::enableInterrupts(true);
   return tempSouth;
}

bool getCentrePress()
{
   TimerChannel::enableInterrupts(false);
   bool tempCentre = centreValue;
   centreValue = false;
   TimerChannel::enableInterrupts(true);
   return tempCentre;
}
