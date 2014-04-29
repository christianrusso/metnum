#ifndef _MATRIX_H_
#define _MATRIX_H_
#define _USE_MATH_DEFINES
#include <fstream>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h> 


class Matrix {
public:

    Matrix();
    Matrix(int n, int m);
    Matrix(int n, int m, double dvalue);
    Matrix(int n, int m, double values[]);
    Matrix(char* pgmImage);

    void load(int n, int m, double dvalue);
    void wipe();

    Matrix& operator=(const Matrix &other);
    bool operator==(const Matrix &other);

    friend std::ostream& operator<<(std::ostream& os, Matrix& obj);

    Matrix operator*(const Matrix &other);
    Matrix operator+(const Matrix &other);
    Matrix operator-(const Matrix &other);
    Matrix operator*(const double c);
    Matrix operator/(const double c);
    Matrix operator^(const int c);

    Matrix row(int i) const;
    Matrix col(int j) const;
    double get(int i, int j) const;
    void set(int i, int j, double dvalue);
    void transpose();
    bool invert();
    std::vector<double> diagonal() const;
    void setDiagonal();
    void setRow(int i, Matrix& other);
    void setColumn(int j, Matrix& other);
    double normVector();

    // Operaciones de triangulacion
    void addRow2Row(int i, int z, double c);
    double multiplyRowByVector(int i, Matrix& b);
    Matrix transpuesta();

    int n, m;
    std::vector<std::vector<double> > mat;
private:
    Matrix add(const Matrix &other, bool isadd);
};

#endif // _MATRIX_H_
