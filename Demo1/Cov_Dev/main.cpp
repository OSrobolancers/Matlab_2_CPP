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

	vector<vector<double> > vect(6 , vector<double> (3));

	for (int i = 0; i < size[0]; i++)
	{
		for (int j = 0; j < size[1]; j++)
		{
			vect[i][j] = Data[i][j];
		}
	}

	array* data = new array(2, size, vect);
	array* result = cov(data);

	result->print();
	result->freeArray(result);

	return 0;
}
