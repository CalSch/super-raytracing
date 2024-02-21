#include <stdio.h>
#include "gfx.h"
#include "vec3.h"
#include "scene.h"
#include "objects.h"
#include "material.h"
#include "ray.h"
#include "consts.h"


void castRay(Ray r, Scene scene, HitInfo *hit, Object *obj) {
    Object closestObject = (Object){};
    HitInfo closestHit = makeHitInfo();
    closestHit.dist = INFINITY;
    for (int i=0;i<scene.objectCount;i++) {
        HitInfo hit=makeHitInfo();
        Object o = scene.objects[i];
        switch (o.type) {
            case ObjectTypeSphere:
                hit = intersectRaySphere(r,o.mesh.sphere);
                break;
            case ObjectTypeNone:
                continue;
        }

        if (!hit.didHit) continue;
        if (hit.dist < closestHit.dist) {
            closestHit = hit;
            closestObject = o;
        }
    }
    *hit = closestHit;
    *obj = closestObject;
}
vec3 traceRay(Ray r, Scene scene) {
    HitInfo hit = makeHitInfo();
    Object o;
    castRay(r,scene,&hit,&o);
    if (hit.didHit) {
        float light = vec3Dot(hit.normal,(vec3){5,5,5})/5.0;
        return vec3Scale(o.mat.color,light);
        // return hit.normal;
    } else {
        return scene.skyMaterial.color;
    }
}