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

	// other methods
	Vector3D getVector();
	Vector3D getColor();
	virtual Vector3D getLightVector(Vector3D point) =0;
	virtual Ray generateLightRay(Vector3D inposition, Vector3D innormal)=0;
};

class PointLight:public Light {
public:
	PointLight();
	PointLight(double ix, double iy, double iz, double ir, double ig, double ib);
	Vector3D getLightVector(Vector3D point);
	Ray generateLightRay(Vector3D inposition, Vector3D innormal);

};

class DirectionalLight:public Light {
public:
	DirectionalLight();
	Vector3D getLightVector(Vector3D point);
	Ray generateLightRay(Vector3D inposition, Vector3D innormal);
};