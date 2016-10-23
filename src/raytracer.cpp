#include "ray.h"
#include "raytracer.h"

RayTracer::RayTracer(LightBuffer ilights, int inumlights, ShapeBuffer ishapes, int inumshapes) {
	threshold = 1;
}

void RayTracer::trace(Ray& ray, int depth, Color color) {
	if (depth > threshold) {
		color.zero_out()
		return;
	}
	int thit; int in;
	if (!primitive.intersect(ray, &thit, &in)) {
		color.zero_out();
		return
	}
	Vector3D brdf;
	in.primitive->getBRDF(in.local, brdf);
	for (int i = 0; i < )
}