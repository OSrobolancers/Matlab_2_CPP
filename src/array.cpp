/*
 * array.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: maboelfo
 */

#include "array.h"

array::array()
{
	vectPtr = NULL;
}

array::array(int inNumOfDimensions, int* inSize)
{
	if (inSize != NULL)
	{
		vectPtr = new vector<vector<double> >(inSize[0], vector<double> (inSize[1]));
	}
	else
	{
		vectPtr = NULL;
	}
}

array::array(int inNumOfDimensions, int* inSize, double val)
{
	if (inSize != NULL)
	{
		switch(inNumOfDimensions)
		{
		case 1:
			vectPtr = new vector<vector<double> >(inSize[0], vector<double> (1));
			break;
		case 2:
			vectPtr = new vector<vector<double> >(inSize[0], vector<double> (inSize[1]));
			break;
		default:
			vectPtr = NULL;
			break;
		}
	}
	else
	{
		vectPtr = NULL;
	}

	if (vectPtr != NULL)
	{
		for (unsigned int i = 0; i < vectPtr->size(); i++)
		{
			for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
			{
				(*vectPtr)[i][j] = val;
			}
		}
	}
}

array::array(int inNumOfDimensions, int* inSize, double* arr)
{
	if (inSize != NULL)
	{
		vectPtr = new vector<vector<double> >(inSize[0], vector<double> (inSize[1]));

		for (unsigned int i = 0; i < vectPtr->size(); i++)
		{
			for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
			{
				(*vectPtr)[i][j] += arr[i*vectPtr->size() + j];
			}
		}
	}
	else
	{
		vectPtr = NULL;
	}
}

array::array(vector<vector<double> >* vect)
{
	vectPtr		= new vector<vector<double> >(vect->size(), vector<double> ((*vect)[0].size()));
	*vectPtr	= *vect;
}

array::array(array* arr)
{
	vectPtr		= new vector<vector<double> >(arr->vectPtr->size(), vector<double> ((*arr->vectPtr)[0].size()));
	*vectPtr	= *arr->vectPtr;
}

array::array(double start, double end, int numOfPoints)
{
	vectPtr	= new vector<vector<double> >(1, vector<double> (numOfPoints));

	for (int i = 0; i < numOfPoints; i++)
	{
		setEle(0, i, start + i*(end-start)/(numOfPoints-1));
	}
}

array::array(double start, double end)
{
	int numOfPoints = end-start+1;
	vectPtr	= new vector<vector<double> >(1, vector<double> (numOfPoints));

	for (int i = 0; i < numOfPoints; i++)
	{
			setEle(0, i, start + i*(end-start)/(numOfPoints-1));
	}
}

int array::getSize(int dimension)
{
	int returnVal = 0;

	if (vectPtr != NULL)
	{
		switch(dimension)
		{
		case 0:
			returnVal = vectPtr->size();
			break;
		case 1:
			returnVal = (*vectPtr)[0].size();
			break;
		default:
			break;
		}
	}

	return returnVal;
}

double array::getEle(int row, int col)
{
	return (*vectPtr)[row][col];
}

void array::setEle(int row, int col, double ele)
{
	(*vectPtr)[row][col] = ele;
}

void array::add(array *arr)
{
	for (int i = 0; i < 2; i++)
	{
		if (getSize(i) != arr->getSize(i))
			return;
	}

	for (unsigned int i = 0; i < vectPtr->size(); i++)
	{
		for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
		{
			(*vectPtr)[i][j] += arr->getEle(i, j);
		}
	}
}

void array::add(double val)
{
	for (unsigned int i = 0; i < vectPtr->size(); i++)
	{
		for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
		{
			(*vectPtr)[i][j] += val;
		}
	}
}

void array::sub(array *arr)
{
	for (int i = 0; i < 2; i++)
	{
		if (getSize(i) != arr->getSize(i))
			return;
	}

	for (unsigned int i = 0; i < vectPtr->size(); i++)
	{
		for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
		{
			(*vectPtr)[i][j] -= arr->getEle(i, j);
		}
	}
}

void array::sub(double val)
{
	for (unsigned int i = 0; i < vectPtr->size(); i++)
	{
		for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
		{
			(*vectPtr)[i][j] -= val;
		}
	}
}

void array::mul(array *arr)
{
	if (getSize(1) == arr->getSize(0))
	{
		int resultSize[] = {getSize(0), arr->getSize(1)};
		double locResult;
		array* result = new array(2, resultSize);

		for (int i = 0; i < result->getSize(0); i++)
		{
			for (int j = 0; j < result->getSize(1); j++)
			{
				locResult = 0;
				for (int k = 0; k < arr->getSize(0); k++)
				{
					locResult += getEle(i, k) * arr->getEle(k, j);
				}
				result->setEle(i, j, locResult);
			}
		}

		update(result);
		result->freeArray(result);
	}
}

void array::mulReturn(array *arr, array* result)
{
	if (getSize(1) == arr->getSize(0))
	{
		double locResult;

		for (int i = 0; i < result->getSize(0); i++)
		{
			for (int j = 0; j < result->getSize(1); j++)
			{
				locResult = 0;
				for (int k = 0; k < arr->getSize(0); k++)
				{
					locResult += getEle(i, k) * arr->getEle(k, j);
				}
				result->setEle(i, j, locResult);
			}
		}
	}
}

void array::dotMul(array* arr, array* result)
{
	for (int i = 0; i < arr->getSize(0); i++)
	{
		for (int j = 0; j < arr->getSize(1); j++)
		{
			(*result->vectPtr)[i][j] = (*vectPtr)[i][j] * (*arr->vectPtr)[i][j];
		}
	}
}

void array::dotDiv(array* arr, array* result)
{
	if((getSize(0) == arr->getSize(0)) && (getSize(1) == arr->getSize(1)))
	{
		for (unsigned int i = 0; i < vectPtr->size(); i++)
		{
			for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
			{
				(*result->vectPtr)[i][j] = (*vectPtr)[i][j] / (*arr->vectPtr)[i][j];
			}
		}
	}
	else
	{
		cout<< "Not match size dotMul Function"<<endl;
	}
}

void array::mul(double val)
{
	for (unsigned int i = 0; i < vectPtr->size(); i++)
	{
		for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
		{
			(*vectPtr)[i][j] *= val;
		}
	}
}

void array::transpose()
{
	if (vectPtr != NULL)
	{
		int sizeNew[] = {getSize(1), getSize(0)};

		array* tmp = new array(2, sizeNew);

		for (unsigned int i = 0; i < vectPtr->size(); i++)
		{
			for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
			{
				tmp->setEle(j, i, getEle(i, j));
			}
		}

		update(tmp);
		tmp->freeArray(tmp);
	}

}

void array::diag()
{
	if (getSize(0) == 1)
	{
		int size[] = {getSize(1), getSize(1)};
		array* tmp = new array(2, size, 0.0);

		for (int i = 0; i < getSize(1); i++)
		{
			tmp->setEle(i, i, getEle(0, i));
		}

		update(tmp);
		tmp->freeArray(tmp);
	}
	else if (getSize(1) == 1)
	{
		int size[] = {getSize(0), getSize(0)};
		array* tmp = new array(2, size, 0.0);

		for (int i = 0; i < getSize(0); i++)
		{
			tmp->setEle(i, i, getEle(i, 0));
		}

		update(tmp);
		tmp->freeArray(tmp);
	}
	else
	{

	}
}
void array::sum1D(array* result, int dim)
{
	switch (dim)
	{
	case 1:
		for (unsigned int i = 0; i < (*vectPtr)[0].size(); i++)
		{
			for (unsigned int j = 0; j < vectPtr->size(); j++)
			{
				(*result->vectPtr)[0][i] += getEle(j, i);
			}
		}
		break;
	case 2:
		for (unsigned int i = 0; i < vectPtr->size(); i++)
		{
			for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
			{
				(*result->vectPtr)[i][0] += getEle(i, j);
			}
		}
		break;
	default:
		break;
	}
}

void array::expArr(array* result)
{
	for (unsigned int i = 0; i < vectPtr->size(); i++)
	{
		for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
		{
			(*result->vectPtr)[i][j] += exp(getEle(i, j));
		}
	}
}

double array::sum()
{
	double sum = 0;

	for (unsigned int i = 0; i < vectPtr->size(); i++)
	{
		for (unsigned int j = 0; j < (*vectPtr)[0].size(); j++)
		{
			sum += getEle(i, j);
		}
	}

	return sum;
}

double array::det()
{
	double result = 0.0;

	if ((vectPtr->size() == 3) && ((*vectPtr)[0].size() == 3))
	{
		result = \
				getEle(0, 0) * (getEle(1, 1)*getEle(2, 2) - getEle(1, 2)*getEle(2, 1)) - \
				getEle(0, 1) * (getEle(1, 0)*getEle(2, 2) - getEle(1, 2)*getEle(2, 0)) + \
				getEle(0, 2) * (getEle(1, 0)*getEle(2, 1) - getEle(1, 1)*getEle(2, 0));
	}

	return result;
}

double array::minRow(int rowIdx)
{
	double minVal = getEle(rowIdx, 0);

	for (unsigned int i = 1; i < getSize(1); i++)
	{
		if (getEle(rowIdx, i) < minVal)
			minVal = getEle(rowIdx, i);
	}

	return minVal;
}

double array::maxRow(int rowIdx)
{
	double maxVal = getEle(rowIdx, 0);

	for (unsigned int i = 1; i < getSize(1); i++)
	{
		if (getEle(rowIdx, i) > maxVal)
			maxVal = getEle(rowIdx, i);
	}

	return maxVal;
}

void array::update(array* arr)
{
	if (arr != NULL)
	{
		if (vectPtr != NULL)
		{
			free(vectPtr);
			vectPtr = NULL;
		}

		vectPtr		= new vector<vector<double> >(arr->vectPtr->size(), vector<double> ((*arr->vectPtr)[0].size()));
		*vectPtr	= *arr->vectPtr;
	}
}

void array::update(double* arr)
{

}

void array::print()
{
	if (vectPtr != NULL)
	{
		unsigned int j;
		for (unsigned int i = 0; i < vectPtr->size(); i++)
		{
			for (j = 0; j < (*vectPtr)[0].size()-1; j++)
			{
				cout << (*vectPtr)[i][j] << ", ";
			}
			cout << (*vectPtr)[i][j] << endl;
		}

		cout << endl;
	}
}

void array::freeArray(array* arr)
{
	free(vectPtr);
	free(arr);
}
