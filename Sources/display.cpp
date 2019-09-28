/*
 * display.cpp
 *
 *  Created on: Sep 28, 2019
 *      Author: PLH
 */
#include "display.h"

Display::Display(): lcd(spi)
{
	int currentXPos = first_Xpos;
	int currentYPos = first_Ypos;
	int numberSegments = 3;
	for (int i = 0; i < numberSegments; ++i)
	{
		digit[i].setXY(currentXPos, currentYPos);
		currentXPos -= horizontal_dist;
	}

	lcd.clear(backGroundColor);
	existingFrequency = 1;
}

int getScalar(int frequency)
{
	if (frequency < 0 && frequency > 1000000000)
	{
		return 0;
	}
	else if (frequency >= 1000000)
	{
		return 1000000;
	}
	else if (frequency >= 1000)
	{
		return 1000;
	}
	else
	{
		return 1;
	}
}

void Display::displayUnit(int scalar)
{
	switch(scalar)
	{
	case 1:
		lcd.putStr("Hz", unit_Xpos, unit_Ypos);
		break;
	case 1000:
		lcd.putStr("kHz", unit_Xpos, unit_Ypos);
		break;
	case 1000000:
		lcd.putStr("MHz", unit_Xpos, unit_Ypos);
		break;
	default:
		break;
	}
}

void Display::displayNumber(int number)
{
	int numberSegments = 3;

	int currentDigit;

	for (int i = 0; i < numberSegments; ++i)
	{
		currentDigit = number % 10;
		number/=10;
		digit[i].drawNum(lcd, currentDigit, foreGroundColor, backGroundColor);
	}
}

void Display::displayMessage(int frequency)
{
	lcd.setFont(fontSmall).setForeground(foreGroundColor).setBackground(backGroundColor);
	//
	// not erasing the old message yet
	//
	if (frequency == MIN_FREQUENCY)
	{
		lcd.putStr(minFrequencyMessage, message_Xpos, message_Ypos);
	}
	else if (frequency == MAX_FREQUENCY)
	{
		lcd.putStr(maxFrequencyMessage, message_Xpos, message_Ypos);
	}
}

void Display::display(int frequency)
{
	//char * pUnit = getUnit(frequency);
	int scalar = getScalar(existingFrequency);
	lcd.setFont(fontSmall).setForeground(backGroundColor).setBackground(foreGroundColor);
	displayUnit(scalar);

	scalar = getScalar(frequency);
	lcd.setFont(fontSmall).setForeground(foreGroundColor).setBackground(backGroundColor);
	displayUnit(scalar);

	displayNumber(frequency/scalar);

	//convert into digit

	displayMessage(frequency);
	existingFrequency = frequency;
}



