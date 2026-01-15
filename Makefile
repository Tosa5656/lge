CC=g++
CCFLAGS=-std=c++20 -Wall -Wextra -O2
GL_INCLUDE_FLAGS=-Iglad/include -Iglfw/include

all: lge

lge: libglad libglfw editor.o core-windowmanager.o core-input.o core-filesystemmanager.o core-rendermanager.o core-shadermanager.o install-resources
	@mkdir -p bin
	$(CC) obj/editor.o obj/core-windowmanager.o obj/core-input.o obj/core-filesystemmanager.o obj/core-rendermanager.o obj/core-shadermanager.o obj/glad.o glfw-build/src/libglfw3.a -o bin/lge -ldl -lm

editor.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) -c editor/src/main.cpp -o obj/editor.o

core-windowmanager.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) -c core/src/WindowManager/WindowManager.cpp -o obj/core-windowmanager.o

core-input.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) -c core/src/Utils/Input.cpp -o obj/core-input.o

core-filesystemmanager.o:
	$(CC) $(CCFLAGS) -c core/src/Utils/FileSystemManager.cpp -o obj/core-filesystemmanager.o

core-rendermanager.o:
	$(CC) $(CCFLAGS) -c core/src/Render/RenderManager.cpp -o obj/core-rendermanager.o

core-shadermanager.o:
	$(CC) $(CCFLAGS) -c core/src/Render/ShaderManager.cpp -o obj/core-shadermanager.o

libglad:
	@mkdir -p obj
	gcc -Ilibs/glad/include -c libs/glad/src/gl.c -o obj/glad.o

libglfw:
	@cmake libs/glfw -B glfw-build
	@cmake --build glfw-build

install-resources: lge
	@cp -r resources bin/

clean:
	@rm -rf bin obj
	@rm -rf glfw-build