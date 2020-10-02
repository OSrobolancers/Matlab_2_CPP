/*
 * EM_Func.h
 *
 *  Created on: Sep 30, 2020
 *      Author: oelkawok
 */

#ifndef EM_FUNC_H_
#define EM_FUNC_H_

#include "EM_init_kmeans.h"

typedef struct{
	vector<array*> Pxi;
	array* PxiArr;
}EM_Func_t;

extern EM_Func_t EM_Func_s;

#define realMin (double)2.2251e-308
#define realMaxNeg -1.79769e+308

extern EM_Return_t EM_init_S;

void EM(vector<Point>& data);

void gaussPDF(vector<Point>& data, int idx);

void repmat3xN(array* mu, array* newData, int totalSize, int idx);

void repmat4xN(array* arr, array* newData, int totalSize);

void repmatNx1(array* arr, array* newData, int totalSize);

void print2DVector(vector<vector<double> >& dataPrint);

void printVecArr(vector<array*> mat2Print);

void vectPt2Arr(vector<Point>& data,array* dataArr);

double DET3x3(array* mat);

void INV3x3(array* mat, double determinant, array* out);

double power(double in, int pwr);

void vect2Arr(void);

#endif /* EM_FUNC_H_ */
