#include "brdf.h"

BRDF::BRDF() {

}

BRDF::BRDF(Vector3D ika, Vector3D ikd, Vector3D iks, Vector3D ikr) {
	ka = ika;
	kd = ikd;
	ks = iks;
	kr = ikr;
}
