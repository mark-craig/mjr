#pragma once
#include "CImg.h"
class Film {
public:
	// fields
	int x;
	int y;
	cimg_library::CImg<float> image;

	// constructors
	Film();
	Film(int x, int y);

	// methods
	void display_film();
	// writeColor

};
