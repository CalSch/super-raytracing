#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "rtx_manager.h"
#include "vec3.h"
#include "ray.h"
#include "camera.h"
#include "util.h"
#include "consts.h"
#include "objects.h"
#include "gfx.h"

static void dummyCallback(int) {}

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

    // green ball
    Material greenBallMat = makeMaterial();
    greenBallMat.diffuseColor = (vec3){0.2,0.8,0.4};
    sceneAddObject(&rtx.scene, makeSphere(
        (vec3){0,0,0}, 2.5,
        greenBallMat
    ));
    
    // light
    Material lightMat = makeMaterial();
    lightMat.emissionColor = WHITE;
    lightMat.emissionStrength = 180.0;
    sceneAddObject(&rtx.scene, makeSphere(
        (vec3){-35,5,-20}, 4,
        lightMat
    ));

    // shiny ball
    Material shinyBallMat = makeMaterial();
    shinyBallMat.diffuseColor  = vec3Scale(WHITE, 0.5);
    shinyBallMat.specularColor = vec3Scale(WHITE, 0.5);
    shinyBallMat.specularChance = 0.8;
    shinyBallMat.roughness = 0.2;
    sceneAddObject(&rtx.scene, makeSphere(
        (vec3){-3.5,1,-12}, 4.0,
        shinyBallMat
    ));

    // floor ball
    Material floorMat = makeMaterial();
    floorMat.diffuseColor = (vec3){0.8,0.3,0.1};
    floorMat.checker = true;
    floorMat.checkerColor = (vec3){0.2,0.3,0.8};
    floorMat.checkerScale = 10.0;
    sceneAddObject(&rtx.scene, makeSphere(
        (vec3){0,-100,0}, 98.0,
        floorMat
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
    rtx.currentSamples = 0;

    rtx.lineRenderCallback = dummyCallback;
    
    rtx.config.maxBounces = 6;
    rtx.config.raysPerPixel = 10;

    return rtx;
}
void RTXTick(RTXManager *rtx) {
    // rtx->cam.transform.pos.x=sinf(rtx->time) * 10;
    // rtx->cam.transform.pos.z=cosf(rtx->time) * 10;
    // rtx->cam.transform.pos.y=10;
    // cameraLookAt(&rtx->cam,rtx->scene.objects[0].mesh.sphere.pos);
    rtx->time += 0.05;

}
void RTXRenderChunk(RTXManager *rtx, int cx, int cy, int cw, int ch) {
    int i = cx + cy*rtx->width;
    float weight = min(1.0/((float)rtx->currentSamples+1.0),1.0);
    printf("sample=%d\nweight=%f\n",rtx->currentSamples,weight);
    for (int y=cy; y<min(rtx->height, cy+ch); y++) {
        for (int x=cx; x<min(rtx->width, cx+cw); x++) {
            vec3 color = BLACK;

            for (int j=0;j<rtx->config.raysPerPixel;j++) {
                Ray r = getCameraRay(rtx->cam,(float)x + randomFloat(), (float)y + randomFloat()); // Add randomness for anti-aliasing
                color = vec3Add(color,vec3Scale(traceRay(rtx,r,rtx->scene),1.0/(float)rtx->config.raysPerPixel));
            }

            vec3 rgb = {
                (color.x * 255.0),
                (color.y * 255.0),
                (color.z * 255.0)
            };
            // bool print = (x==47 && y==50);
            // if (print)
            //     printf("color=(%f,%f,%f)\n",rgb.x,rgb.y,rgb.z);

            RGB oldColor = rtx->buf1[i];
            // if (print)
            //     printf("old color=(%d,%d,%d)\n",oldColor.r,oldColor.g,oldColor.b);

            RGB newColor = {
                (unsigned char)(clamp(lerp(oldColor.r, rgb.x, weight),0,255)),
                (unsigned char)(clamp(lerp(oldColor.g, rgb.y, weight),0,255)),
                (unsigned char)(clamp(lerp(oldColor.b, rgb.z, weight),0,255)),
            };
            // if (print)
            //     printf("new color=(%d,%d,%d)\n",newColor.r,newColor.g,newColor.b);


            rtx->buf1[i] = newColor;
            i++;
        }
        rtx->lineRenderCallback(y);
        i += rtx->width - cw;
    }
}
void RTXRender(RTXManager *rtx) {
    RTXRenderChunk(rtx, 0, 0, rtx->width, rtx->height);
    rtx->currentSamples++;
}