#pragma once
#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "vec3.h"
#include "ray.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    vec3 pos;
    float radius;
} Sphere;

HitInfo intersectRaySphere(Ray r, Sphere s);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _OBJECTS_H