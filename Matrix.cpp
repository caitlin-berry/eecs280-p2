#include <cassert>
#include "Matrix.hpp"
using namespace std;

// REQUIRES: mat points to a Matrix
//           0 < width && 0 < height
// MODIFIES: *mat
// EFFECTS:  Initializes *mat as a Matrix with the given width and height,
//           with all elements initialized to 0.
void Matrix_init(Matrix* mat, int width, int height) {
  // check requires statements
  // assert(0 < width);
  // assert(0 < height);
  // assign the parameter width & height to the Matrix struct
  mat->width = width; 
  mat->height = height; 
  // find the size of the matrix
  int vecSize = width * height;
  // resize the data vector in the Matrix struct to be the correct size
  // fill the vector with zeros
  mat->data = vector<int> (vecSize);
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: os
// EFFECTS:  First, prints the width and height for the Matrix to os:
//             WIDTH [space] HEIGHT [newline]
//           Then prints the rows of the Matrix to os with one row per line.
//           Each element is followed by a space and each row is followed
//           by a newline. This means there will be an "extra" space at
//           the end of each line.
void Matrix_print(const Matrix* mat, std::ostream& os) {
  int width = mat->width;
  int height = mat->height;
  // print the width and heigh for th eMatrix to os
  os << width << " " << height << endl;
  // print the rows of the Matrix to os with one row per line
  // loop through each row
  for (int i = 0; i < height; ++i){
    // loop through each column of this row
    for (int j = 0; j < width; ++j){
      // print the value at this row, column spot
      os << *Matrix_at(mat, i, j);
      // seperate values in row with a space
      os <<  " ";
    }
    // create a newline to go to the next row
    os << endl;
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the width of the Matrix.
int Matrix_width(const Matrix* mat) {
  // access the width from the matrix
  int matWidth = mat->width;
  return matWidth;
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the height of the Matrix.
int Matrix_height(const Matrix* mat) {
  // access the height from the matrix
  int matHeight = mat->height;
  return matHeight;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// MODIFIES: (The returned pointer may be used to modify an
//            element in the Matrix.)
// EFFECTS:  Returns a pointer to the element in the Matrix
//           at the given row and column.
int* Matrix_at(Matrix* mat, int row, int column) {
  // check the requires statements
  // assert(0 <= row);
  // assert(row < Matrix_height(mat));
  // assert(0 <= column);
  // assert(column < Matrix_width(mat));
  // find the index in the vector for the (row, column)
  int matWidth = Matrix_width(mat);
  int pos = row * matWidth;
  pos += column;
  // return a pointer to this element
  return &mat->data[pos];
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column && column < Matrix_width(mat)
//
// EFFECTS:  Returns a pointer-to-const to the element in
//           the Matrix at the given row and column.
const int* Matrix_at(const Matrix* mat, int row, int column) {
  // same code as int* Matrix_at(Matrix* mat, int row, int column);
  // check the requires statements
  // assert(0 <= row);
  // assert(row < Matrix_height(mat));
  // assert(0 <= column);
  // assert(column < Matrix_width(mat));
  // find the index in the vector for the (row, column)
  int matWidth = Matrix_width(mat);
  int pos = row * matWidth;
  pos += column;
  // return a pointer to this element
  return &mat->data[pos];
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element of the Matrix to the given value.
void Matrix_fill(Matrix* mat, int value) {
  int height = Matrix_height(mat);
  int width = Matrix_width(mat);
  // loop through each row
  for (int i = 0; i < height; ++i){
    // loop through each column
    for (int j = 0; j < width; ++j){
      // access the element at the specific position
      *Matrix_at(mat, i, j) = value;
    }
  }
}

// REQUIRES: mat points to a valid Matrix
// MODIFIES: *mat
// EFFECTS:  Sets each element on the border of the Matrix to
//           the given value. These are all elements in the first/last
//           row or the first/last column.
void Matrix_fill_border(Matrix* mat, int value) {
  int height = Matrix_height(mat);
  int width = Matrix_width(mat);
  // fill the sides of the boarder (loop through rows)
  for (int i = 0; i < height; ++i){
    int firstVal = 0;
    int lastVal = width - 1;
    // set the element to the given value
    *Matrix_at(mat, i, firstVal) = value;
    *Matrix_at(mat, i, lastVal) = value;
  }
  // fill the top and bottom of the boarder (loop through columns)
  for (int j = 0; j < width; ++j){
    int firstVal = 0;
    int lastVal = height - 1;
    // set the element to the given value
    *Matrix_at(mat, firstVal, j) = value;
    *Matrix_at(mat, lastVal, j) = value;
  }
}

// REQUIRES: mat points to a valid Matrix
// EFFECTS:  Returns the value of the maximum element in the Matrix
int Matrix_max(const Matrix* mat) {
  int matSize = mat->data.size();
  // find the first value in the matrix
  int matrixMax = mat->data[0];
  // compare the current max to the rest of the values in data
  for (int i = 0; i < matSize; ++i){
    int currentVal = mat->data[i];
    if(currentVal > matrixMax){
      matrixMax = currentVal;
    }
  }
  return matrixMax;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the column of the element with the minimal value
//           in a particular region. The region is defined as elements
//           in the given row and between column_start (inclusive) and
//           column_end (exclusive).
//           If multiple elements are minimal, returns the column of
//           the leftmost one.
int Matrix_column_of_min_value_in_row(const Matrix* mat, int row,
                                      int column_start, int column_end) {
  // check requires statements
  // assert(0 <= row);
  // assert(row < Matrix_height(mat));
  // assert(0 <= column_start);
  // assert(column_end <= Matrix_width(mat));
  // assert(column_start < column_end);
  // create minimum variables
  int minColumn = column_start;
  int matrixMin = *Matrix_at(mat, row, column_start);
  // loop through the columns 
  int startVal = column_start + 1;
  int endVal = column_end;
  for (int i = startVal; i < endVal; ++i){
    // find the current value
    int currentVal = *Matrix_at(mat, row, i);
    // compare the current value to the minimum value
    if (currentVal < matrixMin){
      // update minimum values
      matrixMin = currentVal;
      minColumn = i;
    }
  }
  return minColumn;
}

// REQUIRES: mat points to a valid Matrix
//           0 <= row && row < Matrix_height(mat)
//           0 <= column_start && column_end <= Matrix_width(mat)
//           column_start < column_end
// EFFECTS:  Returns the minimal value in a particular region. The region
//           is defined as elements in the given row and between
//           column_start (inclusive) and column_end (exclusive).
int Matrix_min_value_in_row(const Matrix* mat, int row,
                            int column_start, int column_end) {
   // check requires statements
  // assert(0 <= row);
  // assert(row < Matrix_height(mat));
  // assert(0 <= column_start);
  // assert(column_end <= Matrix_width(mat));
  // assert(column_start < column_end);
  // create minimum variables
  int matrixMin = *Matrix_at(mat, row, column_start);
  // loop through the columns 
  int startVal = column_start + 1;
  int endVal = column_end;
  for (int i = startVal; i < endVal; ++i){
    // find the current value
    int currentVal = *Matrix_at(mat, row, i);
    // compare the current value to the minimum value
    if (currentVal < matrixMin){
      // update minimum values
      matrixMin = currentVal;
    }
  }
  return matrixMin;
}
