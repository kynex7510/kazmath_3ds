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

    // Standard orthogonal projection matrix, with a fixed depth range of [-1,0] (required by PICA) and rotated τ/4 radians counterclockwise around the Z axis (due to 3DS screen orientation)
    // http://www.wolframalpha.com/input/?i={{0,1,0,0},{-1,0,0,0},{0,0,1,0},{0,0,0,1}}{{1,0,0,0},{0,1,0,0},{0,0,0.5,-0.5},{0,0,0,1}}
    // http://www.wolframalpha.com/input/?i={{0,1,0,0},{-1,0,0,0},{0,0,0.5,-0.5},{0,0,0,1}}{{2/(r-l),0,0,(l%2Br)/(l-r)},{0,2/(t-b),0,(b%2Bt)/(b-t)},{0,0,2/(n-f),(n%2Bf)/(n-f)},{0,0,0,1}}

    memset(pOut->mat, 0, sizeof(kmScalar) * 16);

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

kmMat4* kmMat4PerspTilt(kmMat4* pOut, kmScalar fovx, kmScalar invaspect, kmScalar near, kmScalar far, bool isLeftHanded) {
    // Notes:
    // We are passed "fovy" and the "aspect ratio". However, the 3DS screens are sideways,
    // and so are these parameters -- in fact, they are actually the fovx and the inverse
    // of the aspect ratio. Therefore the formula for the perspective projection matrix
    // had to be modified to be expressed in these terms instead.

    // Notes:
    // Includes adjusting depth range from [-1,1] to [-1,0]
    // Includes rotation of the matrix one quarter of a turn clockwise in order to fix the 3DS screens' orientation

    // Notes:
    // fovx = 2 atan(tan(fovy/2)*w/h)
    // fovy = 2 atan(tan(fovx/2)*h/w)
    // invaspect = h/w

    // a0,0 = h / (w*tan(fovy/2)) =
    //      = h / (w*tan(2 atan(tan(fovx/2)*h/w) / 2)) =
    //      = h / (w*tan( atan(tan(fovx/2)*h/w) )) =
    //      = h / (w * tan(fovx/2)*h/w) =
    //      = 1 / tan(fovx/2)

    // a1,1 = 1 / tan(fovy/2) = (...) = w / (h*tan(fovx/2))

    const kmScalar fovx_tan = tanf(fovx/2.0f);

    memset(pOut, 0, sizeof(kmMat4));

    pOut->mat[1] = -1.0f / (fovx_tan*invaspect);
    pOut->mat[4] = 1.0f / fovx_tan;
    pOut->mat[11] = isLeftHanded ? 1.0f : -1.0f;
    pOut->mat[10] = -pOut->mat[11] * near / (near - far);
    pOut->mat[14] = near * far / (near - far);

    return pOut;
}

kmMat4* kmMat4PerspStereoTilt(kmMat4* pOut, kmScalar fovx, kmScalar invaspect, kmScalar near, kmScalar far,
    kmScalar iod, kmScalar screen, bool isLeftHanded) {
    // Notes:
    // Once again, we are passed "fovy" and the "aspect ratio"; however the 3DS screens are sideways,
    // and the formula had to be tweaked. With stereo, left/right separation becomes top/bottom separation.
    // The detailed mathematical explanation is in PerspTilt.

    const kmScalar fovx_tan = tanf(fovx/2.0f);
    const kmScalar fovx_tan_invaspect = fovx_tan*invaspect;
    const kmScalar shift = iod / (2.0f*screen); // 'near' not in the numerator because it cancels out in mat[9].

    memset(pOut, 0, sizeof(kmMat4));

    pOut->mat[1] = -1.0f / fovx_tan_invaspect;
    pOut->mat[4] = 1.0f / fovx_tan;
    pOut->mat[11] = isLeftHanded ? 1.0f : -1.0f;
    pOut->mat[9] = -pOut->mat[11] * shift / fovx_tan_invaspect;
    pOut->mat[10] = -pOut->mat[11] * near / (near - far);
    pOut->mat[13] = iod / 2.0f;
    pOut->mat[14] = near * far / (near - far);

    return pOut;
}