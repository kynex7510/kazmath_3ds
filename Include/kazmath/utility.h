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

#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include <math.h>
#include <float.h>

#define KM_FALSE 0
#define KM_TRUE 1

#define kmPI 3.14159265358979323846f
#define kmPIOver180  (kmPI / 180.0f)
#define kmPIUnder180 (180.0 / kmPI)

#define KM_CONTAINS_NONE (kmEnum)0
#define KM_CONTAINS_PARTIAL (kmEnum)1
#define KM_CONTAINS_ALL (kmEnum)2

typedef unsigned char kmBool;
typedef unsigned char kmUchar;
typedef unsigned int kmEnum;
typedef unsigned int vkmUint;
typedef int kmInt;

#ifdef USE_DOUBLE_PRECISION
#define kmEpsilon DBL_EPSILON
typedef double kmScalar;
#else
#define kmEpsilon FLT_EPSILON
typedef float kmScalar;
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Returns the square of s (e.g. s*s)
 */
static inline kmScalar kmSQR(kmScalar s) { return s*s; }

/**
 * Returns degrees as radians.
 */
static inline kmScalar kmDegreesToRadians(kmScalar degrees) { return degrees * kmPIOver180; }

/**
 * Returns radians as degrees
 */
static inline kmScalar kmRadiansToDegrees(kmScalar radians) { return radians * kmPIUnder180; }

static inline kmScalar kmMin(kmScalar lhs, kmScalar rhs) { return (lhs < rhs)? lhs : rhs; }
static inline kmScalar kmMax(kmScalar lhs, kmScalar rhs) { return (lhs > rhs)? lhs : rhs; }
static inline kmBool kmAlmostEqual(kmScalar lhs, kmScalar rhs) { return (fabs(lhs - rhs) <= kmEpsilon * fmax(1.0f, fmax(lhs, rhs))); }

static inline kmScalar kmClamp(kmScalar x, kmScalar min, kmScalar max) { return x < min ? min : (x > max ? max : x); }
static inline kmScalar kmLerp(kmScalar x, kmScalar y, kmScalar factor) { return x + factor * ( y - x ); }

#ifdef __cplusplus
}
#endif

#endif /* UTILITY_H_INCLUDED */
