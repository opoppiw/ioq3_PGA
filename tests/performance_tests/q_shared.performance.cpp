#include <stdio.h>
#include <time.h>
#include "../../../klein/public/klein/klein.hpp"
#include <xmmintrin.h>

#define nr_tests 200000
#define DEG2RAD(a) (((a)*M_PI) / 180.0F)

typedef float vec3_t[3];

/**
 * Returns a random 3D point.
 * The elements of this point will be in the range [0.0, 2147.483647]
 */
kln::point rand_point() {
  float x = (float)(rand()) / 1000000;
  float y = (float)(rand()) / 1000000;
  float z = (float)(rand()) / 1000000;

  return kln::point{x, y, z};
}

/**
 * Returns a random 3D unit plane through the origin.
 */
kln::plane rand_origin_unit_plane() {
  float a = (float)(rand()) / 1000000;
  float b = (float)(rand()) / 1000000;
  float c = (float)(rand()) / 1000000;
  float d = 0;

  float norm = sqrt(a*a + b*b + c*c);

  return kln::plane{a/norm, b/norm, c/norm, d};
}

/**
 * Generates a given number of random 3D unit vectors and writes the results to "vectors".
 * 
 * @param vectors Array consisting of "nr" float arrays of size 3. 
 * @param nr The number of random unit vectors that are generated and written to "vectors".
 */
void rand_unit_vectors(vec3_t *vectors, int nr) {
  for (int i = 0; i < nr; i++) {
    vectors[i][0] = (float)(rand()) / 1000000;
    vectors[i][1] = (float)(rand()) / 1000000;
    vectors[i][2] = (float)(rand()) / 1000000;
    float norm = sqrt(vectors[i][0] * vectors[i][0] + vectors[i][1] * vectors[i][1] + vectors[i][2] * vectors[i][2]);

    vectors[i][0] /= norm;
    vectors[i][1] /= norm;
    vectors[i][2] /= norm;
  }
}

/**
 * Fills the given array with the indicated number of floats.
 * Returns a random floats in the range [0.0, 858.9934588]
 *
 * @param angles Float array where the results are written to.
 * @param nr The number of floats that are generated
 */
void rand_angles(float *angles, int nr)
{
  for (int i = 0; i < nr; i++)
  {
    angles[i] = (float)(rand()) / 2500000;
  }
}

/**
 * Performs Klein library project function for projecting a random points
 * on a random unit plane through the origin a configured number of times.
 * a configured number. The execution time is measured and printed.
 */
void test_ProjectPointOnPlane(void) {
  kln::point result;
  kln::point points[nr_tests];
  kln::plane planes[nr_tests];

  for (int i = 0; i < nr_tests; i++) {
    points[i] = rand_point();
  }

  for (int i = 0; i < nr_tests; i++) {
    planes[i] = rand_origin_unit_plane();
  }

  clock_t t;
  double time_taken;

  t = clock();
  for (int i = 0; i < nr_tests; i++) {
      result = kln::project(points[i], planes[i]);
  }

  t = clock() - t;
  time_taken = ((double)t)/CLOCKS_PER_SEC * 1000;
  printf("PGA C++ version took %f ms to execute\n", time_taken);
}

/**
 * Constructs a rotor using a direction vector and applies this rotor
 * to a given point a configured number of times. The execution time is
 * measured and printed.
 */
void test_RotatePointAroundVector(void)
{
  kln::point result;
  kln::point points[nr_tests];
  vec3_t dirs[nr_tests];
  float angles[nr_tests]; // Angles in degrees

  for (int i = 0; i < nr_tests; i++) {
    points[i] = rand_point();
  }

  rand_unit_vectors(dirs, nr_tests);
  rand_angles(angles, nr_tests);

  clock_t t;
  double time_taken;

  t = clock();
  for (int i = 0; i < nr_tests; i++)
  {
    kln::rotor rotor = kln::rotor(-DEG2RAD(angles[i]), dirs[i][0], dirs[i][1], dirs[i][2]);
    result = rotor(points[i]);
  }

  t = clock() - t;
  time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
  printf("PGA C++ version took %f ms to execute \n", time_taken);
}

int main() {
  srand(time(NULL));

  printf("ProjectPointOnPlane result\n");
  test_ProjectPointOnPlane();
  printf("\nRotatePointAroundVector result\n");
  test_RotatePointAroundVector();

  return 0;
}