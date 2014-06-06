
#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"
#include "functions.h"
#include "data.h"

using namespace std;
/*
// Main Release
int main(int argc, char* argv[]) {
//Creamos los streams para leer archivos y se lo pasamos a una instancia nueva de la clase Data

  if (argc < 4) {
   cout << "Parametros: archivo_entrada archivo_salida metodo(0 o 1)\n";
   exit(1);
  }

  char* inFile = argv[1];
  char* outFile = argv[2];
  int method = atoi(argv[3]);

	// char timesFile[strlen(inFile)+5];
	// strcpy(timesFile, outFile);
	// strcat(timesFile, ".times");

  // string line;
  // char img_dir[50];
  ifstream inputFile(inFile);
  ofstream stream;
  stream.open(outFile);
  // ofstream timesLog;
  // timesLog.open(timesFile);
  // timesLog << "k \t samples \t personas \t tK \t tTodos \t tCentro \t hitsTodos \t hitsCentro \t" << endl;
  //crear los datos, calculando y guardando todo en una instancia de la clase Data
  Data datos(inputFile, stream, method);

  // timesLog.close();
  stream.close();
  inputFile.close();


  //double value[] = {0.0,-3.0,4.0,4.0,0.0,2.0,-3.0,5.0,1.0,1.0,2.0,3.0};
  //Matrix A(4,3,value);

  //double value[] = {0.0,-3.0,4.0,4.0,0.0,2.0,-3.0,5.0,1.0};
  //Matrix A(3,3,value);


  //DESCOMENTAR PARA PROBAR ECUACIONES NORMALES
  //double value[] = {8.0,5.0,3.0,9.0,12.0,2.0,1.0,7.0,6.0,0.0,4.0,8.0,1.0,2.0,5.0,10.0,9.0,8.0,3.0,1.0,9.0,5.0,11.0,19.0,2.0};
  //Matrix A(5,5,value);
  //cout << "A" << endl;
  //cout << A << endl;
  //double value2[] = {3.0,2.0,1.0,3.0,2.4};
  //Matrix b(5,1,value2);
  //cout << "b" << endl;
  //cout << b << endl;
  //cout << "Resultado Ecuaciones normales" << endl;
  //Matrix result = ecuacionesNormales(A,b);
  //cout <<  result << endl;
  return 0;
}
*/

int main(int argc, char* argv[]) {
  Matrix b = Matrix();
  for (int i = 0; i < 50; ++i)
  {
    b.insertToVector(-2000+8568.34*i+1235*i*i + (rand() % 10000)/735);
  }

  Matrix A = crearMatrixCuadradosMinimosConGrado(50,3); //grado maximo 5
  Matrix x =  metodoQR(A, b);

  cout << x << endl;
}