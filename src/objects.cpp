#include "objects.h"

Object::Object() {}

void Object::addMaterial(Vector3D ka, Vector3D kd, Vector3D ks, float sp) {
	Material newmat = Material();
	newmat.anisotropic = false;
	BRDF newbrdf = BRDF(ka, kd, ks, Vector3D(0.0, 0.0, 0.0)); //will replace when reflection implemented
	newmat.brdf = newbrdf;
	newmat.sp = sp;
	material = newmat;
}
void Object::addMaterial(Vector3D ka, Vector3D kd, Vector3D ks, float spu, float spv) {
	Material newmat = Material();
	newmat.anisotropic = true;
	BRDF newbrdf = BRDF(ka, kd, ks, Vector3D(0.0, 0.0, 0.0)); //will replace when reflection implemented
	newmat.brdf = newbrdf;
	newmat.spu = spu;
	newmat.spv = spv;
	material = newmat;
}


void Object::getBRDF(Vector3D position, Vector3D normal, BRDF &brdf){
	brdf = material.calculateBRDF();
}

// bool Object::intersect(Ray ray, Intersection &intersection) {
// 	// ABSTRACT METHOD, THIS SHOULD NEVER BE CALLED !!!!!
// 	cout << "ERROR: ABSTRACT METHOD WAS CALLED SOMEHOW" << endl;
// 	return false;
// }

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
	float B = 2*d.dot(e.subtract(c));
	float C = e.subtract(c).dot(e.subtract(c)) - pow(radius, 2);

	float discriminant = pow(B, 2) - 4*A*C;
	if (discriminant < 0) {
		cout << "discriminant < 0" << endl;
		return false;
	} else {
		float t1 = (-B + sqrt(discriminant))/2*A;
		float t2 = (-B - sqrt(discriminant))/2*A;
		float t;
		if (!ray.valid_t(t1) and !ray.valid_t(t2)) {
			// roots exist, but outside of bounds
			// cout << "both roots outside of bounds" << endl;
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
			t = min(t1, t2);
		}
		
		intersection.position = ray.t(t);
		// bottom of pg. 77
		intersection.normal = intersection.position.subtract(center).scale(1/radius);
		intersection.time = t;
		// cout << "returning true" << endl;
		return true;
	}
}

bool Polygon::intersect(Ray ray, Intersection &intersection) {
	return false;
}