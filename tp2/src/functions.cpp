#include "functions.h"

using namespace std;

double powerMethod(Matrix& B, Matrix& x0, int niters, Matrix& autovector){
	Matrix v(x0.n,x0.m);
	v = x0;
	//Matrix w(B.n, v.m);
	for (int i = 0; i < niters; ++i)
	{
		Matrix w = B*v;
		v = w/w.normVector();	
	}
	autovector = v;
	//V transpuesta
	Matrix vt = v.transpuesta();
	//vt*B*v
	Matrix bv = B*v;
	Matrix vtbv = vt * bv;
	
	//vt*v
	Matrix vvt = vt*v;

	//lamda
	double lamda = vtbv.mat[0][0]/vvt.mat[0][0];
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


void calculateK(Matrix& B, Matrix& x0, int k){
	for (int i = 0; i < k; ++i)
	{
		Matrix autovector(3,1);
		double lambda = powerMethod(B,x0,100,autovector);
		cout << "AUTOVALOR" << endl;
		cout << lambda << endl;
		cout << "AUTOVALOR" << endl;
		cout << autovector << endl;
		deflation(B, autovector,lambda);
	}
}