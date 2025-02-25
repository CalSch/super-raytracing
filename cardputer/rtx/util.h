#pragma once
#ifndef _UTIL_H
#define _UTIL_H

#include <stdlib.h>
#include "vec3.h"

#ifdef __cplusplus
extern "C" {
#endif

static inline float max(float a, float b) {
    return (a > b) ? a : b;
}
static inline float min(float a, float b) {
    return (a < b) ? a : b;
}
static inline float clamp(float a, float low, float high) {
    return min(max(a,low),high);
}

static inline float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

vec3 lerpVec(vec3 a, vec3 b, float t);

/* A random float between 0 and 1 */
static inline float randomFloat() {
    return (float)rand() / (float)RAND_MAX;
}

/* Random with normal distribution */
float randomNormalDist();

vec3 randomDirection();

#ifdef __cplusplus
}
#endif

#endif // #ifndef _UTIL_H