#pragma once
#include "vector3d.h"
#include "ray.h"

class Light
// ====== THIS IS AN ABSTRACT CLASS AND SHOULD NOT BE USED DIRECTLY =======
{
public:
	//position
	double x;
	double y;
	double z;
	//color
	double r;
	double g;
	double b;

	//constructors
	Light();
	Light(double ix, double iy, double iz, double ir, double ig, double ib);

	// other methods
	Vector3D getVector();
	Vector3D getLightVector(Vector3D point);
	Vector3D getColor();
	Ray generateLightRay(Vector3D inposition, Vector3D innormal);
};

class PointLight:public Light {
	PointLight();
	Vector3D getLightVector(Vector3D point);
	Ray generateLightRay(Vector3D inposition, Vector3D innormal);

};

class DirectionalLight:public Light {
	DirectionalLight();
	Vector3D getLightVector(Vector3D point);
	Ray generateLightRay(Vector3D inposition, Vector3D innormal);
};