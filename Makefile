CC=g++
CCFLAGS=-std=c++20 -Wall -Wextra -O2
GL_INCLUDE_FLAGS=-Ilibs/glad/include -Ilibs/glfw/include -Ilibs/soil/include
CORE_INCLUDE_FLAGS=-Icore

all: lge

lge: libglad libglfw soil editor.o core-windowmanager.o core-input.o core-filesystemmanager.o core-mesh.o core-rendermanager.o core-shadermanager.o core-texture.o install-resources
	@mkdir -p bin
	$(CC) obj/editor.o obj/core-windowmanager.o obj/core-input.o obj/core-filesystemmanager.o obj/core-mesh.o obj/core-rendermanager.o obj/core-shadermanager.o  obj/core-texture.o obj/glad.o glfw-build/src/libglfw3.a libs/soil/build/lib/libSOIL.a -o bin/lge -lglfw -lSOIL -lGL -lpthread -lXrandr -lXi -ldl

editor.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) $(CORE_INCLUDE_FLAGS) -c editor/main.cpp -o obj/editor.o

core-windowmanager.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) $(CORE_INCLUDE_FLAGS) -c core/WindowManager/WindowManager.cpp -o obj/core-windowmanager.o

core-input.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) $(CORE_INCLUDE_FLAGS) -c core/Utils/Input.cpp -o obj/core-input.o

core-filesystemmanager.o:
	$(CC) $(CCFLAGS) $(CORE_INCLUDE_FLAGS) -c core/Utils/FileSystemManager.cpp -o obj/core-filesystemmanager.o

core-rendermanager.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) $(CORE_INCLUDE_FLAGS) -c core/Render/RenderManager.cpp -o obj/core-rendermanager.o

core-shadermanager.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) $(CORE_INCLUDE_FLAGS) -c core/Render/ShaderManager.cpp -o obj/core-shadermanager.o

core-mesh.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) $(CORE_INCLUDE_FLAGS) -c core/Render/Mesh.cpp -o obj/core-mesh.o

core-texture.o:
	$(CC) $(CCFLAGS) $(GL_INCLUDE_FLAGS) $(CORE_INCLUDE_FLAGS) -c core/Render/Texture.cpp -o obj/core-texture.o

libglad:
	@mkdir -p obj
	gcc -Ilibs/glad/include -c libs/glad/src/gl.c -o obj/glad.o

libglfw:
	@cmake libs/glfw -B glfw-build
	@cmake --build glfw-build

soil:
	@cd libs/soil && ./configure && make

install-resources: lge
	@cp -r resources bin/

install-soil: soil
	@cd libs/soil && sudo make install

clean:
	@rm -rf bin obj
	@rm -rf glfw-build