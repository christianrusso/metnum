#define _USE_MATH_DEFINES

#include "Matrix.h"

#include <math.h>
#include "functions.h"
#include <istream>

using namespace std;


// Constructors
Matrix::Matrix() { this->n = 0; this->m = 0; }
Matrix::Matrix(int n, int m) { load(n, m, 0.0); }
Matrix::Matrix(int n, int m, double dvalue) { load(n, m, dvalue); }

void Matrix::load(int n, int m, double dvalue) {
    this->n = n;
    this->m = m;
    mat.resize(n);

    for (int i = 0; i < n; i++) {
        mat[i].resize(m);
        for (int j=0; j < m; j++) {
            mat[i][j] = dvalue;
        }
    }
}

Matrix::Matrix(int n, int m, double values[]) {
    this->n = n;
    this->m = m;
    mat.resize(n);
    int k = 0;
    for (int i = 0; i < n; i++) {
        mat[i].resize(m);
        for (int j = 0; j < m; j++) {
            mat[i][j] = values[k];
            k++;
        }
    }
}

Matrix::Matrix(char* pgmImage){
  //*-* Lee una imagen y la "aplasta" como vector traspuesto.
    ifstream ifs;

    char line [100], *ptr;
    ifs.open (pgmImage, std::ifstream::binary);

    ifs.getline(line,100,'\n');

    if((line[0]!='P') || line[1]!='5')
    {
        cout << "La imagen <" << pgmImage << "> no esta en el formato binario PGM 'P5'." << endl;
        //getch();
        exit(1);
    }

    string stringLine = line;
    vector<string> param = split(stringLine);
    unsigned int M;
    unsigned int N;
    if(param.size() == 1){
        ifs.getline(line,100,'\n');
        while(line[0]=='#') ifs.getline(line,100,'\n');

        M = strtol(line,&ptr,0);
        N = atoi(ptr);

        ifs.getline(line,100,'\n');
        unsigned int Q = strtol(line,&ptr,0);
    } else {
        M = atoi(param[1].c_str());
        N = atoi(param[2].c_str());
    }

    this->n = 1;
    this->m = M*N;
    mat.resize(n);
    mat[0].resize(m);

    unsigned char temp;
    for (int i = 0; i < N ; i++){
        for (int j = 0; j < M; j++){
            temp = ifs.get();
            mat[0][j + i*M] = (double)temp;
        }
    }

    ifs.close();
}



void Matrix::wipe() {
    n = 0;
    m = 0;
    mat.clear();
}

Matrix& Matrix::operator=(const Matrix &other) {
    n = other.n;
    m = other.m;
    mat.resize(other.n);

    for (int i = 0; i < other.n; i++) {
        mat[i].resize(other.m);
        for (int j = 0; j < other.m; j++) {
            mat[i][j] = other.mat[i][j];
        }
    }

    return *this;
}

std::ostream& operator<<(std::ostream& os, Matrix& obj) {
    for (int i = 0; i < obj.n; i++) {
        os << "[ ";
        for (int j = 0; j < obj.m; j++) {
            os << obj.get(i, j) << " ";
        }
        os << "]" << std::endl;
    }
    return os;
}

bool Matrix::operator==(const Matrix &other) {
    if (n != other.n || m != other.m) {
        return false;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (!isZero(mat[i][j] - other.mat[i][j])) {
                return false;
            }
        }
    }

    return true;
}

Matrix Matrix::operator+(const Matrix &other) {
    return add(other, true);
}

Matrix Matrix::operator-(const Matrix &other) {
    return add(other, false);
}

Matrix Matrix::add(const Matrix &other, bool isadd) {
    //TODO: Tirar excepcion si las dimensiones de las matrices no son iguales
    Matrix R(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < other.m; j++) {
            if (isadd) {
                R.mat[i][j] = mat[i][j] + other.mat[i][j];
            } else {
                double res = mat[i][j] - other.mat[i][j];
                if(isZero(res)) res = 0;
                R.mat[i][j] = res;
            }
        }
    }
    return R;
}

Matrix Matrix::operator*(const Matrix &other) {    
    //TODO: Tirar excepcion si this->m != other.n
    Matrix R(n, other.m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < other.m; j++) {
            for (int k = 0; k < other.n; k++)  {
                R.mat[i][j] += mat[i][k] * other.mat[k][j];
            }
        }
    }
    return R;
}

Matrix Matrix::operator*(const double c) {
    Matrix R = *this;
    for (int i=0; i < n; i++) {
        for (int j=0; j < m; j++) {
            R.mat[i][j] = R.mat[i][j] * c;
        }
    }
    return R;
}

Matrix Matrix::operator/(const double c) {
    Matrix R = *this;
    for (int i=0; i < n; i++) {
        for (int j=0; j < m; j++) {
            R.mat[i][j] = R.mat[i][j] / c;
        }
    }
    return R;
}

Matrix Matrix::operator^(const int c) {
    //TODO: Que tendria que dar si c es cero?
    Matrix R = *this;
    for (int i=0; i < c-1; i++) {
        R = R*R;
    }
    return R;
}

// Row operations
Matrix Matrix::row(int i) const {
    Matrix R(1, m);
    for (int j = 0; j < m; j++) {
        R.mat[0][j] = mat[i][j];
    }
    return R;
}

void Matrix::setRow(int i, Matrix& other) {
	if (other.m != m) {
		cout << "El vector fila pasado no tiene el mismo tamaño.";
		exit(1);
	}
	
    for (int j = 0; j < m; j++) {
        mat[i][j] = other.mat[0][j];
    }
}

void Matrix::setColumn(int j, Matrix& other) {
	if (other.n != n) {
		cout << "El vector columna pasado no tiene el mismo tamaño.";
		exit(1);
	}
		
    for (int i = 0; i < n; i++) {
        mat[i][j] = other.mat[i][0];
    }
}

void Matrix::addRow2Row(int i, int k, double c) {
    for (int j = 0; j < m; j++) {
        mat[i][j] = mat[i][j] + mat[k][j] * c;
    }
}

double Matrix::multiplyRowByVector(int i, Matrix& b) {
    double result = 0.0; 
    for (int j = 0; j < m; j++) {
        result += mat[i][j] * b.mat[j][0];
    }
    return result;
}

Matrix Matrix::col(int j) const {
    Matrix R(n, 1);
    for (int i = 0; i < n; i++) {
        R.mat[i][0] = mat[i][j];
    }
    return R;
}

Matrix Matrix::transpuesta(){
    Matrix R(m, n);
    for(int i=0;i<m;i++){
            for(int k=0;k<n;k++){
                R.mat[i][k] = mat[k][i];
            }
    }
    return R;
}

double Matrix::get(int i, int j) const {
    if(i>=n || j>=m){
        cout << "Get: No se puede acceder a una posicion inexistente" << endl;
        exit(1);
    }
    return mat[i][j];
}

void Matrix::set(int i, int j, double value){
    if(i>n || j>m){
        cout << "Set: No se puede escribir a una posicion inexistente" << endl;
        exit(1);
    }
    mat[i][j] = value;
}

double Matrix::normVector(){
    double r;
    if(m >= 1 && n == 1) {
        for (int i = 0; i < n; ++i)
		{
			r += mat[0][i]*mat[0][i];
		}
    } else if(n > 1 && m == 1) {
		for (int i = 0; i < n; ++i)
		{
			r += mat[i][0]*mat[i][0];
		}
	} else {
		cout << "No se puede calcular la norma de una matriz que no es un vector" << endl;
		exit(1);
	}
	
    
    return sqrt(r);
}

void Matrix::insertToVector(double val){
    if(m == 0 && n == 0){
        m++;
        std::vector<double> v(1,val);
        mat.push_back(v);
        n++;        
    } else if(m == 1 && n >= 1) {
        std::vector<double> v(1,val);
        mat.push_back(v);
        n++;
    } else if(n == 1 && m >= 1) {
        mat[0].push_back(val);
        m++;
    } else {
        cout << "No se puede insertar el elemento ya que no es un vector" << endl;
        exit(1);
    }
}

void Matrix::deleteFirstFromVector(){
    if(m == 0 && n == 0){
        cout << "No se puede eliminar un elemento ya que el vector esta vacio" << endl;
        exit(1);     
    } else if(m == 1 && n >= 1) {
        mat.erase(mat.begin());
        n--;
    } else if(n == 1 && m >= 1) {
        mat[0].erase(mat[0].begin());
        m--;
    } else {
        cout << "No se puede insertar el elemento ya que no es un vector" << endl;
        exit(1);
    }    
}


double Matrix::distance(Matrix& vector){
    if (vector.m != m) {
        cout << "El vector fila pasado no tiene el mismo tamaño.";
        exit(1);
    }
    if (n != 1) {
        cout << "La matriz no es un vector fila.";
        exit(1);
    }
    if (vector.n != 1) {
        cout << "La matriz parametro no es un vector fila.";
        exit(1);
    }

    double dist = 0;
    for (int i = 0; i < vector.m; ++i)
    {
        double diff = mat[0][i] - vector.get(0,i);
        dist += diff*diff;
    }
    return sqrt(dist);
}


Matrix Matrix::primerasKFilas(int k){
    Matrix B(k,this->m);
    for (int i = 0; i < k; ++i) {
        Matrix row = this->row(i);
        B.setRow(i,row);
    }
    return B;
}


Matrix Matrix::backwardSubstitution(Matrix& b){
    if(b.m != 1){
        cout << "BS:: X no es un vector columna" << endl;
        exit(1);
    }
    if(b.n != this->m){
        cout << "BS:: X no tiene el mismo tamaño de A" << endl;
        exit(1);
    }
    if(this->m > this->n){
        cout << "BS:: No se puede aplicar el metodo en una matriz con m > n" << endl;
        exit(1);
    }
    Matrix x (b);
    for (int i = this->m-1; i >= 0; i--) {
        //x[i] = b[i]; ya fue copiado
        double Xi = b.get(i,0);
        for (int j = this->m-1; j > i; j--)
        {
            Xi = Xi - this->get(i,j)*x.get(j,0);
        }
        Xi = Xi/this->get(i,i);
        x.set(i, 0, Xi);
    }
    return x;
}

void Matrix::identidad(){
    for (int i = 0; i < this->n; ++i)
    {
        for (int j = 0; j < this->m; ++j)
        {
            if(i == j){
                this->mat[i][j] = 1;
            }
        }
    }
}

bool Matrix::isZero(double number){
    return fabs(number) < 0.0000000000000001;
}