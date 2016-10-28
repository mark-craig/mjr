#pragma once
#include "material.h"
#include "vector3d.h"
#include "intersection.h"
#include "transformation.h"
#include "ray.h"

class Object {
	// ====== THIS IS AN ABSTRACT CLASS AND SHOULD NOT BE USED DIRECTLY =======
	// a shape is anything that can be rendered in the 3D space, whether it is defined
	// by a mathematical function or a collection of primitives
public:
	// methods
	// =0 at the end makes it a pure virtual function
	Object();
 	virtual bool intersect(Ray ray, Intersection &intersection) =0;
 	void addMaterial(Vector3D ka, Vector3D kd, Vector3D ks, float sp);
 	void addMaterial(Material the_material);
 	void addMaterial(Vector3D ka, Vector3D kd, Vector3D ks, float spu, float spv);
	void getBRDF(Vector3D position, Vector3D normal, BRDF &brdf);
	// members
	Vector3D center;
	Material material;
	Transformation *transform;
};

class Sphere:public Object {
	// the surface of a sphere can be represented by an implicit mathematical function
public: 
	// constructor
	Sphere();
	Sphere(Vector3D center, float radius);
	bool intersect(Ray ray, Intersection &intersection);
	//members
	float radius;
};

class Mesh:public Object {
	// polygon mesh is a
	Mesh();
	bool intersect(Ray ray, Intersection &intersection);
};

class CombinedObject:public Object {
	CombinedObject();
	bool intersect(Ray ray, Intersection &intersection);
};

class Triangle:public Object {
public:
	Triangle();
	Triangle(Vector3D a, Vector3D b, Vector3D c);
	bool intersect(Ray ray, Intersection &intersection);
	Triangle applyTransformation(Transformation the_transform);

	// members
	Vector3D v1;
	Vector3D v2;
	Vector3D v3;
};

class Polygon: public Object {
public:
	Polygon();
	Polygon(vector<Vector3D> vectors);
	bool intersect(Ray ray, Intersection &intersection);
	int intersectsWith(Ray ray, Vector3D a, Vector3D b);
	// members
	vector<Vector3D> vertices;

};