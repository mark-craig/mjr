#include "scene.h"
#include "parser.h"
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char* argv[])
{
	if (argc == 1) {
		// THE FIRST TEST
		// A wonderful scene
		Scene main_scene = Scene();
		// With an awesome sphere
		Sphere target = Sphere(Vector3D(1,1,-5), 1.0f);
		// Triangle target = Triangle(Vector3D(0,1,5), Vector3D(-1, 0, 4), Vector3D(0, 0, 4));
		// vector<Vector3D> verts = {Vector3D(-1, -1, 5), 
		// 				  		Vector3D(-1, 1, 4),
		// 				  		Vector3D(1, 1, 4),
		// 				  		Vector3D(1, -1, 5)};
		// Polygon target = Polygon(verts);
		target.addMaterial(Vector3D(0, .1, .1), Vector3D(.3, 0, 1), Vector3D(.3, .3, .3), 10.0f);
		// target.addMaterial(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 0, 0), 10.0f);
		// std::cout<<'f'<<target.material.brdf.ka.x<<','<<target.material.brdf.ka.y<<','<<target.material.brdf.ka.z<<std::endl;
		PointLight light = PointLight(0.0f, 5.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0);
		PointLight* light_ptr = &light;
		// PointLight light = PointLight(1.0f, 0.0f, -1.0f, 1.0f, 1.0f, 1.0f);
		// PointLight* light_ptr = &light;

		// A camera for the screen
		Camera camera = Camera();
		// And a light right here
		// PointLight light = PointLight(0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 1.0f);
		// PointLight* light_ptr = &light;

		main_scene.addLight(light_ptr);
		main_scene.addCamera(camera);
		main_scene.addObject(&target);


		// hold onto your butts
		main_scene.render(700, 700, true, string("object.png"));
	}
	else {
		Parser parse = Parser();
		std::vector<void *> garbage;
		Scene main_scene = parse.parseInputFile(string(argv[1]), &garbage);
		if (argc == 3 && strcmp("--write", argv[2]) == 0) {
			main_scene.render(700, 700, true, string("object.png"));
		} else if (argc == 4 && strcmp("--write", argv[2]) == 0) {
			main_scene.render(700, 700, true, string(argv[3]));
		} else {
			main_scene.render(700, 700, false, string("not written"));
		}
		int zzz = (garbage).size();
		for (int i = 0; i < zzz; i += 1) {
			delete garbage[i];
		}
	}
}