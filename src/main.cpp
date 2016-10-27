#include "scene.h"
#include "parser.h"

int main(int argc, char* argv[])
{
	if (argc == 1) {
		// THE FIRST TEST
		// A wonderful scene
		Scene main_scene = Scene();
		// With an awesome sphere
		Triangle target = Triangle(Vector3D(0,1,4), Vector3D(1, 0, 3), Vector3D(1, 1, 4));
		target.addMaterial(Vector3D(.1, .1, .1), Vector3D(0, 0, 1), Vector3D(.3, .3, .3), 10.0f);
	// =======
	// 	Sphere target = Sphere(Vector3D(0,0,0), 1);
	// 	target.addMaterial(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 0, 0), 10.0f);
	// >>>>>>> 67bd428bff229e39590ac708c64f47776837e200
		// std::cout<<'f'<<target.material.brdf.ka.x<<','<<target.material.brdf.ka.y<<','<<target.material.brdf.ka.z<<std::endl;
		DirectionalLight light = DirectionalLight(0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f);
		DirectionalLight* light_ptr = &light;
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
		main_scene.render(500, 500);
	}
}