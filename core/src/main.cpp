#include <iostream>

#include "../include/WindowManager/WindowManager.h"
#include "../include/Utils/Vectors.h"

int main()
{
    WindowManager wm;
    Window* window = new Window("Lumin Engine", 1280, 720);
    Window* window2 = new Window("Lumin Engine2", 1280, 720);

    wm.AddWindow(window);
    wm.AddWindow(window2);

    while(wm.IsRunning())
    {
        wm.RenderAll();
    }

    return 0;
}