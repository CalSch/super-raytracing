#pragma once
#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "vec3.h"
#include "ray.h"
#include "material.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ObjectTypeNone   = 0,
    ObjectTypeSphere = 1,
} ObjectType;

typedef struct {
    vec3 pos;
    float radius;
} Sphere;

typedef union {
    Sphere sphere;
} Mesh;

typedef struct {
    ObjectType type;
    Material mat;
    Mesh mesh;
} Object;

Object makeSphere(vec3 pos, float radius, Material mat);
HitInfo intersectRaySphere(Ray r, Sphere s);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _OBJECTS_H