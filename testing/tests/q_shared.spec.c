/**
 * q_math.spec.c
 *
 * This file contains unit tests for code/qcommon/q_shared.h
 *
 * WORK IN PROGRESS
 */

#include "../unity/unity.h"
#include "../../code/qcommon/q_shared.h"
#include "../ioquake/old_functions.h"
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

    // ! Using the Klein library, the positive direction of rotation around a vector seems to
    // ! be determined using the left-hand rule, while I would expect the right-hand rule.
    // ! The expected results below are those you get using the right-hand rule.
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

    // ! The expected results below are those you get using the right-hand rule.
    vec3_t dirs[nr_tests] =         {{0, 10, 0} , {0,1,0}, {0,0,27}};
    vec3_t points[nr_tests] =       {{5, 0, 0}  , {1,0,0}, {3,3,3}};
    vec3_t expecteds[nr_tests] =    {{-5, 0, 0} , {0,0,-1}, {-3,3,3}};
    float degrees[nr_tests] =       {180        , 90      , 90};
    vec3_t result;

    for (int i = 0; i < nr_tests; i++) {
        old_RotatePointAroundVector(result, dirs[i], points[i], degrees[i]);
        printf("old: result = [%f, %f, %f]\n", result[0], result[1], result[2]); // TODO: REMOVE
        printf("old: expected = [%f, %f, %f]\n\n", expecteds[i][0], expecteds[i][1], expecteds[i][2]); // TODO: REMOVE

        for (int j = 0; j < 3; j++) {
            TEST_ASSERT_FLOAT_WITHIN(float_delta, expecteds[i][j], result[j]);
        }
    }
}

// void test_ProjectPointOnPlane(void) {
//     vec3_t normal = {1.0, 1.0, 0.0};
//     vec3_t point = {0.0, 1.0, 0.0};
//     vec3_t dst;
//     vec3_t expected_dst = {-0.5, 0.5, 0};

//     ProjectPointOnPlane(dst, point, normal);

//     printf("dst: {%f, %f, %f}", dst[0], dst[1], dst[2]);
// }

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_RotatePointAroundVector);
    RUN_TEST(test_old_RotatePointAroundVector);
    return UNITY_END();
}