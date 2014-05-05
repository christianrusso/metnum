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
      img_height = atoi(param[1].c_str());
      img_width =	atoi(param[2].c_str());
      subjects =	atoi(param[3].c_str());
      samples = atoi(param[4].c_str());
      k =	atoi(param[5].c_str());
 	  }
    else {
		cout << "No se pudo abrir el archivo " << inFile << "\n";
		exit(1);
    }

	Matrix A(subjects*samples,img_width*img_height);
	Matrix Mu(1,img_width*img_height);

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
			Mu = Mu + imgAsTrasposedVector;

			A.setRow(i * samples + j, imgAsTrasposedVector);
		}
	}

	Mu = Mu/(subjects*samples);
	double rootOfN = sqrt(subjects*samples - 1);
	Matrix tmp (1, img_width*img_height);


	for (int i = 0; i < subjects*samples; ++i)
	{
		tmp = (A.row(i) - Mu)/rootOfN;
		A.setRow(i, tmp);
	}

	//Guardo una copia de la A original, ya que tiene todos los valores de las imagenes
	//que preciso para inicializar el algoritmo de decision mas tarde.
	Matrix At = A.transpuesta();
	Matrix B = At*A;
	Matrix autovectores = calculateK(B,k,stream);
	Matrix kPoints = A*autovectores; // size: subjects*samples X k;

	Matrix kCentros = centrosDeMasa(kPoints, samples, subjects);

	getline (inputFile,line);
    vector<string> param = split(line);
    int testImages = atoi(param[0].c_str());

    int assertionsDistance = 0;
    int assertionsDistanceToCentre = 0;

    for (int i = 0; i < testImages; ++i)
    {
    	getline (inputFile,line);
  		param = split(line);
    	strcpy(img_dir, param[0].c_str());
    	int whom = atoi(param[1].c_str());
    	
    	Matrix subject(img_dir);
	// Se le resta el Mu y se divide por la raiz de n-1 a la nueva muestra
    	subject = (subject - Mu)/rootOfN;
	// Se busca las coordenadas de la muestra en la base de autovectores
    	subject = subject * autovectores;

    	int dist = whoIsIt(kPoints, subject, samples);
    	int distCentre = whoIsIt(kCentros, subject, 1);

    	assertionsDistance += dist == whom;
    	assertionsDistanceToCentre += distCentre == whom;

    	cout << "Distancia           | Caso " << i << ", expected: " << whom << " actual: " << dist << endl;
    	cout << "Distancia al centro | Caso " << i << ", expected: " << whom << " actual: " << distCentre << endl;
    }

    cout << "Promedio distancia: " << assertionsDistance/testImages << " , distancia al centro: " << assertionsDistanceToCentre/testImages << endl;

	stream.close();
   	inputFile.close();

	return 0;
}
