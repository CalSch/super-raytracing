#pragma once
#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "vec3.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    vec3 diffuseColor;
    vec3 specularColor;
    float specularChance;
    vec3 emissionColor;
    float emissionStrength;
    bool checker;
    vec3 checkerColor;
    float checkerScale;
} Material;

Material makeMaterial();

#ifdef __cplusplus
}
#endif

#endif // #ifndef _MATERIAL_H