/*
 * main.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: maboelfo
 */

#include "cov.h"


using namespace std;

int main(void)
{
	double Data[6][3] = { \
			{90, 80, 40}, \
			{90, 60, 80}, \
			{60, 50, 70}, \
			{30, 40, 70}, \
			{30, 20, 90}, \
			{60, 50, 70}};

	int size[] = {6, 3};

	array* data = new array(2, size, (double*)Data);
	array* result = cov(data);

	result->print();
	result->freeArray(result);

	return 0;
}





