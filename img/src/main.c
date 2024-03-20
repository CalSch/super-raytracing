#include <stdio.h>
#include "rtx_manager.h"

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

int main(int argc, char *argv[]) {
    printf("Hello world\n");
    int width = 200;
    int height = 200;
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
        
        default:
            break;
        }
    }
    rtx = makeRTXManager(width,height);
    printf("RTX init\n");
    RTXRender(&rtx);
    printf("Rendered\n");
    writeToPPM("thing.ppm",rtx);
    printf("done!\n");
    return 0;
}