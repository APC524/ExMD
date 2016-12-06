#include <iostream>
#include "gtest/gtest.h"

#include "physics.h"


// test case at moment of collision, spheres touching on edges
TEST(Collisions, SpheresTouching1D) {
  int nparticles = 2;
  double positions[nparticles][3];
  double velocities[nparticles][3];
  double masses[2] = {1,1};
  double radii[2] = {1,1};

  for (int i = 0; i < nparticles; i++) {
    for (size_t j = 0; j < 3; j++) {
      // positions don't matter for this test, initialize to zero
      positions[i][j] = 0.;
    }
  }
  Particles *particles = new Particles(nparticles,positions,velocities,masses,radii);

  // collision along x-axis, particle 1 moving right, 2 moving left
  double nextpositions[2][3] = {{-1,0,0},{1,0,0}};
  double nextpositions_expect[2][3] = {{-1,0,0},{1,0,0}};
  double nextvelocities[2][3] = {{0.5,0,0},{-0.5,0,0}};
  double nextvelocities_expect[2][3] = {{-0.5,0,0},{0.5,0,0}};
  // for (int i = 0; i < nparticles; i++) {
  //   EXPECT_EQ(masses[i],1);
  // }

  Physics *physics = new Physics();
  physics->Collisions(nparticles,*particles,nextpositions,nextvelocities);
  // positions should stay the same
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
    EXPECT_EQ(nextpositions[1][i],nextpositions_expect[1][i]);
  }
  // velocities should reverse
  for (int i = 0; i < 3; i++) {
    EXPECT_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
    EXPECT_EQ(nextvelocities[1][i], nextvelocities_expect[1][i]);
  }

}

// test case with spheres overlapping 50%, edges touching other sphere's
// center
// TEST(Collisions, Spheres overlapping 1-D movement) {
//   int nparticles = 2;
//   double positions[nparticles][3];
//   double velocities[nparticles][3];
//   double masses[2] = {1,1};
//   double radii[2] = {1,1};
//
//   for (int i = 0; i < nparticles; i++) {
//     for (size_t j = 0; j < 3; j++) {
//       // positions don't matter for this test, initialize to zero
//       positions[i][j] = 0.;
//     }
//   }
//   Particles *particles = new Particles(nparticles,positions,velocities,masses,radii);
//
//   // collision along x-axis, particle 1 moving right, 2 moving left
//   double nextpositions[2][3] = {{-1,0,0},{1,0,0}};
//   double nextpositions_expect[2][3] = {{-1,0,0},{1,0,0}};
//   double nextvelocities[2][3] = {{0.5,0,0},{-0.5,0,0}};
//   double nextvelocities_expect[2][3] = {{-0.5,0,0},{0.5,0,0}};
//   // for (int i = 0; i < nparticles; i++) {
//   //   EXPECT_EQ(masses[i],1);
//   // }
//
//   Physics *physics = new Physics();
//   physics->Collisions(nparticles,*particles,nextpositions,nextvelocities);
//   // positions should stay the same
//   for (int i = 0; i < 3; i++) {
//     EXPECT_EQ(nextpositions[0][i], nextpositions_expect[0][i]);
//     EXPECT_EQ(nextpositions[1][i],nextpositions_expect[1][i]);
//   }
//   // velocities should reverse
//   for (int i = 0; i < 3; i++) {
//     EXPECT_EQ(nextvelocities[0][i], nextvelocities_expect[0][i]);
//     EXPECT_EQ(nextvelocities[1][i], nextvelocities_expect[1][i]);
//   }
//
// }
