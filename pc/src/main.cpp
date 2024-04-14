#include <stdio.h>
namespace rl {
    #include <raylib.h>
    #include <rlgl.h>
};
#include "rtx_manager.h"
#include "util.h"

#define WIDTH 800
#define HEIGHT 600

RTXManager rtx;

rl::Camera3D rlCam;

// Convert an RTX vec3 to a Raylib Vector3
rl::Vector3 vec3RtxToRaylib(vec3 v) {
    // Do -z because raylib 3d is weird 
    return (rl::Vector3){v.x,v.y,-v.z};
}

rl::Color colorToRaylib(vec3 c) {
    return (rl::Color){
        (unsigned int)(c.x*255),
        (unsigned int)(c.y*255),
        (unsigned int)(c.z*255),
        255
    };
} 

rl::Color getMaterialColor(Material m) {
    return colorToRaylib(
        lerpVec(
            lerpVec(m.diffuseColor,m.specularColor,m.specularChance),
            m.emissionColor,
            m.emissionStrength
        )
    );
}

void updateRaylibCam() {
    rlCam.position = vec3RtxToRaylib(rtx.cam.transform.pos);
    rlCam.target   = vec3RtxToRaylib(vec3Add(rtx.cam.transform.pos,rtx.cam.transform.forwards));
    rlCam.up       = vec3RtxToRaylib(rtx.cam.transform.up);
    rlCam.fovy = rtx.cam.fov * rtx.cam.aspectRatio;
}

bool rlDebug = false;

int main() {
    printf("hi\n");
    rtx = makeRTXManager(WIDTH,HEIGHT);
    rtx.config.raysPerPixel=1;

    RTXTick(&rtx);

    rl::InitWindow(WIDTH,HEIGHT,"hi");

    rlCam.projection = rl::CAMERA_PERSPECTIVE;


    while (!rl::WindowShouldClose()) {
        if (rl::IsMouseButtonDown(rl::MOUSE_LEFT_BUTTON)) {
            rotateTransform(&rtx.cam.transform,rtx.cam.transform.up,rl::GetMouseDelta().x/100);
            rotateTransform(&rtx.cam.transform,rtx.cam.transform.right,rl::GetMouseDelta().y/100);
            resetTransformRoll(&rtx.cam.transform);
            RTXResetRender(&rtx);
        }
        float moveAmount = rl::GetFrameTime()*14;
        if (rl::IsKeyDown(rl::KEY_W)) {
            rtx.cam.transform.pos = vec3Add(rtx.cam.transform.pos,vec3Scale(rtx.cam.transform.forwards,moveAmount));
            RTXResetRender(&rtx);
        }
        if (rl::IsKeyDown(rl::KEY_A)) {
            rtx.cam.transform.pos = vec3Add(rtx.cam.transform.pos,vec3Scale(rtx.cam.transform.right,-moveAmount));
            RTXResetRender(&rtx);
        }
        if (rl::IsKeyDown(rl::KEY_S)) {
            rtx.cam.transform.pos = vec3Add(rtx.cam.transform.pos,vec3Scale(rtx.cam.transform.forwards,-moveAmount));
            RTXResetRender(&rtx);
        }
        if (rl::IsKeyDown(rl::KEY_D)) {
            rtx.cam.transform.pos = vec3Add(rtx.cam.transform.pos,vec3Scale(rtx.cam.transform.right,moveAmount));
            RTXResetRender(&rtx);
        }
        if (rl::IsKeyPressed(rl::KEY_Z)) {
            rlDebug = !rlDebug;
            printf("aaaahhhhh!\n\n\n\n");
            printf("%d\n\n\n\n\n",rlDebug);
        }

        rl::BeginDrawing();

        if (rlDebug) {
            updateRaylibCam();
            rl::ClearBackground(getMaterialColor(rtx.scene.skyMaterial));

            rl::BeginMode3D(rlCam);
            // rl::rlTranslatef(,0,0);

            rl::DrawGrid(50,1);

            for (int i=0;i<rtx.scene.objectCount;i++) {
                Object o = rtx.scene.objects[i];

                rl::Color color = getMaterialColor(o.mat);

                switch (o.type) {
                    case ObjectTypeSphere:
                        rl::DrawSphere(
                            vec3RtxToRaylib(o.mesh.sphere.pos),
                            o.mesh.sphere.radius,
                            color
                        );
                        break;
                    case ObjectTypeTriangle:
                        rl::DrawTriangle3D(
                            vec3RtxToRaylib(o.mesh.triangle.v0),
                            vec3RtxToRaylib(o.mesh.triangle.v1),
                            vec3RtxToRaylib(o.mesh.triangle.v2),
                            color
                        );
                        break;
                    case ObjectTypeBox:
                        rl::DrawCubeV(
                            vec3RtxToRaylib(getBoxCenter(o.mesh.box)),
                            vec3RtxToRaylib(vec3Sub(o.mesh.box.min,o.mesh.box.max)),
                            color
                        );
                        break;
                    default:
                        break;
                }
            }

            rl::EndMode3D();
            rl::rlScalef(sinf(rl::GetTime()),1,1);

        } else {
            // Render normally
            RTXRender(&rtx);
            // RTXRenderChunk(&rtx,40,40,64,64);
            
            rl::ClearBackground((rl::Color){ 0, 0, 0, 255 }); // Can't use BLACK because it's redefined in the raytracing

            int i=0;
            for (int y=0;y<HEIGHT;y++) {
                for (int x=0;x<WIDTH;x++) {
                    RGB c=rtx.buf1[i];
                    rl::DrawPixel(x,y,{c.r,c.g,c.b,255});
                    i++;
                }
            }


        }

        rl::DrawFPS(10,10);

        rl::EndDrawing();
    }

    rl::CloseWindow();
    
    free(rtx.buf1);
    free(rtx.buf2);
}