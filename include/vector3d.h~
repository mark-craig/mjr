#pragma once
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Vector3D
{
public:
	// fields
	float x;
	float y;
	float z;
	
	// constructors
	Vector3D();
	Vector3D(float inputx, float inputy, float inputz);
	// other methods
	void zero_out();
	void modify(float inputx, float inputy, float inputz);
	void modify(Vector3D copy);
	float magnitude();
	Vector3D normalize();
	Vector3D scale(float scalefactor);
	Vector3D add(Vector3D v2);
	Vector3D subtract(Vector3D v2);
	float dot(Vector3D v2);
	Vector3D cross(Vector3D v2);
	Vector3D project(Vector3D v2);
	float getTheta(Vector3D v2);
	vector<float> value();
};

