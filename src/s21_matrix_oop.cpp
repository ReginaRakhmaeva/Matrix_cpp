#include "s21_matrix_oop.h"
// конструктор
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows_ < 1 || cols_ < 1) {
    throw std::invalid_argument("Invalid matrix dimensions");
  }

  // Выделение памяти для матрицы
  matrix_ = new double*[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]();
  }
}
// деструктор
S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];  // Освобождаем память для каждой строки
  }
  delete[] matrix_;  // Освобождаем память для массива указателей
}

// // заполнение матриц для тестов
// void s21_fill_matrix_with_value(matrix_t *matrix, double value) {
//   for (int i = 0; i < matrix->rows; i++) {
//     for (int j = 0; j < matrix->columns; j++) {
//       matrix->matrix[i][j] = value;
//     }
//   }
// }
// // Создание матриц (create_matrix)
// int s21_create_matrix(int rows, int columns, matrix_t *result) {
//   int fl = OK;
//   if (rows < 1 || columns < 1 || result == NULL) {
//     fl = FAIL_1;
//   }
//   if (fl == OK) {
//     result->rows = rows;
//     result->columns = columns;
//     result->matrix = (double **)calloc(rows, sizeof(double *));
//     if (result->matrix == NULL) {
//       fl = FAIL_1;
//     }
//     for (int i = 0; i < rows; i++) {
//       result->matrix[i] = (double *)calloc(columns, sizeof(double));
//       if (result->matrix[i] == NULL) {
//         for (int j = 0; j < i; j++) {
//           free(result->matrix[j]);
//         }
//         free(result->matrix);
//         fl = FAIL_1;
//       }
//     }
//   }
//   return fl;
// }
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
