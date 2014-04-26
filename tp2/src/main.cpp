#define _USE_MATH_DEFINES
#include <fstream>
#include <istream>
#include <iostream>
#include <vector>
#include <math.h>

#include "Matrix.cpp"

#include "functions.cpp"

using namespace std;


// Main Release
int main(int argc, char* argv[]) {
	//Ejemplo 1 lamda1 = 6
	double value[3] = {1.0,0.0,0.0};
    Matrix x0(3,1, value);
    double valueB[9] = {4.0,-1.0,1.0,-1.0,3.0,-2.0,1.0,-2.0,3.0};
    Matrix B(3,3,valueB);
    powerMethod(B,x0,30);

    //Ejemplo 1 lamda1 = 4
	double value[3] = {1.0,1.0,1.0};
    Matrix x0(3,1, value);
    double valueB[9] = {3.0,-1.0,0.0,-1.0,2.0,-1.0,0.0,-1.0,3.0};
    Matrix B(3,3,valueB);
    powerMethod(B,x0,30);

    return 0;
}




