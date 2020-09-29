/*
 * cov.cpp
 *
 *  Created on: Sep 30, 2020
 *      Author: maboelfo
 */

#include "cov.h"

array* cov(array* data)
{
	array* a = new array(data);

	int size[2];
	size[0] = data->getSize(0);
	size[1] = size[0];

	array* ones = new array(2, size, 1.0);

	ones->mul(data);
	ones->mul(1.0/double(data->getSize(0)));
	a->sub(ones);

	ones->freeArray(ones);

	array* result = new array(a);
	result->transpose();
	result->mul(a);
	result->mul(1.0/double(data->getSize(0) - 1));

	data->freeArray(data);
	a->freeArray(a);

	return result;
}
