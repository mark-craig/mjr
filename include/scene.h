#pragma once
#include "light.h"
#include "objects.h"
#include <vector>

class Scene {
public:
	// constructor
	Scene();
	// methods
	void render(int x, int y);
	void addLight(Light light);
	void addObject(Object object);
	//items
	vector<Light> lightiter;
	int numlights;
	vector<Object> objectiter;
	int numobjects;
	
};
