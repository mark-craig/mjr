#include "objects.h"
Sphere::Sphere(Vector3D icenter, float iradius) {
	center = icenter;
	radius = iradius;
}
bool Sphere::intersect(Ray &ray, Intersection &intersection) {
	vector<float> dvalues = ray.dir.value();
	vector<float> cvalues = center.value();
	vector<float> evalues = ray.pos.value();

	float a;
	float b;
	float c;
	float discriminant;
	Vector3D intersectionPoint;
	for(int i = 0; i < 3, i++) {
		

	}
	float b = ray.dir * (ray.origin)
}