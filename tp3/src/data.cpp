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

//////////////////////////////////////////////////////////////

// Constructors
Data::Data(){ }
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
Data::Data(ifstream &inputFile, ofstream &stream, char* inFile, std::ofstream &timesLog, int method){
  //Instancia la clase que sabe hacer todo con las imagenes

  setearParamsSimples(inputFile, inFile);
  importarImgs(inputFile);
  leerImagenesDeTest(inputFile);

  init_time();
  restarMuYHacerSqrt();
  kCommonTime = get_time();

  calcularAutovectores(stream, method); //este metodo caculas los tiempos de forma independiente

  //guardo los autovectores originales
  Matrix todosLosAutovectores = autovectores;
  for (kActual = 1; kActual <= k; kActual++){
    Matrix autovectoresK(todosLosAutovectores.n,kActual);
    for(int j = 0; j < kActual; j++){
      Matrix unAutovector = todosLosAutovectores.col(j);
      autovectoresK.setColumn(j,unAutovector);
    }
    //defino autovectores, con los primeros i de la matriz orignal
    autovectores = autovectoresK;

    init_time();
    calcularNuevasCoordenadas();
	  tTodos = get_time(); //solo necesito cambiar de coordenadas para comparar contra todos
	  calcularKCentrosDeMasa();
	  tCentro = get_time(); //para comparar con los centors tambien los debo calcular

    identificarSujetos();//este metodo guarda los tiempos de manera independiente en tTods y tCentro

    timesLog << kActual << "\t" << samples << "\t" << subjects << "\t";
    timesLog << (kCommonTime + tK[kActual-1] + kOnlyTransposedTime*kActual/k); //kOnlytransposedTime es cero en caso de utilizar el metodo de la matriz transpuesta, por lo que no afecta los calculos
    timesLog << "\t" << tTodos << "\t" << tCentro;
    timesLog << "\t"  <<  hitsTodos << "\t" << hitsCentro << "\t" << endl;
	}

}
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

//Funciones
//
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::leerImagenesDeTest(std::ifstream &inputFile){
  string line;
  getline (inputFile,line);
  vector<string> param = split(line);
  testSubjects = atoi(param[0].c_str());

  for (int i = 0; i < testSubjects; ++i)
  {
    getline (inputFile,line);
    param = split(line);
    strcpy(img_dir, param[0].c_str());
    int whom = atoi(param[1].c_str());
    testExpectedSubject.push_back(whom);
    Matrix subject(img_dir);
    testSubjectImg.push_back(subject);
  }
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::identificarSujetos(){
  hitsTodos = 0;
  hitsCentro = 0;

  for (int i = 0; i < testSubjects; ++i)
  {
    Matrix subject = testSubjectImg[i];
    int whom = testExpectedSubject[i];

	  double rootOfN = sqrt(subjects*samples - 1);
// Se le resta el Mu y se divide por la raiz de n-1 a la nueva muestra
  	init_time(); //empiezo a contar el tiempo
    subject = (subject - Mu)/rootOfN;

// Se busca las coordenadas de la muestra en la base de autovectores
  	subject = subject * autovectores;
    double processImage = get_time();
    tCentro += processImage;
    tTodos += processImage;

    init_time(); //empiezo a contar el tiempo
  	int dist = whoIsIt(kPoints, subject, samples);
    tTodos += get_time();

    init_time(); //empiezo a contar el tiempo
    int distCentre = whoIsIt(kCentros, subject, 1);
    tCentro += get_time();

  	hitsTodos += dist == whom ? 1 : 0;
  	hitsCentro += (distCentre == whom) ? 1 : 0;

  //	cout << "Distancia a todos   | Caso " << i+1 << ", expected: " << whom << " actual: " << dist << endl;
  //	cout << "Distancia al centro | Caso " << i+1 << ", expected: " << whom << " actual: " << distCentre << endl;
  }
  hitsTodos = hitsTodos/testSubjects;
  hitsCentro = hitsCentro/testSubjects;
  // cout << "Promedio distancia: " << assertionsDistance/testSubjects << " , distancia al centro: " << assertionsDistanceToCentre/testSubjects << endl;
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
  init_time();
  Matrix At = A_final.transpuesta();
  Matrix B;
	if(method == 0){
	  B = At*A_final;
	} else {
	  B = A_final*At;
	}
  kCommonTime += get_time();

	autovectores = calculateK(B,k,stream,tK);

  init_time();
  if(method == 1){
	  autovectores = At * autovectores;
      for (int i = 0; i < autovectores.m ; ++i){
		Matrix vector = autovectores.col(i); //agarro el vector
		vector = vector/vector.normVector(); //lo normalizo
		autovectores.setColumn(i, vector);
	  }
	}
  kOnlyTransposedTime = get_time();
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
