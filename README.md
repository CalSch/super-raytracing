# super-raytracing
This will hopefully become a raytracing program that can run on many different platforms, by having one base library with a wrapper for each platform.  
I currently have the following platforms:
```
PC - using Raylib
Nintendo DS - using DevkitPro and NightFoxLib
CLI Image renderer - using libbmp, it takes command line arguments and renders to an image
```
I'm hoping to support more like the SNES (probably not but maybe), the PineTime (very silly), and any other platform that you can compile C/C++ for.

## Demo
Heres a render at 500x500, 2 rays per pixel, and 60 samples:  
![out](https://github.com/CalSch/super-raytracing/assets/35741152/c976d032-d642-4cbb-aeea-ff4833339034)

# Todo
 - add a pixel skip mask, so maybe it only traces every other pixel to get a faster response
 - improve the scene
 - add debug controls to PC, so you can change what you see (ex. show normals, no shading)
 - add a scene editor
 - better documentation