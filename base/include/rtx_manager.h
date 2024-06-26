#pragma once
#ifndef _MANAGER_H
#define _MANAGER_H

#include "vec3.h"
#include "ray.h"
#include "transform.h"
#include "camera.h"
#include "scene.h"
#include "consts.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} RGB;

typedef struct {
    int raysPerPixel;
    int maxBounces;
} RTXConfig;

typedef struct {
    Camera cam;
    Scene scene;
    
    int width;
    int height;
    RGB *buf1;
    RGB *buf2;
    float time;
    int currentSamples;

    void (*lineRenderCallback)(int);

    RTXConfig config;
} RTXManager;

RTXManager makeRTXManager(int width, int height);

void RTXTick(RTXManager *rtx);
void RTXResetRender(RTXManager *rtx);
void RTXRenderChunk(RTXManager *rtx, int cx, int cy, int cw, int ch);
void RTXRender(RTXManager *rtx);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _MANAGER_H