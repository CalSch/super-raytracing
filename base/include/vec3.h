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

#ifdef __cplusplus
}
#endif

#endif // #ifndef _VEC_H