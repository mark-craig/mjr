#include "ray.h"
#include "raytracer.h"
#include "scene.h"
#include "material.h"

RayTracer::RayTracer(Scene the_scene) {
	// how many times it can bounce
	threshhold = 1;
	scene = the_scene;
}
Vector3D black = Vector3D(0,0,0);

Vector3D RayTracer::trace(Ray ray, int depth) {
	if (depth > threshhold) {
 		return black;
 	}
 	float thit = 0; Intersection in; Object primitive;
 	if (!this->intersection(ray, in, primitive)) {
 		return black;
	}
 	BRDF brdf;
 	primitive.getBRDF(in.position, in.normal, brdf);
 	Vector3D color();
 	for (int i = 0; i < this->scene.numlights; i += 1) {
		Vector3D lray = this->scene.lightiter[i].generateLightRay(in.position, in.normal);
		if (!this->intersection(lray, in.primitive)) {
			Vector3D temp_color = material::shading(ray.dir in.position, in.normal, brdf, the_scene.lightiter[i])
			color.add(temp_color);
		}
	}
	// handle reflections soon
	if (!brdf.kr.iszero()) {
		Ray reflectRay = ray.createReflectRay(in.position, in.normal);
		Color tempcolor = trace(reflectRay, depth + 1);
		color.add(tempcolor.multiplytwo(brdf.kr));
	}
	return color;
}

bool RayTracer::intersection(Ray ray, Intersection &in, Object &primitive) {
	Intersection temp;
	float best_time = -1;
	for (int i = 0; i < the_scene.numobjects; i += i) {
		the_scene.objectiter[i].intersection(ray, temp);
		if (best_time == -1) {
			best_time = temp.time;
			in = temp;
			primitive = the_scene.objectiter[i]
		} else if (temp->time < best_time && temp->time >= 0) {
			best_time = temp->time;
			in = temp;
			primitive = the_scene.objectiter[i]
		}
	}
	if (best_time != -1) {
		return true;
	} else {
		return false;
	}
}
bool RayTracer::intersection(Ray ray, Primitive object) {
	Intersection temp;
	for (int i = 0; i < the_scene.numobjects; i += i) {
		the_scene.objectiter[i].intersection(ray, temp);
		if (temp->time >= 0) {
			return true;
		}
	}
	return false;
}
