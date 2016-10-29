#include "ray.h"
#include "camera.h"
#include "vector3d.h"
#include <iostream>
#include <cfloat>

Ray::Ray() {}
Ray::Ray(Vector3D position, Vector3D direction, float tMinimum, float tMaximum) {
	pos = position;
	dir = direction.normalize();
	t_min = tMinimum;
	t_max = tMaximum;
}

Vector3D Ray::t(float time) {
	// ray should not return positions outside of bounds
	if (time < t_min) {
		return pos;
	}
	if (time > t_max) {
		return pos.add(dir.scale(t_max));
	}
	Vector3D result_position = pos;
	return pos.add(dir.scale(time));
}

bool Ray::valid_t(float time) {
	if (time <= t_min) {
		return false;
	} else if (time >= t_max) {
		return false;
	} else {
		return true;
	}
}
Ray Ray::createReflectRay(Vector3D inposition, Vector3D innormal) {
		Vector3D r = this->dir.add(innormal.scale(-2*(this->dir.dot(innormal)))).normalize();
		return Ray(inposition, r, 0.1f, FLT_MAX);
}