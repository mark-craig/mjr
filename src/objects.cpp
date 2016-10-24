#include "objects.h"
Sphere::Sphere(Vector3D icenter, float iradius) {
	center = icenter;
	radius = iradius;
}
bool Sphere::intersect(Ray &ray, vector<Intersection> &intersections, int depth) {
	return true;
}