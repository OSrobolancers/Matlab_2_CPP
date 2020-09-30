/*
 * array.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: maboelfo
 */

#include "array.h"

array::array()
{
	data 			= NULL;
	size 			= NULL;
	numOfDimensions = 0;
	numOfElements	= 0;
	freeAbility		= 1;
}

array::array(int inNumOfDimensions, int* inSize)
{
	if (inSize != NULL)
	{
		int loc_NumOfElements = 1;

		size 			= (int*)malloc(inNumOfDimensions*sizeof(int));
		numOfDimensions = inNumOfDimensions;

		for (int i = 0; i < numOfDimensions; i++)
		{
			size[i] = inSize[i];
			loc_NumOfElements *= size[i];
		}

		numOfElements	= loc_NumOfElements;
		data			= (double*)malloc(numOfElements*sizeof(double));
	}
	else
	{
		data 			= NULL;
		size 			= NULL;
		numOfDimensions = 0;
		numOfElements	= 0;
	}
	freeAbility		= 1;
}

array::array(int inNumOfDimensions, int* inSize, double val)
{

	if (inSize != NULL)
	{
		int loc_NumOfElements = 1;

		size 			= (int*)malloc(inNumOfDimensions*sizeof(int));
		numOfDimensions = inNumOfDimensions;

		for (int i = 0; i < numOfDimensions; i++)
		{
			size[i] = inSize[i];
			loc_NumOfElements *= size[i];
		}

		numOfElements	= loc_NumOfElements;
		data			= (double*)malloc(numOfElements*sizeof(double));

		for (int i = 0; i < numOfElements; i++)
		{
			data[i] = val;
		}
	}
	else
	{
		data 			= NULL;
		size 			= NULL;
		numOfDimensions = 0;
		numOfElements	= 0;
	}
	freeAbility		= 1;
}

array::array(int inNumOfDimensions, int* inSize, double* arr)
{
	if (inSize != NULL)
	{
		int loc_NumOfElements = 1;

		size 			= (int*)malloc(inNumOfDimensions*sizeof(int));
		numOfDimensions = inNumOfDimensions;

		for (int i = 0; i < numOfDimensions; i++)
		{
			size[i] = inSize[i];
			loc_NumOfElements *= size[i];
		}

		numOfElements	= loc_NumOfElements;
		data			= (double*)malloc(numOfElements*sizeof(double));

		for (int i = 0; i < numOfElements; i++)
		{
			data[i] = arr[i];
		}
	}
	else
	{
		data 			= NULL;
		size 			= NULL;
		numOfDimensions = 0;
		numOfElements	= 0;
	}
	freeAbility		= 1;
}

array::array(int inNumOfDimensions, int* inSize, vector<vector<double> > vect)
{
	if (inSize != NULL)
	{
		int loc_NumOfElements = 1;

		size 			= (int*)malloc(inNumOfDimensions*sizeof(int));
		numOfDimensions = inNumOfDimensions;

		for (int i = 0; i < numOfDimensions; i++)
		{
			size[i] = inSize[i];
			loc_NumOfElements *= size[i];
		}

		numOfElements	= loc_NumOfElements;
		data			= (double*)malloc(numOfElements*sizeof(double));

		for (int i = 0; i < numOfElements; i++)
		{
			data[i] = vect[i/size[1]][i%size[1]];
		}
	}
	else
	{
		data 			= NULL;
		size 			= NULL;
		numOfDimensions = 0;
		numOfElements	= 0;
	}
	freeAbility		= 1;
}

array::array(array* arr)
{
	data 			= NULL;
	size 			= NULL;
	numOfDimensions = 0;
	numOfElements	= 0;
	freeAbility		= 1;

	update(arr);
}

int array::getSize(int dimension)
{
	int returnVal = 1;

	if (dimension < numOfDimensions)
	{
		returnVal = size[dimension];
	}

	return returnVal;
}

double array::getEle(int row, int col)
{
	double returnVal = 0.0;

	if ((row < size[0]) && (col < size[1]))
	{
		returnVal = data[row*size[1] + col];
	}

	return returnVal;
}

void array::setEle(int row, int col, double ele)
{
	if ((row < size[0]) && (col < size[1]))
	{
		data[row*size[1] + col] = ele;
	}
}

void array::add(array *arr)
{
	if (numOfDimensions == arr->numOfDimensions)
	{
		for (int i = 0; i < numOfDimensions; i++)
		{
			if (size[i] != arr->size[i])
				return;
		}

		for (int i = 0; i < numOfElements; i++)
		{
			data[i] += arr->data[i];
		}
	}
}

void array::add(double val)
{
	for (int i = 0; i < numOfElements; i++)
	{
		data[i] += val;
	}
}

void array::sub(array *arr)
{
	if (numOfDimensions == arr->numOfDimensions)
	{
		for (int i = 0; i < numOfDimensions; i++)
		{
			if (size[i] != arr->size[i])
				return;
		}

		for (int i = 0; i < numOfElements; i++)
		{
			data[i] -= arr->data[i];
		}
	}
}

void array::sub(double val)
{
	for (int i = 0; i < numOfElements; i++)
	{
		data[i] -= val;
	}
}

void array::mul(array *arr)
{
	if (size[numOfDimensions-1] == arr->size[0])
	{
		int resultSize[] = {size[0], arr->size[1]};
		double locResult;
		array* result = new array(numOfDimensions, resultSize, 0.0);

		for (int i = 0; i < result->size[0]; i++)
		{
			for (int j = 0; j < result->size[1]; j++)
			{
				locResult = 0;
				for (int k = 0; k < arr->size[0]; k++)
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

void array::mul(double val)
{
	for (int i = 0; i < numOfElements; i++)
	{
		data[i] *= val;
	}
}

void array::transpose()
{
	if ((data != NULL) && (size != NULL))
	{
		int sizeNew[] = {size[1], size[0]};

		array* tmp = new array(numOfDimensions, sizeNew);

		for (int i = 0; i < size[0]; i++)
		{
			for (int j = 0; j < size[1]; j++)
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
	if ((arr != NULL) && freeAbility)
	{
		if (data != NULL)
		{
			free(data);
			data = NULL;
		}

		if (data != NULL)
		{
			free(size);
			size = NULL;
		}

		numOfDimensions	= arr->numOfDimensions;
		numOfElements	= arr->numOfElements;
		freeAbility		= arr->freeAbility;
		data			= (double*)malloc(numOfElements*sizeof(double));
		size 			= (int*)malloc(numOfDimensions*sizeof(int));

		for (int i = 0; i < numOfDimensions; i++)
		{
			size[i] = arr->size[i];
		}

		for (int i = 0; i < numOfElements; i++)
		{
			data[i] = arr->data[i];
		}
	}
}

void array::update(double* arr)
{
	if (arr != NULL)
	{
		for (int i = 0; i < numOfElements; i++)
		{
			data[i] = arr[i];
		}
	}
	else
	{
		data = NULL;
	}
}

void array::print()
{
	switch(numOfDimensions)
	{
	case 1:
		for (int i = 0; i < size[0]-1; i++)
		{
			cout << data[i] << ", ";
		}

		cout << data[size[0] - 1] << endl << endl;
	case 2:
		for (int i = 0; i < size[0]; i++)
		{
			for (int j = 0; j < size[1]-1; j++)
			{
				cout << data[i*size[1] + j] << ", ";
			}
			cout << data[i*size[1] + size[1] - 1] << endl;
		}

		cout << endl;
	default:
		break;
	}
}

void array::freeArray(array* arr)
{
	free(size);
	free(data);
	free(arr);
}
