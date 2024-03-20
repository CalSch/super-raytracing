#include <math.h>
#include "camera.h"
#include "consts.h"
#include "vec3.h"
#include "ray.h"
#include "transform.h"

Camera makeCamera(vec3 pos, vec3 forwards, vec3 up, int resX, int resY, float fov) {
    Camera cam;

    cam.transform.pos=pos;
    cam.transform.forwards=forwards;
    cam.transform.up=up;
    updateTransformRight(&cam.transform);

    cam.resX=resX;
    cam.resY=resY;
    cam.aspectRatio = (float)resY / (float)resX;
    updateCameraFOV(&cam,fov);

    return cam;
}

void updateCameraFOV(Camera *cam, float fov) {
    cam->fov = fov;
    cam->planeWidth = tanf(fov * 0.5 * DEG2RAD) * 2.0;
    cam->planeHeight = cam->planeWidth * cam->aspectRatio;

    cam->topLeftLocal = (vec3){
        -cam->planeWidth/2.0,
        cam->planeHeight/2.0,
        1.0
    };
}

Ray getCameraRay(Camera cam, float x, float y) {
    float tx = (float)x / (float)cam.resX;
    float ty = (float)y / (float)cam.resY;

    vec3 pointLocal = vec3Add(
        cam.topLeftLocal,
        (vec3){
            cam.planeWidth * tx,
            cam.planeHeight * -ty,
            0
        }
    );

    // point = cam.right    *  pointLocal.x +
    //         cam.up       * -pointLocal.y +
    //         cam.forwards *  pointLocal.z
    vec3 point = vec3Add(
        vec3Add(
            vec3Scale(cam.transform.right,pointLocal.x),
            vec3Scale(cam.transform.up,pointLocal.y)
        ),
        vec3Scale(cam.transform.forwards,pointLocal.z)
    );
    // vec3 point = (vec3){0,0,0};

    Ray r = {cam.transform.pos, point};

    return r;
}
void cameraLookAt(Camera *cam, vec3 focus) {
    vec3 dir = vec3Normalize(vec3Sub(focus,cam->transform.pos));
    cam->transform.forwards = dir;
    cam->transform.right = vec3Normalize(vec3Cross((vec3){0,1,0},dir));
    cam->transform.up = vec3Normalize(vec3Cross(dir,cam->transform.right));
}