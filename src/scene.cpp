#include "scene.h"

using namespace cimg_library;

Scene::Scene() {
	lightiter = {};
	numlights = 0;
	objectiter = {};
	numobjects = 0;
}

void Scene::render(int x, int y) {
	Sampler sampler = Sampler(x, y);
	Film film = Film(x, y);
	Sample sample = Sample();
	RayTracer raytracer = RayTracer(numlights, numobjects, lightiter, objectiter);
	while(sampler.getSample(sample)) {
		Ray ray = Ray();
		camera.generateRay(sample, ray, -1, -1);
		Vector3D color = raytracer.trace(ray, 0);
		film.commit(sample, color);
	}
	film.display_film();
};

void Scene::addLight(Light light) {
	this->lightiter.push_back(light);
	this->numlights += 1;
}

void Scene::addObject(Object object) {
	this->objectiter.push_back(object);
	this->numobjects += 1;
}
void Scene::addCamera(Camera sceneCamera) {
	camera = sceneCamera;
}

