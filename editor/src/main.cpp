#include <iostream>

#include "../../core/include/WindowManager/WindowManager.h"
#include "../../core/include/Utils/Vectors.h"
#include "../../core/include/Utils/FileSystemManager.h"

void Awake(Window* window)
{
    std::cout << "Awake user function for " << window->GetTitle() << " window" << std::endl;
}

void Start(Window* window)
{
    std::cout << "Start user function for " << window->GetTitle() << " window" << std::endl;
}

void Update(Window* window)
{

}

int main()
{
    WindowManager wm;
    Window* window = new Window("Lumin Engine", 1280, 720, 0, 0, Update, Start, Awake);

    wm.AddWindow(window);


    while(wm.IsRunning())
    {
        wm.RenderAll();

        if(window->GetInput()->IsKeyDown(GLFW_KEY_W))
            std::cout << "Pressed key W" << std::endl;
    }

    return 0;
}