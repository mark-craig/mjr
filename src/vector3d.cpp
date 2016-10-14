#include <cmath>
#include <iostream>
#include "vector3d.h"
using namespace std;


// functions for vectors
Vector3D::Vector3D() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector3D::Vector3D(double inputx, double inputy, double inputz) {
	x = inputx;
	y = inputy;
	z = inputz;
}

double Vector3D::magnitude(){
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));	
}
	
Vector3D Vector3D::normalize(){
	// returns a new vector in the same direction, such that the magnitude is 1
	double mag = magnitude();
	return Vector3D(x / mag, y / mag, z / mag);
}

Vector3D Vector3D::scale(double scalefactor) {
	// returns a new vector with components multiplied by the given scale factor
	return Vector3D(x * scalefactor, y * scalefactor, z * scalefactor);
}

Vector3D Vector3D::add(Vector3D v2) {
	// returns the vector that is the sum between two vectors
	double newx = x + v2.x;
	double newy = y + v2.y;
	double newz = z + v2.z;
	return Vector3D(newx, newy, newz);
}

Vector3D Vector3D::subtract(Vector3D v2) {
	// returns the vector that is the difference between two vectors
	double newx = x - v2.x;
	double newy = y - v2.y;
	double newz = z - v2.z;
	return Vector3D(newx, newy, newz);
}

double Vector3D::dot(Vector3D v2) {
	// returns a double that is the dot product between two vectors
	return x*v2.x + y*v2.y + z*v2.z;
}

Vector3D Vector3D::cross(Vector3D v2) {
	// returns the vector that is the crossproduct of the vector and v2.
	Vector3D xunit = Vector3D(1, 0 ,0);
	Vector3D yunit = Vector3D(0, 1, 0);
	Vector3D zunit = Vector3D(0, 0, 1);

	return xunit.scale(y * v2.z - z * v2.y).add(yunit.scale(z * v2.x - x * v2.z)).add(zunit.scale(x * v2.y - y * v2.x));
}

Vector3D Vector3D::project(Vector3D v2) {
	// returns the projection of the vector onto vector v2
	double scalarProj = (this->dot(v2))*(1.0/v2.magnitude());
	return (v2.scale(1.0/v2.magnitude())).scale(scalarProj);

}

double Vector3D::getTheta(Vector3D v2) {
	// find the angle between the two vectors
	double cosTheta = (this->dot(v2)) * (this->magnitude() * v2.magnitude());
	return acos(cosTheta);
}

