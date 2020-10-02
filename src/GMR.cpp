/*
 * GMR.cpp
 *
 *  Created on: Oct 1, 2020
 *      Author: maboelfo
 */

#include "GMR.h"

GMR_Out_t struct_tmp;

void GMR(array* x, int in, array* out)
{
	int nbData = x->getSize(1);
	int nbStates = EM_init_S.Sigma.size();

	array* tmp = NULL;

	int size[] = {nbData, nbStates};
	array* Pxi = new array(2, size);

	for (int i = 0; i < nbStates; i++)
	{
		tmp = gaussPDFScaler(x, EM_init_S.Mu->getEle(i, in), EM_init_S.Sigma[i]->getEle(in, in));
		tmp->mul(EM_init_S.PriorArr->getEle(0, i));

		for (int j = 0; j < nbData; j++)
		{
			Pxi->setEle(j, i, tmp->getEle(j, 0));
		}
		tmp->freeArray(tmp);
	}
	//Pxi->print();

	array* tmp2 = new array(2, size);
	array* beta = new array(2, size);

	size[1] = 1;
	tmp = new array(2, size);

	Pxi->sum1D(tmp, 2);
	tmp->add(2.2251e-308);

	repmatNx1(tmp, tmp2, nbStates);
	tmp->freeArray(tmp);

	Pxi->dotDiv(tmp2, beta);
	Pxi->freeArray(Pxi);
	tmp2->freeArray(tmp2);

	//beta->print();

	vector<array*> y_tmp;

	size[0] = out->getSize(1);
	size[1] = 1;
	array* Mu2 = new array(2, size);

	size[0] = 1;
	array* tmp3 = new array(2, size);

	size[1] = nbData;
	array* tmp4 = new array(2, size);

	for (int i = 0; i < nbStates; i++)
	{
		size[0] = out->getSize(1);
		size[1] = nbData;
		tmp = new array(2, size);

		size[1] = 1;
		array* Sigma2 = new array(2, size);

		for (int j = 0; j < out->getSize(1); j++)
		{
			Mu2->setEle(j, 0, EM_init_S.Mu->getEle(i, out->getEle(0, j)));
		}

		repmatNx1(Mu2, tmp, nbData);

		for (int j = 0; j < out->getSize(1); j++)
		{
			Sigma2->setEle(j, 0, EM_init_S.Sigma[i]->getEle(out->getEle(0, j), in));
		}
		//Sigma2->print();

		Sigma2->mul(1/EM_init_S.Sigma[i]->getEle(in, in));
		tmp3->setEle(0, 0, EM_init_S.Mu->getEle(i, in));
		repmatNx1(tmp3, tmp4, nbData);
		tmp4->sub(x);
		tmp4->mul(-1.0);

		//tmp4->print();

		Sigma2->mul(tmp4);
		tmp->add(Sigma2);

		y_tmp.push_back(tmp);
		Sigma2->freeArray(Sigma2);
	}
	Mu2->freeArray(Mu2);
	tmp3->freeArray(tmp3);
	tmp4->freeArray(tmp4);

//	y_tmp[0]->print();
//	y_tmp[1]->print();
//	y_tmp[2]->print();
//	y_tmp[3]->print();

	vector<array*> beta_tmp;

	size[0] = 1;
	size[1] = beta->getSize(0);
	for (int i = 0; i < beta->getSize(1); i++)
	{
		tmp = new array(2, size);

		for (int j = 0; j < size[1]; j++)
		{
			tmp->setEle(0, j, beta->getEle(j, i));
		}

		beta_tmp.push_back(tmp);
	}

//	beta_tmp[0]->print();
//	beta_tmp[1]->print();
//	beta_tmp[2]->print();
//	beta_tmp[3]->print();

	vector<array*> y_tmp2_;

	for (unsigned int i = 0; i < beta_tmp.size(); i++)
	{
		size[0] = out->getSize(1);
		size[1] = beta_tmp[i]->getSize(1);
		tmp = new array(2, size);

		for (int j = 0; j < out->getSize(1); j++)
		{
			for (int k = 0; k < beta_tmp[i]->getSize(1); k++)
			{
				tmp->setEle(j, k, beta_tmp[i]->getEle(0, k));
			}
		}

		y_tmp2_.push_back(tmp);
	}
//	y_tmp2_[0]->print();
//	y_tmp2_[1]->print();
//	y_tmp2_[2]->print();
//	y_tmp2_[3]->print();

	for (unsigned int i = 0; i < beta_tmp.size(); i++)
	{
		beta_tmp[i]->freeArray(beta_tmp[i]);
	}

	vector<array*> y_tmp2;

	for (unsigned int i = 0; i < y_tmp2_.size(); i++)
	{
		tmp = new array(2, size);
		y_tmp2_[i]->dotMul(y_tmp[i], tmp);
		y_tmp2.push_back(tmp);
	}
//	y_tmp2[0]->print();
//	y_tmp2[1]->print();
//	y_tmp2[2]->print();
//	y_tmp2[3]->print();

	for (unsigned int i = 0; i < y_tmp2_.size(); i++)
	{
		y_tmp2_[i]->freeArray(y_tmp2_[i]);
		y_tmp[i]->freeArray(y_tmp[i]);
	}

	size[0] = out->getSize(1)+1;
	struct_tmp.expData = new array(2, size);

	for (int j = 0; j < y_tmp2[0]->getSize(1); j++)
	{
		struct_tmp.expData->setEle(0, j, x->getEle(0, j));
	}

	for (int i = 0; i < y_tmp2[0]->getSize(0); i++)
	{
		for (int j = 0; j < y_tmp2[0]->getSize(1); j++)
		{
			double val = 0.0;
			for (unsigned int k = 0; k < y_tmp2.size(); k++)
			{
				val += y_tmp2[k]->getEle(i, j);
			}
			struct_tmp.expData->setEle(i+1, j, val);
		}
	}
	//struct_tmp.expData->print();

	for (unsigned int i = 0; i < y_tmp2.size(); i++)
	{
		y_tmp2[i]->freeArray(y_tmp2[i]);
	}

	vector<vector<array*> > Sigma_y_tmp;
	vector<array*> vect_tmp;

	for (int i = 0; i < nbStates; i++)
	{
		size[0] = out->getSize(1);
		size[1] = 1;
		array* Sigma2 = new array(2, size);

		size[0] = out->getSize(1);
		size[1] = out->getSize(1);
		tmp = new array(2, size);

		size[0] = 1;
		size[1] = out->getSize(1);
		tmp2 = new array(2, size);

		for (int j = 0; j < tmp->getSize(0); j++)
		{
			for (int k = 0; k < tmp->getSize(1); k++)
			{
				tmp->setEle(j, k, EM_init_S.Sigma[i]->getEle(out->getEle(0, j), out->getEle(0, k)));
			}
		}

		for (int j = 0; j < out->getSize(1); j++)
		{
			Sigma2->setEle(j, 0, EM_init_S.Sigma[i]->getEle(out->getEle(0, j), in));
		}
		Sigma2->mul(1/EM_init_S.Sigma[i]->getEle(in, in));
		//Sigma2->print();

		for (int j = 0; j < out->getSize(1); j++)
		{
			tmp2->setEle(0, j, EM_init_S.Sigma[i]->getEle(in, out->getEle(0, j)));
		}
		//tmp2->print();

		Sigma2->mul(tmp2);
		tmp->sub(Sigma2);

		vect_tmp.push_back(tmp);

		tmp2->freeArray(tmp2);
		Sigma2->freeArray(Sigma2);
	}
	Sigma_y_tmp.push_back(vect_tmp);

//	Sigma_y_tmp[0][0]->print();
//	Sigma_y_tmp[0][1]->print();
//	Sigma_y_tmp[0][2]->print();
//	Sigma_y_tmp[0][3]->print();

	vector<vector<array*> > Sigma_y_tmp2;

	for (int j = 0; j < beta->getSize(0); j++)
	{
		vector<array*> vect_tmp;
		for (int i = 0; i < beta->getSize(1); i++)
		{
			size[0] = out->getSize(1);
			size[1] = out->getSize(1);
			tmp = new array(2, size, beta->getEle(j, i)*beta->getEle(j, i));
			tmp2 = new array(2, size);

			tmp->dotMul(Sigma_y_tmp[0][i], tmp2);
			tmp->freeArray(tmp);
			vect_tmp.push_back(tmp2);
		}
		Sigma_y_tmp2.push_back(vect_tmp);
	}
//	Sigma_y_tmp2[0][0]->print();
//	Sigma_y_tmp2[0][1]->print();
//	Sigma_y_tmp2[0][2]->print();
//	Sigma_y_tmp2[0][3]->print();
//	Sigma_y_tmp2[1][0]->print();
//	Sigma_y_tmp2[1][1]->print();
//	Sigma_y_tmp2[1][2]->print();
//	Sigma_y_tmp2[1][3]->print();

	for (unsigned int k = 0; k < Sigma_y_tmp2.size(); k++)
	{
		tmp = new array(2, size);
		for (int i = 0; i < Sigma_y_tmp2[0][0]->getSize(0); i++)
		{
			for (int j = 0; j < Sigma_y_tmp2[0][0]->getSize(1); j++)
			{
				double val = 0.0;
				for (unsigned int m = 0; m < Sigma_y_tmp2[0].size(); m++)
				{
					val += Sigma_y_tmp2[k][m]->getEle(i, j);
				}
				tmp->setEle(i, j, val);
			}
		}
		struct_tmp.expSigma.push_back(tmp);
	}
//	Sigma_y[0]->print();
//	Sigma_y[1]->print();
//	Sigma_y[2]->print();
//	Sigma_y[3]->print();

	for (unsigned int k = 0; k < Sigma_y_tmp2.size(); k++)
	{
		for (unsigned int m = 0; m < Sigma_y_tmp2[0].size(); m++)
		{
			Sigma_y_tmp2[k][m]->freeArray(Sigma_y_tmp2[k][m]);
		}
	}

	beta->freeArray(beta);
}

array* gaussPDFScaler(array* x, double Mu, double Sigma)
{
	int nbVar = x->getSize(0);
	int nbData = x->getSize(1);
	int size[2];

	size[0] = nbData;
	size[1] = 1;
	array* tmp1 = new array(2, size, Mu);
	array* tmp2 = new array(x);

	tmp2->transpose();
	tmp2->sub(tmp1);
	tmp1->update(tmp2);
	tmp2->mul(1.0/Sigma);

	size[0] = tmp2->getSize(0);
	size[1] = tmp2->getSize(1);
	array* tmp3 = new array(2, size);

	size[1] = 1;
	array* prob = new array(2, size);

	tmp2->dotMul(tmp1, tmp3);
	tmp3->sum1D(prob, 2);

	tmp1->freeArray(tmp1);
	tmp2->freeArray(tmp2);
	tmp3->freeArray(tmp3);

	prob->mul(-0.5);

	array* prob1 = new array(2, size);

	prob->expArr(prob1);
	prob->freeArray(prob);

	prob1->mul(1/sqrt(pow(2*3.14, nbVar) * (abs(Sigma) + 2.225073858507201e-308)));

	return prob1;
}

