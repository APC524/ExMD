/** @file   main.cpp
 *  @brief  Main driving program for ExMD simlation
 *
 *  @author Hugh Wilson (hswilson@princeton.edu)
 *  @date   2016-12-28
 *  @bug    No known bugs
 */

/* -- Includes -- */

/* libc includes */
#include <iostream>
#include <math.h>

/* MD header files */
#include "simulation.h"
#include "particles.h"
#include "physics.h"
#include "force.h"
#include "gravity.h"
#include "boundary.h"
#include "write.h"

int main() {
  std::cout << "working\n";

  #define DIM 3

  /* Simulation parameters */
  // int nsteps = 100;
  bool checkNaN = false;

  /* Simulation parameters */
  int nsteps = 70;
  /* Make a particles object */
  const int kNparticles = 10;
  double positions[kNparticles][DIM];
  double velocites[kNparticles][DIM];
  double masses[kNparticles];
  double radii[kNparticles];

  int half = kNparticles/2;

  for (int i = 0; i < kNparticles; i++) {
    if (i < half) {
      positions[i][0] = 10;
      velocites[i][0] = -1;
    } else {
      positions[i][0] = -10;
      velocites[i][0] = 1;
    }

    positions[i][1] = 3*(i % half);
    positions[i][2] = 0;
    velocites[i][1] = 0;
    velocites[i][2] = 0;

    masses[i] = 1;
    radii[i] = 1;
  }


  Particles *particles;
  particles = new Particles(kNparticles, positions, \
          velocites, masses, radii);


  /* Make force object (depending on user input) UPDATE THIS */
  double G = 6.67408 * pow(10, -11);  // gravitational constant
  Force *gravity = new Gravity(G);

  /* Make a physics object */
  Physics *physics;
  physics = new Physics();

  /* Add forces to physics */
  physics->AddForce(gravity);

  /* Make a boundary object */
  Boundary boundary = { reflecting, {{-100, 100}, {-100, 100}, {-100, 100}} };

  /* Make a simulation object */
  double dt = 0.5;
  int output_period = 1;

  Simulation *simulation;
  simulation = new Simulation(dt, output_period, kNparticles, DIM, checkNaN, \
          particles, physics, &boundary);

  WriteParametersCSV(nsteps, kNparticles);

  /* Step through time */
  for (int nt = 0; nt < nsteps; nt++) {
      WriteParticlesCSV(particles, kNparticles, nt);
      simulation->Step();
  }

  printf("Simulation finished!\n");

  /* Delete Simulation Objects */
  delete physics;
  delete particles;
  delete force;
  delete simulation;

  return 0;
}
