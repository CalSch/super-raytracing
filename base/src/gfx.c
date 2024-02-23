#include <stdio.h>
#include "gfx.h"
#include "vec3.h"
#include "scene.h"
#include "objects.h"
#include "material.h"
#include "ray.h"
#include "consts.h"
#include "util.h"


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
    vec3 rayColor=(vec3){1,1,1};
    vec3 incomingLight=(vec3){0,0,0};

    for (int i=0;i<MAX_RAY_BOUNCES;i++) {
        HitInfo hit = makeHitInfo();
        Object obj = {ObjectTypeNone,makeMaterial(),{}};
        castRay(r,scene,&hit,&obj);
        
        if (hit.didHit) {
            vec3 diffuseDir = vec3Add(hit.normal, randomDirection());
            vec3 specularDir = vec3Reflect(r.dir, hit.normal);
    
            bool isSpecularBounce = randomFloat() <= obj.mat.specularChance;
            r.dir = isSpecularBounce ? specularDir : diffuseDir;
            r.origin = vec3Add(hit.point, vec3Scale(r.dir, 0.01));

            vec3 emittedLight = vec3Scale(obj.mat.emissionColor, obj.mat.emissionStrength);


            incomingLight = vec3Add(incomingLight, vec3Mult(emittedLight, rayColor));

            if (vec3Distance(emittedLight) > 2) {
                break;
            }
            rayColor = vec3Mult(
                rayColor,
                isSpecularBounce ? obj.mat.specularColor : obj.mat.diffuseColor
            );

            // rayColor = vec3Scale(rayColor, 0);

            float p = max(max(rayColor.x,rayColor.y),rayColor.z);
            if (randomFloat()/2 > p) {
                break;
            }
            rayColor = vec3Scale(rayColor,1.0/p);
        } else {
            // emittedLight = emissionColor * emissionStrength * rayColor
            vec3 emittedLight = vec3Mult(
                vec3Scale(
                    scene.skyMaterial.emissionColor,
                    scene.skyMaterial.emissionStrength
                ),
                rayColor
            );
            incomingLight = vec3Add(incomingLight, emittedLight);
            break;
        }
    }

    return incomingLight;
}