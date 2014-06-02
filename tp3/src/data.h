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
    Data(std::ifstream &inputFile, std::ofstream &stream, int method);

    /* Funciones Publicas */
private:
  /* Variables Privadas */

  double x_goal, x_keeper;
  double y_keeper;
  double mu;
  double y_goal_left, y_goal_right;
  bool gameHasEnd;
  Matrix x_ball, y_ball;

  //funciones privadas
  void setearParamsSimples(std::ifstream &inputFile);
  void leerNuevosDatos(std::ifstream &inputFile);
  double moverArquero(int method);
};

#endif //__DATA__
