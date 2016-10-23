#pragma once
#include <vector>
#include "ray.h"
#include "shape.h"
#include "light.h"
#include "vector3d.h"

typedef std::vector<Shape> ShapeBuffer;
typedef std::vector<Light> LightBuffer;
typedef std::vector<int> IntBuffer;
typedef Vector3D Color;

class RayTracer {
public:
	// Constructor
	RayTracer(LightBuffer ilights, int inumlights, ShapeBuffer ishapes, int inumshapes);
	// values
	int threshhold;
	LightBuffer lights; int numlights; ShapeBuffer shapes; int numshapes;
	void trace(Ray& ray, int depth, Color* color);
}