CC=g++
CCFLAGS=-std=c++17 -Wall -Wextra -O2
GL_INCLUDE_FLAGS=-Iglad/include -Iglfw/include

all: lge

lge: libglad libglfw core-main.o core-windowmanager.o
	@mkdir -p bin
	$(CC) obj/core-main.o obj/core-windowmanager.o obj/glad.o glfw-build/src/libglfw3.a -o bin/lge -ldl -lm

core-main.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) -c core/src/main.cpp -o obj/core-main.o

core-windowmanager.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) -c core/src/WindowManager/WindowManager.cpp -o obj/core-windowmanager.o

libglad:
	@mkdir -p obj
	gcc -Ilibs/glad/include -c libs/glad/src/gl.c -o obj/glad.o

libglfw:
	@cmake libs/glfw -B glfw-build
	@cmake --build glfw-build

clean:
	@rm -rf bin obj
	@rm -rf glfw-build