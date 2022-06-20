/**
 *
 * old_functions.h
 *
 * This file contains all the functions that have been replaced by PGA
 * implementations. These functions are still used in unit testing.
 *
 */

#include "../../code/qcommon/q_shared.h"

void old_RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point, float degrees );

void old_ProjectPointOnPlane(vec3_t dst, const vec3_t p, const vec3_t normal);

int old_CM_TransformedPointContents(const vec3_t p, clipHandle_t model, const vec3_t origin, const vec3_t angles);