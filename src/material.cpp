#include "brdf.h"
#include "vector3d.h"
#include "light.h"
#include "material.h"
#include <algorithm>

using namespace std;

Material::Material() {
	brdf = BRDF();
}

Material::Material(BRDF ibrdf){
	brdf = ibrdf;
}

BRDF Material::calculateBRDF() {
	return this->brdf;
}

// Vector3D shading(Vector3D view, Vector3d position, Vector3D normal,
// 				 BRDF this_brdf, Light light) {
// 	if (light.pointLight) {
// 		// set l to be the difference between the intersection point and the position
// 		Vector3D l = lights[k].getVector().subtract(n).normalize();
// 		Vector3D I = lights[k].getColor();
// 	} else if (light.directionalLight) {
// 		// set l to be the unit vector in the direction of the light
// 		Vector3D l = lights[k].getVector().normalize().scale(-1);
// 		Vector3D I = lights[k].getColor();
// 		numberOfDirectionalLights += 1;
// 	} else {
// 		// light does not exist or we have reached capacity
// 		return Vector3D(0.0, 0.0, 0.0);
// 	}
// 	// compute half vector for specular component
// 	Vector3D h = v.add(l).normalize();
// 	Vector3D r = l.scale(-1).add(n.scale(2*(l.dot(n)))).normalize();
// 	Vector3D R = Vector3D();
// 	// calculate diffuse
// 	R.x += kd.x * I.x * max(0.0f, n.dot(l));
// 	R.y += kd.y * I.y * max(0.0f, n.dot(l));
// 	R.z += kd.z * I.z * max(0.0f, n.dot(l));

// 	// calculate specular
// 	if (anisotropic) {
// 		Vector3D yVector = Vector3D(0,1,0);
// 		// formulas for u and v given in doc
// 		Vector3D paramv = (yVector.subtract(n.scale(n.dot(yVector)))).normalize();
// 		Vector3D paramu = (paramv.cross(n)).normalize();

// 		// the anisotropic exponent for specular
// 		float as = (spu * sqr(h.dot(paramu)) + spv * sqr((h.dot(paramv))))/(1 - sqr(h.dot(n)));
	   
// 		R.x += ks.x * I.x * pow(max(0.0f, r.dot(v)), as);
// 		R.y += ks.y * I.y * pow(max(0.0f, r.dot(v)), as);
// 		R.z += ks.z * I.z * pow(max(0.0f, r.dot(v)), as);
// 	} else {
// 	R.x += ks.x * I.x * pow(max(0.0f, r.dot(v)), sp);
// 	R.y += ks.y * I.y * pow(max(0.0f, r.dot(v)), sp);
// 	R.z += ks.z * I.z * pow(max(0.0f, r.dot(v)), sp);
// 	}
// 	Vector3D temp_vector = Vector3D(R.x, R.y, R.z);
// }
