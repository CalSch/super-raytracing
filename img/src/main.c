#include <stdio.h>
#include "rtx_manager.h"
#include "libbmp.h"

RTXManager rtx;

//TODO: add error handling
int writeToPPM(const char *filename, RTXManager r) {
    FILE *f=fopen(filename,"w");
    // fwrite(data,size,0,f);
    // ofs << "P6\n" << width << " " << height << "\n255\n";
    fprintf(f,"P6\n%d %d\n255\n",r.width,r.height);
    for (int i=0;i<r.width*r.height;i++) {
        fputc(r.buf1[i].r,f);
        fputc(r.buf1[i].g,f);
        fputc(r.buf1[i].b,f);
    }
    fclose(f);
    return 0;
}

int writeToBMP(char *filename, RTXManager r) {
    bmp_img bmp;
    bmp_img_init_df(&bmp, r.width, r.height);

    for (int y=0;y<r.height;y++) {
        for (int x=0;x<r.width;x++) {
            int i = x + y*r.width;
            RGB c = r.buf1[i];
            bmp_pixel_init(&bmp.img_pixels[y][x],c.r,c.g,c.b);
        }
    }

    
	bmp_img_write(&bmp, filename);
	bmp_img_free(&bmp);
    return 0;
}

int main(int argc, char *argv[]) {
    printf("Hello world\n");
    int width = 200;
    int height = 200;
    int raysPerPixel = 20;
    for (int i=0;i<argc;i++) {
        printf("argv[%d]=\"%s\"\n",i,argv[i]);
        switch (i)
        {
        case 1:
            width = atoi(argv[i]);
            printf("\twidth=%d\n",width);
            break;
        case 2:
            height = atoi(argv[i]);
            printf("\theight=%d\n",height);
            break;
        case 3:
            raysPerPixel = atoi(argv[i]);
            printf("\trays per pixel=%d\n",raysPerPixel);
            break;
        
        default:
            break;
        }
    }
    rtx = makeRTXManager(width,height);
    rtx.config.raysPerPixel = raysPerPixel;
    printf("RTX init\n");
    RTXRender(&rtx);
    printf("Rendered\n");

    // writeToPPM("thing.ppm",rtx);
    writeToBMP("out.bmp",rtx);

    printf("done!\n");
    return 0;
}