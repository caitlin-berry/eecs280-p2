// Sample main.cpp for EECS 280 Setup Tutorials

#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include "jpeg.hpp"
#include "Matrix.hpp"
#include "Image.hpp"    
#include "processing.hpp" 
using namespace std;

int main(int argc, char **argv){
  // get filename
  string fileInput = argv[1];
  string fileOutput = argv[2];
  // create file streams
  ifstream fin(fileInput);
  ofstream fout(fileOutput);
  // open the file
  //fin.open(fileInput);
  // If the input or output files cannot be opened...
  if (!fin.is_open()){
    cout << "Error opening file: " << fileInput << endl;
    return 1;
  }  
  if (!fout.is_open()){
    cout << "Error opening file: " << fileInput << endl;
    return 1;
  }  
  // process the command line arguments
  // check for errors
  // check that the command line arguments obey the following rules
  // "There are 4 or 5 arguments, including the executable name itself (i.e. argv[0])."
  if (argc != 4){
    if (argc != 5){
      cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
    return 1;
    }
  }
  // create new image and find values
  Image img;
  int width = stoi(argv[3]);
  int height = 0;
  string strHeight;
  if (argc != 4){
    strHeight = argv[4];
    height = stoi(strHeight);
  } else {
    height = Image_height(&img);
  }
  // run the program
  Image_init(&img, fin);
  seam_carve(&img, width, height);
  Image_print(&img, fout);
  // successfully end !!
  return 0;
}
