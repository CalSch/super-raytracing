#pragma once
#ifndef _GFX_H
#define _GFX_H

#include "vec3.h"
#include "ray.h"
#include "scene.h"

#ifdef __cplusplus
extern "C" {
#endif

void castRay(Ray r, Scene scene, HitInfo *hit, Object *obj);
vec3 traceRay(Ray r, Scene scene);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _GFX_H