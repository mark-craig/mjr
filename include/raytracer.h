#pragma once
#include "scene.h"

class RayTracer {
public:
	// Constructor
	RayTracer(Scene the_scene);
	// values
	int threshhold;
	Scene scene;
	void trace(Ray ray, int depth);
}
