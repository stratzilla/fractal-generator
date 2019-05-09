#!/usr/bin/env bash

if [ -f fractal-generator.out ]; then
	./fractal-generator.out $1
else
	g++ src/main.cpp -o fractal-generator.out -O2 -lGL -lGLU -lglut -lfreeimage -lX11 -std=c++0x
	./fractal-generator.out $1
fi
	
