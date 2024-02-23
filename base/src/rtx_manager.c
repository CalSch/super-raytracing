#include <stdlib.h>
#include <stdbool.h>
#include "rtx_manager.h"
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "util.h"
#include "consts.h"
#include "objects.h"
#include "gfx.h"

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
    rtx.scene = makeScene();
    sceneAddObject(&rtx.scene, makeSphere(
        (vec3){0,0,0}, 2.5,
        (Material){
            (vec3){0.7,0.8,0.9},
            (vec3){0.7,0.8,0.9},
            0.1,
            BLACK,
            0
        }
    ));
    sceneAddObject(&rtx.scene, makeSphere(
        (vec3){2.3,-0.2,0}, 1.65,
        (Material){
            BLACK,
            BLACK,
            0,
            (vec3){0.8,0.6,0.2},
            10
        }
    ));
    sceneAddObject(&rtx.scene, makeSphere(
        (vec3){-3.5,0,-12}, 4.0,
        (Material){
            (vec3){0.4,0.4,0.4},
            (vec3){0.9,0.9,0.9},
            0.9,
            BLACK,
            0
        }
    ));
    sceneAddObject(&rtx.scene, makeSphere(
        (vec3){0,-100,0}, 98.0,
        (Material){
            (vec3){0.8,0.3,0.1},
            BLACK,
            0,
            BLACK,
            0
        }
    ));

    rtx.cam.transform.pos.x=10;
    rtx.cam.transform.pos.y=10;
    rtx.cam.transform.pos.z=10;
    cameraLookAt(&rtx.cam,(vec3){0,0,0});

    rtx.buf1 = (RGB*)malloc(width * height * sizeof(RGB));
    rtx.buf2 = (RGB*)malloc(width * height * sizeof(RGB));
    for (int i=0;i<width*height;i++) {
        rtx.buf1[i]=(RGB){0,0,0};
        rtx.buf2[i]=(RGB){0,0,0};
    }
    rtx.time = 2;
    return rtx;
}
void RTXTick(RTXManager *rtx) {
    rtx->scene.objects[1].mesh.sphere.pos.z = sinf(rtx->time * 1.5) * 7.0;
    rtx->scene.objects[1].mesh.sphere.pos.x = cosf(rtx->time * 1.5) * 4.0;
    // rtx->cam.transform.pos.x=sinf(rtx->time) * 10;
    // rtx->cam.transform.pos.z=cosf(rtx->time) * 10;
    // rtx->cam.transform.pos.y=10;
    // cameraLookAt(&rtx->cam,rtx->scene.objects[0].mesh.sphere.pos);
    rtx->time += 0.05;

}
void RTXRender(RTXManager *rtx) {
    int i=0;
    for (int y=0;y<rtx->height;y++) {
        for (int x=0;x<rtx->width;x++) {
            Ray r = getCameraRay(rtx->cam,x,y);
            vec3 color = BLACK;

            for (int j=0;j<RAYS_PER_PIXEL;j++) {
                color = vec3Add(color,vec3Scale(traceRay(r,rtx->scene),1.0/(float)RAYS_PER_PIXEL));
            }
            
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