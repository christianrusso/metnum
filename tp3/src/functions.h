#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include "Matrix.h"
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <fstream>

void init_time();
double get_time();
double powerMethod(Matrix& B, Matrix& x0, int niters, Matrix& autovector);
void deflation(Matrix& A, Matrix& v, float lambda);
Matrix calculateK(Matrix& B, int k, std::ofstream& stream, std::vector<double>& tK);
std::vector<std::string> split(std::string &line);
Matrix centrosDeMasa(Matrix& B, int samples, int subjects);
int whoIsIt(Matrix& M, Matrix& Subject, int samples);
Matrix metodoQR(Matrix& A, Matrix& b);
void factorizacionQR(Matrix& A,Matrix& Qt, Matrix& R);
void generarSubMatrix(Matrix& sub, Matrix& A, int i);
void triangularColumna(Matrix& sub, Matrix& subQt);
void agregarSubMatrix(Matrix& sub, Matrix& A, int i);
float aQuePosicionLlegaEn(float tiempo, Matrix C);
float enQueTiempoLlegaA(float pos,int time, Matrix C);
Matrix crearMatrixCuadradosMinimosConGrado(int n, int m);
void eliminacionGauss(Matrix& A, Matrix& resultados,Matrix& incognitas);
void obtenerIncognitas(Matrix& A, Matrix& resultados,Matrix& incognitas);
Matrix ecuacionesNormales(Matrix& A, Matrix& b);


#endif
