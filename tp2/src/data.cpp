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

 #include <sys/time.h>
using namespace std;

timeval start, end;

void init_time()
{
     gettimeofday(&start,NULL);
}

double get_time()
{
     gettimeofday(&end,NULL);
     return
(1000000*(end.tv_sec-start.tv_sec)+(end.tv_usec-start.tv_usec))/1000000.0;
}
//////////////////////////////////////////////////////////////

// Constructors
Data::Data(){ }
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
Data::Data(ifstream &inputFile, ofstream &stream, char* inFile, std::ofstream &timesLog, int method){
  //Instancia la clase que sabe hacer todo con las imagenes

  setearParamsSimples(inputFile, inFile);
  importarImgs(inputFile);
  init_time();
  restarMuYHacerSqrt();
  
  calcularAutovectores(stream, method);
  for (int i = 1; i <= k; i++){
  
      calcularNuevasCoordenadas();

	  
	  tTraspasarEspacios = get_time();
	  
	  calcularKCentrosDeMasa();
	  identificarSujetos(inputFile);
	  tK = get_time();
	  tTraspasarEspacios = tk-get_time();
	}
  timesLog << k << "\t" << samples << "\t" << subjects << "\t" << tK << "\t" << tTraspasarEspacios << "\t" << tTodos << "\t" << tCentro << endl;
  
}
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

//Funciones
//

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::identificarSujetos(std::ifstream &inputFile){
  string line;
  getline (inputFile,line);
  vector<string> param = split(line);
  int testImages = atoi(param[0].c_str());

  double assertionsDistance = 0;
  double assertionsDistanceToCentre = 0;

  for (int i = 0; i < testImages; ++i)
  {
  	getline (inputFile,line);
    param = split(line);
  	strcpy(img_dir, param[0].c_str());
  	int whom = atoi(param[1].c_str());

  	Matrix subject(img_dir);
	double rootOfN = sqrt(subjects*samples - 1);
// Se le resta el Mu y se divide por la raiz de n-1 a la nueva muestra
  	subject = (subject - Mu)/rootOfN;

// Se busca las coordenadas de la muestra en la base de autovectores
  	subject = subject * autovectores;

  	int dist = whoIsIt(kPoints, subject, samples);
  	cout << "----------" << endl;
  	int distCentre = whoIsIt(kCentros, subject, 1);
	
  	assertionsDistance += dist == whom ? 1 : 0;
  	assertionsDistanceToCentre += (distCentre == whom) ? 1 : 0;

  	cout << "Distancia a todos   | Caso " << i+1 << ", expected: " << whom << " actual: " << dist << endl;
  	cout << "Distancia al centro | Caso " << i+1 << ", expected: " << whom << " actual: " << distCentre << endl;
  }

  cout << "Promedio distancia: " << assertionsDistance/testImages << " , distancia al centro: " << assertionsDistanceToCentre/testImages << endl;

}
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
const Matrix& Data::getKCentros(){
  return kCentros;
}
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::calcularKCentrosDeMasa(){
  //Calcula los K centros de masa
  kCentros = centrosDeMasa(kPoints, samples, subjects);
}
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::calcularNuevasCoordenadas(){
  //Setea en kPoints las nuevas coordenadas de las imagenes originales
	kPoints = A_final*autovectores; // size: subjects*samples X k;
}
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::calcularAutovectores(ofstream &stream, int method){
  Matrix At = A_final.transpuesta();
  Matrix B;
	if(method == 0){
	  B = At*A_final;
	} else {
	  B = A_final*At;
	}
	autovectores = calculateK(B,k,stream);
	if(method == 1){
	  autovectores = At * autovectores;
      for (int i = 0; i < autovectores.m ; ++i){
		Matrix vector = autovectores.col(i); //agarro el vector
		vector = vector/vector.normVector(); //lo normalizo
		autovectores.setColumn(i, vector);
	  }
	}

}
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::restarMuYHacerSqrt(){
  //Crea la matriz A_final que es la matriz A pero restado el vector Mu a cada
  //una de sus filas y además, dividida cada celda por la raiz cuadrada de n-1
	double rootOfN = sqrt(subjects*samples - 1);
	Matrix tmp (1, img_width*img_height);

	for (int i = 0; i < subjects*samples; ++i)
	{
		tmp = (A_final.row(i) - Mu)/rootOfN;
		A_final.setRow(i, tmp);
	}
}
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::importarImgs(std::ifstream &inputFile){
  //Lee todas las imagenes a las cuales hay que calcular los autovectores
  //y guarda las matrices correspondientes a A_orig, Mu y A_final (que hasta aca es igual 
  //a A_orig)
  this->A_orig = Matrix(subjects*samples, img_width*img_height);
  this->A_final = Matrix(subjects*samples, img_width*img_height);
  this->Mu = Matrix(1, img_width*img_height);

  /* Lee las p filas siguientes y guarda las imagenes en la matriz */
  string line;
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

			A_orig.setRow(i * samples + j, imgAsTrasposedVector);
			A_final.setRow(i * samples + j, imgAsTrasposedVector);
		}
	}

	Mu = Mu/(subjects*samples);
}
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::setearParamsSimples(ifstream &inputFile, char* inFile){
  // Setea las variables ints y el img_dir que es un char*
  // inFile solo es requerido para devolver el nombre del archivo en caso de error
  string line;
  if (inputFile.is_open())  {
    /* Lee primer fila */
    getline (inputFile,line);
    vector<string> param = split(line);

    if (param.size() != 6) {
      cout << param.size();
      cout << "Archivo invalido entrada " << endl;
      exit(1);
    }

    strcpy(this->img_dir, param[0].c_str());
    this->img_height = atoi(param[1].c_str());
    this->img_width =	atoi(param[2].c_str());
    this->subjects =	atoi(param[3].c_str());
    this->samples = atoi(param[4].c_str());
    this->k =	atoi(param[5].c_str());
 	}
  else {
	  cout << "No se pudo abrir el archivo " << inFile << "\n";
	  exit(1);
  }
}
