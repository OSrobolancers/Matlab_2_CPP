/*
 * Point.cpp
 *
 *  Created on: Sep 28, 2020
 *      Author: oelkawok
 */

#include "Point.h"

Point::Point(int idx_, double x_, double y_)
{
	// TODO Auto-generated constructor stub
	idx = idx_;
	x = x_;
	y = y_;
	cluster = -1;
	minDist = __DBL_MAX__;
}

double Point::distance(Point p)
{
		return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
}

