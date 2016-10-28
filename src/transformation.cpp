#include "transformation.h"
#include <cmath>
using namespace std;

Transformation::Transformation() {
	m << 1, 0, 0, 0,
		 0, 1, 0, 0,
		 0, 0, 1, 0,
		 0, 0, 0, 1;
}

void Transformation::apply(Triangle &target) {
 	// convert internal Vector class to Eigen representation
 	Vector4f va(target.v1.x, target.v1.y, target.v1.z, 0);
 	Vector4f vb(target.v2.x, target.v2.y, target.v2.z, 0);
 	Vector4f vc(target.v3.x, target.v3.y, target.v3.z, 0);
 	// apply transformation
 	va = m*va;
 	vb = m*vb;
 	vc = m*vc;
 	// // set back to internal representation in place
 	target.v1 = Vector3D(va[0], va[1], va[2]);
 	target.v2 = Vector3D(vb[0], vb[1], vb[2]);
 	target.v3 = Vector3D(vc[0], vc[1], vc[2]);
 }

Scale::Scale(float x, float y, float z) {
	m << x, 0, 0, 0,
		 0, y, 0, 0,
		 0, 0, z, 0,
		 0, 0, 0, 1;
}

Translate::Translate(float x, float y, float z) {
	m << 1, 0, 0, x,
		 0, 1, 0, y,
		 0, 0, 1, z,
		 0, 0, 0, 1;
}

Rotate::Rotate(float alpha, float beta, float gamma) {
	Matrix4f t;
	t <<   1, 0, 0, 0,
		   0, cos(alpha), -sin(alpha), 0,
		   0, sin(alpha), cos(alpha), 0,
		   0, 0, 0, 1;
	Matrix4f s;
	s << cos(beta), 0, sin(beta), 0,
		 0, 1, 0, 0,
		 -sin(beta), 0, cos(beta), 0,
		 0, 0, 0, 1;
	Matrix4f r;
	r << cos(beta), -sin(beta), 0, 0,
		 sin(beta), cos(beta), 0, 0,
		  0, 0, 1, 0,
		  0, 0, 0, 1;
	
	m = t*s*r;
}