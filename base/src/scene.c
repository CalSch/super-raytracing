#include <stdlib.h>
#include "consts.h"
#include "scene.h"
#include "objects.h"
#include "material.h"

Scene makeScene() {
    Scene s;
    s.skyMaterial.color = BLUE;
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