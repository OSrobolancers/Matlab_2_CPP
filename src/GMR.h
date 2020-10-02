/*
 * GMR.h
 *
 *  Created on: Oct 1, 2020
 *      Author: maboelfo
 */

#ifndef GMR_H_
#define GMR_H_

#include "EM_Func.h"

typedef struct
{
	array* expData;
	vector<array*> expSigma;
}GMR_Out_t;

extern GMR_Out_t struct_tmp;

void GMR(array* x, int in, array* out);
array* gaussPDFScaler(array* x, double Mu, double Sigma);

#endif /* GMR_H_ */
