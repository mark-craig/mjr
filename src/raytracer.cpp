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
	// trace the given ray depth# of bounces. Output the resulting color perceived..
	Vector3D black = Vector3D(0,0,0);
	// if we have bounced more than threshold, color is black
	if (depth > threshhold) {
 		return black;
 	}
 	Intersection in;
 	Object primitive;
 	// if we do not hit any objects in the scene, color is black
 	if (!interceptsObject(ray, in, primitive)) {
 		return black;
	}
	// otherwise we now have the correct intersection and object
 	// brdf will be obtained from Material's shading method
 	//==== I think these lines can be deleted ====
 	// BRDF brdf;
 	// primitive.getBRDF(in.position, in.normal, brdf);
 	// ===========================================
 	// this will be our final output, everything will be channeled into here.
 	Vector3D color = Vector3D();
 	Light currentLight;
 	// for every light in the scene, generate its ray to the point
 	for (int i = 0; i < scene.numlights; i += 1) {
		Ray lray = scene.lightiter[i].generateLightRay(in.position, in.normal); // generate a light ray for the point
		if (!intersection(lray)) { // if nothing intersects the light ray before it hits the point
			// get the color that is added _from_the_single_light_ray_
			Vector3D shadingFromLight = primitive.material.shade(ray.dir, in.position, in.normal, scene.lightiter[i]);
			color = color.add(shadingFromLight);
		}
	}
	// // handle reflections soon
	// if (!brdf.kr.iszero()) {
	// 	Ray reflectRay = ray.createReflectRay(in.position, in.normal);
	// 	Vector3D tempcolor = trace(reflectRay, depth + 1);
	// 	color = color.add(tempcolor.multiply(brdf.kr));
	// }
	// return color;
}

bool RayTracer::interceptsObject(Ray ray, Intersection &in, Object &primitive) {
	// find the closest intersection if there is one, capture the Interception and the Object
	Intersection temp;
	float best_time = -1;
	// for every object in the scene, check if ray intersects it
	for (int i = 0; i < scene.numobjects; i += i) {
		if (scene.objectiter[i].intersect(ray, temp)) {
			if (best_time == -1) {
				// this is our first hit, best time by default
				best_time = temp.time; // intersection stores hittime!
				in = temp; // capture the intersection
				primitive = scene.objectiter[i]; // capture the object
			} else if (temp.time < best_time && temp.time >= 0) {
				// new closest intersection
				best_time = temp.time; 
				in = temp; // capture interception
				primitive = scene.objectiter[i]; // capture object
			}
		}
	}
	if (best_time != -1) {
		// we found an interesection
		return true;
	} else {
		// we did not
		return false;
	}
}
bool RayTracer::intersection(Ray ray) {
	// find whether there is any intersection at all. Capture nothing. (Justin is this right?)
	Intersection temp;
	for (int i = 0; i < scene.numobjects; i += i) {
		// for every object, check if there is an intersection
		if (scene.objectiter[i].intersect(ray, temp)) {
			// if there was an intersection
			if (ray.valid_t(temp.time)) { // and it is within our time limits
			// we found an intersection
			return true;
			}
		}
	}
	// we did not
	return false;
}
