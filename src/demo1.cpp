/*
 * demo1.cpp


 *
 *  Created on: Sep 29, 2020
 *      Author: oelkawok
 */

#include "kmeans.h"
#include "array.h"
#include "cov.h"
#include "EM_init_kmeans.h"
#include "EM_Func.h"
#include "GMR.h"

EM_Return_t EM_init_S;

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		cout<<"Error: command-line argument count mismatch.";
		return 1;
	}
	//Fetching number of clusters
	unsigned int K = atoi(argv[2]);

	//Open file for fetching points
	string filename = argv[1];
	ifstream infile(filename.c_str());

	if(!infile.is_open()){
		cout<<"Error: Failed to open file."<<endl;
		return 1;
	}

	//Fetching points from file
	int pointId = 1;
	vector<Point> all_points;
	string line;

	while(getline(infile, line)){
		Point point(pointId, line);
		all_points.push_back(point);
		pointId++;
	}
	infile.close();
	cout<<"\nData fetched successfully!"<<endl<<endl;

	//Return if number of clusters > number of points
	if(all_points.size() < K){
		cout<<"Error: Number of clusters greater than number of points."<<endl;
		return 1;
	}

	EM_init_kmeans(all_points, K);
	EM(all_points);

	int size[2];
	size[0] = 3;
	size[1] = all_points.size();
	array* Data = new array(2, size);

	for(unsigned int i = 0; i < all_points.size(); i++)
	{
		Data->setEle(T, i, all_points[i].getVal(T));
		Data->setEle(X, i, all_points[i].getVal(X));
		Data->setEle(Y, i, all_points[i].getVal(Y));
	}

	double nbVar = 3;

	size[0] = nbVar;
	size[1] = 1;
	array* tmp = new array(Data->minRow(0), Data->maxRow(0), 100);
	array* tmp2 = new array(1, nbVar-1);

	//tmp->print();

	GMR(tmp, 1-1, tmp2);

	struct_tmp.expData->print();

	struct_tmp.expSigma[0]->print();
	struct_tmp.expSigma[1]->print();
	struct_tmp.expSigma[2]->print();
	struct_tmp.expSigma[3]->print();







	//struct_tmp

	tmp->freeArray(tmp);
	tmp2->freeArray(tmp2);

	return 0;
}


