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
}

Camera::Camera(double x, double y, double z,
			   double illx, double illy, double illz,
			   double ilrx, double ilry,double ilrz,
			   double iulx, double iuly,double iulz,
			   double iurx, double iury,double iurz) {
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
