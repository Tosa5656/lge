#include <iostream>

#include "../../core/include/WindowManager/WindowManager.h"
#include "../../core/include/Utils/Vectors.h"

Window* window;

void key_callback(GLFWwindow* wnd, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
        window->SetTitle("test");
}

int main()
{
    WindowManager wm;
    window = new Window("Lumin Engine", 1280, 720);
    glfwSetKeyCallback(window->GetWindow(), key_callback);

    wm.AddWindow(window);

    while(wm.IsRunning())
    {
        wm.RenderAll();
    }

    return 0;
}