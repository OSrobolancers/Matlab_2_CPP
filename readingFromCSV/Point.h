/*
 * Point.h
 *
 *  Created on: Sep 28, 2020
 *      Author: oelkawok
 */

#ifndef POINT_H_
#define POINT_H_



class Point {
public:
	int idx = 0;
	double x = 0.0;
	double y = 0.0;     // coordinates
	int cluster = -1;     // no default cluster
	double minDist = __DBL_MAX__;  // default infinite dist to nearest cluster

	Point(int idx, double x_, double y_);

	double distance(Point p);

};



#endif /* POINT_H_ */
