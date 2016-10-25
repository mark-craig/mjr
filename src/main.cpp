#include "scene.h"

int main()
{
	// THE FIRST TEST
	// A wonderful scene
	Scene main_scene = Scene();
	// With an awesome sphere
	Sphere ball = Sphere(Vector3D(0.0f, 0.0f, 0.0f), 0.3f);
	Sphere* ball_ptr = &ball;
	
	Vector3D ka = Vector3D(0.0, 0.0, 0.0);
	Vector3D kd = Vector3D(1.0, 0.0, 0.0);
	Vector3D ks = Vector3D(0.5, 0.5, 0.5);
	ball_ptr->addMaterial(ka, kd, ks, 0.3);

	// A camera for the screen
	Camera camera = Camera();
	// And a light right here
	PointLight light = PointLight(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
	PointLight* light_ptr = &light;

	main_scene.addLight(light_ptr);
	main_scene.addCamera(camera);
	main_scene.addObject(ball_ptr);


	// hold onto your butts
	main_scene.render(700, 500);

}