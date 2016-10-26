#include "gtest/gtest.h"
#include "raytracer.h"
#include "objects.h"
#include "intersection.h"
#include "ray.h"
#include <vector>
#include <iostream>

TEST(RayTracerTest, IntersectionTest) {
	// initialize the raytracer
	Ray hits = Ray(Vector3D(0,0,5), Vector3D(0,0,-1));
	Sphere target = Sphere(Vector3D(0,0,0), 1);
	std::vector<Object*> v = {&target};	
	RayTracer raytracer = RayTracer(0, 1, {}, v);
	Intersection in = Intersection();
	// create a pointer to an object pointer
	Object *temptemp;
	Object **temp = &temptemp;
	// test
	bool should_be_true = raytracer.interceptsObject(hits, in, temp);
	EXPECT_EQ(should_be_true, true);
	EXPECT_EQ(in.position.value(), Vector3D(0,0,1).value());
	EXPECT_EQ(in.normal.value(), Vector3D(0,0,1).value());
	EXPECT_EQ(*temp, &target);
}
TEST(RayTracerTest, LightTest) {
	// initialize the raytracer
	Ray hits = Ray(Vector3D(0,0,5), Vector3D(0,0,-1));
	Sphere target = Sphere(Vector3D(0,0,0), 1);
	target.addMaterial(Vector3D(0, 1, 1), Vector3D(1, 1, 1), Vector3D(0, 1, 1), 10.0f);
	// std::cout<<'f'<<target.material.brdf.ka.x<<','<<target.material.brdf.ka.y<<','<<target.material.brdf.ka.z<<std::endl;
	DirectionalLight light = DirectionalLight(0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 0.0f);
	DirectionalLight* light_ptr = &light;
	std::vector<Object*> v = {&target};	
	std::vector<Light*> u = {&light};	
	RayTracer raytracer = RayTracer(1, 1, u, v);
	Intersection in = Intersection();
	// create a pointer to an object pointer
	// test
	Vector3D color = raytracer.trace(hits, 0);
	// scale it down to 1,1,1
	color = color.scale(1.0f / color.x);
	EXPECT_EQ(color.iszero(), false);
	EXPECT_EQ(color.x, 1.0f);
	EXPECT_EQ(color.y, 2.0f);
	EXPECT_EQ(color.z, 0.0f);
}