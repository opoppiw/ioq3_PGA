/**
 * q_math.spec.c
 *
 * This file contains unit tests for code/qcommon/q_shared.h
 *
 * WORK IN PROGRESS
 */

#include "../unity/unity.h"
#include "../../code/qcommon/q_shared.h"
#include <stdio.h>

void setUp(void) {
    // set stuff up here
}

void tearDown(void) {
    // clean stuff up here
}

void test_ColorBytes3(void) {
    TEST_ASSERT(ColorBytes3(1.1, 2.2, 3.3) == 4796696);
}

// not needed when using generate_test_runner.rb
int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_ColorBytes3);
    return UNITY_END();
}