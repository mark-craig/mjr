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
	Ray(Vector3D position, Vector3D direction, float tMinimum=0.0f, float tMaximum=FLT_MAX);

	//methods
	Vector3D t(float time);
};