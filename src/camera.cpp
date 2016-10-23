#include "camera.h"
#include "sample.h"
#include "vector3d.h"

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
	Vector3D ur = Vector3D(urx, ury, urz);
	Vector3D ul = Vector3D(ulx, uly, ulz);
	Vector3D ll = Vector3D(llx, lly, llz);
	Vector3D lr = Vector3D(lrx, lry, lrz);

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
}

Vector3D Camera::getPosition() {
	return Vector3D(x, y, z);
}

Vector3D Camera::getCenterOfImagePlane() {
	Vector3D ur = Vector3D(urx, ury, urz);
	Vector3D ul = Vector3D(ulx, uly, ulz);
	Vector3D ll = Vector3D(llx, lly, llz);
	Vector3D lr = Vector3D(lrx, lry, lrz);

}



void Camera::generateRay(Sample sample, Ray &ray, int nx, int ny) {
	Vector3D ur = Vector3D(urx, ury, urz);
	Vector3D ul = Vector3D(ulx, uly, ulz);
	Vector3D ll = Vector3D(llx, lly, llz);
	Vector3D lr = Vector3D(lrx, lry, lrz);
	// add the vectors of the corners together and scale by 1/4
	Vector3D ipc = ur.add(ul.add(ll.add(lr))).scale(0.25);

	Vector3D e = getPosition();
	// w is the vector pointing behind the camera.
	// the rays travel out from the camera in -w
	Vector3D w = ipc.subtract(e).normalize();
	// u is calculated by taking the cross product of u and y
	// http://web.cse.ohio-state.edu/~parent/classes/681/Lectures/08.RTgeometryHO.pdf
	Vector3D up_vector = Vector3D(0, 1, 0);
	Vector3D u = w.cross(up_vector).normalize();
	Vector3D v = u.cross(w).normalize();

	// Shirley, Marschner pg. 75
	// ....two assumptions here
	// A) top of plane and bottom are the same width, same for left and right lengths
	// B) u and v will always meet in the middle
	// C) l = – r and b = – t, "Many systems assume"
	// I think these are both safe for now
	float l = ur.subtract(ul).magnitude()/2.0;
	float b = ur.subtract(lr).magnitude()/2.0;
	float pixel_u = l + (-2.0*l)*(sample.x + 0.5)/nx; // dimensions hard-coded
	float pixel_v = b + (-2.0*b)*(sample.y + 0.5)/ny;

	Vector3D origin = e.add(u.scale(pixel_u).add(v.scale(pixel_v)));
	Vector3D neg_w = w.scale(-1.0f);
	Ray result = Ray(origin, neg_w);
}

