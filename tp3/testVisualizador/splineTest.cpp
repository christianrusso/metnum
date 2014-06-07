
#include <magnet/math/spline.hpp>
#include <fstream>
#include <magnet/color/transferFunction.hpp>
#include <iostream>
#include <string>

using namespace magnet::math;
using namespace std;

void splinear(int x0, int y0, int x1, int y1, int xf, int yf, string  archivo ){
	ofstream outputFile;
	outputFile.open(archivo);
	Spline spline;

	spline.addPoint(x0, y0);
	spline.addPoint(x1,y1); 
	spline.addPoint(xf, yf);
	outputFile << "375 315 385 4" << endl;
	double dist = (x0 - (xf-50))/20; 
  	for (int i = x0; i > 50; i = i - dist)
  	{
  		double y = spline(i);
  		outputFile << i << " " << y << endl;	
  	}

}


int main(int argc, char *argv[])
{
	for (int i = 0; i < 10; ++i)
	{
		string archivo = "cuadratica" + to_string(i);
		string final = ".tiro";
		archivo = archivo+final;
		int x0 = (rand()%150) + 160;
		int y0 = rand()%500;
		int x1 = (rand()%20) + 140;
		int y1 = rand()%500; 
		int xf = 125;
		int yf = (rand()%60)+315;

		splinear(x0,y0,x1,y1,xf,yf,archivo);
	}
	

	

}


