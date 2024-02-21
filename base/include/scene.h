#pragma once
#ifndef _SCENE_H
#define _SCENE_H

#include <stdlib.h>
#include "objects.h"
#include "material.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct {
    Object *objects;
    int objectCount;
    Material skyMaterial;
} Scene;

Scene makeScene();
void sceneAddObject(Scene *scene, Object o);

#ifdef __cplusplus
}
#endif

#endif // #ifndef _SCENE_H