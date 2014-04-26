#include "functions.h"

using namespace std;

double powerMethod(Matrix& B, Matrix& x0, int niters){
	Matrix v(x0.n,x0.m);
	v = x0;
	Matrix w(B.n, v.m);
	for (int i = 0; i < niters; ++i)
	{
		w = B*v;
		v = w/normVector(w);
	}
	//V transpuesta
	Matrix vt(v.m,v.n);
	vt = transpuesta(v);
	//vt*B*v
	Matrix bv(B.n, v.m);
	bv = B*v;
	
	Matrix vtbv(vt.n, bv.m);
	vtbv = vt * bv;
	
	//vt*v
	Matrix vvt(v.n,vt.m);
	vvt = vt*v;

	//lamda
	double lamda = vtbv.mat[0][0]/vvt.mat[0][0];
	
	cout << "lamda: " << lamda << endl;
	
}