CC=g++
CCFLAGS=-std=c++17 -Wall -Wextra -O2
GL_INCLUDE_FLAGS=-Iglad/include -Iglfw/include

all: lge

lge: libglad libglfw editor.o core-windowmanager.o
	@mkdir -p bin
	$(CC) obj/editor.o obj/core-windowmanager.o obj/glad.o glfw-build/src/libglfw3.a -o bin/lge -ldl -lm

editor.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) -c editor/src/main.cpp -o obj/editor.o

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