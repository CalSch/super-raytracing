#pragma once
#ifndef _CAMERA_H
#define _CAMERA_H

#include "vec3.h"
#include "ray.h"
#include "transform.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    Transform transform;
    int resX;
    int resY;
    float fov;
    float aspectRatio;

    float planeWidth;
    float planeHeight;
    vec3 topLeftLocal;
} Camera;

Camera makeCamera(vec3 pos, vec3 forwards, vec3 up, int resX, int resY, float fov);
void updateCameraFOV(Camera *cam, float fov);
Ray getCameraRay(Camera cam, float x, float y);
void cameraLookAt(Camera *cam, vec3 focus);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _CAMERA_H