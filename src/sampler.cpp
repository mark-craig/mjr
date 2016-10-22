#include "sample.h"
#include "sampler.h"

Sampler::Sampler(int ix, int iy) {
	x = ix;
	y = iy;
}

bool Sampler::getSample(Sample &sample) {
	if (current_x <= x && current_y <= y) {
		// we have not passed the last sample
		sample.x = float(current_x);
		sample.y = float(current_y);

		// increment x and possibly y
		if (current_x < x) {
			current_x += 1;
		} else {
			current_x = 0;
			current_y += 1;
		}
		return true;
	} else {
		return false;
	}
}
