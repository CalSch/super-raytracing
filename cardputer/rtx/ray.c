#include <stdbool.h>
#include "ray.h"
#include "vec3.h"

HitInfo makeHitInfo() {
    HitInfo hit;
    hit.didHit = false;
    hit.normal = (vec3){0,0,0};
    hit.point = (vec3){0,0,0};
    hit.dist = 0;
    return hit;
}