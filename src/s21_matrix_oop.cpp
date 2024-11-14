#include "s21_matrix_oop.h"

// Конструктор по умолчанию создает матрицу 1x1, заполненную 0
S21Matrix::S21Matrix() : rows_(1), cols_(1) {
  matrix_ = new double *[1];
  matrix_[0] = new double[1];
  matrix_[0][0] = 0.0;
}

// Параметризированный конструктор
S21Matrix::S21Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), matrix_(nullptr) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Rows and columns must be positive integers");
  }

  matrix_ = new double *[rows_]();
  try {
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_]();
    }
  } catch (...) {
    for (int k = 0; k < rows_; ++k) {
      if (matrix_[k] != nullptr) {
        delete[] matrix_[k];
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
    throw;
  }
}

// Конструктор переноса
S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
};

// Конструктор копирования
S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  matrix_ = new double *[rows_];
  try {
    for (int i = 0; i < rows_; ++i) {
      matrix_[i] = new double[cols_];
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  } catch (...) {
    for (int k = 0; k < rows_; ++k) {
      if (matrix_[k] != nullptr) {
        delete[] matrix_[k];
      }
    }
    delete[] matrix_;
    matrix_ = nullptr;
    throw;
  }
}

// Деструктор
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

// Индексация по элементам матрицы (строка, колонка)
double &S21Matrix::operator()(int i, int j) {
  CheckIndex(i, j);
  return matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  CheckIndex(i, j);
  return matrix_[i][j];
}

// Оператор присваивания
S21Matrix &S21Matrix::operator=(S21Matrix other) {
  this->swap(other);
  return *this;
}

void S21Matrix::swap(S21Matrix &other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

// для проверок входных данных
void S21Matrix::CheckDimensions(const S21Matrix &other,
                                const std::string &op) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices must have the same dimensions" + op);
  }
}

void S21Matrix::CheckCompatibility(const S21Matrix &other) const {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrices cannot be multiplied: incompatible dimensions.");
  }
}

void S21Matrix::CheckIndex(int i, int j) const {
  if (i >= rows_ || j >= cols_ || i < 0 || j < 0) {
    throw std::out_of_range("Matrix indices are out of range");
  }
}

void S21Matrix::CheckPositiveDimensions(const S21Matrix &other) const {
  if (rows_ <= 0 || cols_ <= 0 || other.rows_ <= 0 || other.cols_ <= 0) {
    throw std::invalid_argument("Matrices must have positive dimensions.");
  }
}

// равенство матриц
bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  CheckPositiveDimensions(other);
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }
  const double epsilon = 1e-7;  // Погрешность для сравнения значений
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (std::fabs((*this)(i, j) - other(i, j)) > epsilon) {
        return false;
      }
    }
  }
  return true;
};

bool S21Matrix::operator==(const S21Matrix &other) const {
  return EqMatrix(other);
}

// операции с умножением
S21Matrix S21Matrix::Multiply(const S21Matrix &other) const {
  CheckPositiveDimensions(other);
  CheckCompatibility(other);
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      result(i, j) = 0.0;
      for (int k = 0; k < cols_; ++k) {
        result(i, j) += (*this)(i, k) * other(k, j);
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

void S21Matrix::MulMatrix(const S21Matrix &other) { *this = Multiply(other); }

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      (*this)(i, j) *= num;
    }
  }
}

// сложение
S21Matrix S21Matrix::Sumtract(const S21Matrix &other) const {
  CheckDimensions(other, "addition");
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result(i, j) = (*this)(i, j) + other(i, j);
    }
  }
  return result;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  return Sumtract(other);
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  *this = Sumtract(other);
  return *this;
}

void S21Matrix::SumMatrix(const S21Matrix &other) { *this = Sumtract(other); }

// вычитание
S21Matrix S21Matrix::Subtract(const S21Matrix &other) const {
  CheckDimensions(other, "subtraction");
  S21Matrix result(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result(i, j) = (*this)(i, j) - other(i, j);
    }
  }
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  return Subtract(other);
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  *this = Subtract(other);
  return *this;
}

void S21Matrix::SubMatrix(const S21Matrix &other) { *this = Subtract(other); }

// транспонирование
S21Matrix S21Matrix::Transpose() const {
  S21Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      transposed(j, i) = (*this)(i, j);
    }
  }
  return transposed;
}
// определитель
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
// миноры
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
// матрица алгебраических дополнений
S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument(
        "Matrix must be square to calculate complements.");
  }
  S21Matrix complements(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor = this->GetMinor(i, j);
      double cofactor = (i + j) % 2 == 0 ? 1.0 : -1.0;
      complements(i, j) = cofactor * minor.Determinant();
    }
  }
  return complements;
}
// обратная матрица
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

// Accessors
int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }
double **S21Matrix::getMatrix() const { return matrix_; }

// Mutator для rows_
void S21Matrix::setRows(int new_rows) {
  if (new_rows <= 0) {
    throw std::invalid_argument("Row count must be a positive integer.");
  }
  if (new_rows != rows_) {
    copyDataToTempMatrix(new_rows, cols_);
  }
}

// Mutator для cols_
void S21Matrix::setCols(int new_cols) {
  if (new_cols <= 0) {
    throw std::invalid_argument("Column count must be a positive integer.");
  }
  if (new_cols != cols_) {
    copyDataToTempMatrix(rows_, new_cols);
  }
}

void S21Matrix::copyDataToTempMatrix(int new_rows, int new_cols) {
  S21Matrix temp(new_rows, new_cols);

  for (int i = 0; i < std::min(rows_, new_rows); ++i) {
    for (int j = 0; j < std::min(cols_, new_cols); ++j) {
      temp(i, j) = (*this)(i, j);
    }
  }

  *this = temp;
}
