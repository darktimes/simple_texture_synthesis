# Simple Texture Synthesis
This is a common texture synthesis based works of Wey and Levoy.

To compile (makefile is to come):
g++ -o window -std=c++11 -Wall window.cpp GLShader.cpp GLShader.hpp Image.hpp Image.cpp Utils.hpp Utils.cpp Patch.hpp Patch.cpp Pixel.hpp -lGL -lGLEW -lglfw3 -lpthread -lXrandr -lX11 -ldl -lXi -lXxf86vm -lXinerama -lrt -lm -lXcursor -lSOIL

To synthesise, edit window.cpp: lines 116-126 are examples.
