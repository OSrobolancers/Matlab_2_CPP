#include <iostream>
#include <fstream>
#include <stdio.h>
#include "gnuplot.h"

using namespace std;

int main()
{
	//CMD commands for saving plot to files
	//system("cd C:\\Projects\\myProject\\INDEPENDENT\\MATLAB_2_C++\\GNUPLOT\\GnuPlotTrial3");
	//system("gnuplot -e \"set terminal png size 400,300; set output 'xyz.png'; plot 'data1_1.txt'\"");
	
	FILE* gp = popen("C:\\TOOLS\\GNUPLOT\\gnuplotPortable\\App\\gnuplot\\bin\\gnuplot.exe", "w");
	fprintf(gp, "cd 'C:\\Projects\\myProject\\INDEPENDENT\\MATLAB_2_C++\\GNUPLOT\\GnuPlotTrial3'");
//TODO: delete file output before fprintf this command
	fprintf(gp, "set terminal png size 400,300; set output 'xyz.png'; plot [-4:4] exp(-x**2 / 2)\n");
	fflush(gp);
	pclose(gp);
	
	//fprintf(gnuplot, "plot \'C:\\Projects\\myProject\\INDEPENDENT\\MATLAB_2_C++\\GNUPLOT\\GnuPlotTrial3\\data1_1x.txt\'\n");
	//fflush(gnuplot);
	
	//FILE* gp = popen("C:\\TOOLS\\GNUPLOT\\gnuplotPortable\\App\\gnuplot\\bin\\gnuplot.exe", "w");
	//gnuplot p;
	//p("set term postscript eps");
	//p("set output \"a.eps\" ");
	//fprintf(gp, "set terminal png size 400,300; set output 'xyz.png'; plot [-4:4] exp(-x**2 / 2)\n"); 
	//p("set terminal png size 400,300; set output 'xyz.png'; plot \"data1_1.txt\"");
	
	return 0;
}