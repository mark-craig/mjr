#include "brdf.h"
#include "vector3d.h"
#include "light.h"
#include "material.h"
#include <algorithm>

using namespace std;

Material::Material() {
	brdf = BRDF();
	anisotropic = false;
}

Material::Material(BRDF ibrdf){
	brdf = ibrdf;
}

Material::Material(BRDF ibrdf, float isp){
	brdf = ibrdf;
	sp = isp;
}

Material::Material(BRDF ibrdf, float ispu, float ispv){
	brdf = ibrdf;
	spu = ispu;
	spv = ispv;
}

BRDF Material::calculateBRDF() {
	// eventually this will actually take into account textures
	return this->brdf;
}

Vector3D Material::shade(Vector3D view, Vector3D position, Vector3D normal, Light light) {
	// calculate the total effect of this light on the color value
	
	// will return result at the end
	Vector3D result = Vector3D();
	// useless at the moment.
	BRDF this_brdf = calculateBRDF();

	// get relevant vectors from the light
	Vector3D l = light.getLightVector(position);
	Vector3D I = light.getColor();

	// mix in ambient
	result.add(shadeAmbient(this_brdf.ka, I));
	//mix in diffuse
	result.add(shadeDiffuse(this_brdf.kd, I, l, normal));
	//mix in specular
	result.add(shadeSpecular(this_brdf.ks, view, l, normal));

	return result;
}


Vector3D Material::shadeAmbient(Vector3D ka, Vector3D lightColor) {
	// calculate the ambient lighting
	return ka.multiply(lightColor);
}

Vector3D Material::shadeDiffuse(Vector3D kd, Vector3D lightColor, Vector3D lightVector, Vector3D normal) {
	// calculate the diffuse color given the relevant variables
	// the light does add to the color if the diffuse factor is negative
	float diffuseFactor = max(0.0f, normal.dot(lightVector));
	return kd.multiply(lightColor).scale(diffuseFactor);
}

Vector3D Material::shadeSpecular(Vector3D ks, Vector3D viewVector, Vector3D lightVector, Vector3D normal) {
	// compute half vector for specular component
	Vector3D h = viewVector.add(lightVector).normalize();
	Vector3D r = lightVector.scale(-1).add(normal.scale(2*(lightVector.dot(normal)))).normalize();

	// calculate specular
	float specularComponent;
	if (anisotropic) {
		Vector3D yVector = Vector3D(0,1,0);
		// formulas for u and v given in doc
		Vector3D paramv = (yVector.subtract(normal.scale(normal.dot(yVector)))).normalize();
		Vector3D paramu = (paramv.cross(normal)).normalize();

		// the anisotropic exponent for specular
		float as = (spu * pow(h.dot(paramu), 2) + spv * pow((h.dot(paramv)), 2))/(1 - pow(h.dot(normal), 2));
		specularComponent = pow(max(0.0f, r.dot(viewVector)), as);
	} else {
		specularComponent = pow(max(0.0f, r.dot(viewVector)), sp);
	}
	return ks.multiply(lightVector).scale(specularComponent);
}
