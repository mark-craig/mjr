# Mark and Justin's Raytracer (MJR)
A raytracing renderer created by Justin Kirk and Mark Craig as a class project for CS 184.

Implemented in C++ and Python using the CMake build system. As such, it should potentially work on any Unix system or environment.

The following libraries and scripts were also used and are bundled in the source code:
 * Eigen (http://eigen.tuxfamily.org/index.php?title=Main_Page)
 * CImg (http://cimg.eu/)
 * Pystring (https://github.com/imageworks/pystring)
 * Google Test (https://github.com/google/googletest)

The source code was submitted for the assignment by Justin Kirk on 10/28/16.

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
