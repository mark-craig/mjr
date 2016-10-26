#include "scene.h"

int main()
{
	// THE FIRST TEST
	// A wonderful scene
	Scene main_scene = Scene();
	// With an awesome sphere
	Ray hits = Ray(Vector3D(0,0,5), Vector3D(0,0,-1));
	Sphere target = Sphere(Vector3D(0,0,0), 1);
	target.addMaterial(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(1, 0, 0), 10.0f);
	// std::cout<<'f'<<target.material.brdf.ka.x<<','<<target.material.brdf.ka.y<<','<<target.material.brdf.ka.z<<std::endl;
	DirectionalLight light = DirectionalLight(0.0f, 0.0f, -1.0f, 1.0f, 1.0f, 1.0f);
	DirectionalLight* light_ptr = &light;
	std::vector<Object*> v = {&target};	
	std::vector<Light*> u = {&light};	
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