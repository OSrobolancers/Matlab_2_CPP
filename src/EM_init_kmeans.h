/*
 * EM_init_kmeans.h
 *
 *  Created on: Sep 30, 2020
 *      Author: oelkawok
 */

#ifndef EM_INIT_KMEANS_H_
#define EM_INIT_KMEANS_H_
#include "kmeans.h"
#include "array.h"
#include "cov.h"
#include <numeric>

typedef struct{
	array* Mu;
	vector<array*> Sigma;
	vector<double> Prior;
	array* PriorArr;
}EM_Return_t;

extern EM_Return_t EM_init_S;

void EM_init_kmeans(vector<Point>& data, unsigned int nbStates);


#endif /* EM_INIT_KMEANS_H_ */
