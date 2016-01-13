CC=g++
CFLAGS=-c -Wall -std=c++11 
LFLAGS=-lGL -lGLEW -lglfw3 -lpthread -lXrandr -lX11 -ldl -lXi -lXxf86vm -lXinerama -lrt -lm -lXcursor -lSOIL
all: synthesis

synthesis: Window.o GLShader.o Image.o Utils.o Pixel.o Color.o Patch.o
	$(CC) Window.o GLShader.o Image.o Utils.o Pixel.o Color.o Patch.o -o synthesis $(LFLAGS)

Window.o: Window.cpp
	$(CC) $(CFLAGS) Window.cpp $(LFLAGS)

GLShader.o: GLShader.cpp
	$(CC) $(CFLAGS) GLShader.cpp $(LFLAGS)

Image.o: Image.cpp
	$(CC) $(CFLAGS) Image.cpp $(LFLAGS)

Utils.o: Utils.cpp
	$(CC) $(CFLAGS) Utils.cpp $(LFLAGS)

Pixel.o: Pixel.cpp
	$(CC) $(CFLAGS) Pixel.cpp $(LFLAGS)

Color.o: Color.cpp
	$(CC) $(CFLAGS) Color.cpp $(LFLAGS)

Patch.o: Patch.cpp
	$(CC) $(CFLAGS) Patch.cpp $(LFLAGS)

clean:
	rm *o *~ *gch synthesis
