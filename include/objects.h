#pragma once
#include "vector3d.h"
#include "intersection.h"
#include "ray.h"

class Object {
	// a shape is anything that can be rendered in the 3D space, whether it is defined
	// by a mathematical function or a collection of primitives
public:
	virtual ~Object() =0;
	// methods
	// =0 at the end makes it a pure virtual function
	virtual bool intersect(Ray ray, Intersection &intersection) =0;
	// members
	Vector3D center;
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

class PolygonMesh:public Object {
	// polygon mesh is a
	PolygonMesh();
	bool intersect(Ray ray, Intersection &intersection);
};

class CombinedObject:public Object {
	CombinedObject();
	bool intersect(Ray ray, Intersection &intersection);
};

class Polygon:public Object {
	Polygon();
	bool intersect(Ray ray, Intersection &intersection);

};