/*
Copyright (c) 2008, Luke Benstead.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file mat4.c
 */
#include <memory.h>
#include <assert.h>
#include <stdlib.h>

#include <kazmath/utility.h>
#include <kazmath/vec3.h>
#include <kazmath/mat4.h>
#include <kazmath/mat3.h>
#include <kazmath/quaternion.h>
#include <kazmath/plane.h>

kmMat4* kmMat4Fill(kmMat4* pOut, const kmScalar* pMat)
{
    memcpy(pOut->mat, pMat, sizeof(kmScalar) * 16);
    return pOut;
}

kmMat4* kmMat4Identity(kmMat4* pOut)
{
	memset(pOut->mat, 0, sizeof(kmScalar) * 16);
	pOut->mat[0] = pOut->mat[5] = pOut->mat[10] = pOut->mat[15] = 1.0f;
	return pOut;
}

kmMat4* kmMat4Inverse(kmMat4* pOut, const kmMat4* pM) {
    kmMat4 tmp;
    kmScalar det;
    int i;

    tmp.mat[0] = pM->mat[5]  * pM->mat[10] * pM->mat[15] -
             pM->mat[5]  * pM->mat[11] * pM->mat[14] -
             pM->mat[9]  * pM->mat[6]  * pM->mat[15] +
             pM->mat[9]  * pM->mat[7]  * pM->mat[14] +
             pM->mat[13] * pM->mat[6]  * pM->mat[11] -
             pM->mat[13] * pM->mat[7]  * pM->mat[10];

    tmp.mat[4] = -pM->mat[4]  * pM->mat[10] * pM->mat[15] +
              pM->mat[4]  * pM->mat[11] * pM->mat[14] +
              pM->mat[8]  * pM->mat[6]  * pM->mat[15] -
              pM->mat[8]  * pM->mat[7]  * pM->mat[14] -
              pM->mat[12] * pM->mat[6]  * pM->mat[11] +
              pM->mat[12] * pM->mat[7]  * pM->mat[10];

    tmp.mat[8] = pM->mat[4]  * pM->mat[9] * pM->mat[15] -
             pM->mat[4]  * pM->mat[11] * pM->mat[13] -
             pM->mat[8]  * pM->mat[5] * pM->mat[15] +
             pM->mat[8]  * pM->mat[7] * pM->mat[13] +
             pM->mat[12] * pM->mat[5] * pM->mat[11] -
             pM->mat[12] * pM->mat[7] * pM->mat[9];

    tmp.mat[12] = -pM->mat[4]  * pM->mat[9] * pM->mat[14] +
               pM->mat[4]  * pM->mat[10] * pM->mat[13] +
               pM->mat[8]  * pM->mat[5] * pM->mat[14] -
               pM->mat[8]  * pM->mat[6] * pM->mat[13] -
               pM->mat[12] * pM->mat[5] * pM->mat[10] +
               pM->mat[12] * pM->mat[6] * pM->mat[9];

    tmp.mat[1] = -pM->mat[1]  * pM->mat[10] * pM->mat[15] +
              pM->mat[1]  * pM->mat[11] * pM->mat[14] +
              pM->mat[9]  * pM->mat[2] * pM->mat[15] -
              pM->mat[9]  * pM->mat[3] * pM->mat[14] -
              pM->mat[13] * pM->mat[2] * pM->mat[11] +
              pM->mat[13] * pM->mat[3] * pM->mat[10];

    tmp.mat[5] = pM->mat[0]  * pM->mat[10] * pM->mat[15] -
             pM->mat[0]  * pM->mat[11] * pM->mat[14] -
             pM->mat[8]  * pM->mat[2] * pM->mat[15] +
             pM->mat[8]  * pM->mat[3] * pM->mat[14] +
             pM->mat[12] * pM->mat[2] * pM->mat[11] -
             pM->mat[12] * pM->mat[3] * pM->mat[10];

    tmp.mat[9] = -pM->mat[0]  * pM->mat[9] * pM->mat[15] +
              pM->mat[0]  * pM->mat[11] * pM->mat[13] +
              pM->mat[8]  * pM->mat[1] * pM->mat[15] -
              pM->mat[8]  * pM->mat[3] * pM->mat[13] -
              pM->mat[12] * pM->mat[1] * pM->mat[11] +
              pM->mat[12] * pM->mat[3] * pM->mat[9];

    tmp.mat[13] = pM->mat[0]  * pM->mat[9] * pM->mat[14] -
              pM->mat[0]  * pM->mat[10] * pM->mat[13] -
              pM->mat[8]  * pM->mat[1] * pM->mat[14] +
              pM->mat[8]  * pM->mat[2] * pM->mat[13] +
              pM->mat[12] * pM->mat[1] * pM->mat[10] -
              pM->mat[12] * pM->mat[2] * pM->mat[9];

    tmp.mat[2] = pM->mat[1]  * pM->mat[6] * pM->mat[15] -
             pM->mat[1]  * pM->mat[7] * pM->mat[14] -
             pM->mat[5]  * pM->mat[2] * pM->mat[15] +
             pM->mat[5]  * pM->mat[3] * pM->mat[14] +
             pM->mat[13] * pM->mat[2] * pM->mat[7] -
             pM->mat[13] * pM->mat[3] * pM->mat[6];

    tmp.mat[6] = -pM->mat[0]  * pM->mat[6] * pM->mat[15] +
              pM->mat[0]  * pM->mat[7] * pM->mat[14] +
              pM->mat[4]  * pM->mat[2] * pM->mat[15] -
              pM->mat[4]  * pM->mat[3] * pM->mat[14] -
              pM->mat[12] * pM->mat[2] * pM->mat[7] +
              pM->mat[12] * pM->mat[3] * pM->mat[6];

    tmp.mat[10] = pM->mat[0]  * pM->mat[5] * pM->mat[15] -
              pM->mat[0]  * pM->mat[7] * pM->mat[13] -
              pM->mat[4]  * pM->mat[1] * pM->mat[15] +
              pM->mat[4]  * pM->mat[3] * pM->mat[13] +
              pM->mat[12] * pM->mat[1] * pM->mat[7] -
              pM->mat[12] * pM->mat[3] * pM->mat[5];

    tmp.mat[14] = -pM->mat[0]  * pM->mat[5] * pM->mat[14] +
               pM->mat[0]  * pM->mat[6] * pM->mat[13] +
               pM->mat[4]  * pM->mat[1] * pM->mat[14] -
               pM->mat[4]  * pM->mat[2] * pM->mat[13] -
               pM->mat[12] * pM->mat[1] * pM->mat[6] +
               pM->mat[12] * pM->mat[2] * pM->mat[5];

    tmp.mat[3] = -pM->mat[1] * pM->mat[6] * pM->mat[11] +
              pM->mat[1] * pM->mat[7] * pM->mat[10] +
              pM->mat[5] * pM->mat[2] * pM->mat[11] -
              pM->mat[5] * pM->mat[3] * pM->mat[10] -
              pM->mat[9] * pM->mat[2] * pM->mat[7] +
              pM->mat[9] * pM->mat[3] * pM->mat[6];

    tmp.mat[7] = pM->mat[0] * pM->mat[6] * pM->mat[11] -
             pM->mat[0] * pM->mat[7] * pM->mat[10] -
             pM->mat[4] * pM->mat[2] * pM->mat[11] +
             pM->mat[4] * pM->mat[3] * pM->mat[10] +
             pM->mat[8] * pM->mat[2] * pM->mat[7] -
             pM->mat[8] * pM->mat[3] * pM->mat[6];

    tmp.mat[11] = -pM->mat[0] * pM->mat[5] * pM->mat[11] +
               pM->mat[0] * pM->mat[7] * pM->mat[9] +
               pM->mat[4] * pM->mat[1] * pM->mat[11] -
               pM->mat[4] * pM->mat[3] * pM->mat[9] -
               pM->mat[8] * pM->mat[1] * pM->mat[7] +
               pM->mat[8] * pM->mat[3] * pM->mat[5];

    tmp.mat[15] = pM->mat[0] * pM->mat[5] * pM->mat[10] -
              pM->mat[0] * pM->mat[6] * pM->mat[9] -
              pM->mat[4] * pM->mat[1] * pM->mat[10] +
              pM->mat[4] * pM->mat[2] * pM->mat[9] +
              pM->mat[8] * pM->mat[1] * pM->mat[6] -
              pM->mat[8] * pM->mat[2] * pM->mat[5];

    det = pM->mat[0] * tmp.mat[0] + pM->mat[1] * tmp.mat[4] + pM->mat[2] * tmp.mat[8] + pM->mat[3] * tmp.mat[12];

    if (det == 0) {
        return NULL;
    }

    det = 1.0 / det;

    for (i = 0; i < 16; i++) {
        pOut->mat[i] = tmp.mat[i] * det;
    }

    return pOut;
}

int  kmMat4IsIdentity(const kmMat4* pIn)
{
	static kmScalar identity [] = { 	1.0f, 0.0f, 0.0f, 0.0f,
	                                    0.0f, 1.0f, 0.0f, 0.0f,
	                                    0.0f, 0.0f, 1.0f, 0.0f,
	                                    0.0f, 0.0f, 0.0f, 1.0f
	                                 };

	return (memcmp(identity, pIn->mat, sizeof(kmScalar) * 16) == 0);
}

kmMat4* kmMat4Transpose(kmMat4* pOut, const kmMat4* pIn)
{
    int x, z;

    for (z = 0; z < 4; ++z) {
        for (x = 0; x < 4; ++x) {
	    pOut->mat[(z * 4) + x] = pIn->mat[(x * 4) + z];
        }
    }

    return pOut;
}

kmMat4* kmMat4Multiply(kmMat4* pOut, const kmMat4* pM1, const kmMat4* pM2)
{
	kmScalar mat[16];

	const kmScalar *m1 = pM1->mat, *m2 = pM2->mat;

	mat[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	mat[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	mat[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	mat[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

	mat[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	mat[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	mat[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	mat[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

	mat[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
	mat[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
	mat[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
	mat[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

	mat[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
	mat[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
	mat[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
	mat[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];


	memcpy(pOut->mat, mat, sizeof(kmScalar)*16);

	return pOut;
}

kmMat4* kmMat4Assign(kmMat4* pOut, const kmMat4* pIn)
{
	assert(pOut != pIn && "You have tried to self-assign!!");

	memcpy(pOut->mat, pIn->mat, sizeof(kmScalar)*16);

	return pOut;
}

kmMat4* kmMat4AssignMat3(kmMat4* pOut, const kmMat3* pIn) {
    kmMat4Identity(pOut);

    pOut->mat[0] = pIn->mat[0];
    pOut->mat[1] = pIn->mat[1];
    pOut->mat[2] = pIn->mat[2];
    pOut->mat[3] = 0.0;

    pOut->mat[4] = pIn->mat[3];
    pOut->mat[5] = pIn->mat[4];
    pOut->mat[6] = pIn->mat[5];
    pOut->mat[7] = 0.0;

    pOut->mat[8] = pIn->mat[6];
    pOut->mat[9] = pIn->mat[7];
    pOut->mat[10] = pIn->mat[8];
    pOut->mat[11] = 0.0;

    return pOut;
}


int kmMat4AreEqual(const kmMat4* pMat1, const kmMat4* pMat2)
{
    int i = 0;

	assert(pMat1 != pMat2 && "You are comparing the same thing!");

	for (i = 0; i < 16; ++i)
	{
        if(!kmAlmostEqual(pMat1->mat[i], pMat2->mat[i])) {
			return KM_FALSE;
        }
	}

	return KM_TRUE;
}

kmMat4* kmMat4RotationAxisAngle(kmMat4* pOut, const kmVec3* axis, kmScalar radians)
{
    kmQuaternion quat;
    kmQuaternionRotationAxisAngle(&quat, axis, radians);
    kmMat4RotationQuaternion(pOut, &quat);
    return pOut;
}

kmMat4* kmMat4RotationX(kmMat4* pOut, const kmScalar radians)
{
	/*
		 |  1  0       0       0 |
	 M = |  0  cos(A) -sin(A)  0 |
	     |  0  sin(A)  cos(A)  0 |
	     |  0  0       0       1 |

	*/

	pOut->mat[0] = 1.0f;
	pOut->mat[1] = 0.0f;
	pOut->mat[2] = 0.0f;
	pOut->mat[3] = 0.0f;

	pOut->mat[4] = 0.0f;
	pOut->mat[5] = cosf(radians);
	pOut->mat[6] = sinf(radians);
	pOut->mat[7] = 0.0f;

	pOut->mat[8] = 0.0f;
	pOut->mat[9] = -sinf(radians);
	pOut->mat[10] = cosf(radians);
	pOut->mat[11] = 0.0f;

	pOut->mat[12] = 0.0f;
	pOut->mat[13] = 0.0f;
	pOut->mat[14] = 0.0f;
	pOut->mat[15] = 1.0f;

	return pOut;
}

kmMat4* kmMat4RotationY(kmMat4* pOut, const kmScalar radians)
{
	/*
	     |  cos(A)  0   sin(A)  0 |
	 M = |  0       1   0       0 |
	     | -sin(A)  0   cos(A)  0 |
	     |  0       0   0       1 |
	*/

	pOut->mat[0] = cosf(radians);
	pOut->mat[1] = 0.0f;
	pOut->mat[2] = -sinf(radians);
	pOut->mat[3] = 0.0f;

	pOut->mat[4] = 0.0f;
	pOut->mat[5] = 1.0f;
	pOut->mat[6] = 0.0f;
	pOut->mat[7] = 0.0f;

	pOut->mat[8] = sinf(radians);
	pOut->mat[9] = 0.0f;
	pOut->mat[10] = cosf(radians);
	pOut->mat[11] = 0.0f;

	pOut->mat[12] = 0.0f;
	pOut->mat[13] = 0.0f;
	pOut->mat[14] = 0.0f;
	pOut->mat[15] = 1.0f;

	return pOut;
}

kmMat4* kmMat4RotationZ(kmMat4* pOut, const kmScalar radians)
{
	/*
	     |  cos(A)  -sin(A)   0   0 |
	 M = |  sin(A)   cos(A)   0   0 |
	     |  0        0        1   0 |
	     |  0        0        0   1 |
	*/

	pOut->mat[0] = cosf(radians);
	pOut->mat[1] = sinf(radians);
	pOut->mat[2] = 0.0f;
	pOut->mat[3] = 0.0f;

	pOut->mat[4] = -sinf(radians);
	pOut->mat[5] = cosf(radians);
	pOut->mat[6] = 0.0f;
	pOut->mat[7] = 0.0f;

	pOut->mat[8] = 0.0f;
	pOut->mat[9] = 0.0f;
	pOut->mat[10] = 1.0f;
	pOut->mat[11] = 0.0f;

	pOut->mat[12] = 0.0f;
	pOut->mat[13] = 0.0f;
	pOut->mat[14] = 0.0f;
	pOut->mat[15] = 1.0f;

	return pOut;
}

kmMat4* kmMat4RotationYawPitchRoll(kmMat4* pOut, const kmScalar pitch, const kmScalar yaw, const kmScalar roll)
{

    kmMat4 yaw_matrix;
    kmMat4 roll_matrix;
    kmMat4 pitch_matrix;

    kmMat4RotationY(&yaw_matrix, yaw);

    kmMat4RotationX(&pitch_matrix, pitch);

    kmMat4RotationZ(&roll_matrix, roll);

    kmMat4Multiply(pOut, &pitch_matrix, &roll_matrix);
    kmMat4Multiply(pOut, &yaw_matrix, pOut);

    return pOut;
}

kmMat4* kmMat4RotationQuaternion(kmMat4* pOut, const kmQuaternion* pQ)
{
    double xx = pQ->x * pQ->x;
    double xy = pQ->x * pQ->y;
    double xz = pQ->x * pQ->z;
    double xw = pQ->x * pQ->w;

    double yy = pQ->y * pQ->y;
    double yz = pQ->y * pQ->z;
    double yw = pQ->y * pQ->w;

    double zz = pQ->z * pQ->z;
    double zw = pQ->z * pQ->w;

    pOut->mat[0] = 1 - 2 * (yy + zz);
    pOut->mat[1] = 2 * (xy + zw);
    pOut->mat[2] = 2 * (xz - yw);
    pOut->mat[3] = 0;

    pOut->mat[4] = 2 * (xy - zw);
    pOut->mat[5] = 1 - 2 * (xx + zz);
    pOut->mat[6] = 2 * (yz + xw);
    pOut->mat[7] = 0.0;

    pOut->mat[8] = 2 * (xz + yw);
    pOut->mat[9] = 2 * (yz - xw);
    pOut->mat[10] = 1 - 2 * (xx + yy);
    pOut->mat[11] = 0.0;

    pOut->mat[12] = 0.0;
    pOut->mat[13] = 0.0;
    pOut->mat[14] = 0.0;
    pOut->mat[15] = 1.0;

    return pOut;
}

kmMat4* kmMat4Scaling(kmMat4* pOut, const kmScalar x, const kmScalar y,
                      kmScalar z)
{
	memset(pOut->mat, 0, sizeof(kmScalar) * 16);
	pOut->mat[0] = x;
	pOut->mat[5] = y;
	pOut->mat[10] = z;
	pOut->mat[15] = 1.0f;

	return pOut;
}

kmMat4* kmMat4Translation(kmMat4* pOut, const kmScalar x,
                          kmScalar y, const kmScalar z)
{
    /*FIXME: Write a test for this*/
    memset(pOut->mat, 0, sizeof(kmScalar) * 16);

    pOut->mat[0] = 1.0f;
    pOut->mat[5] = 1.0f;
    pOut->mat[10] = 1.0f;

    pOut->mat[12] = x;
    pOut->mat[13] = y;
    pOut->mat[14] = z;
    pOut->mat[15] = 1.0f;

    return pOut;
}

kmVec3* kmMat4GetUpVec3(kmVec3* pOut, const kmMat4* pIn)
{
    kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_Y, pIn);
    kmVec3Normalize(pOut, pOut);
    return pOut;
}

kmVec3* kmMat4GetRightVec3(kmVec3* pOut, const kmMat4* pIn)
{
    kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_X, pIn);
    kmVec3Normalize(pOut, pOut);
    return pOut;
}

kmVec3* kmMat4GetForwardVec3RH(kmVec3* pOut, const kmMat4* pIn)
{
    kmVec3MultiplyMat4(pOut, &KM_VEC3_NEG_Z, pIn);
    kmVec3Normalize(pOut, pOut);
    return pOut;
}

kmVec3* kmMat4GetForwardVec3LH(kmVec3* pOut, const kmMat4* pIn)
{
    kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_Z, pIn);
    kmVec3Normalize(pOut, pOut);
	return pOut;
}

kmMat4* kmMat4PerspectiveProjection(kmMat4* pOut, kmScalar fovY,
                                    kmScalar aspect, kmScalar zNear,
                                    kmScalar zFar)
{
	kmScalar r = kmDegreesToRadians(fovY / 2);
    kmScalar deltaZ = zNear - zFar;
	kmScalar s = sin(r);
	kmScalar cotangent = 0;

	if (deltaZ == 0 || s == 0 || aspect == 0) {
		return NULL;
	}

    /*cos(r) / sin(r) = cot(r)*/
	cotangent = cos(r) / s;

	kmMat4Identity(pOut);
	pOut->mat[0] = cotangent / aspect;
	pOut->mat[5] = cotangent;
    pOut->mat[10] = (zFar + zNear) / deltaZ;
	pOut->mat[11] = -1;
    pOut->mat[14] = (2 * zFar * zNear) / deltaZ;
	pOut->mat[15] = 0;

	return pOut;
}

kmMat4* kmMat4OrthographicProjection(kmMat4* pOut, kmScalar left,
                                     kmScalar right, kmScalar bottom,
                                     kmScalar top, kmScalar nearVal,
                                     kmScalar farVal)
{
	kmScalar tx = -((right + left) / (right - left));
	kmScalar ty = -((top + bottom) / (top - bottom));
	kmScalar tz = -((farVal + nearVal) / (farVal - nearVal));

	kmMat4Identity(pOut);
	pOut->mat[0] = 2 / (right - left);
	pOut->mat[5] = 2 / (top - bottom);
	pOut->mat[10] = -2 / (farVal - nearVal);
	pOut->mat[12] = tx;
	pOut->mat[13] = ty;
	pOut->mat[14] = tz;

	return pOut;
}

kmMat4* kmMat4LookAt(kmMat4* pOut, const kmVec3* pEye,
                     const kmVec3* pCenter, const kmVec3* pUp)
{
    kmVec3 f;
    kmVec3 s;
    kmVec3 u;

    kmVec3Subtract(&f, pCenter, pEye);
    kmVec3Normalize(&f, &f);

    kmVec3Cross(&s, &f, pUp);
    kmVec3Normalize(&s, &s);

    kmVec3Cross(&u, &s, &f);

    pOut->mat[0] = s.x;
    pOut->mat[1] = u.x;
    pOut->mat[2] = -f.x;
    pOut->mat[3] = 0.0;

    pOut->mat[4] = s.y;
    pOut->mat[5] = u.y;
    pOut->mat[6] = -f.y;
    pOut->mat[7] = 0.0;

    pOut->mat[8] = s.z;
    pOut->mat[9] = u.z;
    pOut->mat[10] = -f.z;
    pOut->mat[11] = 0.0;

    pOut->mat[12] = -kmVec3Dot(&s, pEye);
    pOut->mat[13] = -kmVec3Dot(&u, pEye);
    pOut->mat[14] = kmVec3Dot(&f, pEye);
    pOut->mat[15] = 1.0;

    return pOut;
}

kmMat3* kmMat4ExtractRotationMat3(const kmMat4* pIn, kmMat3* pOut)
{
    pOut->mat[0] = pIn->mat[0];
    pOut->mat[1] = pIn->mat[1];
    pOut->mat[2] = pIn->mat[2];

    pOut->mat[3] = pIn->mat[4];
    pOut->mat[4] = pIn->mat[5];
    pOut->mat[5] = pIn->mat[6];

    pOut->mat[6] = pIn->mat[8];
    pOut->mat[7] = pIn->mat[9];
    pOut->mat[8] = pIn->mat[10];

    return pOut;
}

kmVec3* kmMat4RotationToAxisAngle(kmVec3* pAxis, kmScalar* radians, const kmMat4* pIn)
{
    /*Surely not this easy?*/
    kmQuaternion temp;
    kmMat3 rotation;
    kmMat4ExtractRotationMat3(pIn, &rotation);
    kmQuaternionRotationMatrix(&temp, &rotation);
    kmQuaternionToAxisAngle(&temp, pAxis, radians);
    return pAxis;
}

kmMat4* kmMat4RotationTranslation(kmMat4* pOut, const kmMat3* rotation, const kmVec3* translation)
{
    pOut->mat[0] = rotation->mat[0];
    pOut->mat[1] = rotation->mat[1];
    pOut->mat[2] = rotation->mat[2];
    pOut->mat[3] = 0.0f;

    pOut->mat[4] = rotation->mat[3];
    pOut->mat[5] = rotation->mat[4];
    pOut->mat[6] = rotation->mat[5];
    pOut->mat[7] = 0.0f;

    pOut->mat[8] = rotation->mat[6];
    pOut->mat[9] = rotation->mat[7];
    pOut->mat[10] = rotation->mat[8];
    pOut->mat[11] = 0.0f;

    pOut->mat[12] = translation->x;
    pOut->mat[13] = translation->y;
    pOut->mat[14] = translation->z;
    pOut->mat[15] = 1.0f;

    return pOut;
}

kmPlane* kmMat4ExtractPlane(kmPlane* pOut, const kmMat4* pIn, const kmEnum plane)
{
    kmScalar t = 1.0f;

    switch(plane) {
        case KM_PLANE_RIGHT:
            pOut->a = pIn->mat[3] - pIn->mat[0];
            pOut->b = pIn->mat[7] - pIn->mat[4];
            pOut->c = pIn->mat[11] - pIn->mat[8];
            pOut->d = pIn->mat[15] - pIn->mat[12];
        break;
        case KM_PLANE_LEFT:
            pOut->a = pIn->mat[3] + pIn->mat[0];
            pOut->b = pIn->mat[7] + pIn->mat[4];
            pOut->c = pIn->mat[11] + pIn->mat[8];
            pOut->d = pIn->mat[15] + pIn->mat[12];
        break;
        case KM_PLANE_BOTTOM:
            pOut->a = pIn->mat[3] + pIn->mat[1];
            pOut->b = pIn->mat[7] + pIn->mat[5];
            pOut->c = pIn->mat[11] + pIn->mat[9];
            pOut->d = pIn->mat[15] + pIn->mat[13];
        break;
        case KM_PLANE_TOP:
            pOut->a = pIn->mat[3] - pIn->mat[1];
            pOut->b = pIn->mat[7] - pIn->mat[5];
            pOut->c = pIn->mat[11] - pIn->mat[9];
            pOut->d = pIn->mat[15] - pIn->mat[13];
        break;
        case KM_PLANE_FAR:
            pOut->a = pIn->mat[3] - pIn->mat[2];
            pOut->b = pIn->mat[7] - pIn->mat[6];
            pOut->c = pIn->mat[11] - pIn->mat[10];
            pOut->d = pIn->mat[15] - pIn->mat[14];
        break;
        case KM_PLANE_NEAR:
            pOut->a = pIn->mat[3] + pIn->mat[2];
            pOut->b = pIn->mat[7] + pIn->mat[6];
            pOut->c = pIn->mat[11] + pIn->mat[10];
            pOut->d = pIn->mat[15] + pIn->mat[14];
        break;
        default:
            assert(0 && "Invalid plane index");
    }

    t = sqrtf(pOut->a * pOut->a +
                    pOut->b * pOut->b +
                    pOut->c * pOut->c);
    pOut->a /= t;
    pOut->b /= t;
    pOut->c /= t;
    pOut->d /= t;

    return pOut;
}

kmVec3* kmMat4ExtractTranslationVec3(const kmMat4* pIn, struct kmVec3* pOut) {
    pOut->x = pIn->mat[12];
    pOut->y = pIn->mat[13];
    pOut->z = pIn->mat[14];
    return pOut;
}
