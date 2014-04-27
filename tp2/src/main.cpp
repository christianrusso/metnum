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

using namespace std;

int img_hight;
int img_widht;
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
  	if (inputFile.is_open())  {
		/* Lee primer fila */
		getline (inputFile,line);
		vector<string> param = split(line);

		if (param.size() != 6) {
			cout << param.size();
			cout << "Archivo invalido entrada " << endl;
			exit(1);
		}
		
		strcpy(img_dir, param[0].c_str());
		img_hight = atoi(param[1].c_str());
		img_widht =	atoi(param[2].c_str());	
		subjects =	atoi(param[3].c_str());	
		samples = atoi(param[4].c_str());	
		k =	atoi(param[5].c_str());	
 	} else {
		cout << "No se pudo abrir el archivo " << inFile << "\n";
		exit(1);
	}

	Matrix A(subjects*samples,img_widht*img_hight);

	char img_file[50];
	/* Lee las p filas siguientes y guarda las imagenes en la matriz */
	for (int i=0; i < subjects; i++) {
		getline (inputFile,line);
		vector<string> param = split(line);

		if (param.size() != samples + 1) {
			cout << param.size();
			cout << "Archivo invalido entrada " << endl;
			exit(1);
		}

		strcpy(img_file, img_dir);
		strcat(img_file, param[0].c_str());

		for (int j = 0; j < samples; j++){
			char img[50];
			strcpy(img, img_file);
			strcat(img, param[j+1].c_str());
			strcat(img, ".pgm");

			Matrix imgAsTrasposedVector(img);

			A.setRow(i * samples + j, imgAsTrasposedVector);
		}
	} 

	//Guardo una copia de la A original, ya que tiene todos los valores de las imagenes
	//que preciso para inicializar el algoritmo de decision mas tarde.
	Matrix Acopy;
	Acopy = A;



   	inputFile.close();

	//Ejemplo 1 lamda1 = 6
	double value[3] = {1.0,0.0,0.0};
	Matrix x0(3,1, value);
	double valueB[9] = {4.0,-1.0,1.0,-1.0,3.0,-2.0,1.0,-2.0,3.0};
	Matrix B(3,3,valueB);
	powerMethod(B,x0,30);


	return 0;
}





// //Ejemplo 1 lamda1 = 6
// double value[3] = {1.0,0.0,0.0};
//    Matrix x0(3,1, value);
//    double valueB[9] = {4.0,-1.0,1.0,-1.0,3.0,-2.0,1.0,-2.0,3.0};
//    Matrix B(3,3,valueB);
//    powerMethod(B,x0,30);

//    //Ejemplo 1 lamda1 = 4
// double value[3] = {1.0,1.0,1.0};
//    Matrix x0(3,1, value);
//    double valueB[9] = {3.0,-1.0,0.0,-1.0,2.0,-1.0,0.0,-1.0,3.0};
//    Matrix B(3,3,valueB);
//    powerMethod(B,x0,30);
