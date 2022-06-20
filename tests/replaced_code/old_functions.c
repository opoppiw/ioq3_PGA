/**
 * old_functions.c
 *
 * This file contains all the functions that have been replaced by PGA implementations.
 * These functions are still used in unit testing.
 *
 */

#include "old_functions.h"
#include "../../code/qcommon/cm_local.h"

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
	 *        | cos(rad)  sin(rad)  0 |
	 * zrot = | -sin(rad) cos(rad)  0 |
	 *        | 0         0         1 |
	 */

	MatrixMultiply( m, zrot, tmpmat );
	MatrixMultiply( tmpmat, im, rot );

	/**
	 *
	 * rot = m * zrot * im = m * zrot * m^T = m * zrot * m^(-1)
	 *
	 */

	for ( i = 0; i < 3; i++ ) {
		dst[i] = rot[i][0] * point[0] + rot[i][1] * point[1] + rot[i][2] * point[2];
	}
}

/**
 * Old version of ProjectPointOnPlane().
 *
 * This function projects point 'p' on the plane with normal vector 'normal'
 * and places the result in 'd'. Note that the plane goes through the origin.
 *
 * ! Important: This function contains a mistake. It normalizes 'normal' to get
 * !            'n', but it should not do that. Because of this, the function
 * !            only gives correct results if 'normal' has length 1.
 */
void old_ProjectPointOnPlane( vec3_t dst, const vec3_t p, const vec3_t normal )
{
	float d;
	vec3_t n;
	float inv_denom;

	inv_denom =  DotProduct( normal, normal );
// #ifndef Q3_VM
// 	assert( Q_fabs(inv_denom) != 0.0f ); // zero vectors get here
// #endif
	inv_denom = 1.0f / inv_denom;

	d = DotProduct( normal, p ) * inv_denom;

	n[0] = normal[0] * inv_denom;
	n[1] = normal[1] * inv_denom;
	n[2] = normal[2] * inv_denom;

	dst[0] = p[0] - d * n[0];
	dst[1] = p[1] - d * n[1];
	dst[2] = p[2] - d * n[2];
}

/*
==================
CM_TransformedPointContents

Handles offseting and rotation of the end points for moving and
rotating entities
==================
*/
int old_CM_TransformedPointContents(const vec3_t p, clipHandle_t model, const vec3_t origin, const vec3_t angles)
{
	vec3_t p_l;
	vec3_t temp;
	vec3_t forward, right, up;

	// subtract origin offset
	VectorSubtract(p, origin, p_l);

	// rotate start and end into the models frame of reference
	if (model != BOX_MODEL_HANDLE &&
		(angles[0] || angles[1] || angles[2]))
	{
		AngleVectors(angles, forward, right, up);

		VectorCopy(p_l, temp);
		p_l[0] = DotProduct(temp, forward);
		p_l[1] = -DotProduct(temp, right);
		p_l[2] = DotProduct(temp, up);
	}

	return CM_PointContents(p_l, model);
}