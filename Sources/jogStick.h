/*
 * clockControl.h
 *
 *  Created on: Sep 29, 2019
 *      Author: PLH
 */

#ifndef SOURCES_JOGSTICK_H_
#define SOURCES_JOGSTICK_H_

#include "hardware.h"
#include "pit.h"
#include "smc.h"

using namespace USBDM;

using EastSwitch   = USBDM::GpioC<0,ActiveLow>;
using SouthSwitch  = USBDM::GpioC<1,ActiveLow>;
using WestSwitch   = USBDM::GpioD<6,ActiveLow>;
using CentreSwitch = USBDM::GpioD<5,ActiveLow>;
using NorthSwitch  = USBDM::GpioB<1,ActiveLow>;

// Time between samples of the input
static constexpr float DEBOUNCE_SAMPLE_TIME = 5*ms;
// Number of debug samples for a stable input
static constexpr unsigned DEBOUNCE_SAMPLES = 5;

enum SwitchValue {
       //!< No Switch or multiple switches pressed
   eastSwitch,  //!< East Switch
   southSwitch, //!< South Switch
   westSwitch,  //!< West Switch
   centreSwitch,//!< Centre Switch
   northSwitch, //!< North Switch
   noSwitch
};

static volatile SwitchValue switchValue = noSwitch;

using Timer        = Pit;
using TimerChannel = Timer::Channel<0>;

void deBouncer();
void initialiseClockControl();
SwitchValue getJogswitchValue();


#endif /* SOURCES_JOGSTICK_H_ */
