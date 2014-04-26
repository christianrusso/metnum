#define _USE_MATH_DEFINES
#include <fstream>
#include <istream>
#include <iostream>
#include <vector>
#include <math.h>

#include "Matrix.cpp"

using namespace std;

double powerMethod(Matrix& B, Matrix& x0, int niters){
	cout << "B tam" << endl;
	cout << B.n << "x" << B.m <<endl;
	Matrix v;
	v = x0;
	cout << "V tam" << endl;
	cout << v.n << "x" << v.m <<endl;

	cout << "Bv" << endl;
	Matrix w = B*v;
	cout << w <<endl;
		
	Matrix T(w.n,w.m);

	T = transpuesta(w); 

	cout << T << endl;



	cout << "Bv Tam" << endl;
	cout << w.n << "x" << w.m <<endl;

}

// Main Release
int main(int argc, char* argv[]) {
	double value[3] = {1.1,1.2,1.3};
    Matrix x0(1,3, value);
    Matrix B(11,1,1.2);
    powerMethod(B,x0,10);
    return 0;
}




