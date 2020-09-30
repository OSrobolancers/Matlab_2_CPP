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

	vector<vector<double> >* vect = new vector<vector<double> >(6 , vector<double> (3));

	for (unsigned int i = 0; i < vect->size(); i++)
	{
		for (unsigned int j = 0; j < (*vect)[0].size(); j++)
		{
			(*vect)[i][j] = Data[i][j];
		}
	}

	array* data = new array(vect);
	array* result = cov(data);

	result->print();
	result->freeArray(result);
	free(vect);

	return 0;
}
