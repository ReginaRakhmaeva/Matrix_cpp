#include "tests.h"

// Тестирование конструктора по умолчанию
TEST(S21MatrixTest, DefaultConstructor) {
  S21Matrix m;
  EXPECT_EQ(m.getRows(), 1);
  EXPECT_EQ(m.getCols(), 1);
  EXPECT_DOUBLE_EQ(m(0, 0), 0.0);
}

// Тестирование параметризированного конструктора
TEST(S21MatrixTest, ParameterizedConstructor) {
  S21Matrix m(2, 3);
  EXPECT_EQ(m.getRows(), 2);
  EXPECT_EQ(m.getCols(), 3);
  EXPECT_NE(m.getMatrix(), nullptr);
  EXPECT_EQ(m(0, 0), 0.0);
}

// Тестирование конструктора копирования
TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix original(2, 3);
  original(0, 0) = 5.0;
  S21Matrix copy(original);
  EXPECT_EQ(copy.getRows(), 2);
  EXPECT_EQ(copy.getCols(), 3);
  EXPECT_EQ(copy(0, 0), 5.0);
}

// Тестирование конструктора перемещения
TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix original(2, 3);
  original(0, 0) = 5.0;
  S21Matrix moved(std::move(original));
  EXPECT_EQ(moved.getRows(), 2);
  EXPECT_EQ(moved.getCols(), 3);
  EXPECT_EQ(moved(0, 0), 5.0);
  EXPECT_EQ(original.getMatrix(), nullptr);
}

// Тестирование оператора сложения +
TEST(S21MatrixTest, OperatorPlus) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 1.123456;
  m1(0, 1) = 2.654321;
  m1(0, 2) = 3.999999;
  m1(1, 0) = 4.123456;
  m1(1, 1) = 5.654321;
  m1(1, 2) = 6.999999;
  m1(2, 0) = 7.123456;
  m1(2, 1) = 8.654321;
  m1(2, 2) = 9.999999;

  m2(0, 0) = 1.123456;
  m2(0, 1) = 2.654321;
  m2(0, 2) = 3.999999;
  m2(1, 0) = 4.123456;
  m2(1, 1) = 5.654321;
  m2(1, 2) = 6.999999;
  m2(2, 0) = 7.123456;
  m2(2, 1) = 8.654321;
  m2(2, 2) = 9.999999;

  S21Matrix result = m1 + m2;

  EXPECT_NEAR(result(0, 0), 2.246912, 1e-6);
  EXPECT_NEAR(result(0, 1), 5.308642, 1e-6);
  EXPECT_NEAR(result(0, 2), 7.999998, 1e-6);

  EXPECT_NEAR(result(1, 0), 8.246912, 1e-6);
  EXPECT_NEAR(result(1, 1), 11.308642, 1e-6);
  EXPECT_NEAR(result(1, 2), 13.999998, 1e-6);

  EXPECT_NEAR(result(2, 0), 14.246912, 1e-6);
  EXPECT_NEAR(result(2, 1), 17.308642, 1e-6);
  EXPECT_NEAR(result(2, 2), 19.999998, 1e-6);
}

TEST(S21MatrixTest, OperatorPlus_InvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);

  EXPECT_THROW(m1 + S21Matrix(0, 2), std::invalid_argument);
  EXPECT_THROW(m2 + S21Matrix(2, 0), std::invalid_argument);
}

TEST(S21MatrixTest, OperatorMinus_DifferentSizes) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);
  m1(0, 0) = 5.0;
  m1(0, 1) = 6.0;
  m1(1, 0) = 7.0;
  m1(1, 1) = 8.0;

  EXPECT_THROW(m1 - m2, std::invalid_argument);
}
// Тест оператора вычитания -
TEST(S21MatrixTest, OperatorMinus_Regular) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 1.123456;
  m1(0, 1) = 2.654321;
  m1(0, 2) = 3.999999;
  m1(1, 0) = 4.123456;
  m1(1, 1) = 5.654321;
  m1(1, 2) = 6.999999;
  m1(2, 0) = 7.123456;
  m1(2, 1) = 8.654321;
  m1(2, 2) = 9.999999;

  m2(0, 0) = 9.876543;
  m2(0, 1) = 8.123456;
  m2(0, 2) = 7.543210;
  m2(1, 0) = 6.987654;
  m2(1, 1) = 5.321098;
  m2(1, 2) = 4.210987;
  m2(2, 0) = 3.654321;
  m2(2, 1) = 2.123456;
  m2(2, 2) = 1.543210;

  S21Matrix result = m1 - m2;

  EXPECT_NEAR(result(0, 0), -8.753087, 1e-6);
  EXPECT_NEAR(result(0, 1), -5.469135, 1e-6);
  EXPECT_NEAR(result(0, 2), -3.543211, 1e-6);

  EXPECT_NEAR(result(1, 0), -2.864198, 1e-6);
  EXPECT_NEAR(result(1, 1), 0.333223, 1e-6);
  EXPECT_NEAR(result(1, 2), 2.789012, 1e-6);

  EXPECT_NEAR(result(2, 0), 3.469135, 1e-6);
  EXPECT_NEAR(result(2, 1), 6.530865, 1e-6);
  EXPECT_NEAR(result(2, 2), 8.456789, 1e-6);
}

TEST(S21MatrixTest, OperatorMinus_ZeroValues) {
  S21Matrix m3(2, 2);
  S21Matrix m4(2, 2);
  m3(0, 0) = 0.0;
  m3(0, 1) = 0.0;
  m4(0, 0) = 1.0;
  m4(0, 1) = 2.0;

  S21Matrix result2 = m3 - m4;

  EXPECT_EQ(result2(0, 0), -1.0);
  EXPECT_EQ(result2(0, 1), -2.0);
}

TEST(S21MatrixTest, OperatorMinus_InvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(2, 2);
  EXPECT_THROW(m1 - S21Matrix(0, 2), std::invalid_argument);
  EXPECT_THROW(m2 - S21Matrix(2, 0), std::invalid_argument);
}

// Тестирование оператора +=
TEST(S21MatrixTest, OperatorPlusEqual) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 1.123456;
  m1(0, 1) = 2.654321;
  m1(0, 2) = 3.999999;
  m1(1, 0) = 4.123456;
  m1(1, 1) = 5.654321;
  m1(1, 2) = 6.999999;
  m1(2, 0) = 7.123456;
  m1(2, 1) = 8.654321;
  m1(2, 2) = 9.999999;

  m2(0, 0) = 1.123456;
  m2(0, 1) = 2.654321;
  m2(0, 2) = 3.999999;
  m2(1, 0) = 4.123456;
  m2(1, 1) = 5.654321;
  m2(1, 2) = 6.999999;
  m2(2, 0) = 7.123456;
  m2(2, 1) = 8.654321;
  m2(2, 2) = 9.999999;

  m1 += m2;

  EXPECT_NEAR(m1(0, 0), 2.246912, 1e-6);
  EXPECT_NEAR(m1(0, 1), 5.308642, 1e-6);
  EXPECT_NEAR(m1(0, 2), 7.999998, 1e-6);

  EXPECT_NEAR(m1(1, 0), 8.246912, 1e-6);
  EXPECT_NEAR(m1(1, 1), 11.308642, 1e-6);
  EXPECT_NEAR(m1(1, 2), 13.999998, 1e-6);

  EXPECT_NEAR(m1(2, 0), 14.246912, 1e-6);
  EXPECT_NEAR(m1(2, 1), 17.308642, 1e-6);
  EXPECT_NEAR(m1(2, 2), 19.999998, 1e-6);
}

// Тестирование оператора -= для вычитания матриц
TEST(S21MatrixTest, SubtractMatrixAssign) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 1.123456;
  m1(0, 1) = 2.654321;
  m1(0, 2) = 3.999999;
  m1(1, 0) = 4.123456;
  m1(1, 1) = 5.654321;
  m1(1, 2) = 6.999999;
  m1(2, 0) = 7.123456;
  m1(2, 1) = 8.654321;
  m1(2, 2) = 9.999999;

  m2(0, 0) = 9.876543;
  m2(0, 1) = 8.123456;
  m2(0, 2) = 7.543210;
  m2(1, 0) = 6.987654;
  m2(1, 1) = 5.321098;
  m2(1, 2) = 4.210987;
  m2(2, 0) = 3.654321;
  m2(2, 1) = 2.123456;
  m2(2, 2) = 1.543210;

  m1 -= m2;

  EXPECT_NEAR(m1(0, 0), -8.753087, 1e-6);
  EXPECT_NEAR(m1(0, 1), -5.469135, 1e-6);
  EXPECT_NEAR(m1(0, 2), -3.543211, 1e-6);

  EXPECT_NEAR(m1(1, 0), -2.864198, 1e-6);
  EXPECT_NEAR(m1(1, 1), 0.333223, 1e-6);
  EXPECT_NEAR(m1(1, 2), 2.789012, 1e-6);

  EXPECT_NEAR(m1(2, 0), 3.469135, 1e-6);
  EXPECT_NEAR(m1(2, 1), 6.530865, 1e-6);
  EXPECT_NEAR(m1(2, 2), 8.456789, 1e-6);
}

TEST(S21MatrixTest, SubtractMatrixAssignInvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);

  EXPECT_THROW({ m1 -= m2; }, std::invalid_argument);
}

TEST(S21MatrixTest, OperatorMinusEqual_InvalidDimensions) {
  S21Matrix m1(2, 2);
  EXPECT_THROW(m1 -= S21Matrix(0, 2), std::invalid_argument);
  EXPECT_THROW(m1 -= S21Matrix(2, 0), std::invalid_argument);
}

// Тестирование оператора *= для умножения матриц
TEST(S21MatrixTest, MultiplyMatrixAssign) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  m1(0, 0) = 1.123456;
  m1(0, 1) = 2.654321;
  m1(0, 2) = 3.999999;
  m1(1, 0) = 4.123456;
  m1(1, 1) = 5.654321;
  m1(1, 2) = 6.999999;
  m1(2, 0) = 7.123456;
  m1(2, 1) = 8.654321;
  m1(2, 2) = 9.999999;

  m2(0, 0) = 1.123456;
  m2(0, 1) = 2.654321;
  m2(0, 2) = 3.999999;
  m2(1, 0) = 4.123456;
  m2(1, 1) = 5.654321;
  m2(1, 2) = 6.999999;
  m2(2, 0) = 7.123456;
  m2(2, 1) = 8.654321;
  m2(2, 2) = 9.999999;

  m1 *= m2;

  EXPECT_NEAR(m1(0, 0), 40.700946113, 1e-6);
  EXPECT_NEAR(m1(0, 1), 52.60767117, 1e-6);
  EXPECT_NEAR(m1(0, 2), 63.074053222, 1e-6);

  EXPECT_NEAR(m1(1, 0), 77.812050113, 1e-6);
  EXPECT_NEAR(m1(1, 1), 103.49656017, 1e-6);
  EXPECT_NEAR(m1(1, 2), 126.074044222, 1e-6);

  EXPECT_NEAR(m1(2, 0), 114.923154113, 1e-6);
  EXPECT_NEAR(m1(2, 1), 154.38544917, 1e-6);
  EXPECT_NEAR(m1(2, 2), 189.074035222, 1e-6);
}

TEST(S21MatrixTest, MultiplyMatrixAssignInvalidDimensions) {
  S21Matrix m1(2, 2);
  S21Matrix m2(3, 3);

  EXPECT_THROW({ m1 *= m2; }, std::invalid_argument);
}

// Проверка правильности присваивания
TEST(S21MatrixTest, AssignmentOperator) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(1, 1) = 2.0;

  S21Matrix m2(2, 2);
  m2 = m1;

  EXPECT_EQ(m2(0, 0), 1.0);
  EXPECT_EQ(m2(1, 1), 2.0);
}

// Проверка самоприсваивания
TEST(S21MatrixTest, SelfAssignment) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(1, 1) = 2.0;

  m1 = m1;

  EXPECT_EQ(m1(0, 0), 1.0);
  EXPECT_EQ(m1(1, 1), 2.0);
}

// Проверка корректности работы с динамической памятью
TEST(S21MatrixTest, AssignmentDifferentSizes) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.0;
  m1(1, 1) = 2.0;

  S21Matrix m2(3, 3);
  m2 = m1;

  EXPECT_EQ(m2.getRows(), 2);
  EXPECT_EQ(m2.getCols(), 2);
  EXPECT_EQ(m2(0, 0), 1.0);
  EXPECT_EQ(m2(1, 1), 2.0);
}

// Тестирование метода SumMatrix
TEST(S21MatrixTest, SumMatrixMethod) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 1.123456;
  m1(0, 1) = 2.654321;
  m1(0, 2) = 3.999999;
  m1(1, 0) = 4.123456;
  m1(1, 1) = 5.654321;
  m1(1, 2) = 6.999999;
  m1(2, 0) = 7.123456;
  m1(2, 1) = 8.654321;
  m1(2, 2) = 9.999999;

  m2(0, 0) = 1.123456;
  m2(0, 1) = 2.654321;
  m2(0, 2) = 3.999999;
  m2(1, 0) = 4.123456;
  m2(1, 1) = 5.654321;
  m2(1, 2) = 6.999999;
  m2(2, 0) = 7.123456;
  m2(2, 1) = 8.654321;
  m2(2, 2) = 9.999999;

  m1.SumMatrix(m2);

  EXPECT_NEAR(m1(0, 0), 2.246912, 1e-6);
  EXPECT_NEAR(m1(0, 1), 5.308642, 1e-6);
  EXPECT_NEAR(m1(0, 2), 7.999998, 1e-6);

  EXPECT_NEAR(m1(1, 0), 8.246912, 1e-6);
  EXPECT_NEAR(m1(1, 1), 11.308642, 1e-6);
  EXPECT_NEAR(m1(1, 2), 13.999998, 1e-6);

  EXPECT_NEAR(m1(2, 0), 14.246912, 1e-6);
  EXPECT_NEAR(m1(2, 1), 17.308642, 1e-6);
  EXPECT_NEAR(m1(2, 2), 19.999998, 1e-6);
}

// Тестирование метода SubMatrix
TEST(S21MatrixTest, SubMatrixMethod) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);
  m1(0, 0) = 1.123456;
  m1(0, 1) = 2.654321;
  m1(0, 2) = 3.999999;
  m1(1, 0) = 4.123456;
  m1(1, 1) = 5.654321;
  m1(1, 2) = 6.999999;
  m1(2, 0) = 7.123456;
  m1(2, 1) = 8.654321;
  m1(2, 2) = 9.999999;

  m2(0, 0) = 9.876543;
  m2(0, 1) = 8.123456;
  m2(0, 2) = 7.543210;
  m2(1, 0) = 6.987654;
  m2(1, 1) = 5.321098;
  m2(1, 2) = 4.210987;
  m2(2, 0) = 3.654321;
  m2(2, 1) = 2.123456;
  m2(2, 2) = 1.543210;

  m1.SubMatrix(m2);

  EXPECT_NEAR(m1(0, 0), -8.753087, 1e-6);
  EXPECT_NEAR(m1(0, 1), -5.469135, 1e-6);
  EXPECT_NEAR(m1(0, 2), -3.543211, 1e-6);

  EXPECT_NEAR(m1(1, 0), -2.864198, 1e-6);
  EXPECT_NEAR(m1(1, 1), 0.333223, 1e-6);
  EXPECT_NEAR(m1(1, 2), 2.789012, 1e-6);

  EXPECT_NEAR(m1(2, 0), 3.469135, 1e-6);
  EXPECT_NEAR(m1(2, 1), 6.530865, 1e-6);
  EXPECT_NEAR(m1(2, 2), 8.456789, 1e-6);
}

// Тестирование на выброс исключения при некорректных размерах
TEST(S21MatrixTest, InvalidConstructor) {
  EXPECT_THROW(S21Matrix(-1, 2), std::invalid_argument);
  EXPECT_THROW(S21Matrix(2, -1), std::invalid_argument);
}

// Тестирование деструктора
TEST(S21MatrixTest, DestructorTest) {
  S21Matrix *m = new S21Matrix(2, 2);
  delete m;
  SUCCEED();
}

// Тестирование метода EqMatrix
TEST(S21MatrixTest, EqMatrix_SameMatrices) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 5.0;
  matrix1(1, 2) = -3.0;
  S21Matrix matrix2(2, 3);
  matrix2(0, 0) = 5.0;
  matrix2(1, 2) = -3.0;
  EXPECT_TRUE(matrix1.EqMatrix(matrix2));
}

TEST(S21MatrixTest, EqMatrix_DifferentSizes) {
  S21Matrix matrix1(2, 3);
  S21Matrix matrix2(3, 2);
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

TEST(S21MatrixTest, EqMatrix_SameMatrixReference) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 2.0;
  matrix(2, 2) = 3.0;
  EXPECT_TRUE(matrix.EqMatrix(matrix));
}

TEST(S21MatrixTest, EqMatrix_DifferentElements) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 5.0;
  S21Matrix matrix2(2, 3);
  matrix2(0, 0) = 6.0;
  EXPECT_FALSE(matrix1.EqMatrix(matrix2));
}

// Тестирование перегруженного оператора сравнения ==
TEST(S21MatrixTest, OperatorEquals) {
  S21Matrix matrix1(2, 3);
  matrix1(0, 0) = 5.0;
  matrix1(1, 2) = 7.0;
  S21Matrix matrix2(2, 3);
  matrix2(0, 0) = 5.0;
  matrix2(1, 2) = 7.0;
  EXPECT_TRUE(matrix1 == matrix2);
  matrix2(1, 2) = 10.0;
  EXPECT_FALSE(matrix1 == matrix2);
}

// Тестирование оператора умножения *
TEST(S21MatrixTest, OperatorMultiply) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  m1(0, 0) = 1.123456;
  m1(0, 1) = 2.654321;
  m1(0, 2) = 3.999999;
  m1(1, 0) = 4.123456;
  m1(1, 1) = 5.654321;
  m1(1, 2) = 6.999999;
  m1(2, 0) = 7.123456;
  m1(2, 1) = 8.654321;
  m1(2, 2) = 9.999999;

  m2(0, 0) = 1.123456;
  m2(0, 1) = 2.654321;
  m2(0, 2) = 3.999999;
  m2(1, 0) = 4.123456;
  m2(1, 1) = 5.654321;
  m2(1, 2) = 6.999999;
  m2(2, 0) = 7.123456;
  m2(2, 1) = 8.654321;
  m2(2, 2) = 9.999999;

  S21Matrix result = m1 * m2;

  EXPECT_NEAR(result(0, 0), 40.700946113, 1e-6);
  EXPECT_NEAR(result(0, 1), 52.60767117, 1e-6);
  EXPECT_NEAR(result(0, 2), 63.074053222, 1e-6);

  EXPECT_NEAR(result(1, 0), 77.812050113, 1e-6);
  EXPECT_NEAR(result(1, 1), 103.49656017, 1e-6);
  EXPECT_NEAR(result(1, 2), 126.074044222, 1e-6);

  EXPECT_NEAR(result(2, 0), 114.923154113, 1e-6);
  EXPECT_NEAR(result(2, 1), 154.38544917, 1e-6);
  EXPECT_NEAR(result(2, 2), 189.074035222, 1e-6);
}

// Тест на исключение при попытке умножить матрицы с несовместимыми размерами
TEST(S21MatrixTest, OperatorMultiplyInvalidDimensions) {
  S21Matrix m1(2, 3);
  S21Matrix m2(4, 2);
  EXPECT_THROW({ S21Matrix result = m1 * m2; }, std::invalid_argument);
}
// тест для MulMatrix
TEST(S21MatrixTest, MulMatrix) {
  S21Matrix m1(3, 3);
  S21Matrix m2(3, 3);

  m1(0, 0) = 1.123456;
  m1(0, 1) = 2.654321;
  m1(0, 2) = 3.999999;
  m1(1, 0) = 4.123456;
  m1(1, 1) = 5.654321;
  m1(1, 2) = 6.999999;
  m1(2, 0) = 7.123456;
  m1(2, 1) = 8.654321;
  m1(2, 2) = 9.999999;

  m2(0, 0) = 1.123456;
  m2(0, 1) = 2.654321;
  m2(0, 2) = 3.999999;
  m2(1, 0) = 4.123456;
  m2(1, 1) = 5.654321;
  m2(1, 2) = 6.999999;
  m2(2, 0) = 7.123456;
  m2(2, 1) = 8.654321;
  m2(2, 2) = 9.999999;

  m1.MulMatrix(m2);

  EXPECT_NEAR(m1(0, 0), 40.700946113, 1e-6);
  EXPECT_NEAR(m1(0, 1), 52.60767117, 1e-6);
  EXPECT_NEAR(m1(0, 2), 63.074053222, 1e-6);

  EXPECT_NEAR(m1(1, 0), 77.812050113, 1e-6);
  EXPECT_NEAR(m1(1, 1), 103.49656017, 1e-6);
  EXPECT_NEAR(m1(1, 2), 126.074044222, 1e-6);

  EXPECT_NEAR(m1(2, 0), 114.923154113, 1e-6);
  EXPECT_NEAR(m1(2, 1), 154.38544917, 1e-6);
  EXPECT_NEAR(m1(2, 2), 189.074035222, 1e-6);
}

TEST(S21MatrixTest, MulMatrixIncompatibleSizes) {
  S21Matrix m1(2, 3);
  S21Matrix m2(4, 2);

  EXPECT_THROW(m1.MulMatrix(m2), std::invalid_argument);
}

// тест для MulNumber
TEST(S21MatrixTest, MulNumber) {
  S21Matrix m1(2, 3);

  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 4.0;
  m1(1, 1) = 5.0;
  m1(1, 2) = 6.0;

  double num = 2.0;
  m1.MulNumber(num);

  EXPECT_EQ(m1(0, 0), 2.0);
  EXPECT_EQ(m1(0, 1), 4.0);
  EXPECT_EQ(m1(0, 2), 6.0);
  EXPECT_EQ(m1(1, 0), 8.0);
  EXPECT_EQ(m1(1, 1), 10.0);
  EXPECT_EQ(m1(1, 2), 12.0);
}

TEST(S21MatrixTest, MulNumberNegative) {
  S21Matrix m1(2, 2);

  m1(0, 0) = 1.0;
  m1(0, 1) = -2.0;
  m1(1, 0) = 3.0;
  m1(1, 1) = -4.0;

  m1.MulNumber(-3.0);
  EXPECT_EQ(m1(0, 0), -3.0);
  EXPECT_EQ(m1(0, 1), 6.0);
  EXPECT_EQ(m1(1, 0), -9.0);
  EXPECT_EQ(m1(1, 1), 12.0);
}

// тест метода Transpose
TEST(S21MatrixTest, Transpose) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  S21Matrix transposed = matrix.Transpose();

  EXPECT_EQ(transposed.getRows(), 3);
  EXPECT_EQ(transposed.getCols(), 2);
  EXPECT_EQ(transposed(0, 0), 1.0);
  EXPECT_EQ(transposed(1, 0), 2.0);
  EXPECT_EQ(transposed(2, 0), 3.0);
  EXPECT_EQ(transposed(0, 1), 4.0);
  EXPECT_EQ(transposed(1, 1), 5.0);
  EXPECT_EQ(transposed(2, 1), 6.0);
}

// Тестирование метода Determinant
TEST(S21MatrixTest, DeterminantInvalidMatrix) {
  S21Matrix m(2, 3);

  EXPECT_THROW(m.Determinant(), std::invalid_argument);
}
TEST(S21MatrixTest, Determinant1x1) {
  S21Matrix m1(1, 1);
  m1(0, 0) = 3.678;
  double result = m1.Determinant();
  EXPECT_NEAR(result, 3.678, 1e-6);
}

TEST(S21MatrixTest, Determinant2x2) {
  S21Matrix m2(2, 2);
  m2(0, 0) = 12.345678;
  m2(0, 1) = 4.34;
  m2(1, 0) = 4.6;
  m2(1, 1) = 7.24;
  double result = m2.Determinant();
  EXPECT_NEAR(result, 69.41870872, 1e-6);
}

TEST(S21MatrixTest, Determinant3x3Negative) {
  S21Matrix m3(3, 3);
  m3(0, 0) = 9.876543;
  m3(0, 1) = 8.123456;
  m3(0, 2) = 7.543210;
  m3(1, 0) = 6.987654;
  m3(1, 1) = 5.321098;
  m3(1, 2) = 4.210987;
  m3(2, 0) = 3.654321;
  m3(2, 1) = 2.123456;
  m3(2, 2) = 1.543210;
  double result = m3.Determinant();
  EXPECT_NEAR(result, -4.55678868, 1e-6);
}

TEST(S21MatrixTest, Determinant3x3Zero) {
  S21Matrix m3_zero(3, 3);
  m3_zero(0, 0) = 1.0;
  m3_zero(0, 1) = 2.0;
  m3_zero(0, 2) = 3.0;
  m3_zero(1, 0) = 1.0;
  m3_zero(1, 1) = 2.0;
  m3_zero(1, 2) = 3.0;
  m3_zero(2, 0) = 1.0;
  m3_zero(2, 1) = 2.0;
  m3_zero(2, 2) = 3.0;
  double result = m3_zero.Determinant();
  EXPECT_NEAR(result, 0.0, 1e-6);
}

TEST(S21MatrixTest, GetMinor3x3Matrix) {
  S21Matrix m(3, 3);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(0, 2) = 3.0;
  m(1, 0) = 4.0;
  m(1, 1) = 5.0;
  m(1, 2) = 6.0;
  m(2, 0) = 7.0;
  m(2, 1) = 8.0;
  m(2, 2) = 9.0;

  S21Matrix minor = m.GetMinor(0, 0);

  EXPECT_EQ(minor.getRows(), 2);
  EXPECT_EQ(minor.getCols(), 2);
  EXPECT_EQ(minor(0, 0), 5.0);
  EXPECT_EQ(minor(0, 1), 6.0);
  EXPECT_EQ(minor(1, 0), 8.0);
  EXPECT_EQ(minor(1, 1), 9.0);
}

TEST(S21MatrixTest, GetMinorInvalidIndex) {
  S21Matrix m(2, 2);
  m(0, 0) = 1.0;
  m(0, 1) = 2.0;
  m(1, 0) = 3.0;
  m(1, 1) = 4.0;
  EXPECT_THROW(m.GetMinor(2, 2), std::out_of_range);
}

// Тестирование метода CalcComplements
TEST(S21MatrixTest, CalcComplementsMethod) {
  S21Matrix m1(5, 5);

  m1(0, 0) = 12.345678;
  m1(0, 1) = 3.876543;
  m1(0, 2) = 45.678912;
  m1(0, 3) = 78.123456;
  m1(0, 4) = 9.876543;

  m1(1, 0) = 65.432109;
  m1(1, 1) = 87.654321;
  m1(1, 2) = 21.345678;
  m1(1, 3) = 9.012345;
  m1(1, 4) = 54.321098;

  m1(2, 0) = 76.543210;
  m1(2, 1) = 32.109876;
  m1(2, 2) = 98.765432;
  m1(2, 3) = 10.123456;
  m1(2, 4) = 43.210987;

  m1(3, 0) = 88.765432;
  m1(3, 1) = 65.987654;
  m1(3, 2) = 32.543210;
  m1(3, 3) = 11.234567;
  m1(3, 4) = 21.098765;

  m1(4, 0) = 44.321098;
  m1(4, 1) = 78.654321;
  m1(4, 2) = 54.098765;
  m1(4, 3) = 12.345678;
  m1(4, 4) = 3.987654;

  S21Matrix result = m1.CalcComplements();

  EXPECT_NEAR(result(0, 0), -1062782.246069, 1e-6);
  EXPECT_NEAR(result(0, 1), -1713903.813708, 1e-6);
  EXPECT_NEAR(result(0, 2), -1173056.473802, 1e-6);
  EXPECT_NEAR(result(0, 3), 19462293.903043, 1e-6);
  EXPECT_NEAR(result(0, 4), 1277771.252671, 1e-6);

  EXPECT_NEAR(result(1, 0), -11273141.845822, 1e-6);
  EXPECT_NEAR(result(1, 1), 9238244.402757, 1e-6);
  EXPECT_NEAR(result(1, 2), -6633220.176592, 1e-6);
  EXPECT_NEAR(result(1, 3), 1677833.155165, 1e-6);
  EXPECT_NEAR(result(1, 4), 27872331.812391, 1e-6);

  EXPECT_NEAR(result(2, 0), 195853.974113, 1e-6);
  EXPECT_NEAR(result(2, 1), -8855164.883991, 1e-6);
  EXPECT_NEAR(result(2, 2), 14044499.341250, 1e-6);
  EXPECT_NEAR(result(2, 3), -9072603.153888, 1e-6);
  EXPECT_NEAR(result(2, 4), 10039458.254847, 1e-6);

  EXPECT_NEAR(result(3, 0), 31792177.838998, 1e-6);
  EXPECT_NEAR(result(3, 1), -8447340.501648, 1e-6);
  EXPECT_NEAR(result(3, 2), -13620683.551006, 1e-6);
  EXPECT_NEAR(result(3, 3), 5924869.487017, 1e-6);
  EXPECT_NEAR(result(3, 4), -20294832.634977, 1e-6);

  EXPECT_NEAR(result(4, 0), -14136802.005580, 1e-6);
  EXPECT_NEAR(result(4, 1), 19049980.757630, 1e-6);
  EXPECT_NEAR(result(4, 2), 13143685.209138, 1e-6);
  EXPECT_NEAR(result(4, 3), -4095945.607323, 1e-6);
  EXPECT_NEAR(result(4, 4), -18196597.497454, 1e-6);
}

TEST(S21MatrixTest, CalcComplementsMethod1) {
  S21Matrix m1(2, 2);

  m1(0, 0) = 12.345678;
  m1(0, 1) = 3.876543;

  m1(1, 0) = 65.432109;
  m1(1, 1) = 87.654321;

  S21Matrix result = m1.CalcComplements();

  EXPECT_NEAR(result(0, 0), 87.654321, 1e-6);
  EXPECT_NEAR(result(0, 1), -65.432109, 1e-6);
  EXPECT_NEAR(result(1, 0), -3.876543, 1e-6);
  EXPECT_NEAR(result(1, 1), 12.345678, 1e-6);
}

TEST(S21MatrixTest, CalcComplementsNonSquareMatrix) {
  S21Matrix m1(2, 3);
  EXPECT_THROW(m1.CalcComplements(), std::invalid_argument);
}
// Тестирование метода InverseMatrix
TEST(S21MatrixTest, InverseMatrixMethod) {
  S21Matrix m1(3, 3);

  m1(0, 0) = 2.0;
  m1(0, 1) = -1.0;
  m1(0, 2) = 0.0;
  m1(1, 0) = -1.0;
  m1(1, 1) = 2.0;
  m1(1, 2) = -1.0;
  m1(2, 0) = 0.0;
  m1(2, 1) = -1.0;
  m1(2, 2) = 2.0;

  S21Matrix inverse = m1.InverseMatrix();

  // Проверка значений обратной матрицы
  EXPECT_NEAR(inverse(0, 0), 0.75, 1e-6);
  EXPECT_NEAR(inverse(0, 1), 0.5, 1e-6);
  EXPECT_NEAR(inverse(0, 2), 0.25, 1e-6);
  EXPECT_NEAR(inverse(1, 0), 0.5, 1e-6);
  EXPECT_NEAR(inverse(1, 1), 1.0, 1e-6);
  EXPECT_NEAR(inverse(1, 2), 0.5, 1e-6);
  EXPECT_NEAR(inverse(2, 0), 0.25, 1e-6);
  EXPECT_NEAR(inverse(2, 1), 0.5, 1e-6);
  EXPECT_NEAR(inverse(2, 2), 0.75, 1e-6);
}

// Тестирование исключений InverseMatrix для вырожденной матрицы
TEST(S21MatrixTest, InverseMatrixSingularMatrix) {
  S21Matrix m1(3, 3);

  m1(0, 0) = 1.0;
  m1(0, 1) = 2.0;
  m1(0, 2) = 3.0;
  m1(1, 0) = 4.0;
  m1(1, 1) = 5.0;
  m1(1, 2) = 6.0;
  m1(2, 0) = 7.0;
  m1(2, 1) = 8.0;
  m1(2, 2) = 9.0;

  EXPECT_THROW(m1.InverseMatrix(), std::invalid_argument);
}

// Тестирование исключений InverseMatrix для неквадратной матрицы
TEST(S21MatrixTest, InverseMatrixNonSquareMatrix) {
  S21Matrix m1(2, 3);

  EXPECT_THROW(m1.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixTest, SetRowsIncrease) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.1;
  m1(0, 1) = 2.2;
  m1(1, 0) = 3.3;
  m1(1, 1) = 4.4;

  // Увеличение количества строк
  m1.setRows(3);

  // Проверка, что размеры изменены корректно
  EXPECT_EQ(m1.getRows(), 3);
  EXPECT_EQ(m1.getCols(), 2);

  // Проверка, что существующие элементы сохранены
  EXPECT_NEAR(m1(0, 0), 1.1, 1e-6);
  EXPECT_NEAR(m1(0, 1), 2.2, 1e-6);
  EXPECT_NEAR(m1(1, 0), 3.3, 1e-6);
  EXPECT_NEAR(m1(1, 1), 4.4, 1e-6);

  // Проверка, что новые элементы инициализированы нулями
  EXPECT_DOUBLE_EQ(m1(2, 0), 0.0);
  EXPECT_DOUBLE_EQ(m1(2, 1), 0.0);
}

TEST(S21MatrixTest, SetRowsDecrease) {
  S21Matrix m1(3, 2);
  m1(0, 0) = 1.1;
  m1(0, 1) = 2.2;
  m1(1, 0) = 3.3;
  m1(1, 1) = 4.4;
  m1(2, 0) = 5.5;
  m1(2, 1) = 6.6;

  // Уменьшение количества строк
  m1.setRows(2);

  // Проверка, что размеры изменены корректно
  EXPECT_EQ(m1.getRows(), 2);
  EXPECT_EQ(m1.getCols(), 2);

  // Проверка, что существующие элементы сохранены
  EXPECT_NEAR(m1(0, 0), 1.1, 1e-6);
  EXPECT_NEAR(m1(0, 1), 2.2, 1e-6);
  EXPECT_NEAR(m1(1, 0), 3.3, 1e-6);
  EXPECT_NEAR(m1(1, 1), 4.4, 1e-6);
}

TEST(S21MatrixTest, SetColsIncrease) {
  S21Matrix m1(2, 2);
  m1(0, 0) = 1.1;
  m1(0, 1) = 2.2;
  m1(1, 0) = 3.3;
  m1(1, 1) = 4.4;

  // Увеличение количества столбцов
  m1.setCols(3);

  // Проверка, что размеры изменены корректно
  EXPECT_EQ(m1.getRows(), 2);
  EXPECT_EQ(m1.getCols(), 3);

  // Проверка, что существующие элементы сохранены
  EXPECT_NEAR(m1(0, 0), 1.1, 1e-6);
  EXPECT_NEAR(m1(0, 1), 2.2, 1e-6);
  EXPECT_NEAR(m1(1, 0), 3.3, 1e-6);
  EXPECT_NEAR(m1(1, 1), 4.4, 1e-6);

  // Проверка, что новые элементы инициализированы нулями
  EXPECT_DOUBLE_EQ(m1(0, 2), 0.0);
  EXPECT_DOUBLE_EQ(m1(1, 2), 0.0);
}

TEST(S21MatrixTest, SetColsDecrease) {
  S21Matrix m1(2, 3);
  m1(0, 0) = 1.1;
  m1(0, 1) = 2.2;
  m1(0, 2) = 3.3;
  m1(1, 0) = 4.4;
  m1(1, 1) = 5.5;
  m1(1, 2) = 6.6;

  // Уменьшение количества столбцов
  m1.setCols(2);

  // Проверка, что размеры изменены корректно
  EXPECT_EQ(m1.getRows(), 2);
  EXPECT_EQ(m1.getCols(), 2);

  // Проверка, что существующие элементы сохранены
  EXPECT_NEAR(m1(0, 0), 1.1, 1e-6);
  EXPECT_NEAR(m1(0, 1), 2.2, 1e-6);
  EXPECT_NEAR(m1(1, 0), 4.4, 1e-6);
  EXPECT_NEAR(m1(1, 1), 5.5, 1e-6);
}

TEST(S21MatrixTest, SetRowsNegative) {
  S21Matrix m1(2, 2);
  EXPECT_THROW(m1.setRows(-1), std::invalid_argument);  // Ожидаем исключение
}

TEST(S21MatrixTest, SetColsNegative) {
  S21Matrix m1(2, 2);
  EXPECT_THROW(m1.setCols(-1), std::invalid_argument);  // Ожидаем исключение
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
