#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

// Ошибки сравнение матриц (eq_matrix)
#define SUCCESS 1
#define FAILURE 0

// Результирующий код операций
#define OK 0
#define FAIL_1 1  // Некорректная матрица;
#define FAIL_2 2
// Вычисления (несовпадающие размеры матриц; матрица, для
// которой нельзя провести вычисления и т. д.).

#include <math.h>

#include <cstring>
#include <iostream>  // директива препроцессора

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(S21Matrix &&other);
  S21Matrix(const S21Matrix &other);
  ~S21Matrix();

  int getRows() const;
  int getCols() const;
  double **getMatrix() const;
  void setValue(int row, int col, double value);
  double getValue(int row, int col) const;

  bool operator==(const S21Matrix &other) const;
  bool EqMatrix(const S21Matrix &other) const;
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  double Determinant();
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
};

#endif  // s21_matrix_oop_H