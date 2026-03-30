#include <cassert>
#include <vector>
#include "processing.hpp"

using namespace std;

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_left is provided for you.
// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the left (counterclockwise).
void rotate_left(Image* img) {

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, width - 1 - c, r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------

// v DO NOT CHANGE v ------------------------------------------------
// The implementation of rotate_right is provided for you.
// REQUIRES: img points to a valid Image.
// MODIFIES: *img
// EFFECTS:  The image is rotated 90 degrees to the right (clockwise).
void rotate_right(Image* img){

  // for convenience
  int width = Image_width(img);
  int height = Image_height(img);

  // auxiliary image to temporarily store rotated image
  Image aux;
  Image_init(&aux, height, width); // width and height switched

  // iterate through pixels and place each where it goes in temp
  for (int r = 0; r < height; ++r) {
    for (int c = 0; c < width; ++c) {
      Image_set_pixel(&aux, c, height - 1 - r, Image_get_pixel(img, r, c));
    }
  }

  // Copy data back into original
  *img = aux;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// v DO NOT CHANGE v ------------------------------------------------
// The implementation of diff2 is provided for you.
static int squared_difference(Pixel p1, Pixel p2) {
  int dr = p2.r - p1.r;
  int dg = p2.g - p1.g;
  int db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows
  // later on in the algorithm.
  return (dr*dr + dg*dg + db*db) / 100;
}
// ^ DO NOT CHANGE ^ ------------------------------------------------


// ------------------------------------------------------------------
// You may change code below this line!



// REQUIRES: img points to a valid Image.
//           energy points to a Matrix.
// MODIFIES: *energy
// EFFECTS:  energy serves as an "output parameter".
//           The Matrix pointed to by energy is initialized to be the same
//           size as the given Image, and then the energy matrix for that
//           image is computed and written into it.
//           See the project spec for details on computing the energy matrix.
void compute_energy_matrix(const Image* img, Matrix* energy) {
  int height = Image_height(img);
  int width = Image_width(img);
  // create the energy matrix
  Matrix_init(energy, width, height);
  Matrix_fill(energy, 0);
  // access each pixel not on the border
  for (int i = 1; i < height - 1; ++i){
    for (int j = 1; j < width - 1; ++j){
      // find north / south / east / west
      Pixel north = Image_get_pixel(img, i - 1, j);
      Pixel south = Image_get_pixel(img, i + 1, j);
      Pixel east = Image_get_pixel(img, i, j + 1);
      Pixel west = Image_get_pixel(img, i, j - 1);
      // compute the energy
      int energyVal = squared_difference(north, south) + squared_difference(west, east);
      // put it in the matrix
      *Matrix_at(energy, i, j) = energyVal;
    }
  }
  Matrix_fill_border(energy, Matrix_max(energy));
}


// REQUIRES: energy points to a valid Matrix.
//           cost points to a Matrix.
//           energy and cost aren't pointing to the same Matrix
// MODIFIES: *cost
// EFFECTS:  cost serves as an "output parameter".
//           The Matrix pointed to by cost is initialized to be the same
//           size as the given energy Matrix, and then the cost matrix is
//           computed and written into it.
//           See the project spec for details on computing the cost matrix.
void compute_vertical_cost_matrix(const Matrix* energy, Matrix *cost) {
  int height = Matrix_height(energy);
  int width = Matrix_width(energy);
  // create the energy matrix
  Matrix_init(cost, width, height);
  // loop through all elements in the first row
  // place the energy in the matrix
  for (int i = 0; i < width; ++i){
    *Matrix_at(cost, 0, i) = *Matrix_at(energy, 0, i);
  }
  // access all pixels after first row
  // find the minimum cost from 3 pixels above the current pixel
  for (int i = 1; i < height; ++i){
    for (int j = 0; j < width; ++j){
      int currentEnergy = *Matrix_at(energy, i, j);
      int columnStart;
      if (j > 0){
        columnStart = j - 1;
      } else {
        columnStart = j;
      }
      int columnEnd;
      if (j < width - 1){
        columnEnd = j + 1 + 1;
      } else {
        columnEnd = j + 1;
      }
      // get minCost
      int minCost = Matrix_min_value_in_row(cost, i - 1, columnStart, columnEnd);
      // set cost
      *Matrix_at(cost, i, j) = currentEnergy + minCost;
    }
  }
}


// REQUIRES: cost points to a valid Matrix
// EFFECTS:  Returns the vertical seam with the minimal cost according to the given
//           cost matrix, represented as a vector filled with the column numbers for
//           each pixel along the seam, starting with the lowest numbered row (top
//           of image) and progressing to the highest (bottom of image). The length
//           of the returned vector is equal to Matrix_height(cost).
//           While determining the seam, if any pixels tie for lowest cost, the
//           leftmost one (i.e. with the lowest column number) is used.
//           See the project spec for details on computing the minimal seam.
vector<int> find_minimal_vertical_seam(const Matrix* cost) {
  int height = Matrix_height(cost);
  int width = Matrix_width(cost); 
  int lastRow = height - 1; 
  int colStart = 0;
  int colEnd = width;
  vector<int> seam(height);
  // find the minCost in the last row
  int lastCol = Matrix_column_of_min_value_in_row(cost, lastRow, colStart, colEnd);
  seam[lastRow] = lastCol;
  // go up from the bottom row
  for (int i = height - 2; i >= 0; --i){
    int priorCol = seam[i + 1];
    int columnStart = priorCol - 1;
    int columnEnd = priorCol + 2;
    if (columnStart < 0){
      columnStart = priorCol;
    }
    if (columnEnd > width){
      columnEnd = priorCol + 1;
    }
    int minCol = Matrix_column_of_min_value_in_row(cost, i, columnStart, columnEnd);
    seam[i] = minCol;
  }
  return seam;
}


// REQUIRES: img points to a valid Image with width >= 2
//           seam.size() == Image_height(img)
//           each element x in seam satisfies 0 <= x < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Removes the given vertical seam from the Image. That is, one
//           pixel will be removed from every row in the image. The pixel
//           removed from row r will be the one with column equal to seam[r].
//           The width of the image will be one less than before.
//           See the project spec for details on removing a vertical seam.
// NOTE:     Declare a new variable to hold the smaller Image, and
//           then do an assignment at the end to copy it back into the
//           original image.
void remove_vertical_seam(Image *img, const vector<int> &seam) {
  int height = Image_height(img);
  int width = Image_width(img);
  // check requires statements
  // assert(seam.size() == height);
  // for (int i = 0; i < seam.size(); ++i){
  //   assert(0 <= seam[i]);
  //   assert(seam[i] < width);
  // }
  // create a new image
  Image newImg;
  // get rid of one of the columns
  Image_init(&newImg, width - 1, height);
  // access all the pixels
  for (int i = 0; i < height; ++i){
    int colSeam = seam[i];
    int newCol = 0;
    for (int j = 0; j < width; ++j){
      if (j != colSeam){
        Pixel pixel = Image_get_pixel(img, i, j);
        Image_set_pixel(&newImg, i, newCol, pixel);
        newCol++;
      }
    }
  }
  *img = newImg;
}


// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width of the given Image to be newWidth by using
//           the seam carving algorithm. See the spec for details.
// NOTE:     Use a vector to hold the seam, and make sure that it has
//           the right size. You can use .data() on a vector to get
//           the underlying array.
void seam_carve_width(Image *img, int newWidth) {
  int width = Image_width(img);
  // check requires statements
  // assert(0 < newWidth);
  // assert(newWidth <= width);
  while(width > newWidth){
    Matrix energy;
    // get the energy
    compute_energy_matrix(img, &energy);
    Matrix cost;
    // get the cost
    compute_vertical_cost_matrix(&energy, &cost);
    // get the minimal vertical seam
    vector<int> seam(Matrix_height(&cost));
    seam = find_minimal_vertical_seam(&cost);
    // get rid of the minimal vertical seam
    remove_vertical_seam(img, seam);
    width = Image_width(img);
  }
}

// REQUIRES: img points to a valid Image
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the height of the given Image to be newHeight.
// NOTE:     This is equivalent to first rotating the Image 90 degrees left,
//           then applying seam_carve_width(img, newHeight), then rotating
//           90 degrees right.
void seam_carve_height(Image *img, int newHeight) {
  //int height = Image_height(img);
  //check requires statements
  // assert(0 < newHeight);
  // assert(newHeight <= height);
  // turn the img
  rotate_left(img);
  // set the new height
  seam_carve_width(img, newHeight);
  // reset the img
  rotate_right(img);
}

// REQUIRES: img points to a valid Image
//           0 < newWidth && newWidth <= Image_width(img)
//           0 < newHeight && newHeight <= Image_height(img)
// MODIFIES: *img
// EFFECTS:  Reduces the width and height of the given Image to be newWidth
//           and newHeight, respectively.
// NOTE:     This is equivalent to applying seam_carve_width(img, newWidth)
//           and then applying seam_carve_height(img, newHeight).
void seam_carve(Image *img, int newWidth, int newHeight) {
  int width = Image_width(img);
  int height = Image_height(img);
  // check requires statements
  // assert(0 < newWidth);
  // assert(newWidth <= width);
  // assert(0 < newHeight);
  // assert(newHeight <= height);
  // check the width
  if (width > newWidth){
    seam_carve_width(img, newWidth);
  }
  // check the height
  if (height > newHeight){
    seam_carve_height(img, newHeight);
  }
}
