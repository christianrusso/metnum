#ifndef ___DATA___
#define ___DATA___
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>


class Data {
public:

    Data();
    Data(std::ifstream &inputFile, std::ofstream &stream, char* inFile, std::ofstream &timesLog, int method);

    /* Funciones Publicas */
    const Matrix& getKCentros();
private:
  /* Variables Privadas */
  char img_dir[50];
  char img_file[50];
  int img_height, img_width;
  int subjects, samples, testSubjects;
  int k, kActual;
  double tTodos, tCentro, hitsTodos, hitsCentro;
  double kCommonTime, kOnlyTransposedTime;
  std::vector<double> tK;
  std::vector<int> testExpectedSubject;
  std::vector<Matrix> testSubjectImg;

  Matrix A_orig, Mu, A_final, autovectores, kPoints, kCentros;
  //funciones privadas
  void setearParamsSimples(std::ifstream &inputFile, char* inFile);
  void importarImgs(std::ifstream &inputFile);
  void leerImagenesDeTest(std::ifstream &inputFile);
  void restarMuYHacerSqrt();
  void calcularAutovectores(std::ofstream &stream, int method);
  void calcularNuevasCoordenadas();
  void calcularKCentrosDeMasa();
  void identificarSujetos();
};

#endif //__DATA__
