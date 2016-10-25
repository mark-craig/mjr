#pragma once
#include "light.h"
#include "objects.h"
#include "camera.h"
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
