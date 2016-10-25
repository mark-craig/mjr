#pragma once
#include "vector3d.h"

class BRDF {
public:
	BRDF(Vector3D a, Vector3D d, Vector3D s, Vector3D r);
	// members
	Vector3D ka;
	Vector3D kd;
	Vector3D ks;
	Vector3D kr;
};