#include <stdlib.h>
#include "consts.h"
#include "scene.h"
#include "objects.h"
#include "material.h"

Scene makeScene() {
    Scene s;
    // s.skyMaterial.emissionColor = vec3Scale((vec3){73, 134, 227},1.0/255.0);
    s.skyMaterial.emissionColor = (vec3){0.35,0.52,0.65};
    s.skyMaterial.emissionStrength = 1.0;
    s.objectCount = 0;
    s.objects = NULL; // No objects yet, so there's no pointer to the first one
    return s;
}

void sceneAddObject(Scene *scene, Object o) {
    scene->objectCount++;

    // Reallocate the objects
    Object *newObjects = realloc(scene->objects, sizeof(Object) * scene->objectCount);
    
    // Set the last object in the list to be the new one
    newObjects[scene->objectCount-1] = o;

    scene->objects = newObjects;
}