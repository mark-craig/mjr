#include "transformation.h"
#include <cmath>
using namespace std;
#define PI 3.14159265

Transformation::Transformation() {
	m << 1, 0, 0, 0,
		 0, 1, 0, 0,
		 0, 0, 1, 0,
		 0, 0, 0, 1;
}

Transformation::Transformation(Transformation left, Transformation right) {
	m = left.m*right.m;
}

bool Transformation::isIdentity() {
	Matrix4f temp;
	temp << 1, 0, 0, 0,
	     	0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1;
	return m == temp;
}


Scale::Scale(float x, float y, float z) {
	m << x, 0, 0, 0,
		 0, y, 0, 0,
		 0, 0, z, 0,
		 0, 0, 0, 1;
}

Translate::Translate(float x, float y, float z) {
	m << 1, 0, 0, x,
		 0, 1, 0, y,
		 0, 0, 1, z,
		 0, 0, 0, 1;
}

Rotate::Rotate(float alpha, float beta, float gamma) {
	Matrix4f t;
	t <<   1, 0, 0, 0,
		   0, cos(alpha * PI / 180), -sin(alpha * PI / 180), 0,
		   0, sin(alpha * PI / 180), cos(alpha * PI / 180), 0,
		   0, 0, 0, 1;
	Matrix4f s;
	s << cos(beta * PI / 180), 0, sin(beta * PI / 180), 0,
		 0, 1, 0, 0,
		 -sin(beta * PI / 180), 0, cos(beta * PI / 180), 0,
		 0, 0, 0, 1;
	Matrix4f r;
	r << cos(beta * PI / 180), -sin(beta * PI / 180), 0, 0,
		 sin(beta * PI / 180), cos(beta * PI / 180), 0, 0,
		  0, 0, 1, 0,
		  0, 0, 0, 1;
	
	m = t*s*r;
}