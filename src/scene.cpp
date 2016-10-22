#include "CImg.h"
#include "scene.h"
#include "sample.h"
#include "sampler.h"

using namespace cimg_library;

void Scene::render() {
	Sampler sampler = Sampler(640, 480);
	Sample sample = Sample();
	while(sampler.getSample(sample)) {
	}
};