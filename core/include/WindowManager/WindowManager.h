#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

#include "../../../libs/glad/include/glad/gl.h"
#include "../../../libs/glfw/include/GLFW/glfw3.h"
#include "../Utils/Vectors.h"
#include "../Utils/Input.h"
#include "../Render/RenderManager.h"

using namespace lmt;

inline bool gl_inited = false;

class Window
{
public:
    Window();
    Window(std::string title, int width, int height, int x, int y, std::function<void(Window*)> update, std::function<void(Window*)> start, std::function<void(Window*)> awake);
    Window(std::string title, Vector2 size, Vector2 position, std::function<void(Window*)> update, std::function<void(Window*)> start, std::function<void(Window*)> awake);

    ~Window();

    bool RenderFrame();

    void Close() { glfwSetWindowShouldClose(gl_window, GLFW_TRUE); }

    bool ShouldClose() const { return glfwWindowShouldClose(gl_window); }
    bool IsValid() const { return gl_window != nullptr; }

    void SetTitle(std::string title);
    void SetSize(Vector2 size);
    void SetPosition(Vector2 position);

    GLFWwindow* GetWindow();
    std::string GetTitle();
    Vector2 GetSize();
    Vector2 GetPosition();
    InputManager* GetInput();
private:
    void Init();
    void Cleanup();

    GLFWwindow* gl_window = nullptr;
    std::string window_title = "";
    Vector2 window_size = Vector2(0, 0);;
    Vector2 window_position = Vector2(0, 0);
    InputManager window_input;
    RenderManager window_render;

    bool is_inited = false;

    std::function<void(Window*)> windowAwake;
    std::function<void(Window*)> windowStart;
    std::function<void(Window*)> windowUpdate;

    GLuint shaderProgram;
    GLuint VBO, VAO;
};

class WindowManager
{
public:
    WindowManager();
    ~WindowManager();

    void AddWindow(Window* window);
    Window* GetWindow(int index);

    void RenderAll();

    bool IsRunning() { return is_running; }
private:
    bool is_running = false;
    std::vector<Window*> windows;
};