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
