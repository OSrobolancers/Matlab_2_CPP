/*
 * array.h
 *
 *  Created on: Sep 29, 2020
 *      Author: maboelfo
 */

#ifndef SRC_ARRAY_H_
#define SRC_ARRAY_H_

#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

class array
{
public:
	double* data;
	int* size;
	int numOfDimensions;
	int numOfElements;
	bool freeAbility;

	array();
	array(int inNumOfDimensions, int* inSize);
	array(int inNumOfDimensions, int* inSize, double val);
	array(int inNumOfDimensions, int* inSize, double* arr);
	array(int inNumOfDimensions, int* inSize, vector<vector<double> > vect);
	array(array* arr);

	int getSize(int dimension);
	double getEle(int row, int col);
	void setEle(int row, int col, double ele);
	void add(array* arr);
	void add(double val);
	void sub(array* arr);
	void sub(double val);
	void mul(array* arr);
	void mul(double val);
	void transpose();
	void update(array* arr);
	void update(double* arr);
	void print();
	void freeArray(array* arr);
};

#endif /* SRC_ARRAY_H_ */
