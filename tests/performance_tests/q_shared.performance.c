#include "../../code/qcommon/q_shared.h"
#include "../replaced_code/old_functions.h"
#include "../replaced_code/cm_test_definitions.h"

#include <stdio.h>
#include <time.h>

/**
 * The number of executions that will be performed on random inputs
 * for each experiment.
 */
#define nr_tests 100000

/**
 * Generates a random 3D vector.
 * The elements of this vector will be in the range [0.0, 2147.483647]
 *
 * @param vector Array of size 3 where the result is written.
 */
void rand_vector(vec3_t vector) {
  vector[0] = (float)(rand()) / 1000000;
  vector[1] = (float)(rand()) / 1000000;
  vector[2] = (float)(rand()) / 1000000;
}

/**
 * Generates a given number of random 3D vectors and writes the results to "vectors".
 * The elements of these vectors will be in the range [0.0, 2147.483647]
 *
 * @param vectors Array consisting of "nr" float arrays of size 3.
 * @param nr The number of random vectors that are generated and written to "vectors".
 */
void rand_vectors(vec3_t* vectors, int nr) {
  for (int i = 0; i < nr; i++) {
    rand_vector(vectors[i]);
  }
}

/**
 * Generates a random 3D unit vector.
 * 
 * @param vector Array of size 3 where the result is written.
 */
void rand_unit_vector(vec3_t vector) {
  rand_vector(vector);

  float norm = sqrt(vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2]);

  vector[0] /= norm;
  vector[1] /= norm;
  vector[2] /= norm;
}

/**
 * Generates a given number of random 3D unit vectors and writes the results to "vectors".
 * 
 * @param vectors Array consisting of "nr" float arrays of size 3. 
 * @param nr The number of random unit vectors that are generated and written to "vectors".
 */
void rand_unit_vectors(vec3_t* vectors, int nr) {
  for (int i = 0; i < nr; i++) {
    rand_unit_vector(vectors[i]);
  }
}


/**
 * Fills the given array with the indicated number of floats.
 * Returns a random floats in the range [0.0, 858.9934588] 
 * 
 * @param angles Float array where the results are written to.
 * @param nr The number of floats that are generated 
 */
void rand_angles(float* angles, int nr) {
  for (int i = 0; i < nr; i++) {
    angles[i] = (float)(rand()) / 2500000;
  }
}

/**
 * Executes the Ioquake and PGA version of the ProjectPointOnPlane function for a configured 
 * number of random unit vector inputs. For each version of ProjectPointOnPlane, the total 
 * execution time of executing ProjectPointOnPlane for all generated inputs is measured and 
 * printed.
 */
void test_ProjectPointOnPlane(void) {
  vec3_t result;
  vec3_t points[nr_tests];
  vec3_t normals[nr_tests];

  rand_vectors(points, nr_tests);
  rand_unit_vectors(normals, nr_tests);

  clock_t t;
  double time_taken;

  t = clock();
  for (int i = 0; i < nr_tests; i++) {
      ProjectPointOnPlane(result, points[i], normals[i]);
  }

  t = clock() - t;
  time_taken = ((double)t)/CLOCKS_PER_SEC * 1000;
  printf("PGA       version took %f ms to execute \n", time_taken);


  t = clock();
  for (int i = 0; i < nr_tests; i++) {
      old_ProjectPointOnPlane(result, points[i], normals[i]);
  }

  t = clock() - t;
  time_taken = ((double)t)/CLOCKS_PER_SEC * 1000;
  printf("Ioquake3  version took %f ms to execute \n", time_taken);
}

/**
 * Executes the Ioquake and PGA version of the RotatePointAroundVector function for a configured
 * number of random unit vector inputs. For each version of RotatePointAroundVector, the total
 * execution time of executing RotatePointAroundVector for all generated inputs is measured and
 * printed.
 */
void test_RotatePointAroundVector(void)
{
  vec3_t result;
  vec3_t points[nr_tests];
  vec3_t dirs[nr_tests];
  float angles[nr_tests];

  rand_vectors(points, nr_tests);
  rand_unit_vectors(dirs, nr_tests);
  rand_angles(angles, nr_tests);

  clock_t t;
  double time_taken;

  t = clock();
  for (int i = 0; i < nr_tests; i++)
  {
    RotatePointAroundVector(result, dirs[i], points[i], angles[i]);
  }

  t = clock() - t;
  time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
  printf("PGA       version took %f ms to execute \n", time_taken);

  t = clock();
  for (int i = 0; i < nr_tests; i++)
  {
    old_RotatePointAroundVector(result, dirs[i], points[i], angles[i]);
  }

  t = clock() - t;
  time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
  printf("Ioquake3  version took %f ms to execute \n", time_taken);
}

/**
 * Executes the Ioquake and PGA version of the CM_TransformedPointContents function for a 
 * configured number of random inputs. For both version of the function, the total execution 
 * time for all generated inputs is measured and printed.
 */
void test_CM_TransformedPointContents(void)
{
  vec3_t result;
  vec3_t points[nr_tests];
  vec3_t origins[nr_tests];
  float angles[nr_tests];
  clock_t t;
  double time_taken;
  clipHandle_t model = 5; // The value of "model" does not matter for testing purposes. 

  rand_vectors(points, nr_tests);
  rand_vectors(origins, nr_tests);
  rand_angles(angles, nr_tests);

  t = clock();
  for (int i = 0; i < nr_tests; i++)
  {
    CM_TransformedPointContents(points[i], model, origins[i], angles);
  }

  t = clock() - t;
  time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
  printf("PGA       version took %f ms to execute \n", time_taken);

  t = clock();
  for (int i = 0; i < nr_tests; i++)
  {
    old_CM_TransformedPointContents(points[i], model, origins[i], angles);
  }

  t = clock() - t;
  time_taken = ((double)t) / CLOCKS_PER_SEC * 1000;
  printf("Ioquake3  version took %f ms to execute \n", time_taken);
}

int main() {
  srand(time(NULL));

  printf("ProjectPointOnPlane results\n");
  test_ProjectPointOnPlane();
  printf("\nRotatePointAroundVector results\n");
  test_RotatePointAroundVector();
  printf("\nCM_TransformedPointContents results\n");
  test_CM_TransformedPointContents();
  return 0;
}