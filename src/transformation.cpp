#include "transformation.h"
#include <cmath>
#include <iostream>
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
	Matrix3f t;
	alpha = alpha * (PI / 180);
	beta = beta * (PI / 180);
	gamma = gamma * (PI / 180);
	t << 0, -gamma, beta,
		gamma, 0, -alpha,
		-beta, alpha, 0;
	Vector3f rhat  = Vector3f(alpha, beta, gamma);
	rhat.normalize();
	Matrix3f stuff; stuff =  rhat * rhat.transpose();
	float theta = rhat.norm();
	Matrix3f xprime;
	xprime = (stuff + sin(theta) * t - cos(theta) * t * t);
	Matrix4f shit;
	shit << 1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1;
	shit.block(0,0,3,3) = xprime;
	m = shit;
}