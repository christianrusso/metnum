
#include "spline.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace magnet::math;
using namespace std;
string directorio = "./instancias/cuadraticas/";

void splinear(int x0, int y0, int x1, int y1, int xf, int yf, string  archivo ){
	ofstream outputFile;
	outputFile.open(archivo);
	Spline spline;

	spline.addPoint(x0, y0);
	spline.addPoint(x1,y1); 
	spline.addPoint(xf, yf);
	outputFile << "375 315 385 4" << endl;
	//Queremos que imprima 24 puntos.
	double dist_entre_puntos = x0/24; 
  	for (int i = 0; i < 24; i = i++){
  		double x = x0-i*dist_entre_puntos;
  		double y = spline(x0-i*dist_entre_puntos);
  		outputFile << x << " " << y;
  		if(i+1 < 24){ outputFile << endl;}
  	}
}


int main(int argc, char *argv[])
{
	for (int i = 0; i < 10; ++i)
	{
		string archivo = "cuadratica" + to_string(i);
		string final = ".tiro";
		archivo = directorio + archivo + final;
		int x0 = (rand()%150) + 400;
		int y0 = rand()%500;
		int x1 = (rand()%20) + 250;
		int y1 = rand()%500; 
		int xf = 125;
		int yf = (rand()%60)+315;

		splinear(x0,y0,x1,y1,xf,yf,archivo);
	}
	

	

}


