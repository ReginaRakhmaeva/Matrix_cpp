#include "s21_matrix_oop.h"

// Конструктор по умолчанию
S21Matrix::S21Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

// Параметризированный конструктор
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Rows and columns must be positive integers");
  }
  matrix_ = new double *[rows_];
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

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Matrices cannot be multiplied: incompatible dimensions.");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      result.matrix_[i][j] = 0.0;
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  return result;
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

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Matrices must have the same dimensions for addition.");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

// для тестов
int S21Matrix::getRows() const { return rows_; }
int S21Matrix::getCols() const { return cols_; }
double **S21Matrix::getMatrix() const { return matrix_; }
void S21Matrix::setValue(int row, int col, double value) {
  if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
    matrix_[row][col] = value;
  } else {
    throw std::out_of_range("Invalid matrix indices");
  }
}
double S21Matrix::getValue(int row, int col) const {
  if (row >= 0 && row < rows_ && col >= 0 && col < cols_) {
    return matrix_[row][col];
  } else {
    throw std::out_of_range("Invalid matrix indices");
  }
}

// // Очистка матриц(remove_matrix)
// void s21_remove_matrix(matrix_t *A) {
//   if (A != NULL && A->matrix != NULL) {
//     for (int i = 0; i < A->rows; i++) {
//       free(A->matrix[i]);
//     }
//     free(A->matrix);
//     A->matrix = NULL;
//     A->rows = 0;
//     A->columns = 0;
//   }
// }
// // Сравнение матриц (eq_matrix)
// int s21_eq_matrix(matrix_t *A, matrix_t *B) {
//   int fl = FAILURE;
//   if (A != NULL && B != NULL) {
//     if (A->rows == B->rows && A->columns == B->columns) {
//       fl = SUCCESS;
//       for (int i = 0; i < A->rows; i++) {
//         for (int j = 0; j < A->columns; j++) {
//           if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) fl = FAILURE;
//         }
//       }
//     }
//   }
//   return fl;
// }
// // Сложение (sum_matrix)
// int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
//   int fl = OK;
//   if (A == NULL || B == NULL || result == NULL)
//     fl = FAIL_1;
//   else if (A->rows != B->rows || A->columns != B->columns)
//     fl = FAIL_2;
//   if (fl == OK) {
//     fl = s21_create_matrix(A->rows, A->columns, result);
//     if (fl == OK) {
//       for (int i = 0; i < result->rows; i++) {
//         for (int j = 0; j < result->columns; j++) {
//           result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
//         }
//       }
//     }
//   }
//   return fl;
// }
// // вычитание матриц (sub_matrix)
// int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
//   int fl = OK;
//   if (A == NULL || B == NULL || result == NULL) {
//     fl = FAIL_1;
//   } else if (A->rows != B->rows || A->columns != B->columns)
//     fl = FAIL_2;
//   if (fl == OK) {
//     fl = s21_create_matrix(A->rows, A->columns, result);
//     if (fl == OK) {
//       for (int i = 0; i < result->rows; i++) {
//         for (int j = 0; j < result->columns; j++) {
//           result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
//         }
//       }
//     }
//   }
//   return fl;
// }
// // Умножение матрицы на число (mult_number)
// int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
//   int fl = OK;
//   if (A == NULL || result == NULL)
//     fl = FAIL_1;
//   else {
//     fl = s21_create_matrix(A->rows, A->columns, result);
//     if (fl == OK) {
//       for (int i = 0; i < result->rows; i++) {
//         for (int j = 0; j < result->columns; j++) {
//           result->matrix[i][j] = A->matrix[i][j] * number;
//         }
//       }
//     }
//   }
//   return fl;
// }
// // Умножение двух матриц (mult_matrix)
// int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
//   int fl = OK;
//   if (A == NULL || B == NULL || result == NULL)
//     fl = FAIL_1;
//   else if (A->columns != B->rows)
//     fl = FAIL_2;
//   if (fl == OK) {
//     fl = s21_create_matrix(A->rows, B->columns, result);
//     if (fl == OK) {
//       for (int i = 0; i < result->rows; i++) {
//         for (int j = 0; j < result->columns; j++) {
//           for (int k = 0; k < A->columns; k++) {
//             result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
//           }
//         }
//       }
//     }
//   }
//   return fl;
// }
// // Транспонирование матрицы (transpose)
// int s21_transpose(matrix_t *A, matrix_t *result) {
//   int fl = OK;
//   if (A == NULL || result == NULL)
//     fl = FAIL_1;
//   else {
//     fl = s21_create_matrix(A->columns, A->rows, result);
//     if (fl == OK) {
//       for (int i = 0; i < result->rows; i++) {
//         for (int j = 0; j < result->columns; j++) {
//           result->matrix[i][j] = A->matrix[j][i];
//         }
//       }
//     }
//   }
//   return fl;
// }

// int s21_minor(matrix_t *A, matrix_t *minor, int row_to_skip, int col_to_skip)
// {
//   int fl = s21_create_matrix(A->rows - 1, A->columns - 1, minor);
//   if (fl == OK) {
//     for (int row = 0, minor_row = 0; row < A->rows; row++) {
//       if (row == row_to_skip) continue;
//       for (int col = 0, minor_col = 0; col < A->columns; col++) {
//         if (col == col_to_skip) continue;
//         minor->matrix[minor_row][minor_col] = A->matrix[row][col];
//         minor_col++;
//       }
//       minor_row++;
//     }
//   }

//   return fl;
// }
// // Минор матрицы и матрица алгебраических дополнений (calc_complements)
// int s21_calc_complements(matrix_t *A, matrix_t *result) {
//   int fl = OK;
//   matrix_t minor;
//   if (A == NULL || result == NULL) {
//     fl = FAIL_1;
//   } else if (A->rows != A->columns) {
//     fl = FAIL_2;
//   } else {
//     fl = s21_create_matrix(A->rows, A->columns, result);
//     if (fl == OK) {
//       for (int i = 0; i < result->rows && fl == OK; i++) {
//         for (int j = 0; j < result->columns && fl == OK; j++) {
//           fl = s21_minor(A, &minor, i, j);
//           if (fl == OK) {
//             double minor_det = 0;
//             fl = s21_determinant(&minor, &minor_det);
//             if (fl == OK) {
//               result->matrix[i][j] = minor_det * ((i + j) % 2 == 0 ? 1 : -1);
//             }
//             s21_remove_matrix(&minor);
//           }
//         }
//       }
//     }
//   }
//   return fl;
// }

// // Определитель матрицы (determinant)
// int s21_determinant(matrix_t *A, double *result) {
//   int fl = OK;
//   if (A == NULL || A->rows < 1 || A->columns < 1) {
//     fl = FAIL_1;
//   } else if (A->rows != A->columns) {
//     fl = FAIL_2;
//   } else {
//     if (A->rows == 1) {
//       *result = A->matrix[0][0];
//     } else if (A->rows == 2) {
//       *result =
//           A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] *
//           A->matrix[1][0];
//     } else {
//       matrix_t minor;
//       int j = 0;
//       double det = 0;
//       while (j < A->columns && fl == OK) {
//         fl = s21_minor(A, &minor, 0, j);
//         if (fl == OK) {
//           double minor_det = 0;
//           fl = s21_determinant(&minor, &minor_det);
//           if (fl == OK)
//             det += A->matrix[0][j] * minor_det * ((j % 2 == 0) ? 1 : -1);
//           s21_remove_matrix(&minor);
//         }
//         j++;
//       }
//       if (fl == OK) {
//         *result = det;
//       }
//     }
//   }
//   return fl;
// }

// // Обратная матрица (inverse_matrix)
// int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
//   int fl = OK;
//   double det = 0;
//   matrix_t complements, transpose;

//   if (A == NULL || A->rows < 1 || A->columns < 1 || result == NULL) {
//     fl = FAIL_1;
//   } else if (A->rows != A->columns) {
//     fl = FAIL_2;
//   } else {
//     fl = s21_determinant(A, &det);
//   }

//   if (fl == OK && det != 0) {
//     fl = s21_calc_complements(A, &complements);
//     if (fl == OK) {
//       fl = s21_transpose(&complements, &transpose);
//     }
//     if (fl == OK) {
//       fl = s21_create_matrix(A->rows, A->columns, result);
//     }
//     if (fl == OK) {
//       for (int i = 0; i < transpose.rows; i++) {
//         for (int j = 0; j < transpose.columns; j++) {
//           result->matrix[i][j] = transpose.matrix[i][j] / det;
//         }
//       }
//     }
//   } else if (fl == OK && det == 0) {
//     fl = FAIL_2;
//   }
//   if (fl != FAIL_1 && fl != FAIL_2) {
//     s21_remove_matrix(&transpose);
//     s21_remove_matrix(&complements);
//   }

//   return fl;
// }
