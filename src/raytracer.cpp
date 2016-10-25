#include "ray.h"
#include "raytracer.h"
#include "material.h"
#include <vector>

RayTracer::RayTracer(int inumlights, int inumobjects,
					 vector<Light> ilightiter, vector<Object> iobjectiter) {
	// how many times it can bounce
	threshhold = 1;
	// the stuff from the scene
	numlights = inumlights;  numobjects = inumobjects;
	lightiter = ilightiter; objectiter = iobjectiter;
}

Vector3D RayTracer::trace(Ray ray, int depth) {
	Vector3D black = Vector3D(0,0,0);
	if (depth > threshhold) {
 		return black;
 	}
 	float thit = 0; Intersection in; Object primitive;
 	if (!this->intersection(ray, in, primitive)) {
 		return black;
	}
 	BRDF brdf;
 	primitive.getBRDF(in.position, in.normal, brdf);
 	Vector3D color = Vector3D();
 	for (int i = 0; i < this->scene.numlights; i += 1) {
		Ray lray = this->scene.lightiter[i].generateLightRay(in.position, in.normal);
		if (!this->intersection(lray)) {
			Vector3D temp_color = shading(ray.dir, in.position, in.normal, brdf, this->scene.lightiter[i]);
			color = color.add(temp_color);
		}
	}
	// handle reflections soon
	if (!brdf.kr.iszero()) {
		Ray reflectRay = ray.createReflectRay(in.position, in.normal);
		Vector3D tempcolor = trace(reflectRay, depth + 1);
		color = color.add(tempcolor.multiplytwo(brdf.kr));
	}
	return color;
}

bool RayTracer::intersection(Ray ray, Intersection &in, Object &primitive) {
	Intersection temp;
	float best_time = -1;
	for (int i = 0; i < this->scene.numobjects; i += i) {
		this->scene.objectiter[i].intersect(ray, temp);
		if (best_time == -1) {
			best_time = temp.time;
			in = temp;
			primitive = this->scene.objectiter[i];
		} else if (temp.time < best_time && temp.time >= 0) {
			best_time = temp.time;
			in = temp;
			primitive = this->scene.objectiter[i];
		}
	}
	if (best_time != -1) {
		return true;
	} else {
		return false;
	}
}
bool RayTracer::intersection(Ray ray) {
	Intersection temp;
	for (int i = 0; i < this->scene.numobjects; i += i) {
		this->scene.objectiter[i].intersect(ray, temp);
		if (temp.time >= 0) {
			return true;
		}
	}
	return false;
}
