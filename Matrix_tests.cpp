#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
  Matrix mat;
  const int width = 3;
  const int height = 5;
  const int value = 42;
  Matrix_init(&mat, 3, 5);
  Matrix_fill(&mat, value);

  for(int r = 0; r < height; ++r){
    for(int c = 0; c < width; ++c){
      ASSERT_EQUAL(*Matrix_at(&mat, r, c), value);
    }
  }
}


// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.


TEST(testMatrixInit) {
  Matrix mat;
  const int width = 2;
  const int height = 4;
  Matrix_init(&mat, width, height);
  // check matrix width & height
  ASSERT_EQUAL(Matrix_width(&mat), width);
  ASSERT_EQUAL(Matrix_height(&mat), height);
}

TEST(testMatrixAt) {
  Matrix mat;
  Matrix_init(&mat, 2, 4);
  *Matrix_at(&mat, 1, 3) = 10;
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 3), 10);
}

TEST(testConstMatrixAt) {
  Matrix mat;
  Matrix_init(&mat, 2, 4);
  *Matrix_at(&mat, 1, 3) = 10;
  const Matrix* constMat = &mat;
  ASSERT_EQUAL(*Matrix_at(constMat, 1, 3), 10);
}

TEST(testMatrixFill) {
  Matrix mat;
  Matrix_init(&mat, 2, 4);
  Matrix_fill(&mat, 4);
  // loop through the matrix
  for (int i = 0; i < Matrix_height(&mat); ++i) {
    for (int j = 0; j < Matrix_width(&mat); ++j) {
      ASSERT_EQUAL(*Matrix_at(&mat, i, j), 4);
    }
  }
}

// Tests if Matrix_at works for edge indices.
TEST(testMatrixFillBorder) {
  Matrix mat;
  Matrix_init(&mat, 3, 3);
  Matrix_fill_border(&mat, 4);
  // compare border values to center values
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 2), 4);
  ASSERT_EQUAL(*Matrix_at(&mat, 1, 1), 0); 
}

TEST(testMatrixMax){
  Matrix mat;
  Matrix_init(&mat, 2, 3);
  // fill the matrix
  *Matrix_at(&mat, 0, 0) = 4;
  *Matrix_at(&mat, 0, 1) = 2;
  *Matrix_at(&mat, 0, 2) = 7; 
  *Matrix_at(&mat, 1, 0) = 12;
  *Matrix_at(&mat, 1, 1) = 4;
  *Matrix_at(&mat, 1, 2) = 5;
  ASSERT_EQUAL(Matrix_max(&mat), 12);
  Matrix_fill(&mat, 15);
  ASSERT_EQUAL(Matrix_max(&mat), 15);
}

TEST(testMatrixColMinValue1) {
  Matrix mat;
  Matrix_init(&mat, 2, 4); 
  // fill the matrix with values
  *Matrix_at(&mat, 0, 0) = 4;
  *Matrix_at(&mat, 0, 1) = 2; 
  *Matrix_at(&mat, 0, 2) = 5;
  *Matrix_at(&mat, 0, 3) = 3;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 3), 1); 
}

TEST(testMatrixColMinValue2) {
  Matrix mat;
  Matrix_init(&mat, 2, 4); 
  // fill the matrix with values
  *Matrix_at(&mat, 0, 0) = 3;
  *Matrix_at(&mat, 0, 1) = 2; 
  *Matrix_at(&mat, 0, 2) = 5;
  *Matrix_at(&mat, 0, 3) = 1;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 4), 3); 
}

TEST(testMatrixColMinValue3) {
  Matrix mat;
  Matrix_init(&mat, 2, 4); 
  // fill the matrix with values
  *Matrix_at(&mat, 0, 0) = 4;
  *Matrix_at(&mat, 0, 1) = 2; 
  *Matrix_at(&mat, 0, 2) = 5;
  *Matrix_at(&mat, 0, 3) = 3;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 2, 2), 2); 
}

TEST(testMatrixColMinValueOneCol){
  Matrix mat;
  Matrix_init(&mat, 1, 4);
  *Matrix_at(&mat, 0, 0) = 8;
  *Matrix_at(&mat, 1, 0) = 4;
  *Matrix_at(&mat, 2, 0) = 5;
  *Matrix_at(&mat, 3, 0) = 3;
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 0, 0, 1), 0); 
  ASSERT_EQUAL(Matrix_column_of_min_value_in_row(&mat, 3, 0, 1), 0); 
}

TEST(testMatrixMinVal){
  Matrix mat;
  Matrix_init(&mat, 3, 4); 
  Matrix_fill(&mat, 15);
  // fill the matrix with values
  *Matrix_at(&mat, 1, 0) = 14; 
  *Matrix_at(&mat, 1, 1) = 2; 
  *Matrix_at(&mat, 2, 1) = 3;
  ASSERT_EQUAL(Matrix_min_value_in_row(&mat, 1, 0, 2), 2); 
}

TEST(testEmptyMatrix){
  Matrix mat;
  Matrix_init(&mat, 0, 0); 
  ASSERT_EQUAL(Matrix_width(&mat), 0);
  ASSERT_EQUAL(Matrix_height(&mat), 0);
}

TEST(tesetOneValueMatrix){
  Matrix mat;
  Matrix_init(&mat, 1, 1);
  *Matrix_at(&mat, 0, 0) = 4;
  ASSERT_EQUAL(*Matrix_at(&mat, 0, 0), 4);
}

TEST(testMatrixFillBig){
  Matrix mat;
  Matrix_init(&mat, 10000, 10000);
  Matrix_fill(&mat, 10);
  for (int i = 0; i < Matrix_height(&mat); ++i){
    for (int j = 0; j < Matrix_width(&mat); ++j){
      ASSERT_EQUAL(*Matrix_at(&mat, i, j), 10);
    }
  }
}

TEST_MAIN() // Do NOT put a semicolon here
