#pragma once
#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "vec3.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    vec3 color;
} Material;

Material makeMaterial();

#ifdef __cplusplus
}
#endif

#endif // #ifndef _MATERIAL_H