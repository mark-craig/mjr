#include "vector3d.h"
#include "light.h"
#include "ray.h"
#include <cfloat>
// functions for lights
Light::Light() {
	x = 0.0;
	y = 0.0;
	z = 0.0;
	r = 0.0;
	g = 0.0;
	b = 0.0;
}
Light::Light(double ix, double iy, double iz, double ir, double ig, double ib) {
	x = ix;
	y = iy;
	z = iz;
	r = ir;
	g = ig;
	b = ib;
}

Vector3D Light::getVector() {
	return Vector3D(x, y, z);
}
Vector3D Light::getLightVector(Vector3D point) {
	return Vector3D(x, y, z); // this should never be called.
	// see Light subclasses below for implementations.
}
Vector3D Light::getColor() {
	return Vector3D(r, g, b);
}

Ray Light::generateLightRay(Vector3D inposition, Vector3D innormal) {
	// === THIS SHOULD NEVER BE CALLED ======
	Vector3D direction_temp = getVector().subtract(inposition);
	float time_to = direction_temp.magnitude();
	Vector3D direction = direction_temp.normalize();
	return Ray(inposition, direction, 0.0f, time_to);

}

Vector3D PointLight::getLightVector(Vector3D point) {
	// l is the difference between the position of the light and the intersection point
	Vector3D l = getVector().subtract(point).normalize();
}

Ray PointLight::generateLightRay(Vector3D inposition, Vector3D innormal) {
	// generate light ray for a point light
	Vector3D direction_temp = getVector().subtract(inposition);
	float time_to = direction_temp.magnitude();
	Vector3D direction = direction_temp.normalize();
	return Ray(inposition, direction, 0.0f, time_to);

}

Vector3D DirectionalLight::getLightVector(Vector3D point) {
	// l is simply the normalized vector in the direction of the light
	// the point is not taken into account
	Vector3D l = getVector().normalize();// .scale(-1); I think this was an error
}

Ray DirectionalLight::generateLightRay(Vector3D inposition, Vector3D innormal) {
	// generate light ray for a directional light
	float time_to = FLT_MAX;
	Vector3D direction = getVector().scale(-1).normalize();
	return Ray(inposition, direction, 0.0f, time_to);

}