#include "objects.h"
#include "transformation.h"
#include <cfloat>
#include <iostream>

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
void Object::addMaterial(Material the_material) {
	material = the_material;
}

void Object::getBRDF(Vector3D position, Vector3D normal, BRDF &brdf){
	brdf = material.calculateBRDF();
}
void Object::addTransformation(Transformation newTransform) {
	transform = newTransform;
}



Sphere::Sphere(Vector3D icenter, float iradius) {
	center = icenter;
	radius = iradius;
}
bool Sphere::intersect(Ray ray, Intersection &intersection) {
	// convert ray to object space
	Vector4f dir = Vector4f(ray.dir.x, ray.dir.y, ray.dir.z, 0.0f);
	Vector4f pos = Vector4f(ray.pos.x, ray.pos.y, ray.pos.z, 1.0f);
	// cout<<center.x<<','<<center.y<<','<<center.z<<endl;
	Vector4f new_dir;
	Vector4f new_pos;
	if (transform.isIdentity()) {
		new_dir = dir;
		new_pos = pos;
	}
	else {
		// cout<<"pre"<<transform.m<<endl;
		// cout<<"inv"<<transform.m.inverse()<<endl;
		new_dir = transform.m.inverse()*dir;
		new_pos = transform.m.inverse()*pos;
		// cout<<'p'<<dir<<','<<pos<<endl;
		// cout<<"kek"<<new_dir<<','<<new_pos<<endl;
	}
	Vector3D d = Vector3D(new_dir[0], new_dir[1], new_dir[2]);
	Vector3D c = center;
	Vector3D e = Vector3D(new_pos[0], new_pos[1], new_pos[2]);

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
		
		intersection.position = e.add(d.scale(t));
		// bottom of pg. 77
		intersection.normal = intersection.position.subtract(center).normalize();
		// cout<<"fssss"<<endl;
		// cout<<intersection.normal.x<<','<<intersection.normal.y<<','<<intersection.normal.z<<endl;
		// back to world space
		Vector4f innom = Vector4f(intersection.normal.x, intersection.normal.y, intersection.normal.z, 0.0f);
		Vector4f new_innom;
		if (transform.isIdentity()) {
			new_innom = innom;
		}
		else {
			new_innom = transform.m.inverse().transpose()*innom;
		}
		// intersection.position = Vector3D(new_inpos[0], new_inpos[1], new_inpos[2]);
		intersection.position = ray.t(t);
		intersection.normal = Vector3D(new_innom[0], new_innom[1], new_innom[2]).normalize();
		// cout<<"Kill me"<<","<<t<<endl;
		// cout<<intersection.position.x<<','<<intersection.position.y<<','<<intersection.position.z<<endl;
		// cout<<intersection.normal.x<<','<<intersection.normal.y<<','<<intersection.normal.z<<endl;
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
	Vector4f dir = Vector4f(ray.dir.x, ray.dir.y, ray.dir.z, 0.0f);
	Vector4f pos = Vector4f(ray.pos.x, ray.pos.y, ray.pos.z, 1.0f);
	Vector4f new_dir;
	Vector4f new_pos;
	if (transform.isIdentity()) {
		new_dir = dir;
		new_pos = pos;
	}
	else {
		new_dir = transform.m.inverse()*dir;
		new_pos = transform.m.inverse()*pos;
	}
	Vector3D d = Vector3D(new_dir[0], new_dir[1], new_dir[2]);
	Vector3D e = Vector3D(new_pos[0], new_pos[1], new_pos[2]);

	Matrix3f A;
	A << v1.x - v2.x, v1.x - v3.x, d.x,
		 v1.y - v2.y, v1.y - v3.y, d.y,
 		 v1.z - v2.z, v1.z - v3.z, d.z;
 	float detA = A.determinant();
 	Matrix3f tMatrix;
 	tMatrix << v1.x - v2.x, v1.x - v3.x, v1.x - e.x,
		 	   v1.y - v2.y, v1.y - v3.y, v1.y - e.y,
 		 	   v1.z - v2.z, v1.z - v3.z, v1.z - e.z;
 	float t = tMatrix.determinant()/detA;
 	if (t < ray.t_min || t > ray.t_max) {
 		return false;
 	}
 	Matrix3f gammaMatrix;
 	gammaMatrix << v1.x - v2.x, v1.x - e.x, d.x,
 				   v1.y - v2.y, v1.y - e.y, d.y,
 				   v1.z - v2.z, v2.z - e.z, d.z;
 	float gamma = gammaMatrix.determinant()/detA;
 	if (gamma < 0 || gamma > 1) {
 		return false;
 	}
 	Matrix3f betaMatrix;
 	betaMatrix << v1.x - e.x, v1.x - v3.x, d.x,
 				  v1.y - e.y, v1.y - v3.y, d.y,
 				  v1.z - e.z, v1.z - v3.z, d.z;
 	float beta = betaMatrix.determinant()/detA;
 	if (beta < 0 || beta > 1 - gamma) {
 		return false;
 	}
 	intersection.position = ray.t(t);
 	 // Justin's solution for making sure normal is pointed in right direction
 	Vector3D n = v1.subtract(v2).cross(v1.subtract(v3));
 	intersection.normal = n.scale(-n.dot(d)/abs(n.dot(d)));
 	Vector4f inpos = Vector4f(intersection.position.x, intersection.position.y, intersection.position.z, 1.0f);
	Vector4f innom = Vector4f(intersection.normal.x, intersection.normal.y, intersection.normal.z, 0.0f);
	Vector4f new_inpos;
	Vector4f new_innom;
	if (transform.isIdentity()) {
		new_inpos = inpos;
		new_innom = innom;
	}
	else {
		new_inpos = transform.m*inpos;
		new_innom = transform.m*innom;
	}
	intersection.position = Vector3D(new_inpos[0], new_inpos[1], new_inpos[2]);
	intersection.normal = Vector3D(new_innom[0], new_innom[1], new_innom[2]).normalize();
 	return true;
}

// Triangle Triangle::applyTransformation(Transformation transform) {
// 	// convert internal Vector class to Eigen representation
//  	Vector4f va(v1.x, v1.y, v1.z, 0);
//  	Vector4f vb(v2.x, v2.y, v2.z, 0);
//  	Vector4f vc(v3.x, v3.y, v3.z, 0);
//  	// apply transformation
//  	va = transform.m*va;
//  	vb = transform.m*vb;
//  	vc = transform.m*vc;
//  	// // set back to internal representation in place
//  	Triangle newT = Triangle();
//  	newT.v1 = Vector3D(va[0], va[1], va[2]);
//  	newT.v2 = Vector3D(vb[0], vb[1], vb[2]);
//  	newT.v3 = Vector3D(vc[0], vc[1], vc[2]);

// }

Polygon::Polygon(vector<Vector3D> vectors) {
	for (int i = 0; i < vectors.size(); i++) {
		this->vertices.push_back(vectors[i]);
	}
}

bool Polygon::intersect(Ray ray, Intersection &intersection) {
	//Find whether the ray intersects the polygon, capture intersection if true
	// Shirley & Marschner pg. 80
 	Vector3D n = vertices[0].subtract(vertices[1]).cross(vertices[0].subtract(vertices[2])); // assuming geometry is manifold
	// compute intersection points
	float t = vertices[0].subtract(ray.pos).dot(n)/(1/(ray.dir.dot(n)));
	float index0;
	float index1;
	if ((abs(n.z) > abs(n.x)) && (abs(n.z) > abs(n.y))) {
		index0 = 0;
		index1 = 1;
	} else if (abs(n.y) > abs(n.x)) {
		index0 = 0;
		index1 = 2;
	} else {
		index0 = 1;
		index1 = 2;
	}
	// project vectors onto 2d plane
	Ray projectedRay = Ray(Vector3D(ray.t(t).index(index0), ray.t(t).index(index1), 0), Vector3D(1, 0, 0));
	vector<Vector3D> projectedVertices;
	for(int i = 0; i < vertices.size(); i++) {
		projectedVertices.push_back(Vector3D(vertices[i].index(index0), vertices[i].index(index1), 0));
	}

	int sum = 0;
	for(int i = 0; i < vertices.size() - 2; i++) {
		sum += intersectsWith(projectedRay,
							  projectedVertices[i],
							  projectedVertices[i+1]);
							  
	}
	// handle last term
	sum += intersectsWith(projectedRay, projectedVertices[0], projectedVertices[projectedVertices.size() - 1]);
	// cerr << sum << endl;
	if (sum % 2 == 1) {
		intersection.normal = n;
		intersection.position = ray.t(t);
		intersection.time = t;
		return true;
	} else {
		return false;
	}
}


int Polygon::intersectsWith(Ray ray, Vector3D a, Vector3D b) {
	// determine if 2D ray intersects with the line segment formed by the two points (z=0)
	// returns 0 if it does not intersect, returns 1 if it does
	// https://rootllama.wordpress.com/2014/06/20/ray-line-segment-intersection-test-in-2d/
	Vector3D v1 = ray.pos.subtract(a);
	Vector3D v2 = b.subtract(a);
	Vector3D v3 = Vector3D(-ray.dir.y, ray.dir.x, 0);
	float t1 = (v2.x*v1.y - v2.y*v1.x)/(v2.dot(v3));
	float t2 = v1.dot(v3)/v2.dot(v3);
	// cerr << t1 << "t1" << endl;
	// cerr << t2 << "t2" << endl;
	if ((t1 >= 0) && (0 <= t2) && (t2 <= 1)) {
		return 1;
	} else {
		return 0;
	}
}