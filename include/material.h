#pragma once
#include "brdf.h"

class Material {
public:
	Material();
	// all materials are phong shaders at the moment.
	BRDF calculateBRDF();
};