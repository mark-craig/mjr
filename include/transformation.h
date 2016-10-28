#pragma once
#include "objects.h"
#include <Eigen/Dense>

using namespace Eigen;

class Transformation { 
// abstract class
public:
	Transformation();
	void apply(Triangle &target);
	// members
	Matrix4f m;
	Matrix4f inv_m; // inverse
};

class Scale:public Transformation {
public:
	Scale(float x, float y, float z);
};

class Translate:public Transformation {
public:
	Translate(float x, float y, float z);
};

class Rotate:public Transformation {
public:
	Rotate(float alpha, float beta, float gamma);
	// members

};