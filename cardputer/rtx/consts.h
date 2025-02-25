#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#define PI 3.141592653589793
#define DEG2RAD PI/180.0
#define RAD2DEG 180.0/PI

#define EPSILON 0.001

#define WHITE   (vec3){1,1,1}
#define BLACK   (vec3){0,0,0}
#define RED     (vec3){1,0,0}
#define GREEN   (vec3){0,1,0}
#define BLUE    (vec3){0,0,1}
#define CYAN    (vec3){0,1,1}
#define MAGENTA (vec3){1,0,1}
#define YELLOW  (vec3){1,1,0}

#define VEC0 (vec3){0,0,0}
#define VEC1 (vec3){1,1,1}
#define VEC_X (vec3){1,0,0}
#define VEC_Y (vec3){0,1,0}
#define VEC_Z (vec3){0,0,1}
#define VEC_NX (vec3){-1,0,0}
#define VEC_NY (vec3){0,-1,0}
#define VEC_NZ (vec3){0,0,-1}


#endif // #ifndef _CONSTANTS_H