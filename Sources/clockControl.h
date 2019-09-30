/*
 * clockControl.h
 *
 *  Created on: Sep 29, 2019
 *      Author: PLH
 */

#ifndef SOURCES_CLOCKCONTROL_H_
#define SOURCES_CLOCKCONTROL_H_
#include "hardware.h"
#include "pit.h"
#include "smc.h"

using namespace USBDM;

//using East_Switch = GpioC<1,ActiveLow>;
//using West_Switch = GpioB<1,ActiveLow>;

using North_Switch = GpioC<0,ActiveLow>;
using South_Switch = GpioD<6,ActiveLow>;
using Centre_Switch = GpioD<5,ActiveLow>;


// Time between samples of the input
static constexpr float DEBOUNCE_SAMPLE_TIME = 5*ms;

// Number of debug samples for a stable input
static constexpr unsigned DEBOUNCE_SAMPLES = 5;

//static volatile bool eastValue = false;
//static volatile bool westValue = false;

static volatile bool northValue = false;
static volatile bool southValue = false;
static volatile bool centreValue = false;

using Timer        = Pit;
using TimerChannel = Timer::Channel<0>;

void deBouncer();
void initialiseClockControl();

bool getNorthPress();
bool getSouthPress();
bool getCentrePress();

#endif /* SOURCES_CLOCKCONTROL_H_ */
