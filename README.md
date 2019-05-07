# fractal_generator

## Dependencies:
- Freeglut
- Freeimage
- C++03 or later
- gcc
- X11 or other window manager

## Execution
$ g++ Source.cpp -O2 -lGL -lGLU -lglut -lfreeimage -lX11 -std=c++0x
$ /a.out <arg>
  
<arg> is the maximum depth (number of iterations) used to define fractal within the range [32, 4096]. Higher is slower but better representation of the fractal set.
