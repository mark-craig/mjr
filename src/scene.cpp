#include "scene.h"
#include <string>
#include <iostream>

using namespace cimg_library;
using namespace std;

Scene::Scene() {
	lightiter = {};
	numlights = 0;
	objectiter = {};
	numobjects = 0;
}

void Scene::render(int x, int y, bool write, string name) {
	Sampler sampler = Sampler(x, y);
	film = Film(x, y);
	Sample sample = Sample();
	RayTracer raytracer = RayTracer(numlights, numobjects, lightiter, objectiter);
	int n = x * y + 2000;
	ProgressBar *bar2 = new ProgressBar(n, "Rendering: ");
	bar2->SetFrequencyUpdate(1);
	int i = 0;
	while(sampler.getSample(sample)) {
		++i;
		bar2->Progressed(i);
		Ray ray = Ray();
		camera.generateRay(sample, ray, x, y);
		Vector3D color = raytracer.trace(ray, 0);
		film.commit(sample, color);
	}
	if (write) {
		cout<<"Writing"<<","<<name<<endl;
		film.write_film(name);
	}
	film.display_film();
};

void Scene::addLight(Light* light) {
	this->lightiter.push_back(light);
	this->numlights += 1;
}

void Scene::addObject(Object* object) {
	this->objectiter.push_back(object);
	this->numobjects += 1;
}
void Scene::addCamera(Camera sceneCamera) {
	camera = sceneCamera;
}

