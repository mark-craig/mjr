#pragma once
#include "vector3d.h"
#include "sample.h"
#include "ray.h"
#include <vector>

using namespace std;

class Camera
{
public:
	//position
	float x; float y; float z;
	// lower left
	float llx; float lly; float llz;
	// lower right
	float lrx; float lry; float lrz;
	// upper left
	float ulx; float uly; float ulz;
	// upper right
	float urx; float ury; float urz;
	//constructors
	Camera();
	Camera(float ix, float iy, float iz,
		   float illx, float illy, float illz,
		   float ilrx, float ilry,float ilrz,
		   float iulx, float iuly,float iulz,
		   float iurx, float iury,float iurz);

	// other methods
	Vector3D getPosition();
	Vector3D getCenterOfImagePlane();
	vector<Vector3D> getBasisWUV();
	void getImagePlaneVectors();
	void generateRay(Sample sample, Ray &ray, int nx, int ny);

	Vector3D ur = Vector3D(urx, ury, urz);
	Vector3D ul = Vector3D(ulx, uly, ulz);
	Vector3D ll = Vector3D(llx, lly, llz);
	Vector3D lr = Vector3D(lrx, lry, lrz);
};
