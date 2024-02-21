#include <stdbool.h>
#include "objects.h"
#include "ray.h"
#include "material.h"

Object makeSphere(vec3 pos, float radius, Material mat) {
    Object o;
    o.mat=mat;
    o.type=ObjectTypeSphere;
    o.mesh.sphere=(Sphere){pos,radius};
    return o;
}

HitInfo intersectRaySphere(Ray r, Sphere s) {
    HitInfo hit = makeHitInfo();

    vec3 offsetRayOrigin = vec3Sub(r.origin,s.pos);

    float a = vec3Dot(r.dir,r.dir);
    float b = 2 * vec3Dot(offsetRayOrigin,r.dir);
    float c = vec3Dot(offsetRayOrigin,offsetRayOrigin) - s.radius * s.radius;
    
    float discriminant = b * b - 4 * a * c; 

    // No solution when discriminant < 0 (ray misses sphere)
    if (discriminant >= 0) {
        float dst = (-b - sqrt(discriminant)) / (2 * a);

        // ignore hits that are behind the ray, where dst < 0
        if (dst >= 0) {
            hit.didHit = true;
            hit.point = vec3Add(r.origin, vec3Scale(r.dir, dst));
            hit.normal = vec3Normalize(vec3Sub(hit.point,s.pos));
            hit.dist = dst;
        }
    }

    return hit;
}