#include "functions.h"

using namespace std;

double powerMethod(Matrix& B, Matrix& x0, int niters){
	Matrix v(x0.n,x0.m);
	v = x0;
	Matrix w(B.n, v.m);
	for (int i = 0; i < niters; ++i)
	{
		w = B*v;
		v = w/w.normVector();
		cout << v << endl;
	}


	//V transpuesta
	Matrix vt(v.m,v.n);
	vt = v.transpuesta();
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

void deflation(Matrix& A, Matrix& v, float lambda){
	//Matrix A en R nxn
	// autovector v en R n de A con lambda autovector asociado
	int n = A.n;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			double nuevo = A.get(i,j) - lambda*v.get(i,0)*v.get(j,0);
			A.set(i,j, nuevo);
			}
		}
}

vector<string> split(string &line) {
	vector<string> res;
	char* strToken;

	strToken = strtok ((char*) line.c_str()," ");
  	while (strToken != NULL)	
	{
		if (strToken != NULL) { 
			string s(strToken);
			res.push_back(s);
		}
		strToken = strtok (NULL, " ");
	}	
	return res;
}
