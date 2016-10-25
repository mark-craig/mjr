#include "gtest/gtest.h"
#include "film.h"


// A test that outputs random noise. Disabled so that tests can
// be run via commandline.

// TEST(FilmTest, FilmWritesSampledNoise) {
//   Film film = Film(700 , 500);
//   Sample sample;
//   Sampler sampler = Sampler(700, 500);
//   Vector3D color;
//   srand(time(NULL));
//   int random;
//   while(sampler.getSample(sample)) {
//     random = (rand() % 256);
//     color = Vector3D(random, random, random);
//     film.commit(sample, color);
//   }
//   film.display_film("This window should display noise. Close to continue.");
//   EXPECT_EQ(1,1);
// }

