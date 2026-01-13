#include <iostream>
#include <unordered_map>

#include "../../../libs/glfw/include/GLFW/glfw3.h"
#include "Vectors.h"

class InputManager
{
public:
    InputManager();
    ~InputManager();

    bool IsKeyPressed(int key);
    bool IsKeyReleased(int key);

    void SetKeyCallback(GLFWwindow* window);
private:
    static void StaticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void KeyCallback(int key, int scancode, int action, int mods);

    std::unordered_map<int, bool> keyStates;
    std::unordered_map<int, bool> keyPressedOnFrame;
    std::unordered_map<int, bool> keyReleasedOnFrame;
};