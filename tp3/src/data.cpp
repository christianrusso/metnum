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
  double keeper_movement;
  while(!inputFile.eof()){
    leerNuevosDatos(inputFile);
    double keeper_movement = moverArquero(method);
    //cout << "voy a imprimir: " << keeper_movement << endl;
    stream << keeper_movement << endl;
    current_time++;
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
  current_time = 0;

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
  } if(method == 1) {
    if(current_time == 0) movement = calcularMovimientoHacia((y_goal_right - y_goal_left) / 2);
    else {
      movement = calcularMovimientoHacia(cuadradosMinimosQR());
    }
  } else if (method == 2){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion());
  } else if (method == 3){
    movement = calcularMovimientoHacia(cuadradosMinimosQRGradoGradual());
  } else if (method == 4){
    if(current_time == 0) movement = calcularMovimientoHacia((y_goal_right - y_goal_left) / 2);
    else {
      movement = calcularMovimientoHacia(cuadradosMinimosQRGradoUno());
    }
  } else {
    cout << "Hay tres metodos definido, utilizar los metodos: 0, 1 o 2 " << endl;
    exit(1);
  }
  y_keeper = y_keeper + movement;
  cout << "voy a imprimir: " << movement << endl;
  return movement;  
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
double Data::calcularMovimientoHacia(double there){
  //suponemos que dejando 4 de espacio entre el arquero y el palo la va a atajar igual
  double spaceToGoal = maxSpaceToGoal(6);
  double movement;
  if (Matrix::isZero(y_keeper - there)) return 0;
  if (there <= y_keeper){
    double max_movement = min(y_keeper - (y_goal_left + spaceToGoal), mu);
    movement = - min(y_keeper - there, max_movement);
  } else {
    double max_movement = min((y_goal_right - spaceToGoal) - y_keeper, mu);
    movement = min(there - y_keeper, max_movement);
  }
  return movement;
}

double Data::maxSpaceToGoal(double space){
  if (y_goal_right - y_goal_left < space) return (y_goal_right - y_goal_left) / 2;
  else return space;
}

double Data::min(double This, double That){
  return This <= That ? This : That;
}

int Data::min(int This, int That){
  return This <= That ? This : That;
}

double Data::max(double This, double That){
  return This >= That ? This : That;
}

double Data::cuadradosMinimosQR(){
  Matrix A = crearMatrixCuadradosMinimosConGrado(current_time,min(current_time,5)); //grado maximo 5
  Matrix x_const =  metodoQR(A, x_ball);
  Matrix y_const =  metodoQR(A, y_ball);

  //cout << "x const: " << endl << x_const << endl;
  //cout << "y const: " << endl << y_const << endl;

  double tiempo = enQueTiempoLlegaA(x_keeper, current_time, x_const);

  cout << "tiempo retornado " << tiempo << endl;
  if (tiempo == -1){
    return aQuePosicionLlegaEn(tiempo+1,y_const);
  } else {
    return aQuePosicionLlegaEn(current_time, y_const);
  } 
}

double Data::cuadradosMinimosQRConEstimacion(){
  int m = min(current_time,5);
  Matrix A = crearMatrixCuadradosMinimosConGrado(current_time + 1,m); //grado maximo 5
  //Agrego una linea mas que predice el futuro en 10 pasos
  for (int i = 0; i < m; ++i){
    A.set(current_time,i,pow(current_time + 10,(m-1)-i));
  }
  Matrix x = x_ball;
  Matrix y = y_ball;
  //la pelota va a estar atras del arco (x = 0 < 125) y en su centro
  x.insertToVector(0);
  y.insertToVector((y_goal_right - y_goal_left) / 2);
  Matrix x_const =  metodoQR(A, x );
  Matrix y_const =  metodoQR(A, y );

  //cout << "x const: " << endl << x_const << endl;
  //cout << "y const: " << endl << y_const << endl;

  double tiempo = enQueTiempoLlegaA(x_keeper, current_time, x);

  cout << "tiempo retornado " << tiempo << endl;
  if (tiempo == -1){
    return aQuePosicionLlegaEn(tiempo+1,y);
  } else {
    return aQuePosicionLlegaEn(current_time, y);
  } 
}

double Data::cuadradosMinimosQRGradoGradual(){
  if(current_time == 0){
    grado_actual_x = 1;
    grado_actual_y = 1;
    pos_grado_x = 0;
    pos_grado_y = 0;
    pos_grado_sig_x = 0;
    pos_grado_sig_y = 0;
    return ((y_goal_right - y_goal_left) / 2);
  } else {
    double x_ball_now = x_ball.get(current_time,0);
    double y_ball_now = y_ball.get(current_time,0);
    //si con el siguiente polinomio mejore la estimacion, cambio
    if (dist_euclidea(y_ball_now,pos_grado_y) > dist_euclidea(y_ball_now,pos_grado_sig_y)){
      grado_actual_y++;
      cout << "Aumento el grado del polinomio Y a: " << grado_actual_y << endl;
    }
    if (dist_euclidea(x_ball_now,pos_grado_x) > 100*dist_euclidea(x_ball_now,pos_grado_sig_x)){
      grado_actual_x++;
      cout << "Aumento el grado del polinomio X a: " << grado_actual_x << endl;
    }
    //calculos sobre x para el grado actual
    Matrix A = crearMatrixCuadradosMinimosConGrado(current_time+1,grado_actual_x+1);
    Matrix x_const =  metodoQR(A, x_ball);
    pos_grado_x = aQuePosicionLlegaEn(current_time+1,x_ball);
    double tiempo_meta = enQueTiempoLlegaA(x_keeper, current_time, x_const);
    //calculos sobre y para el grado actual
    if(grado_actual_x != grado_actual_y){
      A = crearMatrixCuadradosMinimosConGrado(current_time+1,grado_actual_y+1);
    }
    Matrix y_const =  metodoQR(A, y_ball);
    pos_grado_y = aQuePosicionLlegaEn(current_time+1,y_const);
    //calculos sobre x para el grado siguiente
    if (grado_actual_x+1 <= current_time) {
      if (grado_actual_y != grado_actual_x+1){
      A = crearMatrixCuadradosMinimosConGrado(current_time+1,grado_actual_x+2);
      }
      x_const =  metodoQR(A, x_ball);
      pos_grado_sig_x = aQuePosicionLlegaEn(current_time+1,x_const);
    } else {
      pos_grado_sig_x = pos_grado_x;
    }
    if (grado_actual_y+1 <= current_time) {
    //calculos sobre y para el grado siguiente
      if(grado_actual_x != grado_actual_y){
        A = crearMatrixCuadradosMinimosConGrado(current_time+1,grado_actual_y+2);
      }
      x_const =  metodoQR(A, y_ball); //lo piso total no se vuelve a utilizar
      pos_grado_y = aQuePosicionLlegaEn(current_time+1,x_const);
    } else {
      pos_grado_sig_y = pos_grado_y;
    }
    //devuelvo la posicion en la que estara la pelota en el tiempo calculado
    cout << "tiempo retornado " << tiempo_meta << endl;
    if (tiempo_meta == -1){
      return aQuePosicionLlegaEn(tiempo_meta+1,y_const);
    } else {
      return aQuePosicionLlegaEn(current_time, y_const);
    } 
  }
}

double Data::cuadradosMinimosQRGradoUno(){
  Matrix A = crearMatrixCuadradosMinimosConGrado(current_time,min(current_time,2)); //grado maximo 5
  Matrix x_const =  metodoQR(A, x_ball);
  Matrix y_const =  metodoQR(A, y_ball);
  //cout << "x_ball: " << x_ball << endl;
  // cout << "x const: " << endl << x_const << endl;
  // cout << "y_ball: " << y_ball << endl;
  // cout << "y const: " << endl << y_const << endl;

  double tiempo = enQueTiempoLlegaA(x_keeper, current_time, x_const);

  cout << "tiempo retornado " << tiempo << endl;
  if (tiempo == -1){
    return aQuePosicionLlegaEn(tiempo+1,y_const);
  } else {
    double pos = aQuePosicionLlegaEn(current_time, y_const);
    cout << "posicion en el tiempo futuro: " << pos << endl;
    return pos;
  } 
}