#include "ray.h"
#include "camera.h"

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

