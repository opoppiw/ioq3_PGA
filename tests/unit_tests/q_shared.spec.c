/**
 * q_math.spec.c
 *
 * This file contains unit tests for code/qcommon/q_shared.h
 *
 * WORK IN PROGRESS
 */

#include "unity/unity.h"
#include "../../code/qcommon/q_shared.h"
#include "../replaced_code/old_functions.h"
#include <stdio.h>


#define float_delta 0.00001 // The maximum difference for two floats to be considered equal

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_RotatePointAroundVector(void) {
    #define nr_tests 3

    vec3_t dirs[nr_tests] =         {{0, 10, 0} , {0,1,0}, {0,0,27}};
    vec3_t points[nr_tests] =       {{5, 0, 0}  , {1,0,0}, {3,3,3}};
    vec3_t expecteds[nr_tests] =    {{-5, 0, 0} , {0,0,-1}, {-3,3,3}};
    float degrees[nr_tests] =       {180        , 90      , 90};
    vec3_t result;

    for (int i = 0; i < nr_tests; i++) {
        RotatePointAroundVector(result, dirs[i], points[i], degrees[i]);

        for (int j = 0; j < 3; j++) {
            TEST_ASSERT_FLOAT_WITHIN(float_delta, expecteds[i][j], result[j]);
        }
    }
}

test_old_RotatePointAroundVector(void) {
    #define nr_tests 3

    vec3_t dirs[nr_tests] =         {{0, 50, 0} , {0,1,0}, {0,0,1}};
    vec3_t points[nr_tests] =       {{5, 0, 0}  , {1,0,0}, {3,3,3}};
    vec3_t expecteds[nr_tests] =    {{-5, 0, 0} , {0,0,-1}, {-3,3,3}};
    float degrees[nr_tests] =       {180        , 90      , 90};
    vec3_t result;

    for (int i = 0; i < nr_tests; i++) {
        old_RotatePointAroundVector(result, dirs[i], points[i], degrees[i]);

        for (int j = 0; j < 3; j++) {
            TEST_ASSERT_FLOAT_WITHIN(float_delta, expecteds[i][j], result[j]);
        }
    }
}

void test_ProjectPointOnPlane(void) {
    #define nr_tests 3

    vec3_t result;
    vec3_t points[nr_tests] =    {{0.0, 0.0, 5.0}, {0.0, 1.0, 0.0}, {3.2, 2.3, 3.3}};
    vec3_t normals[nr_tests] =   {{0.0, 0.0, 1.0}, {1.0/sqrt(2), 1.0/sqrt(2), 0.0}, {1/sqrt(21), 2/sqrt(21), 4/sqrt(21)}};
    vec3_t expecteds[nr_tests] = {{0.0, 0.0, 0.0}, {-0.5, 0.5, 0}, {2.2, 0.3, -0.7}};

    for (int i = 0; i < nr_tests; i++) {
        ProjectPointOnPlane(result, points[i], normals[i]);

        for (int j = 0; j < 3; j++) {
            TEST_ASSERT_FLOAT_WITHIN(float_delta, expecteds[i][j], result[j]);
        }
    }
}

void test_old_ProjectPointOnPlane(void) {
    #define nr_tests 3

    vec3_t result;
    vec3_t points[nr_tests] =    {{0.0, 0.0, 5.0}, {0.0, 1.0, 0.0}, {3.2, 2.3, 3.3}};
    vec3_t normals[nr_tests] =   {{0.0, 0.0, 1.0}, {1.0/sqrt(2), 1.0/sqrt(2), 0.0}, {1/sqrt(21), 2/sqrt(21), 4/sqrt(21)}};
    vec3_t expecteds[nr_tests] = {{0.0, 0.0, 0.0}, {-0.5, 0.5, 0}, {2.2, 0.3, -0.7}};

    for (int i = 0; i < nr_tests; i++) {
        old_ProjectPointOnPlane(result, points[i], normals[i]);

        for (int j = 0; j < 3; j++) {
            TEST_ASSERT_FLOAT_WITHIN(float_delta, expecteds[i][j], result[j]);
        }
    }
}

/**
 * roll: rotation around x-axis
 * pitch: rotation around y-axis
 * yaw: rotation around z-axis.
 */
void test_vectoangles(void) {
    vec3_t angles;
    vec3_t vec = {5, -2, 5};

    vectoangles(vec, angles);
    printf("Angles: roll(x)=%f, pitch(y)=%f, yaw(z)=%f\n", angles[ROLL], angles[PITCH], angles[YAW]);
}

int main(void) {
    UNITY_BEGIN();

    // vec3_t vf = {0, 0, 1};
    // vec3_t vr;
    // PerpendicularVector(&vr, &vf);

    // printf("vr = [%f, %f, %f]\n", vr[0], vr[1], vr[2]);

    // RUN_TEST(test_RotatePointAroundVector);
    // RUN_TEST(test_ProjectPointOnPlane);
    // RUN_TEST(test_old_ProjectPointOnPlane);

    // RUN_TEST(test_vectoangles);

    RUN_TEST(test_old_RotatePointAroundVector); // ! Fails

    return UNITY_END();
}
