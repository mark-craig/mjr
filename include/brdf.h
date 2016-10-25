#pragma once
#include "vector3d.h"

class BRDF {
public:
	BRDF();
	BRDF(Vector3D ika, Vector3D ikd, Vector3D iks, Vector3D ikr); 
	// members
	Vector3D ka;
	Vector3D kd;
	Vector3D ks;
	Vector3D kr;
};