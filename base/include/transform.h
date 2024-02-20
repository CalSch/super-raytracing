#pragma once
#ifndef _TRANSFORM_H
#define _TRANSFORM_H

#include "vec3.h"
#include "ray.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    vec3 pos;
    vec3 forwards;
    vec3 up;
    vec3 right;
} Transform;

void updateTransformRight(Transform *t);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _TRANSFORM_H