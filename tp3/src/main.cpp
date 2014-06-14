
#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>

#include "Matrix.h"
#include "functions.h"
#include "data.h"

using namespace std;
//*+-+-+-+-+ PARA TESTS +-+-+-+-+
double buscarElCientoVeintiCinco(ifstream &inputFile){
  string line;
  string iniciales;
  getline(inputFile,iniciales);
  getline(inputFile,line);

  vector<string> param = split(line);

  if(param.size() != 2){
   if(inputFile.eof()){
     return -1;
   }
  cout << "Archivo inválido de entrada" << endl;
  exit(1);
  }
  while(!inputFile.eof()){
    double x = atof(param[0].c_str());
    if(Matrix::isZero(x-125)){
      double y = atof(param[1].c_str());
      return y;
    }
    getline(inputFile,line);
    param = split(line);
    if(param.size() !=2){
      return -1;
    }

    param = split(line);
  }
  //No encontró el 125, devolver -1
  return -1;
}
//*+-+-+-+-+  +-+-+-+-+

// Main Release
int main(int argc, char* argv[]) {
//Creamos los streams para leer archivos y se lo pasamos a una instancia nueva de la clase Data

  if (argc < 5) {
   cout << "Parametros: archivo_entrada archivo_jugadores archivo_salida metodo(0 o 1)\n";
   exit(1);
  }

  char* inFile = argv[1];
  char* playersFile = argv[2];
  char* outFile = argv[3];
  int method = atoi(argv[4]);

//*-+-+-+ PARA TEST +-+-+-+*  
  string inFile2 = inFile;
  ifstream inputFile_tmp(inFile);
  double entra_por = buscarElCientoVeintiCinco(inputFile_tmp);
  inputFile_tmp.close();
  //ARCHIVOS DE ESTADISTICA:
  std::vector<std::string> strs,strs2,strs3;
  boost::split(strs, inFile2 , boost::is_any_of("/"));
  string arch_inicial = strs[strs.size()-1];
  boost::split(strs2, arch_inicial , boost::is_any_of("."));
  string nombre_inicial = strs2[0];
  string arch_movs_arq = "estadisticas/"+nombre_inicial + ".movs";
//*-+-+-+-+-+-+-+-+-+-+-+*  

  ifstream inputFile(inFile);
  ifstream playersStream(playersFile);
  ofstream stream;
  stream.open(outFile);
  // ofstream timesLog;
  // timesLog.open(timesFile);
  // timesLog << "k \t samples \t personas \t tK \t tTodos \t tCentro \t hitsTodos \t hitsCentro \t" << endl;
  //crear los datos, calculando y guardando todo en una instancia de la clase Data
  Data datos(inputFile, playersStream, stream, method, entra_por, arch_movs_arq);

  // timesLog.close();
  stream.close();
  playersStream.close();
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


