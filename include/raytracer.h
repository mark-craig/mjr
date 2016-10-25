#pragma once
#include "scene.h"
#include "ray.h"
#include "intersection.h"
#include "objects.h"
#include <vector>

class RayTracer {
public:
	// Constructor
	RayTracer(int inumlights, int inumobjects,
			  vector<Light> ilightiter, vector<Object> iobjectiter);
	// values
	int threshhold;
	int numlights; int numobjects;
	vector<Light> lightiter; vector<Object> objectiter;
	Scene scene;
	Vector3D trace(Ray ray, int depth);
	bool intersection(Ray ray, Intersection &in, Object &primitive);
	bool intersection(Ray ray);
};
