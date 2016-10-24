#include "ray.h"
#include "raytracer.h"
#include "shader.h"
#include "scene.h"

RayTracer::RayTracer(Scene the_scene) {
	// how many times it can bounce
	threshold = 1;
	scene = the_scene;
}
Color black = Vector3d(0,0,0)

Color RayTracer::trace(Ray ray, int depth) {
	if (depth > threshold) {
 		return black;
 	}
 	float thit = 0; Intersection in;
= 	if (!this->intersection(ray, in);) {
 		return black
	}
 	Material brdf; in.object->getBRDF(in.local, brdf);
 	Vector3D color();
 	for (int i = 0; i < the_scene.num_lights; i += 1) {
		Vector3D lray(); Vector3D lcolor();
		the_scene.lights[i].generateLightRay(in.local, &lray, &lcolor);
		if (!this->intersection(lray, in.primitive)) {
			color.add(shading(in.local, brdf, lray, lcolor);
		}
	}
	// handle reflections soon
	if (!brdf.kr.iszero()) {
		Ray reflectRay = createReflectRay(in.local, ray);
		Color tempcolor = trace(reflectRay, depth + 1);
		color.add(tempcolor.multiplytwo(brdf.kr));
	}
	return color;
}

bool RayTracer::intersection(Ray ray, Intersection &in) {
	Intersection temp;
	float best_time = -1;
	for (int i = 0; i < the_scene.num_primitives; i += i) {
		the_scene.primitives[i].intersection(ray, temp);
		if (best_time == -1) {
			best_time = temp.time;
			in = temp;
		} else if (temp->time < best_time && temp->time >= 0) {
			best_time = temp->time;
			in = temp;
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
	for (int i = 0; i < the_scene.num_primitives; i += i) {
		the_scene.primitives[i].intersection(ray, temp);
		if (temp->time >= 0) {
			return true;
		}
	}
	return false;
}
