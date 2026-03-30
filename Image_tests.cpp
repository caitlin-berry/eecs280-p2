#include "Matrix.hpp"
#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;

// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image img;
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(&img, 2, 2);
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  Image_set_pixel(&img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(&img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE

// Image_init(Image* img, std::istream& is)

// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

TEST(testImageInitWH) {
  Image img;
  Image_init(&img, 2, 4);
  // check matrix width & height
  ASSERT_EQUAL(Image_width(&img), 2);
  ASSERT_EQUAL(Image_height(&img), 4);
  cout << "testImageInitWH : Passed" << endl;
}

TEST(testImageInitOS){
  Image img;
  // create a fake file
  istringstream iss("P3\n2 2\n255\n255 0 0 0 255 0\n0 0 255 255 255 255\n");
  // initialize the image
  Image_init(&img, iss);
  // check matrix width & height
  ASSERT_EQUAL(Image_width(&img), 2);
  ASSERT_EQUAL(Image_height(&img), 2);
  // create colors
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};
  // check that they were created correctly
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 1), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 0), blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 1), white));
  cout << "testImageInitOS : Passed" << endl;
}

TEST(testImagePixel) {
  Image img;
  // create colors
  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  // create an image
  Image_init(&img, 3, 3);
  // test set pixel
  Image_set_pixel(&img, 0, 0, red);
  Image_set_pixel(&img, 0, 1, green);
  Image_set_pixel(&img, 1, 0, blue);
  // test get pixel
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 0), red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 0, 1), green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, 1, 0), blue));
  cout << "testImageSetPixel & testImageGetPixel : Passed" << endl;
}

TEST(testImageFill) {
  Image img;
  // create a color
  const Pixel color = {120, 200, 80};
  Image_init(&img, 2, 4);
  Image_fill(&img, color);
  for (int i = 0; i < Image_height(&img); ++i) {
    for (int j = 0; j < Image_width(&img); ++j) {
      ASSERT_TRUE(Pixel_equal(Image_get_pixel(&img, i, j), color));
    }
  }
  cout << "testImageFill : Passed" << endl;
}


TEST_MAIN() // Do NOT put a semicolon here
