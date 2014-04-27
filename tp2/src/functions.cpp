#include "functions.h"

using namespace std;

double powerMethod(Matrix& B, Matrix& x0, int niters){
	Matrix v;
	v = x0;
	Matrix w;
	for (int i = 0; i < niters; ++i)
	{
		w = B*v;
		v = w/(w.normVector());
	}

	//V transpuesta
	Matrix vt = v.transpuesta();
	//vt*B*v
	Matrix bv = B*v;
	Matrix vtbv = vt * bv;
	
	//vt*v
	Matrix vtv = vt*v;

	//lambda
	double lambda = vtbv.mat[0][0]/vtv.mat[0][0];

	cout << "lambda: " << lambda << endl;
	cout << "autovector: " << v << endl;
	Matrix vLamda = v*lambda;
	cout << "lambda * v: " << endl << vLamda << endl;
	Matrix Bv = B*v;
	cout << "B*v:" << endl << Bv <<endl;

	return lambda;
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
