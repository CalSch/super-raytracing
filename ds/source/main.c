// SPDX-License-Identifier: CC0-1.0
//
// SPDX-FileContributor: NightFox & Co., 2009-2011
//
// 16-bit bitmap backbuffer example.
// http://www.nightfoxandco.com

#include <stdio.h>

#include <nds.h>
#include <nf_lib.h>
#include "rtx_manager.h"


int main(int argc, char **argv)
{
    RTXManager rtx = makeRTXManager(256,192);
    rtx.config.raysPerPixel=1;
    rtx.config.maxBounces=3;
    int chunkX = 0;
    int chunkY = 0;
    int chunkW = 16;
    int chunkH = 16;
    // Initialize 2D engine in both screens and use mode 5
    NF_Set2D(0, 5);
    NF_Set2D(1, 5);

    // Initialize bitmap backgrounds system
    NF_InitBitmapBgSys(0, 1);
    NF_InitBitmapBgSys(1, 1);

    // Initialize backbuffers
    NF_Init16bitsBackBuffer(0);
    NF_Init16bitsBackBuffer(1);

    // Enable backbuffers
    NF_Enable16bitsBackBuffer(0);
    NF_Enable16bitsBackBuffer(1);
    
    int i=0;
    // Fill buffer
    for (int y = 0; y < 256; y++)
    {
        for (int x = 0; x < 256; x++)
        {
            RGB color={12,55,202};
            // Compose RGB value
            u32 rgb = color.r | (color.g << 5) | (color.b << 10) | BIT(15);

            // Write color to the backbuffer
            NF_16BITS_BACKBUFFER[0][(y << 8) + x] = rgb;
            NF_16BITS_BACKBUFFER[1][(y << 8) + x] = rgb;
            i++;
        }
    }
    // Send backbuffers to the screen
    NF_Flip16bitsBackBuffer(0);
    NF_Flip16bitsBackBuffer(1);

    // Wait for the screen refresh
    swiWaitForVBlank();

    // RTXRenderChunk(&rtx,0,0,16,16);
    // RTXRender(&rtx);
    // RTXTick(&rtx);
    RTXResetRender(&rtx);

    // timerStart(1,ClockDivider_1,10000000,NULL);

    while (1)
    {
        RTXRenderChunk(&rtx,chunkX,chunkY,chunkW,chunkH);
        chunkX += chunkW;
        if (chunkX+chunkW >= 256) {
            chunkX = 0;
            chunkY += chunkH;
        }
        if (chunkY+chunkH >= 192) {
            chunkY=0;
            chunkX=0;
            RTXTick(&rtx);
            rtx.currentSamples++;
            // timerStop();
        }
        int i=0;
        // Fill buffer
        for (int y = 0; y < 192; y++)
        {
            for (int x = 0; x < 256; x++)
            {
                RGB color=rtx.buf1[i];
                color.r = color.r*32/256;
                color.g = color.g*32/256;
                color.b = color.b*32/256;
                // Compose RGB value
                u32 rgb = color.r | (color.g << 5) | (color.b << 10) | BIT(15);

                // Write color to the backbuffer
                NF_16BITS_BACKBUFFER[0][(y << 8) + x] = rgb;
                NF_16BITS_BACKBUFFER[1][(y << 8) + x] = rgb;
                i++;
            }
        }

        // Send backbuffers to the screen
        NF_Flip16bitsBackBuffer(0);
        NF_Flip16bitsBackBuffer(1);

        // Wait for the screen refresh
        swiWaitForVBlank();

        rtx.time++;
    }

    return 0;
}
