#include "gtest/gtest.h"
#include "raytracer.h"
#include "objects.h"
#include "intersection.h"
#include "ray.h"
#include <vector>
#include <iostream>

TEST(RayTracerTest, RayHits) {
	// initialize the raytracer
	Ray hits = Ray(Vector3D(0,0,5), Vector3D(0,0,-1));
	Sphere target = Sphere(Vector3D(0,0,0), 1);
	std::vector<Object*> v = {&target};	
	RayTracer raytracer = RayTracer(0, 1, {}, v);
	Vector3D color = raytracer.trace(hits, 0);
	// this test only passes while raytracer returns white on contact. will fail once we begin shading
	EXPECT_EQ(color.iszero(), false);
	EXPECT_EQ(color.x, 1.0f);
	EXPECT_EQ(color.y, 1.0f);
	EXPECT_EQ(color.z, 1.0f);
}

TEST(RayTracerTest, IntersectionTest) {
	// initialize the raytracer
	Ray hits = Ray(Vector3D(0,0,5), Vector3D(0,0,-1));
	Sphere target = Sphere(Vector3D(0,0,0), 1);
	std::vector<Object*> v = {&target};	
	RayTracer raytracer = RayTracer(0, 1, {}, v);
	Intersection in = Intersection();
	// create a pointer to an object pointer
	Object **temp;
	// test
	bool should_be_true = raytracer.interceptsObject(hits, in, temp);
	EXPECT_EQ(should_be_true, true);
	EXPECT_EQ(in.position.value(), Vector3D(0,0,1).value());
	EXPECT_EQ(*temp, &target);
}
TEST(RayTracerTest, LightTest) {
	// initialize the raytracer
	Ray hits = Ray(Vector3D(0,0,5), Vector3D(0,0,-1));
	Sphere target = Sphere(Vector3D(0,0,0), 1);
	target.addMaterial(Vector3D(1,0,0), Vector3D(1,0,0), Vector3D(1,0,0), 10.0f);
	DirectionalLight light = DirectionalLight(0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	DirectionalLight* light_ptr = &light;
	std::vector<Object*> v = {&target};	
	std::vector<Light*> u = {&light};	
	RayTracer raytracer = RayTracer(1, 1, u, v);
	Intersection in = Intersection();
	// create a pointer to an object pointer
	// test
	Vector3D color = raytracer.trace(hits, 0);
	EXPECT_EQ(color.iszero(), false);
	EXPECT_EQ(color.x, 1.0f);
	EXPECT_EQ(color.y, 0.0f);
	EXPECT_EQ(color.z, 1.0f);
}