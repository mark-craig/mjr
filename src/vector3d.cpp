#include "vector3d.h"
using namespace std;

// constructors
Vector3D::Vector3D() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vector3D::Vector3D(float inputx, float inputy, float inputz) {
	x = inputx;
	y = inputy;
	z = inputz;
}

void Vector3D::zero_out() {
	// zero's out the 3D vector
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}

void Vector3D::modify(float inputx, float inputy, float inputz) {
	// modify the values of the Vector
	this->x = inputx;
	this->y = inputy;
	this->z = inputz;
}

void Vector3D::modify(Vector3D copy) {
	// deep copy of the original Vector
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
}
Vector3D Vector3D::multiplytwo(Vector3D other) {
	// multiply two vectors together
	float tempx = this->x * other.x;
	float tempy = this->y * other.y;
	float tempz = this->z * other.z;
	return Vector3D(tempx, tempy, tempz);
}
bool Vector3D::iszero() {
	// returns true if the vector has a magnitude of 0
	if (this->x == 0.0 && this->y == 0.0 && this->z == 0.0) {
		return true;
	}
	return false;
}

float Vector3D::magnitude(){
	// returns the magnitude of the vector
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));	
}
	
Vector3D Vector3D::normalize(){
	// returns a new vector in the same direction, such that the magnitude is 1
	float mag = magnitude();
	return Vector3D(x / mag, y / mag, z / mag);
}

Vector3D Vector3D::scale(float scalefactor) {
	// returns a new vector with components multiplied by the given scale factor
	return Vector3D(x * scalefactor, y * scalefactor, z * scalefactor);
}

Vector3D Vector3D::add(Vector3D v2) {
	// returns the vector that is the sum between two vectors
	float newx = x + v2.x;
	float newy = y + v2.y;
	float newz = z + v2.z;
	return Vector3D(newx, newy, newz);
}

Vector3D Vector3D::subtract(Vector3D v2) {
	// returns the vector that is the difference between two vectors
	float newx = x - v2.x;
	float newy = y - v2.y;
	float newz = z - v2.z;
	return Vector3D(newx, newy, newz);
}

float Vector3D::dot(Vector3D v2) {
	// returns a float that is the dot product between two vectors
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
	float scalarProj = (this->dot(v2))*(1.0/v2.magnitude());
	return (v2.scale(1.0/v2.magnitude())).scale(scalarProj);

}

float Vector3D::getTheta(Vector3D v2) {
	// find the angle between the two vectors
	float cosTheta = (this->dot(v2)) * (this->magnitude() * v2.magnitude());
	return acos(cosTheta);
}

vector<float> Vector3D::value() {
	vector<float> result = {x, y, z};
	return result;
}
