#include <math.h>
#include "vec3.h"
#include "util.h"
#include "consts.h"

vec3 lerpVec(vec3 a, vec3 b, float t) {
    return (vec3){
        lerp(a.x,b.x,t),
        lerp(a.y,b.y,t),
        lerp(a.z,b.z,t),
    };
}

// Random float from 0 to 1 with a normal distribution
float randomNormalDist() {
    float theta = 2 * PI * randomFloat();
    float rho = sqrt(-2 * log(randomFloat()));
    return rho * cos(theta);
}

vec3 randomDirection() {
    return (vec3){
        randomNormalDist(),
        randomNormalDist(),
        randomNormalDist(),
    };
}