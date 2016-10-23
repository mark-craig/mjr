#include "film.h"
#include "CImg.h"
#include <iostream>

using namespace cimg_library;

Film::Film() {
	x = 100; y = 100;
	CImg<float> image(200, 200, 1, 3);
}
Film::Film(int ix, int iy) {
	x = ix; y = iy;
	CImg<float> image(x, y, 1, 3, 255);
}
void Film::display_film() {
	std::cout<<image.width()<<std::endl;
	image.display("Hi");
}