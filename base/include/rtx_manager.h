#pragma once
#ifndef _MANAGER_H
#define _MANAGER_H

#include "vec3.h"
#include "ray.h"
#include "transform.h"
#include "camera.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

typedef struct {
    Camera cam;
    int width;
    int height;
    RGB *buf1;
    RGB *buf2;
    float time;
} RTXManager;

RTXManager makeRTXManager(int width, int height);
void RTXRender(RTXManager *rtx);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _MANAGER_H