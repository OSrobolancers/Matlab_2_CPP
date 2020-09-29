/*
 * readCSV.cpp
 *
 *  Created on: Sep 28, 2020
 *      Author: oelkawok
 */
#include "readCSV.h"

std::vector<Point> readcsv(std::string fileName) {
	std::vector<Point> points;
	std::string line;
	std::ifstream myFile(fileName.c_str());

    if (myFile.is_open())
    {
		while (getline(myFile, line)) {



			std::stringstream lineStream(line);
			std::string bit;
			double x, y;
			int idx;

			//TODO: replace stof with function made by samy
			getline(lineStream, bit, ',');
			idx = std::stof(bit);
			getline(lineStream, bit, ',');
			x = std::stof(bit);
			getline(lineStream, bit, '\n');
			y = std::stof(bit);

			points.push_back(Point(idx, x, y));
		}
	 }
	 else
	 {
		 std::cout<< "ERROR FILE NOT FOUND" <<std::endl;
	 }
    myFile.close();
    return points;
}

