#include "gtest/gtest.h"
#include "objects.h"
#include "intersection.h"
#include "ray.h"
#include "transformation.h"

TEST(ObjectTest, FindsIntersections) {
	Ray hits = Ray(Vector3D(0,0,5), Vector3D(0,0,-1));
	Intersection in = Intersection();
	Sphere target = Sphere(Vector3D(0,0,0), 1);
	Triangle other = Triangle(Vector3D(-1,1,0),Vector3D(1,1,0), Vector3D(0,-1,0));
	target.addTransformation(Translate(0,0,1));
	other.addTransformation(Translate(0,0,1));
	// should intersect at t=4
	EXPECT_EQ(target.intersect(hits, in), true);
	EXPECT_FLOAT_EQ(in.time, 3);
	EXPECT_EQ(in.position.value(), Vector3D(0,0,2).value());
	EXPECT_EQ(in.normal.value(), Vector3D(0,0, 1).value());

	EXPECT_EQ(other.intersect(hits, in), true);
	EXPECT_FLOAT_EQ(in.time, 4);
	EXPECT_EQ(in.position.value(), Vector3D(0,0,1).value());
	EXPECT_EQ(in.normal.value(), Vector3D(0,0, 1).value());

}