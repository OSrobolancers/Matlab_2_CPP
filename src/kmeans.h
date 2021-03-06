/*
 * kmeans.h
 *
 *  Created on: Sep 29, 2020
 *      Author: oelkawok
 */

#ifndef KMEANS_H_
#define KMEANS_H_

#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

#define T 0
#define X 1
#define Y 2

class Point
{
private:
    int pointId, clusterId;
    int dimensions;
    vector<double> values;

public:

    Point(int id, string line);

    int getDimensions();

    int getCluster();

    int getID();

    void setCluster(int val);

    double getVal(int pos);

};

class Cluster{

private:
    int clusterId;
    vector<double> centroid;


public:
    vector<Point> points;

    Cluster(int clusterId, Point centroid);

    void addPoint(Point p);

    bool removePoint(int pointId);

    int getId();

    Point getPoint(int pos);

    int getSize();

    double getCentroidByPos(int pos);

    void setCentroidByPos(int pos, double val);
};

class KMeans{
private:
    int K, iters, dimensions, total_points;

    int getNearestClusterId(Point point);
public:
    vector<Cluster> clusters;
    KMeans(int K, int iterations);
    void run(vector<Point>& all_points);
    void getClusters(vector<Cluster>& _clusters);
};


#endif /* KMEANS_H_ */
