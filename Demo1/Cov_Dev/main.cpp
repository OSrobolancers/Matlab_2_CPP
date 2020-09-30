/*
 * main.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: maboelfo
 */

#include "cov.h"

using namespace std;

void cov_testing()
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
}

void diag_testing1()
{
	vector<vector<double> >* vect = new vector<vector<double> >(3 , vector<double> (1));

	(*vect)[0][0] = 1;
	(*vect)[1][0] = 2;
	(*vect)[2][0] = 3;

	array* data = new array(vect);

	data->diag();
	data->print();

}

void diag_testing2()
{
	vector<vector<double> >* vect = new vector<vector<double> >(1 , vector<double> (3));

	(*vect)[0][0] = 1;
	(*vect)[0][1] = 2;
	(*vect)[0][2] = 3;

	array* data = new array(vect);

	data->diag();
	data->print();

}
int main(void)
{
	cov_testing();
	diag_testing1();
	diag_testing2();

	return 0;
}
