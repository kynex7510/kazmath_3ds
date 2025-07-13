#ifndef KAZMATH_3DS_H_INCLUDED
#define KAZMATH_3DS_H_INCLUDED

#include <kazmath/mat4.h>

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

kmMat4* kmMat4OrthoTilt(kmMat4* pOut, kmScalar left, kmScalar right, kmScalar bottom, kmScalar top,
    kmScalar nearVal, kmScalar farVal, bool isLeftHanded);

kmMat4* kmMat4PerspTilt(kmMat4* pOut, kmScalar fovy, kmScalar aspect, kmScalar near, kmScalar far, bool isLeftHanded);

kmMat4* kmMat4PerspStereoTilt(kmMat4* pOut, kmScalar fovy, kmScalar aspect, kmScalar near, kmScalar far,
    kmScalar iod, kmScalar screen, bool isLeftHanded);

#ifdef __cplusplus
}
#endif

#endif