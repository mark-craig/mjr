#include "objects.h"
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

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
	Vector3D d = ray.dir.normalize();
	Vector3D c = center;
	Vector3D e = ray.pos;

	// slightly different quadratic function, pg. 77 Shirley & Marschner
	float A = d.dot(d);
	float B = 2*d.dot(e.subtract(c));
	float C = e.subtract(c).dot(e.subtract(c)) - pow(radius, 2);

	float discriminant = pow(B, 2) - 4*A*C;
	if (discriminant < 0) {
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
		// cout << "ray hit at" << intersection.position.x << intersection.position.y << intersection.position.z << endl;
		return true;
	}
}

Triangle::Triangle(Vector3D a, Vector3D b, Vector3D c) {
	v1 = a;
	v2 = b;
	v3 = c;
}

bool Triangle::intersect(Ray ray, Intersection &intersection) {
	// calculates whether ray interesects triangle, captures result in intersection
	// Shirley & Marschner pg. 79
	// this could potentially be faster using decomposition of Cramer's rule
	// but I believe in the powers of Eigen
	
	Matrix3f A;
	A << v1.x - v2.x, v1.x - v3.x, ray.dir.x,
		 v1.y - v2.y, v1.y - v3.y, ray.dir.y,
 		 v1.z - v2.z, v1.z - v3.z, ray.dir.z;
 	float detA = A.determinant();
 	Matrix3f tMatrix;
 	tMatrix << v1.x - v2.x, v1.x - v3.x, v1.x - ray.pos.x,
		 	   v1.y - v2.y, v1.y - v3.y, v1.y - ray.pos.y,
 		 	   v1.z - v2.z, v1.z - v3.z, v1.z - ray.pos.z;
 	float t = tMatrix.determinant()/detA;
 	if (t < ray.t_min || t > ray.t_max) {
 		return false;
 	}
 	Matrix3f gammaMatrix;
 	gammaMatrix << v1.x - v2.x, v1.x - ray.pos.x, ray.dir.x,
 				   v1.y - v2.y, v1.y - ray.pos.y, ray.dir.y,
 				   v1.z - v2.z, v2.z - ray.pos.z, ray.dir.z;
 	float gamma = gammaMatrix.determinant()/detA;
 	if (gamma < 0 || gamma > 1) {
 		return false;
 	}
 	Matrix3f betaMatrix;
 	betaMatrix << v1.x - ray.pos.x, v1.x - v3.x, ray.dir.x,
 				  v1.y - ray.pos.y, v1.y - v3.y, ray.dir.y,
 				  v1.z - ray.pos.z, v1.z - v3.z, ray.dir.z;
 	float beta = betaMatrix.determinant()/detA;
 	if (beta < 0 || beta > 1 - gamma) {
 		return false;
 	}
 	intersection.position = ray.t(t);
 	intersection.normal = v1.subtract(v2).cross(v1.subtract(v3)).scale(-1);
 	return true;

}