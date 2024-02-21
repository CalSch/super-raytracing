#pragma once
#ifndef _RAY_H
#define _RAY_H

#include <stdbool.h>
#include "vec3.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    vec3 origin;
    vec3 dir;
} Ray;

typedef struct {
    bool didHit;
    vec3 point;
    vec3 normal;
    float dist;
} HitInfo;

HitInfo makeHitInfo();

#ifdef __cplusplus
}
#endif

#endif // #ifndef _RAY_H