
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

	char timesFile[strlen(inFile)+5];
	strcpy(timesFile, outFile);
	strcat(timesFile, ".times");

  string line;
  char img_dir[50];
  ifstream inputFile(inFile);
  ofstream stream;
  stream.open(outFile);
  ofstream timesLog;
  timesLog.open(timesFile);
  timesLog << "k \t samples \t personas \t tK \t tTodos \t tCentro \t hitsTodos \t hitsCentro \t" << endl;
  //crear los datos, calculando y guardando todo en una instancia de la clase Data
  Data datos(inputFile, stream, inFile, timesLog, method);

  timesLog.close();
  stream.close();
  inputFile.close();

  return 0;
}
