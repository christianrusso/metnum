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
void elminarPrimerColumna(Matrix& sub, Matrix& subQt);
void agregarSubMatrix(Matrix& sub, Matrix& A, int i);



#endif
