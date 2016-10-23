#include "CImg.h"
#include "scene.h"
#include "sample.h"
#include "sampler.h"

using namespace cimg_library;

Scene::Scene() {
}

void Scene::render() {
	Sampler sampler = Sampler(700, 500);
	Sample sample = Sample();
	while(sampler.getSample(sample)) {
		
	}
};