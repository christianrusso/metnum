#include "functions.h"

using namespace std;

double powerMethod(Matrix& B, Matrix& x0, int niters, Matrix& autovector){
	Matrix v;
	v = x0;
	Matrix w;
	for (int i = 0; i < niters; ++i)
	{
		//cout << "Ancho matriz " << B.m << " alto vector " << v.n << endl;
		w = B*v;
		//cout << "Ancho matriz " << B.m << " alto vector " << v.n << endl;
		v = w/(w.normVector());
	}
	autovector = v;
	//V transpuesta
	Matrix vt = v.transpuesta();
	//vt*B*v
	Matrix bv = B*v;
	Matrix vtbv = vt * bv;

	//vt*v
	Matrix vtv = vt*v;

	//lambda
	double lambda = vtbv.mat[0][0]/vtv.mat[0][0];
	
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


Matrix calculateK(Matrix& B, int k){
	int size = B.n;
	Matrix x0(B.m,1);
	Matrix autovector(size,1);

	Matrix autovectores(size,k);

	for (int i = 0; i < size; i++){
		x0.set(i,0, rand());
	}

	for (int i = 0; i < k; i++)
	{
		double lambda = powerMethod(B,x0,100,autovector);
		cout << "autovector " << autovector.n << " autovectores: " << autovectores.n << endl;
		cout << "Autovalor " << i << " : " << lambda << endl;
		deflation(B, autovector,lambda);
		autovectores.setColumn(k-1-i,autovector);
	}
	return autovectores;
}
