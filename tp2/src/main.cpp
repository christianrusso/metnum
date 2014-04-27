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

	int db_size = subjects*samples;
	int img_size = img_widht*img_hight;

	Matrix A(db_size,img_size);
	Matrix Mu(1,img_size, 0.0);

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

			//inicializo A con las imagenes:
			A.setRow(i * samples + j, imgAsTrasposedVector);
			//sumo en Mu para sacar el promedio de cada pixel:
			Mu+imgAsTrasposedVector;
		}
	} 

	//Guardo una copia de la A original, ya que tiene todos los valores de las imagenes
	//que preciso para inicializar el algoritmo de decision mas tarde.
	Matrix Acopy;
	Acopy = A;

	//Calculo el promedio dividiendo la suma total por la cantidad de muestras:
	Mu/(db_size);

	double nRoot = sqrt(db_size-1); //TODO: mover esto a un metodo de matrix?
	for (int i = 0; i < db_size; i++){
		for (int j = 0; j < img_size; j++)
		{
			double tmp = (A.get(i,j) - Mu.get(0,j))/nRoot;
			A.set(i,j,tmp);
		}
	}

	//A ya esta inicializado correctamente para usarse


   	inputFile.close();
	return 0;
}




