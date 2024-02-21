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
        (vec3){0,0,0}, 3.0,
        (Material){
            (vec3){0.8,0.3,0.1}
        }
    ));

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
    rtx->cam.transform.pos.z=cosf(rtx->time) * 10;
    rtx->cam.transform.pos.y=10;
    cameraLookAt(&rtx->cam,rtx->scene.objects[0].mesh.sphere.pos);
    rtx->time += 0.01;
    for (int y=0;y<rtx->height;y++) {
        for (int x=0;x<rtx->width;x++) {
            Ray r = getCameraRay(rtx->cam,x,y);
            vec3 color = traceRay(r,rtx->scene);
            
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