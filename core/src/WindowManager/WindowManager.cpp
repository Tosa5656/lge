#include "../../include/WindowManager/WindowManager.h"

Window::Window()
{

}

Window::~Window()
{
    glfwDestroyWindow(gl_window);
}

Window::Window(std::string title, int width, int height, int x, int y)
{
    window_title = title;
    window_size = Vector2(width, height);
    window_position = Vector2(x, y);

    Init();
}

Window::Window(std::string title, Vector2 size, Vector2 position)
{
    window_title = title;
    window_size = size;
    window_position = position;

    Init();
}

void Window::Init()
{
    gl_window = glfwCreateWindow(window_size.x, window_size.y, window_title.c_str(), NULL, NULL);
    if (!gl_window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        return;
    }

    glfwMakeContextCurrent(gl_window);

    window_input.SetKeyCallback(gl_window);

    if(!gl_inited)
    {
        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0)
        {
            printf("Failed to initialize OpenGL context\n");
            return;
        }
    }
    glfwMakeContextCurrent(NULL);
}

void Window::Cleanup()
{
    if (gl_window)
    {
        glfwDestroyWindow(gl_window);
        gl_window = nullptr;
    }
}

bool Window::RenderFrame()
{
    if (!gl_window || glfwWindowShouldClose(gl_window)) 
        return false;
    
    glfwMakeContextCurrent(gl_window);
    
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(gl_window);
    glfwPollEvents();
    return true;
}

void Window::SetTitle(std::string title) { glfwSetWindowTitle(gl_window, title.c_str()); }
void Window::SetSize(Vector2 size) { glfwSetWindowSize(gl_window, size.x, size.y); }
void Window::SetPosition(Vector2 position) { glfwSetWindowPos(gl_window, position.x, position.y); }

GLFWwindow* Window::GetWindow() { return gl_window; }
std::string Window::GetTitle() { return window_title; }
Vector2 Window::GetSize() { return window_size; }
Vector2 Window::GetPosition() { return window_position; }
InputManager* Window::GetInput() { return &window_input; }

// ============================WindowManager============================
WindowManager::WindowManager()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    is_running = true;
}

WindowManager::~WindowManager()
{
    for (Window* window : windows)
    {
        if (window)
        {
            delete window;
        }
    }
    windows.clear();
    
    glfwTerminate();
    is_running = false;
}

void WindowManager::AddWindow(Window* window)
{
    windows.push_back(window);
}

Window* WindowManager::GetWindow(int index)
{
    if (index >= 0 && index < windows.size())
    {
        return windows[index];
    }
    return nullptr;
}

void WindowManager::RenderAll()
{
    std::vector<Window*> windows_to_close;
    
    for (Window* window : windows)
    {
        if (window && window->IsValid())
        {
            if (!window->RenderFrame())
            {
                windows_to_close.push_back(window);
            }
        }
    }
    
    for (Window* window_to_close : windows_to_close)
    {
        auto it = std::find(windows.begin(), windows.end(), window_to_close);
        if (it != windows.end())
        {
            windows.erase(it);
            
            delete window_to_close;
            window_to_close = nullptr;
        }
    }
    
    if (windows.empty())
    {
        is_running = false;
    }
}