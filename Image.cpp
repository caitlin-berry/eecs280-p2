#include <cassert>
#include "Image.hpp"
using namespace std;

// REQUIRES: img points to an Image
//           0 < width && 0 < height
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height, with
//           all pixels initialized to RGB values of 0.
void Image_init(Image* img, int width, int height) {
  // check requires statements
  // assert(0 < width);
  // assert(0 < height);
  // assign the width & height to the struct
  img->width = width;
  img->height = height;
  // set color channels
  Matrix* redChannel = &img->red_channel;
  Matrix* greenChannel = &img->green_channel;
  Matrix* blueChannel = &img->blue_channel;
  // create the matricies
  Matrix_init(redChannel, width, height);
  Matrix_init(greenChannel, width, height);
  Matrix_init(blueChannel, width, height);
  // go through all the rows
  for (int i = 0; i < height; ++i){
    // go through all the columns
    for (int j = 0; j < width; ++j){
      // set all pixels to RGB values of 0
      *Matrix_at(redChannel, i, j) = 0;
      *Matrix_at(greenChannel, i, j) = 0;
      *Matrix_at(blueChannel, i, j) = 0;
    }
  }
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img, is
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
void Image_init(Image* img, std::istream& is) {
  string header;
  is >> header;
  // check that line was read correctly
  // assert(header == "P3");
  // read in the width of the image
  is >> img->width;
  // read in the height of the image
  is >> img->height;
  // read in max value for RGB intensities
  int junk;
  is >> junk;
  // check that line was read correctly
  // assert(junk == MAX_INTENSITY);
  // set color channels
  Matrix* redChannel = &img->red_channel;
  Matrix* greenChannel = &img->green_channel;
  Matrix* blueChannel = &img->blue_channel;
  // set width & height variables
  int width = img->width;
  int height = img->height;
  // create the matricies
  Matrix_init(redChannel, width, height);
  Matrix_init(greenChannel, width, height);
  Matrix_init(blueChannel, width, height);
  // create color variables
  int red = 0;
  int green = 0;
  int blue = 0;
  // access each individual pixel in the matrix
  for (int i = 0; i < height; ++i){
    for (int j = 0; j < width; ++j){
      // read all the colors
      is >> red;
      is >> green;
      is >> blue;
      // assign the colors to their pixel
      *Matrix_at(redChannel, i, j) = red;
      *Matrix_at(greenChannel, i, j) = green;
      *Matrix_at(blueChannel, i, j) = blue;
    }
  }
}

// REQUIRES: img points to a valid Image
// MODIFIES: os
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  // get width and height values
  int width = img->width;
  int height = img->height;
  // print first three lines
  os << "P3" << endl;
  os << width << " " << height << endl;
  os << MAX_INTENSITY << endl;
  // access the individual pixels
  for (int i = 0; i < height; ++i){
    for (int j = 0; j < width; ++j){
      // get the pixel at given coordinate
      Pixel pixel = Image_get_pixel(img, i, j);
      // print the colors
      os << pixel.r << " ";
      os << pixel.g << " ";
      os << pixel.b << " ";
    }
    // newline for new row
    os << endl;
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  int width = img->width;
  return width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  int height = img->height;
  return height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  // check requires statements
  // assert(0 <= row);
  // assert(row < Image_height(img));
  // assert(0 <= column);
  // assert(column < Image_width(img));
  // set color channels
  const Matrix* redChannel = &img->red_channel;
  const Matrix* greenChannel = &img->green_channel;
  const Matrix* blueChannel = &img->blue_channel;
  // get color values
  int r = *Matrix_at(redChannel, row, column);
  int g = *Matrix_at(greenChannel, row, column);
  int b = *Matrix_at(blueChannel, row, column);
  // create a pixel
  Pixel pixel = {r, g, b};
  return pixel;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  // check requires statements
  // assert(0 <= row);
  // assert(row < Image_height(img));
  // assert(0 <= column);
  // assert(column < Image_width(img));
  // set color channels
  Matrix* redChannel = &img->red_channel;
  Matrix* greenChannel = &img->green_channel;
  Matrix* blueChannel = &img->blue_channel;
  // create Pixel colors
  int red = color.r;
  int green = color.g;
  int blue = color.b;
  // set the pixels
  *Matrix_at(redChannel, row, column) = red;
  *Matrix_at(greenChannel, row, column) = green;
  *Matrix_at(blueChannel, row, column) = blue;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  // get height and width values
  int height = Image_height(img);
  int width = Image_width(img);
  // access individual pixels 
  for (int i = 0; i < height; ++i){
    for (int j = 0; j < width; ++j){
      Image_set_pixel(img, i, j, color);
    }
  }
}
