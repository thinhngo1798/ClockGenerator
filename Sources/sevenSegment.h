/*
 * SevenSegment.h
 *
 *  Created on: Sep 19, 2019
 *      Author: PLH
 */

#ifndef SOURCES_SEVENSEGMENT_H_
#define SOURCES_SEVENSEGMENT_H_

#include "lcd.h"

using namespace USBDM;

class SevenSegment
{
	const int numSegment = 7;
	const int horizontal_bar_width = 20;
	const int horizontal_bar_height = 5;
	const int vertical_bar_width = 5;
	const int vertical_bar_height = 20;
	const int space_height = 5;
	const int space_width = 5;

	int startX[7];
	int startY[7];

	int barWidth[7];
	int barHeight[7];

	int x;
	int y;

	bool table[10][7] = {
							{1,1,1,0,1,1,1},
							{0,0,0,0,0,1,1},
							{0,1,1,1,1,1,0},
							{0,0,1,1,1,1,1},
							{1,0,0,1,0,1,1},
							{1,0,1,1,1,0,1},
							{1,1,1,1,1,0,1},
							{0,0,1,0,0,1,1},
							{1,1,1,1,1,1,1},
							{1,0,1,1,1,1,1}
						};

	public:
		SevenSegment(int aX = 0, int aY = 0);
		void setXY(int new_x, int new_y);
		void drawNum(USBDM::Lcd & lcd, int num, Colour foregroundColor, Colour backgroundColor);

};

#endif /* SOURCES_SEVENSEGMENT_H_ */
