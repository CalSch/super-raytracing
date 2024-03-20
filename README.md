# super-raytracing
This will hopefully become a raytracing program that can run on many different platforms, by having one base library with a wrapper for each platform.  
I currently have the following platforms:
```
PC - using Raylib
Nintendo DS - using DevkitPro and NightFoxLib
CLI Image renderer - using libbmp, it takes command line arguments and renders to an image
```
I'm hoping to support more like the SNES (probably not but maybe), the PineTime (very silly), and any other platform that you can compile C/C++ for.