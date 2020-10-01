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
#include <bits/stdc++.h>

using namespace std;

class array
{
public:
	vector<vector<double> >* vectPtr;

	array();
	array(int inNumOfDimensions, int* inSize);
	array(int inNumOfDimensions, int* inSize, double val);
	array(int inNumOfDimensions, int* inSize, double* arr);
	array(vector<vector<double> >* vect);
	array(array* arr);

	int getSize(int dimension);
	double getEle(int row, int col);
	void setEle(int row, int col, double ele);
	void add(array* arr);
	void add(double val);
	void sub(array* arr);
	void sub(double val);
	void mul(array* arr);
	void mulReturn(array *arr, array* result);
	void dotMul(array* arr, array* result);
	void mul(double val);
	void transpose();
	void diag();
	double sum();
	void sum1D(array* result);
	void expArr(array* result);
	double det();
	void update(array* arr);
	void update(double* arr);
	void print();
	void freeArray(array* arr);
};

#endif /* SRC_ARRAY_H_ */
