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
double dist_patada = 100;
// Constructors
//Data::Data(){ }
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
Data::Data(ifstream &inputFile, ifstream &playersFile, ofstream &stream, int method, double entra_por, string arch_movs_arq_gol, string arch_movs_arq_todos, string arch_movs_arq_estimacion){
//*-+-+-+-+ Para TESTS +-+-+-+-+*
      ofstream stream_movs_gol; stream_movs_gol.open(arch_movs_arq_gol.c_str());
      ofstream stream_movs_todos; stream_movs_todos.open(arch_movs_arq_todos.c_str());
      ofstream stream_movs_estimacion; stream_movs_estimacion.open(arch_movs_arq_estimacion.c_str());
//*-+-+-+-+ +-+-+-+-+*
  setearParamsSimples(inputFile);
  leerJugadores(playersFile);
  double keeper_movement;
  while(!inputFile.eof()){
    //Si al leer, la cantidad de parámetros es 0, pero el inputFile
    //apunta al eof, entonces el último caracter del archivo es el newline
    // y no debe hacer nada más.
    int termina_en_newline = leerNuevosDatos(inputFile);
    if(!termina_en_newline){
      double keeper_movement = moverArquero(method);
      //cout << "voy a imprimir: " << keeper_movement << endl;
      stream << keeper_movement;
//*-+-+-+-+ Para TESTS +-+-+-+-+*
      if(entra_por!=-1){
      // cout << "y_keeper " << y_keeper << " entra_por " << entra_por << endl;
      stream_movs_gol << (y_keeper-entra_por) << endl;
      }
      stream_movs_todos << (y_keeper-last_ball_y) << endl;
      stream_movs_estimacion << (entra_por-last_guess) << endl;
//*-+-+-+-+ +-+-+-+-+*

      if(!inputFile.eof()) stream << endl;
      current_time++;
    }
  }
//*-+-+-+-+ Para TESTS +-+-+-+-+*
      if(entra_por==-1) stream_movs_gol << "NO ESTÁ EL 125 EN LA ENTRADA";
      stream_movs_gol.close();
      stream_movs_todos.close();
      stream_movs_estimacion.close();
//*-+-+-+-+ +-+-+-+-+*
}

//Funciones
//
/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
void Data::setearParamsSimples(ifstream &inputFile){
  // Setea las variables ints y el img_dir que es un char*
  x_goal = 125;
  x_keeper = 125;
  gameHasEnded = false;
  x_ball = Matrix();
  y_ball = Matrix();
  x_jug = Matrix();
  y_jug = Matrix();
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
void Data::leerJugadores(std::ifstream &playersFile){
  while(true){
    string line;
    getline (playersFile,line);
    vector<string> param = split(line);

    if (param.size() != 2) {
      if(playersFile.eof()){
        return;
      }
      cout << param.size();
      cout << "Archivo invalido de jugadores en linea" << x_jug.n << endl;
      exit(1);
    }

    x_jug.insertToVector(atof(param[0].c_str()));
    y_jug.insertToVector(atof(param[1].c_str()));
  }
}


/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
int Data::leerNuevosDatos(std::ifstream &inputFile){
  //El return es para salvar el caso que termine el archivo en un newline
  string line;
  getline (inputFile,line);
  vector<string> param = split(line);

  if (param.size() != 2) {
    if(inputFile.eof()){
      return 1;
    }
    cout << param.size();
    cout << "Archivo invalido de entrada en linea" << x_ball.n << endl;
    exit(1);
  }
  double x = atof(param[0].c_str());
  double y = atof(param[1].c_str());

//*+-+-+-+-+ Para TESTEAR +-+-+-+-+
  last_ball_x = x;
  last_ball_y = y;
//*+-+-+-+-+ +-+-+-+-+
  bool haveToFlush = false;
  for (int i = 0; i < x_jug.n; ++i){
    // cout << "ADSFADSFADSFASDF" << endl;
    double dist_x = dist_euclidea(x,x_jug.get(i,0));
    double dist_y = dist_euclidea(y,y_jug.get(i,0));

    haveToFlush = haveToFlush || (max(dist_y,dist_x) <= dist_patada);
  }

  if(haveToFlush){
    x_ball = Matrix();
    y_ball = Matrix();
    current_time = 0;
    // cout << "FLUSH!!!!!!" << endl;
  }

  x_ball.insertToVector(x);
  y_ball.insertToVector(y);
  // cout << "La pelota esta en: " << param[0] << ", " << param[1] << endl;
  return 0;
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
double Data::moverArquero(int method){
  double movement = 0;
  if (method == 0) {
    double y_ball_actual = y_ball.get(y_ball.n - 1, 0);
    movement =calcularMovimientoHacia(y_ball_actual);
  } else if(method == 1) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(1,1));
  } else if(method == 2) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(1,2));
  } else if(method == 3) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(1,3));
  } else if(method == 4) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(1,4));
  } else if(method == 5) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(2,1));
  } else if(method == 6) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(3,1));
  } else if(method == 7) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(2,2));
  } else if(method == 8) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(3,3));
  } else if(method == 9) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(2,3));
  } else if(method == 10) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(3,2));
  } else if(method == 11) {
      movement = calcularMovimientoHacia(cuadradosMinimosQR(4,4));
  } else if (method == 12){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(1,1));
  } else if (method == 13){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(1,2));
  } else if (method == 14){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(1,3));
  } else if (method == 15){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(1,4));
  } else if (method == 16){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(2,1));
  } else if (method == 17){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(3,1));
  } else if (method == 18){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(2,2));
  } else if (method == 19){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(3,3));
  } else if (method == 19){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(2,3));
  } else if (method == 20){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(3,2));
  } else if (method == 21){
    movement = calcularMovimientoHacia(cuadradosMinimosQRConEstimacion(4,4));
  
  /*} else if (method == 15){
    movement = calcularMovimientoHacia(cuadradosMinimosQRLimiteDeMuestras(2,2,10));
  } else if (method == 16){
    movement = calcularMovimientoHacia(cuadradosMinimosQRLimiteDeMuestras(3,3,10));
  } else if (method == 17){
    movement = calcularMovimientoHacia(cuadradosMinimosQRLimiteDeMuestras(1,1,3));
  */} else{
    cout << "Hay tres metodos definido, utilizar los metodos: 0, 1 o 2 " << endl;
    cout << "Método utilizado: "<< method << endl;
    exit(1);
  }
  y_keeper = y_keeper + movement;
  // cout << "voy a imprimir: " << movement << endl;
  return movement;  
}

/*-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-*/
double Data::calcularMovimientoHacia(double there){
  //*+-+-+-+-+ Para TESTEAR +-+-+-+-+
  last_guess = there;
//*+-+-+-+-+ +-+-+-+-+
  //suponemos que dejando 4 de espacio entre el arquero y el palo la va a atajar igual
  double spaceToGoal = maxSpaceToGoal(6);
  double movement;
  // cout << "El arquero debe moverse hacia: " << there << endl;
  // cout << "Esta parado en: " << y_keeper << endl;
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

double Data::cuadradosMinimosQR(int gradoX, int gradoY){
  if(current_time == 0) return ((y_goal_right - y_goal_left) / 2) + y_goal_left;

  Matrix A = crearMatrixCuadradosMinimosConGrado(current_time,min(current_time,gradoX)); //grado maximo 5
  Matrix x_const =  metodoQR(A, x_ball);
  if (gradoX != gradoY) A = crearMatrixCuadradosMinimosConGrado(current_time,min(current_time,gradoY));
  Matrix y_const =  metodoQR(A, y_ball);

  //cout << "x const: " << endl << x_const << endl;
  //cout << "y const: " << endl << y_const << endl;

  double tiempo = enQueTiempoLlegaA(x_keeper, current_time, x_const);
  // cout << "Tiempo actual: " << current_time << endl;

  // cout << "tiempo retornado " << tiempo << endl;
  // cout << "------------------------"  << endl;
  if (tiempo == -1){
    return aQuePosicionLlegaEn(current_time+1,y_const);
  } else {
    return aQuePosicionLlegaEn(tiempo, y_const);
  } 
}

double Data::cuadradosMinimosQRConEstimacion(int gradoX, int gradoY){
  int m = min(current_time,gradoX);
  Matrix A = crearMatrixCuadradosMinimosConGrado(current_time +1,m); //grado maximo 5
  //Agrego una linea mas que predice el futuro en 10 pasos
  for (int i = 0; i < m; ++i){
    A.set(current_time,i,pow(current_time + 10,(m-1)-i));
  }
  Matrix x = x_ball;
  Matrix y = y_ball;
  //la pelota va a estar atras del arco (x = 0 < 125) y en su centro
  x.insertToVector(0);
  y.insertToVector(((y_goal_right - y_goal_left) / 2) + y_goal_left);
  Matrix x_const =  metodoQR(A, x );
  
  m = min(current_time,gradoY);
  A = crearMatrixCuadradosMinimosConGrado(current_time +1,m); //grado maximo 5
  //Agrego una linea mas que predice el futuro en 10 pasos
  for (int i = 0; i < m; ++i){
    A.set(current_time,i,pow(current_time + 10,(m-1)-i));
  }
  
  Matrix y_const =  metodoQR(A,y);

  //cout << "x const: " << endl << x_const << endl;
  //cout << "y const: " << endl << y_const << endl;

  double tiempo = enQueTiempoLlegaA(x_keeper, current_time, x);
  // cout << "tiempo retornado " << tiempo << endl;
  if (tiempo == -1){
    return aQuePosicionLlegaEn(current_time+1,y_const);
  }else {
    return aQuePosicionLlegaEn(tiempo, y_const);
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
    return (((y_goal_right - y_goal_left) / 2)+y_goal_left);
  } else {
    double x_ball_now = x_ball.get(current_time,0);
    double y_ball_now = y_ball.get(current_time,0);
    //si con el siguiente polinomio mejore la estimacion, cambio
    if (dist_euclidea(y_ball_now,pos_grado_y) > dist_euclidea(y_ball_now,pos_grado_sig_y)){
      grado_actual_y++;
      // cout << "Aumento el grado del polinomio Y a: " << grado_actual_y << endl;
    }
    if (dist_euclidea(x_ball_now,pos_grado_x) > 100*dist_euclidea(x_ball_now,pos_grado_sig_x)){
      grado_actual_x++;
      // cout << "Aumento el grado del polinomio X a: " << grado_actual_x << endl;
    }
    //calculos sobre x para el grado actual
    Matrix A = crearMatrixCuadradosMinimosConGrado(current_time,grado_actual_x);
    Matrix x_const =  metodoQR(A, x_ball);
    pos_grado_x = aQuePosicionLlegaEn(current_time+1,x_ball);
    double tiempo_meta = enQueTiempoLlegaA(x_keeper, current_time, x_const);
    //calculos sobre y para el grado actual
    if(grado_actual_x != grado_actual_y){
      A = crearMatrixCuadradosMinimosConGrado(current_time,grado_actual_y);
    }
    Matrix y_const =  metodoQR(A, y_ball);
    pos_grado_y = aQuePosicionLlegaEn(current_time+1,y_const);
    //calculos sobre x para el grado siguiente
    if (grado_actual_x+1 <= current_time) {
      if (grado_actual_y != grado_actual_x+1){
      A = crearMatrixCuadradosMinimosConGrado(current_time,grado_actual_x+1);
      }
      x_const =  metodoQR(A, x_ball);
      pos_grado_sig_x = aQuePosicionLlegaEn(current_time+1,x_const);
    } else {
      pos_grado_sig_x = pos_grado_x;
    }
    if (grado_actual_y+1 <= current_time) {
    //calculos sobre y para el grado siguiente
      if(grado_actual_x != grado_actual_y){
        A = crearMatrixCuadradosMinimosConGrado(current_time,grado_actual_y+1);
      }
      x_const =  metodoQR(A, y_ball); //lo piso total no se vuelve a utilizar
      pos_grado_y = aQuePosicionLlegaEn(current_time+1,x_const);
    } else {
      pos_grado_sig_y = pos_grado_y;
    }
    //devuelvo la posicion en la que estara la pelota en el tiempo calculado
    // cout << "tiempo retornado " << tiempo_meta << endl;
    if (tiempo_meta == -1){
      return aQuePosicionLlegaEn(current_time+1,y_const);
    } else {
      return aQuePosicionLlegaEn(tiempo_meta, y_const);
    } 
  }
}

double Data::cuadradosMinimosQRLimiteDeMuestras(int gradoX, int gradoY, int maxMuestras){
  if(current_time == 0) return ((y_goal_right - y_goal_left) / 2) + y_goal_left;
  int maxTime = current_time;
  if (x_ball.n == maxMuestras){
    current_time--;
    maxTime--;
    x_ball.deleteFirstFromVector();
    y_ball.deleteFirstFromVector();
  }

  Matrix A = crearMatrixCuadradosMinimosConGrado(maxTime,min(maxTime,gradoX)); //grado maximo 5

  Matrix x_const =  metodoQR(A, x_ball);

  if (gradoX != gradoY) A = crearMatrixCuadradosMinimosConGrado(maxTime,min(maxTime,gradoY));
  Matrix y_const =  metodoQR(A, y_ball);


  //cout << "x const: " << endl << x_const << endl;
  //cout << "y const: " << endl << y_const << endl;

  double tiempo = enQueTiempoLlegaA(x_keeper, maxTime, x_const);

  // cout << "tiempo retornado " << tiempo << endl;
  if (tiempo == -1){
    return aQuePosicionLlegaEn(maxTime+1,y_const);
  } else {
    return aQuePosicionLlegaEn(tiempo, y_const);
  } 
}
