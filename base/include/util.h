#pragma once
#ifndef _UTIL_H
#define _UTIL_H

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

#ifdef __cplusplus
}
#endif

#endif // #ifndef _UTIL_H