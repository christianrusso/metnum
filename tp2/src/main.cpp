
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

int img_height;
int img_width;
int subjects;
int samples;
int k;

// Main Release
int main(int argc, char* argv[]) {

	if (argc < 4) {
		cout << "Parametros: archivo_entrada archivo_salida metodo(0 o 1)\n";
		exit(1);
	}

	char* inFile = argv[1];
	char* outFile = argv[2];
	int method = atoi(argv[3]);

	string line;
	char img_dir[50];
	/* Valida que la estructura del archivo in sea la dada por la catedra */
  ifstream inputFile(inFile);
  ofstream stream;
  stream.open(outFile);
  //crear los datos, calculando y guardando todo en una instancia de la clase Data
  Data datos(inputFile, stream, inFile);


	stream.close();
  inputFile.close();

	return 0;
}
