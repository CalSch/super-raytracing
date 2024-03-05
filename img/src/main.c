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

int main() {
    printf("Hello world\n");
    rtx = makeRTXManager(1000,1000);
    printf("RTX init\n");
    RTXRender(&rtx);
    printf("Rendered\n");
    writeToPPM("thing.ppm",rtx);
    printf("done!\n");
    return 0;
}