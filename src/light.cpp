// #include "vector3d.h"
// #include "light.h"
// #include "ray.h"
// gh
// // functions for lights
// Light::Light() {
// 	pointLight = false;
// 	directionalLight = false;
// 	x = 0.0;
// 	y = 0.0;
// 	z = 0.0;
// 	r = 0.0;
// 	g = 0.0;
// 	b = 0.0;
// }
// Light::Light(double ix, double iy, double iz, double ir, double ig, double ib, int flag) {
// 	if (flag == 0) {
// 		pointLight = true;
// 		directionalLight = false;
// 	} else if (flag == 1) {
// 		directionalLight = true;
// 		pointLight = false;
// 	}
// 	x = ix;
// 	y = iy;
// 	z = iz;
// 	r = ir;
// 	g = ig;
// 	b = ib;
// }

// Vector3D Light::getVector() {
// 	return Vector3D(x, y, z);
// }
// Vector3D Light::getColor() {
// 	return Vector3D(r, g, b);
// }

// Ray Light::generateLightRay(Vector3D inposition, Vector3D innormal) {
// 	if (this->diretionalLight) {
// 		Vector3D direction = this->getVector().scale(-1).normalize();
// 	}
// }
