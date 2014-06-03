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
//Data::Data(){ }
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
Data::Data(ifstream &inputFile, ofstream &stream, int method){
  setearParamsSimples(inputFile);
  double new_y_keeper;
  while(!inputFile.eof()){
    leerNuevosDatos(inputFile);
    double new_y_keeper = moverArquero(method);
    stream << new_y_keeper << endl;
  }


}
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/

//Funciones
//
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::setearParamsSimples(ifstream &inputFile){
  // Setea las variables ints y el img_dir que es un char*
  x_goal = 125;
  x_keeper = 125;
  gameHasEnd = false;
  x_ball = Matrix();
  y_ball = Matrix();

  string line;
  if (inputFile.peek() != char_traits<char>::eof())  {
    /* Lee primer fila */
    getline (inputFile,line);
    vector<string> param = split(line);

    if (param.size() != 4) {
      //cout << param.size();
      cout << "Archivo invalido entrada " << endl;
      exit(1);
    }
    this->y_keeper = atof(param[0].c_str());
    this->y_goal_left =	atof(param[1].c_str());
    this->y_goal_right =	atof(param[2].c_str());
    this->mu = atof(param[3].c_str());

    if (y_goal_left > y_goal_right){
        cout << "El arco tiene los limites invertidos" << endl;
        exit(1);
    }
    if (y_goal_left > y_keeper || y_keeper > y_goal_right) cout << "WARNING: el arquero arranco fuera de su puesto." << endl;
 	}
  else {
	  cout << "No se pudo abrir el archivo de entrada." << endl;
	  exit(1);
  }
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::leerNuevosDatos(std::ifstream &inputFile){
  string line;
  getline (inputFile,line);
  vector<string> param = split(line);

  if (param.size() != 2) {
    cout << param.size();
    cout << "Archivo invalido de entrada en linea" << x_ball.n << endl;
    exit(1);
  }

  x_ball.insertToVector(atof(param[0].c_str()));
  y_ball.insertToVector(atof(param[1].c_str()));
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
double Data::moverArquero(int method){
  double movement = 0;
  if (method == 0) {
    double y_ball_actual = y_ball.get(y_ball.n - 1,0);
    movement =calcularMovimientoHacia(y_ball_actual);
  } else {
    cout << "Hay un solo metodo definido, utilizar los metodos: 0 " << endl;
    exit(1);
  }
  y_keeper = y_keeper + movement;
  return movement;  
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
double Data::calcularMovimientoHacia(float there){
  //suponemos que dejando 4 de espacio entre el arquero y el palo la va a atajar igual
  double spaceToGoal = maxSpaceToGoal(4);
  double movement;
  if (Matrix::isZero(y_keeper - there)) return 0;
  if (there <= y_keeper){
    //TODO tomar en cuenta el radio de ataje
    double max_movement = min(y_keeper - (y_goal_left + spaceToGoal), mu);
    movement = - min(y_keeper - there, max_movement);
  } else {
    //TODO tomar en cuenta el radio de ataje
    double max_movement = min((y_goal_right - spaceToGoal) - y_keeper, mu);
    movement = min(there - y_keeper, max_movement);
  }
  return movement;
}

double Data::maxSpaceToGoal(double space){
  if (y_goal_right - y_goal_left < space) return (y_goal_right - y_goal_left) / 2;
  else return space;
}

double Data::min(float This, float That){
  return This <= That ? This : That;
}

double Data::max(float This, float That){
  return This >= That ? This : That;
}