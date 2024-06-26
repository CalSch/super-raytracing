#pragma once
#ifndef _VEC_H
#define _VEC_H

#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    float x;
    float y;
    float z;
} vec3;

static inline vec3 vec3Add(vec3 v1, vec3 v2) {
    return (vec3){
        v1.x+v2.x,
        v1.y+v2.y,
        v1.z+v2.z,
    };
}
static inline vec3 vec3Sub(vec3 v1, vec3 v2) {
    return (vec3){
        v1.x-v2.x,
        v1.y-v2.y,
        v1.z-v2.z,
    };
}
static inline vec3 vec3Mult(vec3 v1, vec3 v2) {
    return (vec3){
        v1.x*v2.x,
        v1.y*v2.y,
        v1.z*v2.z,
    };
}
static inline vec3 vec3Div(vec3 v1, vec3 v2) {
    return (vec3){
        v1.x/v2.x,
        v1.y/v2.y,
        v1.z/v2.z,
    };
}
static inline vec3 vec3Scale(vec3 vec, float s) {
    return (vec3){
        vec.x*s,
        vec.y*s,
        vec.z*s,
    };
}
static inline float vec3Distance(vec3 vec) {
    return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}
static inline vec3 vec3Normalize(vec3 vec) {
    float dist=vec3Distance(vec);
    return (vec3){
        vec.x / dist,
        vec.y / dist,
        vec.z / dist,
    };
}
static inline float vec3Dot(vec3 v1, vec3 v2) {
    return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z;
}
static inline vec3 vec3Cross(vec3 v1, vec3 v2) {
    return (vec3){
        v1.y * v2.z - v1.z * v2.y,
        v1.z * v2.x - v1.x * v2.z,
        v1.x * v2.y - v1.y * v2.x
    };
}
static inline vec3 vec3Reflect(vec3 v, vec3 norm) {
    return vec3Sub(v, vec3Scale(norm, 2 * vec3Dot(norm, v)));
}

static inline vec3 vec3Rotate(vec3 v, vec3 axis, float theta) {
    // return v*cos(theta) + cross(axis,v)*sin(theta) + axis*dot(axis,v)*(1-cos(theta))
    // Wow thats a lot of stuff!
    return vec3Add(vec3Scale(v,cos(theta)),vec3Add(vec3Scale(vec3Cross(axis,v),sin(theta)),vec3Scale(axis,vec3Dot(axis,v)*(1.0-cos(theta)))));
}

static inline vec3 vec3Min(vec3 a, vec3 b) {
    return (vec3){
        fminf(a.x,b.x),
        fminf(a.y,b.y),
        fminf(a.z,b.z)
    };
}
static inline vec3 vec3Max(vec3 a, vec3 b) {
    return (vec3){
        fmaxf(a.x,b.x),
        fmaxf(a.y,b.y),
        fmaxf(a.z,b.z)
    };
}

static inline vec3 vec3Abs(vec3 a) {
    return (vec3){
        fabsf(a.x),
        fabsf(a.y),
        fabsf(a.z)
    };
}

// Convert the components to integers, then back to floats
static inline vec3 vec3Int(vec3 a) {
    return (vec3){
        (float)((int)(a.x)),
        (float)((int)(a.y)),
        (float)((int)(a.z))
    };
}

#ifdef __cplusplus
}
#endif

#endif // #ifndef _VEC_H