#!/bin/sh

if [ -f fractal-generator.out ]; then
	rm fractal-generator.out
else
	g++ src/main.cpp -o fractal-generator.out -O2 -lGL -lGLU -lglut -lfreeimage -lX11 -std=c++0x
	./fractal-generator.out $1
	rm fractal-generator.out
fi
