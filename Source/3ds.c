// Adapted from https://github.com/devkitPro/citro3d/tree/master/source/maths

/**
 * Copyright (C) 2014-2018 fincs
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <kazmath/3ds.h>

#include <string.h> // memset

kmMat4* kmMat4OrthoTilt(kmMat4* pOut, kmScalar left, kmScalar right, kmScalar bottom, kmScalar top,
    kmScalar nearVal, kmScalar farVal, bool isLeftHanded) {

    memset(pOut->mat, 0, sizeof(kmScalar) * 16);

    /*
    0                2/(top - bottom) 0              (bottom + top)/(bottom - top)
    2/(left - right) 0                0              (left + right)/(right - left)


    leftHanded:
    0                0                1/(far - near) 0.5f*(near + far)/(near - far) - 0.5f
    else:
    0                0                1/(near - far) 0.5f*(near + far)/(near - far) - 0.5f

    0                0                0              1
    */

    pOut->mat[1] = 2.0f/(left - right);
    pOut->mat[4] = 2.0f/(top - bottom);
    
    if (isLeftHanded) {
        pOut->mat[10] = 1.0f/(farVal - nearVal);
    } else {
        pOut->mat[10] = 1.0f/(nearVal - farVal);
    }

    pOut->mat[12] = (bottom + top)/(bottom - top);
    pOut->mat[13] = (left + right)/(right - left);
    pOut->mat[14] = 0.5f * (nearVal + farVal) / (nearVal - farVal) - 0.5f;
    pOut->mat[15] = 1.0f;

    return pOut;
}