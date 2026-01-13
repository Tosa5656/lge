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
    }

    return 0;
}