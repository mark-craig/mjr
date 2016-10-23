#include "gtest/gtest.h"
#include "camera.h"

TEST(CameraTest, FindsCenterOfImagePlane) {
	Camera cam = Camera();
	Vector3D ipc = cam.getCenterOfImagePlane();
	EXPECT_EQ(ipc.x, 0.0);
	EXPECT_EQ(ipc.y, 0.0);
	EXPECT_EQ(ipc.z, -1.0);
}
TEST(CameraTest, FindsBasisForCamera) {
	Camera cam = Camera();
	vector<Vector3D> basis = cam.getBasisWUV();
	// w should be z vector pointing
	EXPECT_FLOAT_EQ(basis[0].x, 0);
	EXPECT_FLOAT_EQ(basis[0].y, 0);
	EXPECT_FLOAT_EQ(basis[0].z, -1);
	// u should be x
	EXPECT_FLOAT_EQ(basis[1].x, 1);
	EXPECT_FLOAT_EQ(basis[1].y, 0);
	EXPECT_FLOAT_EQ(basis[1].z, 0);
	// v should be y
	EXPECT_FLOAT_EQ(basis[2].x, 0);
	EXPECT_FLOAT_EQ(basis[2].y, 1);
	EXPECT_FLOAT_EQ(basis[2].z, 0);
}
TEST(CameraTest, GeneratesRayForSample) {
	Camera cam = Camera();
	Sample sample = Sample();
	sample.x = 160;
	sample.y = 120;
	Ray ray = Ray();
	// a ray from the camera to the point in the center of the image
	// should just be 1 along the z axis (-w).
	cam.generateRay(sample, ray, 321, 241);
	EXPECT_FLOAT_EQ(ray.pos.x, 0.0f);
	EXPECT_FLOAT_EQ(ray.pos.y, 0.0f);
	EXPECT_FLOAT_EQ(ray.pos.z, 0.0f);
	EXPECT_FLOAT_EQ(ray.dir.z, 1.0f);
	EXPECT_FLOAT_EQ(ray.dir.x, 0.0f);
	EXPECT_FLOAT_EQ(ray.dir.y, 0.0f);
}