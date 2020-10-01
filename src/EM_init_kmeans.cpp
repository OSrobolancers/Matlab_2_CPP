/*
 * EM_init_kmeans.cpp
 *
 *  Created on: Sep 29, 2020
 *      Author: oelkawok
 */
#include "EM_init_kmeans.h"


#define ITER_NUM 100

void EM_init_kmeans(vector<Point>& data, unsigned int nbStates)
{
	unsigned int i = 0;
	unsigned int j = 0;
	vector<vector<double> > onesMat;
	vector<vector<double> > tempMat;

	KMeans km(nbStates, ITER_NUM);

	int size[] = {(int)nbStates, 3};
	unsigned int nbVar = 3;

	km.run(data);

	EM_init_S.Mu = new array(2, size);
	//vector<array*> clusArr;

	for(j = 0; j < nbStates;j++)
	{
		for(i = 0;i < km.clusters.size(); i++)
		{
			(*EM_init_S.Mu->vectPtr)[j][T] = km.clusters[j].getCentroidByPos(T);
			(*EM_init_S.Mu->vectPtr)[j][X] = km.clusters[j].getCentroidByPos(X);
			(*EM_init_S.Mu->vectPtr)[j][Y] = km.clusters[j].getCentroidByPos(Y);
		}
	}

	array* tmp;

	size[0] = nbStates;
	size[1] = 1;
//	array* Priors = new array(2, size);

	size[0] = nbVar;
	size[1] = 1;

	array* diag = new array(2, size, 1.0);
	diag->diag();
	diag->mul(1e-5);
	int prSize[2];
	prSize[0] = 1;
	prSize[1] = (int)nbStates;
	EM_init_S.PriorArr = new array(1, prSize);
	for(i = 0; i < nbStates; i++)
	{
		EM_init_S.PriorArr->setEle(0, i, km.clusters[i].getSize());
		EM_init_S.Prior.push_back(km.clusters[i].getSize());
		size[0] = 2*km.clusters[i].getSize();
		size[1] = 3;

		tmp = new array(2, size, 0.0);

		for (j = 0; j < tmp->vectPtr->size(); j++)
		{
			tmp->setEle(j, T, km.clusters[i].points[j%km.clusters[i].getSize()].getVal(T));
			tmp->setEle(j, X, km.clusters[i].points[j%km.clusters[i].getSize()].getVal(X));
			tmp->setEle(j, Y, km.clusters[i].points[j%km.clusters[i].getSize()].getVal(Y));
		}

		tmp = cov(tmp);
		tmp->add(diag);
		EM_init_S.Sigma.push_back(tmp);

	}

	int sum = 0;
	for(i = 0;i < nbStates;i++)
	{
		sum += EM_init_S.Prior[i];
	}
	for(i = 0;i < nbStates;i++)
	{
		EM_init_S.Prior[i] = EM_init_S.Prior[i] / sum;
		(*EM_init_S.PriorArr->vectPtr)[0][i] = (*EM_init_S.PriorArr->vectPtr)[0][i] / sum;
	}
	for(i = 0;i < nbStates;i++)
	{
		cout<<"Proir["<<i<<"]: "<<EM_init_S.Prior[i]<<endl;
	}

//	Priors->print();
//
//	double sum = Priors->sum();
//cout << sum << endl;
//	for(i = 0; i < nbStates; i++)
//	{
//		Priors->setEle(i, 1, Priors->getEle(i, 1)/sum);
//	}
//
//	cout << endl << "Priors:" << endl;
//	Priors->print();








	cout << endl << "Mu:" << endl;
	EM_init_S.Mu->print();
	cout << "Sigma:" << endl;

	for(i = 0; i < nbStates; i++)
	{
		EM_init_S.Sigma[i]->print();
		cout << endl;
	}

	diag->freeArray(diag);
}


