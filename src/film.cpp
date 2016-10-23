#include "film.h"

using namespace cimg_library;

Film::Film() {
	x = 100; y = 100;
	image =  CImg<float>(200, 200, 1, 3, 1);
}
Film::Film(int ix, int iy) {
	x = ix; y = iy;
	image = CImg<float>(x, y, 1, 3, 1);
}

void Film::commit(Sample sample, Vector3D color) {
	vector<float> cv = color.value();
	float* c = &cv[0]; // this assumes the spec for vector3d
	image.draw_point(sample.x, sample.y, c);
} 

void Film::display_film(const char* window_name) {
	CImgDisplay disp(image, window_name, 0); // 0 sets normalization off
	image.display(disp, true); // 'true' leaves the window open
}
void Film::write_film() {
	image.save("output.png");
}