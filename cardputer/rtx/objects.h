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
    ObjectTypeNone     = 0,
    ObjectTypeSphere   = 1,
    ObjectTypeTriangle = 2,
    ObjectTypeBox      = 3,
} ObjectType;

typedef struct {
    vec3 pos;
    float radius;
} Sphere;

typedef struct {
    vec3 v0;
    vec3 v1;
    vec3 v2;
} Triangle;

typedef struct {
    vec3 min;
    vec3 max;
} Box;

typedef union {
    Sphere sphere;
    Triangle triangle;
    Box box;
} Mesh;

typedef struct {
    ObjectType type;
    Material mat;
    Mesh mesh;
    Box boundingBox;
} Object;

Object makeSphere(vec3 pos, float radius, Material mat);
Object makeTriangle(vec3 v0, vec3 v1, vec3 v2, Material mat);
Object makeBox(vec3 bMin, vec3 bMax, Material mat);
vec3 getBoxCenter(Box b);
vec3 calcNormalOnBox(vec3 p, Box b);
HitInfo intersectRaySphere(Ray r, Sphere s);
HitInfo intersectRayTriangle(Ray r, Triangle s);
HitInfo intersectRayBox(Ray r, Box b);
bool testRayBox(Ray r, Box b);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _OBJECTS_H