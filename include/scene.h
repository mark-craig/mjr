#pragma once
#include "CImg.h"
#include "light.h"
#include "sample.h"
#include "sampler.h"
#include "objects.h"
#include "ray.h"
#include "vector3d.h"
#include "film.h"
#include "camera.h"
#include "raytracer.h"
#include "progress_bar.hpp"
#include <vector>



class Scene {
public:
	// constructor
	Scene();
	// methods
	void render(int x, int y);
	void addLight(Light light);
	void addObject(Object object);
	void addCamera(Camera sceneCamera);
	//items
	vector<Light> lightiter;
	int numlights;
	vector<Object> objectiter;
	int numobjects;
	Camera camera;
	
};
