#include <gtest/gtest.h>

#include <string>

#include "matrix.hpp"

using namespace std;

TEST(MatrixTests, RowsAndCols) {
    Matrix<int> mat{3, 2};
    EXPECT_EQ(mat.num_rows(), 3);
    EXPECT_EQ(mat.num_cols(), 2);

    Matrix<double> mat2{5, 1};
    EXPECT_EQ(mat2.num_rows(), 5);
    EXPECT_EQ(mat2.num_cols(), 1);

    Matrix<string> mat3;
    EXPECT_EQ(mat3.num_rows(), 0);
    EXPECT_EQ(mat3.num_cols(), 0);
}

TEST(MatrixTests, Subscript) {
	Matrix<int> int_matrix(3, 3);
    int_matrix.fill(0);
    int_matrix[0][0] = 1;
    int_matrix[1][1] = 2;
    int_matrix[2][2] = 3;

    EXPECT_EQ(int_matrix[0][0], 1);
    EXPECT_EQ(int_matrix[1][1], 2);
    EXPECT_EQ(int_matrix[2][2], 3);
}

//TEST(MatrixTests, Print) {
	 std::stringstream ss;
    Matrix<int> int_matrix(2, 2);
    int_matrix.fill_with_fn([](int row, int col) { return row * 2 + col; });
    ss << int_matrix;
    EXPECT_EQ(ss.str(), "0 1 \n2 3 \n");
}//

TEST(MatrixTests, Read) {
	std::stringstream ss("1 2 3 4 5 6");
    Matrix<int> matrix(2, 3);
    ss >> matrix;
    EXPECT_EQ(matrix[0][0], 1);
    EXPECT_EQ(matrix[0][1], 2);
    EXPECT_EQ(matrix[0][2], 3);
    EXPECT_EQ(matrix[1][0], 4);
    EXPECT_EQ(matrix[1][1], 5);
    EXPECT_EQ(matrix[1][2], 6);
}

TEST(MatrixTests, Fill) {
	Matrix<int> int_matrix(2, 2);
    int_matrix.fill(42);
    for (int i = 0; i < int_matrix.num_rows(); ++i) {
        for (int j = 0; j < int_matrix.num_cols(); ++j) {
            EXPECT_EQ(int_matrix[i][j], 42);
        }
    }
}

TEST(MatrixTests, FillWithFunction) {
	 Matrix<int> int_matrix(2, 3);
    int_matrix.fill_with_fn([](int row, int col) { return row * col; });
    EXPECT_EQ(int_matrix[0][0], 0);
    EXPECT_EQ(int_matrix[0][1], 0);
    EXPECT_EQ(int_matrix[0][2], 0);
    EXPECT_EQ(int_matrix[1][0], 0);
    EXPECT_EQ(int_matrix[1][1], 1);
    EXPECT_EQ(int_matrix[1][2], 2);
}

TEST(MatrixTests, InitialConstructor) {
	Matrix<int> default_matrix;
    EXPECT_EQ(default_matrix.num_rows(), 0);
    EXPECT_EQ(default_matrix.num_cols(), 0);
}




