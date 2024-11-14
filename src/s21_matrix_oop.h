#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <math.h>

#include <cstring>
#include <iostream>

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

  double &operator()(int i, int j);
  const double &operator()(int i, int j) const;

  S21Matrix &operator=(S21Matrix other);
  void swap(S21Matrix &other);

  int getRows() const;
  int getCols() const;
  double **getMatrix() const;
  void setCols(int new_cols);
  void setRows(int new_rows);
  void copyDataToTempMatrix(int new_rows, int new_cols);

  void CheckDimensions(const S21Matrix &other, const std::string &op) const;
  void CheckCompatibility(const S21Matrix &other) const;
  void CheckPositiveDimensions(const S21Matrix &other) const;
  void CheckIndex(int i, int j) const;

  bool operator==(const S21Matrix &other) const;
  bool EqMatrix(const S21Matrix &other) const;

  S21Matrix Sumtract(const S21Matrix &other) const;
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix &operator+=(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);

  S21Matrix Subtract(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix &operator-=(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);

  S21Matrix Multiply(const S21Matrix &other) const;
  S21Matrix operator*(const S21Matrix &other) const;
  S21Matrix &operator*=(const S21Matrix &other);
  void MulMatrix(const S21Matrix &other);
  void MulNumber(const double num);

  double Determinant() const;
  S21Matrix GetMinor(int row, int col) const;
  S21Matrix Transpose() const;
  S21Matrix CalcComplements() const;
  S21Matrix InverseMatrix() const;
};

#endif  // s21_matrix_oop_H