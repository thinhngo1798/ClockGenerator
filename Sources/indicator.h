/*
 * display.h
 *
 *  Created on: Sep 28, 2019
 *      Author: PLH
 */

#ifndef SOURCES_INDICATOR_H_
#define SOURCES_INDICATOR_H_

#include "spi.h"
#include "lcd.h"
#include "sevenSegment.h"
#include "config.h"

using namespace std;

//static constexpr int MIN_FREQUENCY = 1000;
//static constexpr int MAX_FREQUENCY = 2000000;

class Indicator
{
	static constexpr unsigned numberSegments = 3;

	SevenSegment digit[numberSegments];
	//char unit[3];
	//char message[15];
	Spi0 spi;
	Lcd lcd;

	static constexpr int horizontal_dist = 35;
	static constexpr unsigned first_Xpos = 80;
	static constexpr unsigned first_Ypos = 40;
	static constexpr unsigned unit_Xpos = 115;
	static constexpr unsigned unit_Ypos = 50;
	static constexpr unsigned message_Xpos = 5;
	static constexpr unsigned message_Ypos = 5;
	static constexpr unsigned status_Xpos = 5;
	static constexpr unsigned status_Ypos = 110;

	const char minFrequencyMessage[30] = "Min Frequency";
	const char maxFrequencyMessage[30] = "Max Frequency";
	const char onMessage[12] = "Status: On";
	const char offMessage[12] = "Status: Off";
	int existingFrequency;

	Colour foreGroundColor = WHITE;
	Colour numberColor = RED;
	Colour backGroundColor = BLACK;

public:
	Indicator();
	void displayUnit(int frequency);
	void displayNumber(int number);
	void displayMessage(int frequency);
	void displayOnOff(bool isOn);
	void display(bool isOn, int frequency);
};


#endif /* SOURCES_INDICATOR_H_ */
