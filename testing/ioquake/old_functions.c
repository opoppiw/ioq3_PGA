/**
 * old_functions.c
 *
 * This file contains all the functions that have been replaced by PGA implementations.
 * These functions are still used in unit testing.
 *
 */

#include "old_functions.h"

/*
===============
RotatePointAroundVector

This is not implemented very well...
===============
! For some inputs, this functions gives very strange results.
! For dir={0,0,27}, point={3,3,3} and degrees=90 the expected output is {-3,3,3},
! but the output of this function is {-81, 91, 2187}
*/
void old_RotatePointAroundVector( vec3_t dst, const vec3_t dir, const vec3_t point,
							 float degrees ) {
	float	m[3][3];
	float	im[3][3];
	float	zrot[3][3];
	float	tmpmat[3][3];
	float	rot[3][3];
	int	i;
	vec3_t vr, vup, vf;
	float	rad;

	// ! vf seems to be unnecessary. dir can be used everywhere instead of vf.
	vf[0] = dir[0];
	vf[1] = dir[1];
	vf[2] = dir[2];
	// vf equals dir

	PerpendicularVector( vr, dir ); // vr is perpendicular to dir
	CrossProduct( vr, vf, vup ); // vup is perpendicular to vr and vf.

	m[0][0] = vr[0];
	m[1][0] = vr[1];
	m[2][0] = vr[2];

	m[0][1] = vup[0];
	m[1][1] = vup[1];
	m[2][1] = vup[2];

	m[0][2] = vf[0];
	m[1][2] = vf[1];
	m[2][2] = vf[2];

	/**
	 *
	 * m = [vr vup vf]
	 *
	 */

	// ! This operation is unnecessarily expensive, since most values of im are
	// ! overwritten in the following lines.
	memcpy( im, m, sizeof( im ) ); // im is a copy of m

	im[0][1] = m[1][0];
	im[0][2] = m[2][0];
	im[1][0] = m[0][1];
	im[1][2] = m[2][1];
	im[2][0] = m[0][2];
	im[2][1] = m[1][2];

	// im is the transpose of m.

	// ! Unnecessary 0 writes are done. It's also unnecessary to write 1.0F to
	// ! zrot[0][0] and z[1][1] since they are overwritten in the next lines.
	memset( zrot, 0, sizeof( zrot ) );
	zrot[0][0] = zrot[1][1] = zrot[2][2] = 1.0F;

	rad = DEG2RAD( degrees );
	zrot[0][0] = cos( rad );
	zrot[0][1] = sin( rad );
	zrot[1][0] = -sin( rad );
	zrot[1][1] = cos( rad );

	/**
	 *        | cos(rad) -sin(rad) 0 |
	 * zrot = | sin(rad) cos(rad)  0 |
	 *        | 0        0         1 |
	 */

	MatrixMultiply( m, zrot, tmpmat );
	MatrixMultiply( tmpmat, im, rot );

	/**
	 *
	 * rot = m * zrot * im = m * zrot * m^T
	 *
	 */

	for ( i = 0; i < 3; i++ ) {
		dst[i] = rot[i][0] * point[0] + rot[i][1] * point[1] + rot[i][2] * point[2];
	}

}