#include <stdlib.h>
#include <stdbool.h>
#include "rtx_manager.h"
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "util.h"
#include "consts.h"
#include "objects.h"

Sphere s = {
    (vec3){0,0,10},
    2.0
};

RTXManager makeRTXManager(int width, int height) {
    RTXManager rtx;
    rtx.width=width;
    rtx.height=height;
    rtx.cam = makeCamera(
        (vec3){0,0,0},
        (vec3){0,0,1},
        (vec3){0,1,0},
        width, height,
        60
    );

    rtx.buf1 = (RGB*)malloc(width * height * sizeof(RGB));
    rtx.buf2 = (RGB*)malloc(width * height * sizeof(RGB));
    for (int i=0;i<width*height;i++) {
        rtx.buf1[i]=(RGB){0,0,0};
        rtx.buf2[i]=(RGB){0,0,0};
    }
    rtx.time = 0;
    return rtx;
}
void RTXRender(RTXManager *rtx) {
    int i=0;
    rtx->cam.transform.pos.x=sinf(rtx->time) * 10;
    rtx->cam.transform.pos.z=cosf(rtx->time) * 10 + 10;
    rtx->cam.transform.pos.y=10;
    cameraLookAt(&rtx->cam,(vec3){0,0,10});
    rtx->time += 0.01;
    for (int y=0;y<rtx->height;y++) {
        for (int x=0;x<rtx->width;x++) {
            Ray r = getCameraRay(rtx->cam,x,y);
            HitInfo hit = intersectRaySphere(r,s);
            vec3 color = hit.didHit ? hit.normal : BLACK;
            // vec3 color = getCameraRay(rtx->cam,x,y).dir;
            RGB rgb = {
                (unsigned char)(clamp(color.x,0,1) * 255.0),
                (unsigned char)(clamp(color.y,0,1) * 255.0),
                (unsigned char)(clamp(color.z,0,1) * 255.0)
            };
            rtx->buf1[i] = rgb;
            i++;
        }
    }
}