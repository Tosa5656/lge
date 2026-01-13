#include <iostream>

#include "../../core/include/WindowManager/WindowManager.h"
#include "../../core/include/Utils/Vectors.h"

int main()
{
    WindowManager wm;
    Window* window = new Window("Lumin Engine", 1280, 720);

    wm.AddWindow(window);

    while(wm.IsRunning())
    {
        wm.RenderAll();

        if(window->GetInput()->IsKeyPressed(GLFW_KEY_W))
            window->SetTitle("test");
    }

    return 0;
}