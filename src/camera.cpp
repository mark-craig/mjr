#include "camera.h"
#include <vector>

using namespace std;

// function for camera
Camera::Camera() {
	// position
	x = 0.0; y = 0.0; z = 0.0;
	// lower left
	llx = -1.0; lly = -1.0; llz = -1.0;
	// lower right
	lrx = 1.0; lry = -1.0; lrz = -1.0;
	// upper left
	ulx = -1.0; uly = 1.0; ulz = -1.0;
	// upper right
	urx = 1.0; ury = 1.0; urz = -1.0;

	// vectors for imageplane
	getImagePlaneVectors();
}

Camera::Camera(float ix, float iy, float iz,
			   float illx, float illy, float illz,
			   float ilrx, float ilry,float ilrz,
			   float iulx, float iuly,float iulz,
			   float iurx, float iury,float iurz) {
	// position
	x = ix; y = iy; z = iz;
	// lower left
	llx = illx; lly = illy; llz = illz;
	// lower right
	lrx = ilrx; lry = ilry; lrz = ilrz;
	// upper left
	ulx = iulx; uly = iuly; ulz = iulz;
	// upper right
	urx = iurx; ury = iury; urz = iurz;

	// vectors for imageplane
	getImagePlaneVectors();
}

void Camera::getImagePlaneVectors() {
	ur = Vector3D(urx, ury, urz);
	ul = Vector3D(ulx, uly, ulz);
	ll = Vector3D(llx, lly, llz);
	lr = Vector3D(lrx, lry, lrz);
}


Vector3D Camera::getPosition() {
	return Vector3D(x, y, z);
}

Vector3D Camera::getCenterOfImagePlane() {
	// average all the vectors to find the center
	return ur.add(ul.add(ll.add(lr))).scale(0.25);
}

vector<Vector3D> Camera::getBasisWUV() {
	// Shirley, Marschner pg. 75
	// ....some assumptions here
	// A) top of plane and bottom are the same width, same for left and right lengths
	// B) u and v will always meet in the middle
	// I think these are all safe for now
	Vector3D e = getPosition();
	Vector3D ipc = getCenterOfImagePlane();
	// w is the vector pointing behind the camera.
	// the rays travel out from the camera in -w
	Vector3D w = ipc.subtract(e).normalize().scale(-1);
	// u is calculated by taking the cross product of u and y
	// http://web.cse.ohio-state.edu/~parent/classes/681/Lectures/08.RTgeometryHO.pdf
	Vector3D up_vector = Vector3D(0, 1, 0);
	Vector3D u = w.cross(up_vector).normalize();
	Vector3D v = u.cross(w).normalize();
	vector<Vector3D> result;
	result.push_back(w);
	result.push_back(u);
	result.push_back(v);
	return result;
}

Vector3D Camera::getViewVector() {
	return getBasisWUV()[2];
}

void Camera::generateRay(Sample sample, Ray &ray, int nx, int ny) {
	// Another assumption
	// l = – r and b = – t, "Many systems assume"

	Vector3D e = getPosition();
	vector<Vector3D> basis = getBasisWUV();
	Vector3D w = basis[0];
	Vector3D u = basis[1];
	Vector3D v = basis[2];

	float l = ur.subtract(ul).magnitude()/2.0;
	float b = ur.subtract(lr).magnitude()/2.0;
	float pixel_u = l + (-2.0*l)*(sample.x + 0.5)/nx;
	float pixel_v = b + (-2.0*b)*(sample.y + 0.5)/ny;

	// perspective method
	Vector3D d = e.subtract(getCenterOfImagePlane());
	Vector3D direction = w.scale(-1 * d.magnitude()).add(u.scale(pixel_u)).add(v.scale(pixel_v));
	// cout<<e.x<<','<<e.y<<','<<e.z<<endl;
	// cout<<direction.x<<','<<direction.y<<','<<direction.z<<endl;
	ray = Ray(e, direction);
	//// orthographic method
	// Vector3D origin = e.add(u.scale(pixel_u).add(v.scale(pixel_v)));
	// Vector3D neg_w = w.scale(-1);
	// ray = Ray(origin, neg_w);
}

