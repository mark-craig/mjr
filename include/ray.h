#pragma once
#include "vector3d.h"
#include <cfloat>
class Ray {
public:
	Vector3D pos;
	Vector3D dir;
	float t_min;
	float t_max;

	//constructor
	Ray();
	Ray(Vector3D position, Vector3D direction, float tMinimum=FLT_MIN, float tMaximum=FLT_MAX);

	//methods
	Ray createReflectRay(Vector3D inposition, Vector3D innormal);
	Vector3D t(float time);
	bool valid_t(float time);
};