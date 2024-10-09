#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

// Сравнение матриц (eq_matrix)
#define SUCCESS 1
#define FAILURE 0

// Результирующий код операций
#define OK 0
#define FAIL_1 1  // Ошибка, некорректная матрица;
#define FAIL_2 2
// Ошибка вычисления (несовпадающие размеры матриц; матрица, для
// которой нельзя провести вычисления и т. д.).

#include <math.h>

#include <cstring>
#include <iostream>  // директива препроцессора

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double **matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  // Default constructor
  S21Matrix();
  // Параметризированный конструктор с количеством строк и столбцов.
  S21Matrix(int rows, int cols);
  // Конструктор переноса
  S21Matrix(S21Matrix &&other);
  // Конструктор копирования
  S21Matrix(const S21Matrix &other);
  // Destructor
  ~S21Matrix();

  // Проверяет матрицы на равенство между собой
  bool EqMatrix(const S21Matrix &other);
  // Прибавляет вторую матрицу к текущей
  void SumMatrix(const S21Matrix &other);
  // Вычитает из текущей матрицы другую
  void SubMatrix(const S21Matrix &other);
  // Умножает текущую матрицу на число
  void MulNumber(const double num);
  // Умножает текущую матрицу на вторую
  void MulMatrix(const S21Matrix &other);
  // Вычисляет и возвращает определитель текущей матрицы.
  double Determinant();
  // Создает новую транспонированную матрицу из текущей и возвращает ее.
  S21Matrix Transpose();
  // Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает
  // ее
  S21Matrix CalcComplements();
  // Вычисляет и возвращает обратную матрицу.
  S21Matrix InverseMatrix();
};

#endif  // s21_matrix_oop_H