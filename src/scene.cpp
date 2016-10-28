#include "scene.h"
#include <string>
#include <iostream>

using namespace cimg_library;

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
	std::cout<<lightiter.size()<<std::endl;
	int n = x * y + 2000;
	ProgressBar *bar2 = new ProgressBar(n, "Rendering: ");
	bar2->SetFrequencyUpdate(10);
	std::cout<<'z'<<std::endl;
	int i = 0;
	while(sampler.getSample(sample)) {
		++i;
		bar2->Progressed(i);
		std::cout<<'z'<<std::endl;
		Ray ray = Ray();
		std::cout<<'q'<<std::endl;
		camera.generateRay(sample, ray, x, y);
		std::cout<<'p'<<std::endl;
		Vector3D color = raytracer.trace(ray, 0);
		std::cout<<'z'<<std::endl;
		film.commit(sample, color);
		std::cout<<'k'<<std::endl;
	}
	std::cout<<'f'<<std::endl;
	film.display_film();
	film.write_film(name);
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

