#include "s21_matrix_oop.h"

// Конструктор по умолчанию
S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

// Параметризированный конструктор
S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Rows and columns must be positive integers");
  }
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

// Конструктор переноса
S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
};

// Конструктор копирования ??????
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
};

// Деструктор
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (matrix_[i][j] != other.matrix_[i][j]) {
        return false;
      }
    }
  }
  return true;
};

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for addition.");
  }
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[i][j] = this->matrix_[i][j] + other.matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::Multiply(const S21Matrix &other) const {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrices cannot be multiplied: incompatible dimensions.");
  }

  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      result.matrix_[i][j] = 0.0;
      for (int k = 0; k < cols_; ++k) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  return result;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  *this = Multiply(other);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  return Multiply(other);
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrices cannot be multiplied: incompatible dimensions.");
  }
  *this = Multiply(other);
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for addition.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for subtraction.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
  return *this;
}

// Оператор присваивания
S21Matrix &S21Matrix::operator=(S21Matrix other) {
  Swap(*this, other);
  return *this;
}

void Swap(S21Matrix &first, S21Matrix &second) {
  std::swap(first.rows_, second.rows_);
  std::swap(first.cols_, second.cols_);
  std::swap(first.matrix_, second.matrix_);
}

void S21Matrix::SumMatrix(const S21Matrix &other) { *this += other; }
void S21Matrix::SubMatrix(const S21Matrix &other) { *this -= other; }

void S21Matrix::CheckIndex(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Matrix indices are out of range");
  }
}

double &S21Matrix::operator()(int i, int j) {
  CheckIndex(i, j);
  return matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  CheckIndex(i, j);
  return matrix_[i][j];
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      transposed(j, i) = matrix_[i][j];
    }
  }
  return transposed;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate determinant.");
  }
  if (rows_ == 1) {
    return (*this)(0, 0);
  }
  if (rows_ == 2) {
    return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0);
  }
  double det = 0.0;
  for (int j = 0; j < cols_; ++j) {
    S21Matrix minor_matrix = GetMinor(0, j);
    double minor_det = minor_matrix.Determinant();
    double sign = (j % 2 == 0) ? 1.0 : -1.0;
    det += sign * (*this)(0, j) * minor_det;
  }

  return det;
}

S21Matrix S21Matrix::GetMinor(int row, int col) const {
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0, minor_i = 0; i < rows_; ++i) {
    if (i == row) continue;
    for (int j = 0, minor_j = 0; j < cols_; ++j) {
      if (j == col) continue;
      minor(minor_i, minor_j) = (*this)(i, j);
      ++minor_j;
    }
    ++minor_i;
  }
  return minor;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate complements.");
  }
  S21Matrix complements(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minor = this->GetMinor(i, j);
      double cofactor = (i + j) % 2 == 0 ? 1.0 : -1.0;
      complements(i, j) = cofactor * minor.Determinant();
    }
  }
  return complements;
}

S21Matrix S21Matrix::InverseMatrix() const {
  double det = this->Determinant();
  if (det == 0) {
    throw std::invalid_argument("Matrix is singular and cannot be inverted.");
  }
  S21Matrix complements = this->CalcComplements();
  S21Matrix transposedComplements = complements.Transpose();
  transposedComplements.MulNumber(1.0 / det);
  return transposedComplements;
}

// для тестов
int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }
double **S21Matrix::getMatrix() const { return matrix_; }
