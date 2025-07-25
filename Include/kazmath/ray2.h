/*
Copyright (c) 2011, Luke Benstead.
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

#ifndef RAY_2_H
#define RAY_2_H

#include <kazmath/utility.h>
#include <kazmath/vec2.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct kmRay2 {
    kmVec2 start;
    kmVec2 dir;
} kmRay2;

void kmRay2Fill(kmRay2* ray, kmScalar px, kmScalar py, kmScalar vx,
                kmScalar vy);
void kmRay2FillWithEndpoints( kmRay2 *ray, const kmVec2 *start,
                              const kmVec2 *end );

/* 
    Lines are defined by a pt and a vector. It outputs the vector
    multiply factor that gives the intersection point
*/
kmBool kmLine2WithLineIntersection(const kmVec2 *ptA, const kmVec2 *vecA,
                                   const kmVec2 *ptB, const kmVec2 *vecB,
                                   kmScalar *outTA, kmScalar *outTB,
                                   kmVec2 *outIntersection );

kmBool kmSegment2WithSegmentIntersection( const kmRay2 *segmentA, 
                                          const kmRay2 *segmentB, 
                                          kmVec2 *intersection );

kmBool kmRay2IntersectLineSegment(const kmRay2* ray, const kmVec2* p1,
                                  const kmVec2* p2, kmVec2* intersection);
kmBool kmRay2IntersectTriangle(const kmRay2* ray, const kmVec2* p1,
                               const kmVec2* p2, const kmVec2* p3,
                               kmVec2* intersection, kmVec2* normal_out,
                               kmScalar* distance);

kmBool kmRay2IntersectBox(const kmRay2* ray, const kmVec2* p1,
                          const kmVec2* p2, const kmVec2* p3,
                          const kmVec2* p4, kmVec2* intersection,
                          kmVec2* normal_out);

kmBool kmRay2IntersectCircle(const kmRay2* ray, const kmVec2 centre,
                             const kmScalar radius, kmVec2* intersection);

#ifdef __cplusplus
}
#endif

#endif
