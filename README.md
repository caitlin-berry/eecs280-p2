# Project 2 - Image Processing Program

## Overview
This project implements a C++ image processing program that applies various filters and transformations to images. The program operates on pixel data using matrix-based representations and performs operations such as grayscale conversion, blurring, and edge detection.

The project emphasizes algorithmic manipulation of 2D data structures and demonstrates how digital images can be processed programmatically.

## Features
- Applies image filters including:
  - grayscale conversion
  - blur (smoothing)
  - edge detection
- Processes images using 2D arrays (matrices) of pixel values
- Performs pixel-wise and neighborhood-based computations
- Reads and writes image files
- Includes test cases to verify correctness of image transformations

## How to Run

Compile the program:
```bash
g++ processing.cpp resize.cpp image.cpp matrix.cpp -o processing
```
Run the program:
```bash
./processing
```
Follow the prompts or modify input parameters to apply different filters to images.

## Concepts Used
- 2D arrays and matrix manipulation
- Nested loops for pixel processing
- Image representation and transformation
- Modular programming with multiple source files
- File input/output
- Algorithm design for filtering and convolution-like operations
- Testing and debugging

## Program Structure
- `processing.cpp`: Main program and image filter implementations
- `resize.cpp`: Image resizing functionality
- `image.cpp`: Image data structure and operations
- `matrix.cpp`: Matrix operations used for image processing
- `processing_tests.cpp`: Custom test cases
- `processing_public_tests.cpp`: Instructor-provided tests

## Example Features
- Converts images to grayscale by averaging color channels
- Applies blur by averaging neighboring pixel values
- Detects edges using differences in pixel intensity
- Supports chaining multiple transformations

## Example Output
The program takes an input image and produces a modified output image after applying selected filters. For example:
- Original image → grayscale image
- Original image → blurred image
- Original image → edge-detected image
