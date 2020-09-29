//============================================================================
// Name        : GMR_GMM_MAT2CPP.cpp
// Author      : me
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "readCSV.h"

std::vector<Point> vect;

int main() {
	vect = readcsv("C:\\Projects\\myProject\\INDEPENDENT\\MATLAB_2_C++\\GMM-GMR-v2.0\\data\\data1.csv");

	std::cout<< vect[0].idx << std::endl;
	std::cout<< vect[0].x << std::endl;
	std::cout<< vect[0].y << std::endl;

	return 0;
}
