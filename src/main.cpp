#include <ctime>
#include <cstdlib>
#include "CImg.h"
#include "film.h"

using namespace cimg_library;

int main() {
  Film film = Film(700 , 500);
  Sample sample;
  Sampler sampler = Sampler(700, 500);
  Vector3D color;
  srand(time(NULL));
  int random;
  while(sampler.getSample(sample)) {
    random = (rand() % 256);
    color = Vector3D(random, random, random);
    film.commit(sample, color);
  }
  film.display_film();
}