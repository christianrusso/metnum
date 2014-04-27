#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h> 

#include "Matrix.h"
#include "functions.h"

using namespace std;

// Main Release
int main(int argc, char* argv[]) {
	// //Ejemplo 1 lamda1 = 6
	// double value[3] = {1.0,0.0,0.0};
 //    Matrix x0(3,1, value);
 //    double valueB[9] = {4.0,-1.0,1.0,-1.0,3.0,-2.0,1.0,-2.0,3.0};
 //    Matrix B(3,3,valueB);
 //    powerMethod(B,x0,30);

 //    //Ejemplo 1 lamda1 = 4
	// double value[3] = {1.0,1.0,1.0};
 //    Matrix x0(3,1, value);
 //    double valueB[9] = {3.0,-1.0,0.0,-1.0,2.0,-1.0,0.0,-1.0,3.0};
 //    Matrix B(3,3,valueB);
 //    powerMethod(B,x0,30);

	char fileName[] = "../data/big/s1/10.pgm";
	Matrix m(fileName);

	cout << "Imagen s1/10: " << endl << m << endl;

	return 0;
}




