#include <stdio.h>
namespace rl {
    #include <raylib.h>

};
#include "rtx_manager.h"

#define WIDTH 256
#define HEIGHT 192

RTXManager rtx;

int main() {
    printf("hi\n");
    rtx = makeRTXManager(WIDTH,HEIGHT);

    RTXTick(&rtx);

    printf("\nCamera\n");
    printf("\t position       = (%f, %f, %f)\n",rtx.cam.transform.pos.x,rtx.cam.transform.pos.y,rtx.cam.transform.pos.z);
    printf("\t plane size     = (%f, %f)\n",rtx.cam.planeWidth,rtx.cam.planeHeight);
    printf("\t top left local = (%f, %f, %f)\n",rtx.cam.topLeftLocal.x,rtx.cam.topLeftLocal.y,rtx.cam.topLeftLocal.z);
    printf("\t forward        = (%f, %f, %f)\n",rtx.cam.transform.forwards.x,rtx.cam.transform.forwards.y,rtx.cam.transform.forwards.z);
    printf("\t right          = (%f, %f, %f)\n",rtx.cam.transform.right.x,rtx.cam.transform.right.y,rtx.cam.transform.right.z);
    printf("\t up             = (%f, %f, %f)\n",rtx.cam.transform.up.x,rtx.cam.transform.up.y,rtx.cam.transform.up.z);

    Ray r1=getCameraRay(rtx.cam,WIDTH/2,HEIGHT/2);
    printf("\nRay 1\n");
    printf("\t dir = (%f,%f,%f)\n",r1.dir.x,r1.dir.y,r1.dir.z);
    Ray r2=getCameraRay(rtx.cam,WIDTH/2+1,HEIGHT/2+1);
    printf("\nRay 2\n");
    printf("\t dir = (%f,%f,%f)\n",r2.dir.x,r2.dir.y,r2.dir.z);

    printf("\n%d,%d,%d\n",rtx.buf1[10].r,rtx.buf1[10].g,rtx.buf1[10].b);

    rl::InitWindow(WIDTH,HEIGHT,"hi");

    while (!rl::WindowShouldClose()) {
        RTXRender(&rtx);
        // RTXRenderChunk(&rtx,40,40,64,64);
        
        rl::BeginDrawing();
        rl::ClearBackground(rl::BLACK);

        int i=0;
        for (int y=0;y<256;y++) {
            for (int x=0;x<256;x++) {
                RGB c=rtx.buf1[i];
                rl::DrawPixel(x,y,{c.r,c.g,c.b,255});
                i++;
            }
        }

        rl::DrawFPS(10,10);

        rl::EndDrawing();
    }

    rl::CloseWindow();
    
    free(rtx.buf1);
    free(rtx.buf2);
}