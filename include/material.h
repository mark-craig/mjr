#pragma once
#include "brdf.h"
#include "vector3d.h"
#include "light.h"

class Material {
public:
	Material();
	// all materials are phong shaders at the moment.
	BRDF calculateBRDF();
	// members
	bool anisotropic;
	// == PUTTING THESE IN MATERIAL UNTIL I FIGURE OUT WHAT TO DO WITH THEM ===
	float sp;
	float spu;
	float spv;
	BRDF brdf;
	Material(BRDF ibrdf);
	Material(BRDF ibrdf, float isp);
	Material(BRDF ibrdf, float ispu, float ispv);
	// Justin I'm putting this in the class because it's not finding it otherwise
	Vector3D shade(Vector3D view, Vector3D position, Vector3D normal, Light light);

	// adding these for testing and abstraction
	Vector3D shadeAmbient(Vector3D ka, Vector3D lightColor);
	Vector3D shadeDiffuse(Vector3D kd, Vector3D lightColor, Vector3D lightVector, Vector3D normal);
	Vector3D shadeSpecular(Vector3D ks, Vector3D viewVector, Vector3D lightVector, Vector3D normal);

};

