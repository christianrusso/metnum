#include "functions.h"
#include <math.h>
#include <sys/time.h>


using namespace std;


double powerMethod(Matrix& B, Matrix& x0, int niters, Matrix& autovector){
	Matrix v;
	v = x0;
	Matrix w;
	int i;
	for (i = 0; i < niters; ++i)
	{
		w = B*v;
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


Matrix calculateK(Matrix& B, int k, ofstream& stream, std::vector<double>& tK){

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
		deflation(B, autovector,lambda);
		autovectores.setColumn(k-1-i,autovector);
 // Guardo el tiempo en calcular del primero al iesimo autovector
		stream.precision(10);
		stream << sqrt(lambda) << endl; // imprimo el lambda
	 // Reinicio el tiempo
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


/**********************************************************/
// TP3 //
/**********************************************************/

Matrix metodoQR(Matrix& A, Matrix& b) {
    if (A.n < A.m) {
        cout << "QR:: No se puede aplicar el metodo a una matriz con n < m" << endl;
        exit(1);
    }
    Matrix Qt(A.n,A.n);
    Matrix R(A.n,A.m);

    factorizacionQR(A,Qt, R);
    
    Matrix R1 = R.primerasKFilas(A.m);
    Matrix CD = Qt * b;
    Matrix C = CD.primerasKFilas(A.m);
    
    return R1.backwardSubstitution(C);
}


void factorizacionQR(Matrix& A,Matrix& Qt, Matrix& R) {
    R = A;
    Matrix square (A.n,A.n);
    Qt = square;
    Qt.identidad();

    
    for (int i = 0; i < A.m; ++i)
    {
        Matrix tmp(Qt.n,Qt.m);
        tmp.identidad();
        Matrix subR(R.n - i, R.m - i);
        Matrix subQt(Qt.n - i, Qt.m - i);
        subQt.identidad();
        if(subR.n > 1){
            generarSubMatrix(subR,R,i);
            triangularColumna(subR,subQt);
            agregarSubMatrix(subR,R,i);
            agregarSubMatrix(subQt,tmp,i);
        }
        Qt = tmp*Qt;
    }
}


void generarSubMatrix(Matrix& sub, Matrix& A, int i){
    int w = 0;
        for (int j = i; j < A.n; ++j)
        {
            int p = 0;
            for (int k = i; k < A.m; ++k)
            {
                
                sub.mat[w][p] = A.mat[j][k];
                p++;
            }
            w++;
        }           
}

void triangularColumna(Matrix& sub, Matrix& subQt){
    Matrix x(sub.n,1);
    Matrix y(sub.n,1);
    Matrix u(sub.n,1);
    for (int i = 0; i < x.n; ++i)
    {
        x.mat[i][0] = sub.mat[i][0];
    }

    y.mat[0][0] = x.normVector();
    u = x - y;
    double normaU;
    normaU = u.normVector();
    normaU = normaU * normaU;
    Matrix aux(u.n,u.m);
    Matrix uTranspuesto(u.m,u.n);
    uTranspuesto = u.transpuesta();
    aux = uTranspuesto * sub;
    Matrix aux2(sub.n,sub.n);
    aux2 = u*aux;
    double coeficiente = 2/normaU;
    
    sub = sub - (aux2*coeficiente);
    
   
   //CALCULOS PARA Qt_t

    aux = uTranspuesto * subQt;
    aux2 = u*aux;
    subQt = subQt - (aux2 * coeficiente);

}

void agregarSubMatrix(Matrix& sub, Matrix& A, int i){
    int w = 0;
    for (int j = i; j < A.n; ++j)
    {
        int p = 0;
        for (int k = i; k < A.m; ++k)
        {
            A.mat[j][k] = sub.mat[w][p];
            p++;
        }
        w++;    
    }    
}          

float aQuePosicionLlegaEn(float tiempo, Matrix C){
	if(C.m != 1 ){
		cout << "No es un vector columna" << endl;
		exit(1);
	}
	float pos = 0;
	for (int i = 0; i < C.n; ++i)
	{
		//cout << "constant: " << C.get(i,0) << " time^something: " << pow(tiempo, (C.n -1) - i) <<  endl;
		pos += C.get(i,0) * pow(tiempo, (C.n -1) - i);
	}
	//cout << "llega a la posicion: " << pos << endl;
	return pos;
}

float enQueTiempoLlegaA(float pos,int time, Matrix C){
	cout << "Tiempo inicial: " << time << endl;
	int maxIter = time + 1000;
	float newPos;
	do{
		newPos = aQuePosicionLlegaEn(time, C);
		time++;
		//cout << newPos << endl;
	} while(time < maxIter && newPos > pos);
	//cout << "Tiempo final: " << time << endl;
	//cout << "Tiempo maximo: " << maxIter << endl;
	//cout << "Posicion final: " << newPos << endl;
	return newPos < pos ? time : -1;
}

Matrix crearMatrixCuadradosMinimosConGrado(int n, int m){
	Matrix A(n,m);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j)
		{
			A.set(i,j, pow(i,(m-1)-j));
			//cout << "pos i,j, i^(m-1-j) : " << i << j << A.get(i,j) << endl;
		}
	}
	return A;
}