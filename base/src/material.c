#include "consts.h"
#include "material.h"

Material makeMaterial() {
    Material m;
    m.diffuseColor = BLACK;
    m.specularColor = BLACK;
    m.specularChance = 0;
    m.emissionStrength = 0;
    m.emissionColor = BLACK;

    return m;
}