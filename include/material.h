#pragma once
#include "brdf.h"
#include "vector3d.h"
#include "light.h"

class Material {
public:
	Material();
	// all materials are phong shaders at the moment.
	BRDF calculateBRDF();
	// fields
	BRDF brdf;
	Material(BRDF ibrdf);
};

Vector3D shading(Vector3D view, Vector3D position, Vector3D normal,
		 BRDF this_brdf, Light light);
