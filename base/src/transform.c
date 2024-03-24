#include "transform.h"
#include "vec3.h"
#include "consts.h"

void updateTransformRight(Transform *t) {
    t->right=vec3Cross(t->up,t->forwards);
}
void resetTransformRoll(Transform *t) {
    t->right = vec3Normalize(vec3Cross((vec3){0,1,0},t->forwards));
    t->up = vec3Normalize(vec3Cross(t->forwards,t->right));
}
void rotateTransform(Transform *t, vec3 axis, float theta) {
    t->forwards = vec3Rotate(t->forwards, axis, theta);
    t->up       = vec3Rotate(t->up      , axis, theta);
    t->right    = vec3Rotate(t->right   , axis, theta);
}
