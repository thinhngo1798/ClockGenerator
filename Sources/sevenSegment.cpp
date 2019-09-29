/*
 * sevenSegment.cpp
 *
 *  Created on: Sep 28, 2019
 *      Author: PLH
 */
#include "sevenSegment.h"

//using namespace USBDM;

SevenSegment::SevenSegment(int aX, int aY)
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
void SevenSegment::setXY(int new_x, int new_y)
{
	x = new_x;
	y = new_y;
}
void SevenSegment::drawNum(USBDM::Lcd & lcd, int num, Colour foregroundColor, Colour backgroundColor)
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
