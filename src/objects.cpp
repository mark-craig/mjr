#include "objects.h"
#include <cmath>

Object::Object() {}

void Object::getBRDF(Vector3D position, Vector3D normal, BRDF &brdf){
	brdf = material.calculateBRDF();
}

bool Object::intersect(Ray ray, Intersection &intersection) {
	// ABSTRACT METHOD, THIS SHOULD NEVER BE CALLED !!!!!
	return false;
}

Sphere::Sphere(Vector3D icenter, float iradius) {
	center = icenter;
	radius = iradius;
}
bool Sphere::intersect(Ray ray, Intersection &intersection) {
	Vector3D d = ray.dir;
	Vector3D c = center;
	Vector3D e = ray.pos;

	// slightly different quadratic function, pg. 77 Shirley & Marschner
	float A = d.dot(d);
	float B = -e.subtract(c).dot(d);
	float C = e.subtract(c).dot(e.subtract(c)) - pow(radius, 2);
	float discriminant = pow(B, 2) - A*C;
	if (discriminant < 0) {
		return false;
	} else {
		float t1 = (-B + sqrt(discriminant))/pow(A, 2);
		float t2 = (-B - sqrt(discriminant))/pow(A, 2);
		float t;
		if (!ray.valid_t(t1) and !ray.valid_t(t2)) {
			// roots exist, but outside of bounds
			return false;
		}
		if (!ray.valid_t(t1) and ray.valid_t(t2)) {
			// only t2 within bounds
			t = t2;
		} if (!ray.valid_t(t2) and ray.valid_t(t1)) {
			// only t1 within bounds
			t = t1;
		} else {
			// both within bounds, find closest intersection
			float t = min(t1, t2);
		}
		
		intersection.position = ray.t(t);
		intersection.normal = intersection.position.subtract(center);
		intersection.time = t;
		return true;
	}
}

bool Polygon::intersect(Ray ray, Intersection &intersection) {
	return false;
}