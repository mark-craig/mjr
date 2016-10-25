#include "gtest/gtest.h"
#include "objects.h"
#include "intersection.h"
#include "ray.h"

TEST(ObjectTest, FindsIntersections) {
	Ray hits = Ray(Vector3D(0,0,5), Vector3D(0,0,-1));
	Intersection in = Intersection();
	Sphere target = Sphere(Vector3D(0,0,0), 1);
	// should intersect at t=4
	EXPECT_EQ(target.intersect(hits, in), true);
	EXPECT_FLOAT_EQ(in.time, 4);

	EXPECT_EQ(in.position.value(), Vector3D(0,0,1).value());

}