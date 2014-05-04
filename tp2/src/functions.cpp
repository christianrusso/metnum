#include "functions.h"
#include <math.h>

using namespace std;

double powerMethod(Matrix& B, Matrix& x0, int niters, Matrix& autovector){
	Matrix v;
	v = x0;
	Matrix w;
	int i;
	for (i = 0; i < niters; ++i)
	{
		//cout << "Ancho matriz " << B.m << " alto vector " << v.n << endl;
		w = B*v;
		//cout << "Ancho matriz " << B.m << " alto vector " << v.n << endl;
		autovector = w/(w.normVector());
		if (autovector == v) break;
		v = autovector;
	}
	cout << "iteraciones utilizadas para el autovector: " << i << endl;
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


Matrix calculateK(Matrix& B, int k, ofstream& stream){
	int size = B.n;
	Matrix x0(B.m,1);
	Matrix autovector(size,1);

	Matrix autovectores(size,k);

	for (int i = 0; i < size; i++){
		x0.set(i,0, rand());
	}

	for (int i = 0; i < k; i++)
	{
		double lambda = powerMethod(B,x0,10000,autovector);
		stream.precision(10);
		stream << sqrt(lambda) << endl;
		deflation(B, autovector,lambda);
		autovectores.setColumn(k-1-i,autovector);
	}
	return autovectores;
}

Matrix centrosDeMasa(Matrix& B, int samples, int subjects){
	Matrix centros(subjects,B.m);

	Matrix aRow(1,B.m);

	for(int i = 0; i < subjects; i++){
		aRow = B.row(i*samples);
		for (int j = 1; j < samples; j++){
			aRow = aRow + B.row(i*samples + j);
		}
		aRow = aRow/samples;
		centros.setRow(i,aRow);
	}

	return centros;
}

int whoIsIt(Matrix& M, Matrix& Subject, int samples){
	int minIndex = 0;
	double minVal = M.row(0).distance(Subject);

	for (int i = 1; i < M.n; ++i)
	{
		double distance = M.row(i).distance(Subject);
		if(minVal > distance){
			minVal = distance;
			minIndex = i;
		}
	}

	return (minIndex/samples) + 1;
}
