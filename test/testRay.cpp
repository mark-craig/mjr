#include "gtest/gtest.h"
#include "ray.h"

TEST(RayTest, RayMovesToPoint) {
	Ray hits = Ray(Vector3D(0,0,5), Vector3D(0,0,-1));
	// test that the ray moves to the expected position
	Vector3D r = hits.t(5);
	EXPECT_FLOAT_EQ(r.x, 0.0f);
	EXPECT_FLOAT_EQ(r.y, 0.0f);
	EXPECT_FLOAT_EQ(r.z, 0.0f);

}
TEST(RayTest, ZeroIsNotValidTime) {
	Ray hits = Ray(Vector3D(0,0,5), Vector3D(0,0,-1));
		// time 0 should not be a valid t
	EXPECT_EQ(hits.valid_t(0), false);
}