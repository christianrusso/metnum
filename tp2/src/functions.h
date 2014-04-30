#ifndef _FUNCTIONS_
#define _FUNCTIONS_

#include "Matrix.h"
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <fstream>


double powerMethod(Matrix& B, Matrix& x0, int niters, Matrix& autovector);
void deflation(Matrix& A, Matrix& v, float lambda);
Matrix calculateK(Matrix& B, int k, std::ofstream& stream);
std::vector<std::string> split(std::string &line);

#endif
