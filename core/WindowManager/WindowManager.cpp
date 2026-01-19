#include "WindowManager/WindowManager.h"

Window::Window()
{

}

Window::~Window()
{
    window_render.Cleanup();

    glfwDestroyWindow(gl_window);
}

Window::Window(std::string title, int width, int height, int x, int y, std::function<void(Window*)> update, std::function<void(Window*)> start, std::function<void(Window*)> awake)
{
    window_title = title;
    window_size = Vector2(width, height);
    window_position = Vector2(x, y);

    windowUpdate = update;
    windowStart = start;
    windowAwake = awake;

    Init();
}

Window::Window(std::string title, Vector2 size, Vector2 position, std::function<void(Window*)> update, std::function<void(Window*)> start, std::function<void(Window*)> awake)
{
    window_title = title;
    window_size = size;
    window_position = position;

    windowUpdate = update;
    windowStart = start;
    windowAwake = awake;

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

    windowAwake(this);

    window_input.SetKeyCallback(gl_window);

    if(!gl_inited)
    {
        int version = gladLoadGL(glfwGetProcAddress);
        if (version == 0)
        {
            std::cerr << "Failed to initialize OpenGL context" << std::endl;
            return;
        }
        gl_inited = true;
        glEnable(GL_DEPTH_TEST);
        std::cout << "OpenGL version: " << GLAD_VERSION_MAJOR(version) 
                  << "." << GLAD_VERSION_MINOR(version) << std::endl;
    }

    window_render.Init();

    windowStart(this);

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
    
    windowUpdate(this);
    window_input.Update();
    
    glfwMakeContextCurrent(gl_window);
    
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    window_render.RenderFrame();

    glfwSwapBuffers(gl_window);
    glfwPollEvents();

    glfwMakeContextCurrent(NULL);
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