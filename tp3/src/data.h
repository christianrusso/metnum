#ifndef ___DATA___
#define ___DATA___
#include <fstream>
#include <iostream>
#include <istream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>


class Data {
public:

    Data();
    Data(std::ifstream &inputFile, std::ifstream &playersFile, std::ofstream &stream, int method, double entra_por, std::string arch_movs_arq);

    /* Funciones Publicas */
private:
  /* Variables Privadas */

  double x_goal, x_keeper;
  double y_keeper;
  double mu;
  double y_goal_left, y_goal_right;
  bool gameHasEnded;
  Matrix x_ball, y_ball, x_jug, y_jug;
  int current_time;
  int grado_actual_x;
  int grado_actual_y;
  int pos_grado_x;
  int pos_grado_y;
  int pos_grado_sig_x;
  int pos_grado_sig_y;

  //funciones privadas
  void setearParamsSimples(std::ifstream &inputFile);
  void leerJugadores(std::ifstream &playersFile);
  int leerNuevosDatos(std::ifstream &inputFile);
  double moverArquero(int method);
  double calcularMovimientoHacia(double there);
  double maxSpaceToGoal(double space);
  double min(double This, double That);
  int min(int This, int That);
  double max(double This, double That);
  double cuadradosMinimosQR(int gradoX, int gradoY);
  double cuadradosMinimosQRConEstimacion();
  double cuadradosMinimosQRGradoGradual();
  double cuadradosMinimosQRLimiteDeMuestras(int gradoX, int gradoY, int maxMuestras);

};

#endif //__DATA__
