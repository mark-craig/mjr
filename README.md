# Mark and Justin's Raytracer (MJR)
A raytracing renderer created by Justin Kirk and Mark Craig as a class project for CS 184.

Implemented in C++ using the CMake build system. As such, it should potentially work on any Unix system/environment.

The following libraries and scripts were also used and are bundled in the source code:
 * Eigen (http://eigen.tuxfamily.org/index.php?title=Main_Page)
 * CImg (http://cimg.eu/)
 * Pystring (https://github.com/imageworks/pystring)
 * Google Test (https://github.com/google/googletest)
 * C++ Progress Bar (https://github.com/htailor/cpp_progress_bar)

The source code was submitted for the assignment by Justin Kirk on 10/28/16.
## Features
Our raytracer has the following features implemented:
 * Render polygons (i.e. read a simple .obj file and render the polygons in it)
 * Use simple Phong Shading (in color)
 * Compute shadows
 * Compute reflections
 * Apply linear transformations to objects*
 * Use point and directional lights
 * Write its output to a standard image format such as jpg, ppm, png, or tif.

*Normal calculation not working properly for rotation and scaling.


## Build Instructions
From the directory, simply run the following commands:
~~~~
mkdir build
cd build
cmake ..
make
./mjr
~~~~

## Building the Test Suite
Almost the same as above:
~~~~
mkdir build
cd build
cmake -Dtest=ON ..
make
./test/unitTests
~~~~

## Command-Line Arguments
~~~~
./mjr [scene_plaintext] --write
~~~~

The --write flag is used to save the output image as a PNG file ('output.png') in the same directory. Otherwise, it will simply display in a window.
If ./mjr is simply called by itself, it will render an arbitrary example scene.

## Examples
Example scene files and images of our raytracer's output for them can be found in the /examples/ directory.
In order to run one of the examples, simply copy the "input-nn" file desired to the /build/ directory where the executable resides and pass the filename in as the argument.
