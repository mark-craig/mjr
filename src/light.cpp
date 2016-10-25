#include "vector3d.h"
#include "light.h"
#include "ray.h"
#include <cfloat>
// functions for lights
Light::Light() {
	pointLight = false;
	directionalLight = false;
	x = 0.0;
	y = 0.0;
	z = 0.0;
	r = 0.0;
	g = 0.0;
	b = 0.0;
}
Light::Light(double ix, double iy, double iz, double ir, double ig, double ib, int flag) {
	if (flag == 0) {
		pointLight = true;
		directionalLight = false;
	} else if (flag == 1) {
		directionalLight = true;
		pointLight = false;
	}
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
Vector3D Light::getColor() {
	return Vector3D(r, g, b);
}

Ray Light::generateLightRay(Vector3D inposition, Vector3D innormal) {
	Vector3D direction;
	float time_to;
	if (this->directionalLight) {
		Vector3D direction = this->getVector().scale(-1).normalize();
		float time_to = FLT_MAX;
	}
	if (this->pointLight) {
		Vector3D direction_temp = this->getVector().subtract(inposition);
		float time_to = direction_temp.magnitude();
		Vector3D direction = direction_temp.normalize();
	}
	return Ray(inposition, direction, 0.0f, time_to);
}
