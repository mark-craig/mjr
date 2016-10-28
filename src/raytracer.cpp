#include "raytracer.h"
#include <iostream>

RayTracer::RayTracer(int inumlights, int inumobjects,
					 vector<Light*> ilightiter, vector<Object*> iobjectiter) {
	// how many times it can bounce
	threshhold = 5;
	// the stuff from the scene
	numlights = inumlights;  numobjects = inumobjects;
	lightiter = ilightiter; objectiter = iobjectiter;
}

Vector3D RayTracer::trace(Ray ray, int depth) {
	// trace the given ray depth# of bounces. Output the resulting color perceived..
	Vector3D black = Vector3D(0,0,0);
	Vector3D white = Vector3D(255, 255, 255);
	// if we have bounced more than threshold, color is black
	if (depth > threshhold) {
 		return black;
 	}
 	Intersection in;
 	Object* temp_primitive;
 	Object ** primitive = &temp_primitive;
 	// if we do not hit any objects in the scene, color is black
 	//currently segfaults here
 	if (!interceptsObject(ray, in, primitive)) {
 		return black;
	}
	// return Vector3D(1,1,1);
	// otherwise we now have the correct intersection and object
 	// brdf will be obtained from Material's shading method
 	//==== I think these lines can be deleted ====
 	// BRDF brdf;
 	// primitive.getBRDF(in.position, in.normal, brdf);
 	// ===========================================
 	// this will be our final output, everything will be channeled into here.
 	Vector3D color = Vector3D();
 	Light* currentLight;
 	// for every light in the scene, generate its ray to the point
 	for (int i = 0; i < numlights; i++) {
		Ray lray = lightiter[i]->generateLightRay(in.position, in.normal); // generate a light ray for the point
		if (!intersection(lray, *primitive)) { // if nothing intersects the light ray before it hits the point
			// get the color that is added _from_the_single_light_ray_
			Vector3D shadingFromLight = (*primitive)->material.shade(ray.dir, in.position, in.normal, lightiter[i]);
			color = color.add(shadingFromLight);
		}
		color = color.add((*primitive)->material.shadeAmbient(Vector3D(), lightiter[i]->getColor()));
		if (lightiter[i]->falloff == 1) {
			color = color.scale(1.0f / lightiter[i]->getVector().subtract(in.position).magnitude());
		} else if (lightiter[i]->falloff == 2) {
			float fall = lightiter[i]->getVector().subtract(in.position).magnitude() * lightiter[i]->getVector().subtract(in.position).magnitude();
			color = color.scale(1.0f / fall);
		}
	}
	// handle reflections soon
	if (!(*primitive)->material.calculateBRDF().kr.iszero()) {
		Ray reflectRay = ray.createReflectRay(in.position, in.normal);
		Vector3D tempcolor = trace(reflectRay, depth + 1);
		color = color.add(tempcolor.multiply((*primitive)->material.calculateBRDF().kr));
		cout<<"PENOS"<<endl;
	}
	return color;
	// return white;
}

bool RayTracer::interceptsObject(Ray ray, Intersection &in, Object** primitive) {
	// find the closest intersection if there is one, capture the Interception and the Object
	Intersection temp;
	float best_time = -1.0f;
	// for every object in the scene, check if ray intersects it
	for (int i = 0; i < numobjects; i++) {
		// std::cout<<numobjects<<std::endl;
		// std::cout<<objectiter[i]<<std::endl;
		if (objectiter[i]->intersect(ray, temp)) {
			if (best_time == -1 && temp.time >= 0) {
				// this is our first hit, best time by default
				best_time = temp.time; // intersection stores hittime!
				in = temp; // capture the intersection
				*primitive = objectiter[i]; // capture the object
			} else if (temp.time < best_time && temp.time >= 0) {
				// new closest intersection
				best_time = temp.time; 
				in = temp; // capture interception
				*primitive = objectiter[i]; // capture object
			}
		}
	}
	if (best_time != -1.0f) {
		// we found an interesection
		if (* primitive ==objectiter[numobjects - 1]) {
	// // std::cout<<*primitive<<std::endl;
	// // std::cout<<objectiter[numobjects - 1]<<std::endl;
	// // std::cout<<best_time<<std::endl;
	// // std::cout<<temp.time<<std::endl;
	}
		return true;
	} else {
		// we did not
		return false;
	}
}
bool RayTracer::intersection(Ray ray, Object *object) {
	// find whether there is any intersection at all. Capture nothing.
	Intersection temp;
	for (int i = 0; i < numobjects; i ++) {
		// for every object, check if there is an intersection
		if (objectiter[i]->intersect(ray, temp) && !((Object *) objectiter[i] == object)) {
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
