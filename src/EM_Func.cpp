/*
 * EM_Func.cpp
 *
 *  Created on: Sep 30, 2020
 *      Author: oelkawok
 */

#include "EM_Func.h"

EM_Func_t EM_Func_s;

void EM(vector<Point>& data)
{
	int nbVar = data[0].getDimensions();
	int nbData = data.size();
	int nbStates = EM_init_S.Sigma.size();
	//double  = -1.79769e+308;
	cout<<"nbStates: "<<nbStates<<endl;

	double loglik_old = -1.7977e+308;
	double loglik_threshold = 1e-10;

	array* Pix;
	array* diag;

	int size[2];

	size[0] = nbData;
	size[1] = nbStates;

	Pix = new array(2, size);		//nbData x nbStates

	size[0] = nbVar;
	size[1] = 1;

	diag = new array(2, size, 1.0);
	diag->diag();
	diag->mul(1e-5);

	while(true)
	{
		array* Pxi_temp;
		int sizePxi[2];
		sizePxi[0] = nbData;
		sizePxi[1] = nbStates;
		EM_Func_s.PxiArr = new array(2,sizePxi);

		for(int i = 0;i < nbStates;i++)
		{
			gaussPDF(data, i); //return Pxi into global
		}

		//Line 75 EM
		int prmSize[2] = {nbData, (int)EM_init_S.PriorArr->getSize(1)};
		Pxi_temp = new array(2, prmSize);
		repmat4xN(EM_init_S.PriorArr, Pxi_temp, nbData);
		Pxi_temp->dotMul(EM_Func_s.PxiArr, Pxi_temp);
		//Pxi_temp->print();

		size[0] = nbData;
		size[1] = 1;
		array* sum = new array(2, size);
		Pxi_temp->sum1D(sum, 2);

		size[0] = nbData;
		size[1] = nbStates;

		array* tmp = new array(2, size);

		repmatNx1(sum, tmp, nbStates);
		sum->freeArray(sum);

		Pxi_temp->dotDiv(tmp, Pix);
		tmp->freeArray(tmp);
		Pxi_temp->freeArray(Pxi_temp);
		//Pix->print();

		size[0] = 1;
		size[1] = nbStates;

		array* E = new array(2, size, 0.0);
		Pix->sum1D(E, 1);
		//E->print();

		size[0] = nbData;
		size[1] = 1;
		tmp = new array(2, size);

		size[0] = 3;
		size[1] = 1;
		sum = new array(2, size);

		size[0] = 3;
		size[1] = nbData;
		array* Data = new array(2, size);
		array* DataTmp = new array();
		array* DataTmp2 = new array();

		array* tmp2 = new array(2, size);

		size[0] = nbData;
		size[1] = nbVar;
		array* tmp3 = new array(2, size);

		EM_init_S.Mu->transpose();

		for(int i = 0; i < nbData; i++)
		{
			Data->setEle(T, i, data[i].getVal(T));
			Data->setEle(X, i, data[i].getVal(X));
			Data->setEle(Y, i, data[i].getVal(Y));
		}

		EM_init_S.Sigma[0]->freeArray(EM_init_S.Sigma[0]);
		EM_init_S.Sigma[1]->freeArray(EM_init_S.Sigma[1]);
		EM_init_S.Sigma[2]->freeArray(EM_init_S.Sigma[2]);
		EM_init_S.Sigma[3]->freeArray(EM_init_S.Sigma[3]);

		for(int i = 0; i < nbStates; i++)
		{
			size[0] = 3;
			size[1] = nbData;
			array* tmp4 = new array(2, size);
			EM_init_S.PriorArr->setEle(0, i, E->getEle(0, i)/(double)nbData);

			for (int j = 0; j < nbData; j++)
				tmp->setEle(j, 0, Pix->getEle(j, i));

			tmp->mul(1/E->getEle(0, i));
			Data->mulReturn(tmp, sum);

			for (int j = 0; j < EM_init_S.Mu->getSize(0); j++)
				EM_init_S.Mu->setEle(j, i, sum->getEle(j, 0));

			DataTmp->update(Data);
			repmatNx1(sum, tmp2, nbData);
			DataTmp->sub(tmp2);
			DataTmp2->update(DataTmp);
			DataTmp2->transpose();

			tmp->mul(E->getEle(0, i));
			repmatNx1(tmp, tmp3, nbVar);
			tmp3->transpose();
			tmp3->dotMul(DataTmp, tmp4);

			tmp4->mul(DataTmp2);
			tmp4->mul(1/E->getEle(0, i));
			tmp4->add(diag);
			tmp3->transpose();

			EM_init_S.Sigma[i] = tmp4;
		}
		Data->freeArray(Data);
		tmp->freeArray(tmp);
		sum->freeArray(sum);
		E->freeArray(E);
		DataTmp->freeArray(DataTmp);
		DataTmp2->freeArray(DataTmp2);
		tmp2->freeArray(tmp2);
		tmp3->freeArray(tmp3);

//		EM_init_S.PriorArr->print();
//		EM_init_S.Mu->print();
//
//		EM_init_S.Sigma[0]->print();
//		EM_init_S.Sigma[1]->print();
//		EM_init_S.Sigma[2]->print();
//		EM_init_S.Sigma[3]->print();

		EM_init_S.Mu->transpose();

		for(int i = 0; i < nbStates; i++)
		{
			gaussPDF(data, i);
		}

		//EM_Func_s.PxiArr->print();

		tmp = new array(EM_init_S.PriorArr);
		tmp->transpose();

		array* F = new array(EM_Func_s.PxiArr);
		F->mul(tmp);
		tmp->freeArray(tmp);

		//F->print();

		double loglik = 0.0;

		for (int i = 0; i < F->getSize(0); i++)
		{
			if (F->getEle(i, 0) < 2.2251e-308)
			{
				F->setEle(i, 0, 2.2251e-308);
			}
			loglik += log(F->getEle(i, 0));
		}
		//F->print();
		F->freeArray(F);

		loglik /= F->getSize(0);

		if (abs((loglik/loglik_old)-1) < loglik_threshold)
		{
			break;
		}

		loglik_old = loglik;
	}
//	EM_init_S.PriorArr->print();
//	EM_init_S.Mu->print();

	for(int i = 0; i < nbStates; i++)
	{
		EM_init_S.Sigma[i]->add(diag);
	}
//	EM_init_S.Sigma[0]->print();
//	EM_init_S.Sigma[1]->print();
//	EM_init_S.Sigma[2]->print();
//	EM_init_S.Sigma[3]->print();

	Pix->freeArray(Pix);
	diag->freeArray(diag);
}

void gaussPDF(vector<Point>& data, int idx)
{
	int nbVar = data[0].getDimensions();
	int nbData = data.size();
	int arrSize[2];

	//Line 20 gaussPDF
	arrSize[0] = nbData;
	arrSize[1] = nbVar;
	array* newData = new array(2 ,arrSize);
	repmat3xN(EM_init_S.Mu, newData, nbData, idx);
	//print2DVector(newData);
	array* dataArr = new array(2, arrSize);
	vectPt2Arr(data, dataArr);
	dataArr->sub(newData);

	//Line 21 gausPDF
	arrSize[0] = 3;
	arrSize[1] = 3;
	array* invSigma = new array(2, arrSize);
	double determinant = DET3x3(EM_init_S.Sigma[idx]);
	INV3x3(EM_init_S.Sigma[idx], determinant, invSigma);

	arrSize[0] = dataArr->getSize(0);
	arrSize[1] = dataArr->getSize(1);
	array* tempArr = new array(2, arrSize);
	dataArr->mulReturn(invSigma, tempArr);
	array* tempArr2 = new array(2, arrSize);
	dataArr->dotMul(tempArr, tempArr2);

	arrSize[1] = 1;
	array* prob = new array(2, arrSize);
	tempArr2->sum1D(prob, 2);

	//Line 22 gaussPDF
	arrSize[0] = prob->getSize(0);
	arrSize[1] = prob->getSize(1);
	array* locPxi = new array(2, arrSize);
	prob->mul(-0.5);
	prob->expArr(locPxi);

	double PI_Res = power((2*M_PI), nbVar);
	if(determinant < 0) //abs(det
		determinant *= -1;
	determinant += realMin;
	double deno = sqrt((PI_Res * determinant));
	locPxi->mul((1/deno));

	for (int i = 0; i < nbData; i++)
	{
		EM_Func_s.PxiArr->setEle(i, idx, locPxi->getEle(i, 0));
	}
	//gaussPDFCnt++;

//	EM_Func_s.Pxi.push_back(locPxi);


	//EM_init_S.Sigma[idx]->print();
	//newData->print();
}

void repmat3xN(array* mu, array* newData, int totalSize, int idx)
{
	for(int i = 0;i < totalSize;i++)
	{
		(*newData->vectPtr)[i][T] = (*EM_init_S.Mu->vectPtr)[idx][T];
		(*newData->vectPtr)[i][X] = (*EM_init_S.Mu->vectPtr)[idx][X];
		(*newData->vectPtr)[i][Y] = (*EM_init_S.Mu->vectPtr)[idx][Y];
	}
}

void repmatNx1(array* arr, array* newData, int totalSize)
{
	int row = arr->getSize(0);
	for(int i = 0;i < totalSize;i++)
	{
		for(int j = 0;j < row;j++)
		{
			newData->setEle(j, i, arr->getEle(j, 0));
		}
	}
}

void repmat4xN(array* arr, array* newData, int totalSize)
{
	int row = arr->getSize(0);
	int col = arr->getSize(1);
	for(int i = 0;i < totalSize;i++)
	{
		for(int j = 0;j < row;j++)
		{
			for(int k = 0;k < col;k++)
				(*newData->vectPtr)[i][k] = (*arr->vectPtr)[j][k];
		}
	}
}

void repmatVec(vector<double> p, array* newData, int totalSize, int idx)
{
	for(int i = 0;i < totalSize;i++)
	{
		(*newData->vectPtr)[i][T] = (*EM_init_S.Mu->vectPtr)[idx][T];
		(*newData->vectPtr)[i][X] = (*EM_init_S.Mu->vectPtr)[idx][X];
		(*newData->vectPtr)[i][Y] = (*EM_init_S.Mu->vectPtr)[idx][Y];
	}
}

void print2DVector(vector<vector<double> >& dataPrint)
{
	int sizeX = dataPrint.size();
	int sizeY = dataPrint[0].size();
	for(int j = 0;j < sizeX; j++)
	{
		for(int k = 0;k < sizeY;k++)
		{
			cout<<dataPrint[j][k]<<", ";
		}
		cout<<endl;
	}
}

void printVecArr(vector<array*> mat2Print)
{
	int length = mat2Print.size();
	for(int i = 0;i < length;i++)
	{

		mat2Print[i]->print();
	}
}

void vectPt2Arr(vector<Point>& data,array* dataArr)
{
	int row = data.size();
	int col = data[0].getDimensions();

	for(int i = 0;i < row;i++)
	{
		for(int j = 0;j < col;j++)
		{
			(*dataArr->vectPtr)[i][j] = data[i].getVal(j);
		}
	}
}

void vect2Arr()
{
	int len = EM_Func_s.Pxi.size();
	int arrLr = EM_Func_s.Pxi[0]->getSize(0);
	cout<<"ARR:"<<arrLr<<endl;

	for(int i = 0;i < len;i++)
	{
		for(int j = 0;j < arrLr;j++)
		{
			(*EM_Func_s.PxiArr->vectPtr)[j][i] = (*EM_Func_s.Pxi[i]->vectPtr)[j][0];
		}
	}
}

double DET3x3(array* mat) //for
{
	int size0 = mat->getSize(0);
	int size1 = mat->getSize(1);
	double determinant;
   for(int i = 0; i < size1; i++)
   		determinant = determinant + ((*mat->vectPtr)[0][i] * ((*mat->vectPtr)[1][(i+1)%3] * (*mat->vectPtr)[2][(i+2)%3] - (*mat->vectPtr)[1][(i+2)%3] * (*mat->vectPtr)[2][(i+1)%3]));
return determinant;
}

void INV3x3(array* mat, double determinant, array* out)
{
	int size0 = mat->getSize(0);
	int size1 = mat->getSize(1);

	double a = (*mat->vectPtr)[0][0];
	double b = (*mat->vectPtr)[0][1];
	double c = (*mat->vectPtr)[0][2];

	double d = (*mat->vectPtr)[1][0];
	double e = (*mat->vectPtr)[1][1];
	double f = (*mat->vectPtr)[1][2];

	double g = (*mat->vectPtr)[2][0];
	double h = (*mat->vectPtr)[2][1];
	double i = (*mat->vectPtr)[2][2];

	double invDet = 1/determinant;

	//gettting Adj Mat
	(*out->vectPtr)[0][0] = a;
	(*out->vectPtr)[0][1] = b;
	(*out->vectPtr)[0][2] = c;

	(*out->vectPtr)[1][0] = d;
	(*out->vectPtr)[1][1] = e;
	(*out->vectPtr)[1][2] = f;

	(*out->vectPtr)[2][0] = g;
	(*out->vectPtr)[2][1] = h;
	(*out->vectPtr)[2][2] = i;

	out->transpose();

	a = (*out->vectPtr)[0][0];
	b = (*out->vectPtr)[0][1];
	c = (*out->vectPtr)[0][2];

	d = (*out->vectPtr)[1][0];
	e = (*out->vectPtr)[1][1];
	f = (*out->vectPtr)[1][2];

	g = (*out->vectPtr)[2][0];
	h = (*out->vectPtr)[2][1];
	i = (*out->vectPtr)[2][2];

	(*out->vectPtr)[0][0] = (e * i - f * h) * invDet;
	(*out->vectPtr)[0][1] = (d * i - f * g) * invDet;
	(*out->vectPtr)[0][2] = (d * h - e * g) * invDet;

	(*out->vectPtr)[1][0] = (b * i - c * h) * invDet;
	(*out->vectPtr)[1][1] = (a * i - c * g) * invDet;
	(*out->vectPtr)[1][2] = (a * h - b * g) * invDet;

	(*out->vectPtr)[2][0] = (b * f - c * e) * invDet;
	(*out->vectPtr)[2][1] = (a * f - c * d) * invDet;
	(*out->vectPtr)[2][2] = (a * e - b * d) * invDet;

	//matrix cofactor
	(*out->vectPtr)[0][1] = (*out->vectPtr)[0][1] * -1;
	(*out->vectPtr)[1][0] = (*out->vectPtr)[1][0] * -1;
	(*out->vectPtr)[1][2] = (*out->vectPtr)[1][2] * -1;
	(*out->vectPtr)[2][1] = (*out->vectPtr)[2][1] * -1;

}

double power(double in, int pwr)
{
	double result = 1;
	for(int i = 0;i < pwr;i++)
	{
		result *= in;
	}
	return result;
}
