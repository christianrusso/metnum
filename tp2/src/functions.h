#ifndef _FUNCTIONS_
#define _FUNCTIONS_
#include "Matrix.h"

double powerMethod(Matrix& B, Matrix& x0, int niters);
void deflation(Matrix& A, Matrix& v, float lambda);

#endif
