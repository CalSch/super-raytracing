#include "consts.h"
#include "material.h"

Material makeMaterial() {
    Material m;
    m.diffuseColor = BLACK;
    m.specularColor = BLACK;
    m.specularChance = 0;
    m.emissionStrength = 0;
    m.emissionColor = BLACK;
    m.checker = false;
    m.checkerColor = BLACK;
    m.checkerScale = 1.0;

    return m;
}