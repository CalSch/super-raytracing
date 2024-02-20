#include "transform.h"
#include "vec3.h"

void updateTransformRight(Transform *t) {
    t->right=vec3Cross(t->up,t->forwards);
}