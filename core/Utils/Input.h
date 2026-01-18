#include <iostream>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include "Vectors.h"

class InputManager
{
public:
    InputManager();
    ~InputManager();

    bool IsKeyDown(int key);
    bool IsKeyPressed(int key);
    bool IsKeyReleased(int key);

    void SetKeyCallback(GLFWwindow* window);
    void Update();
private:
    static void StaticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void KeyCallback(int key, int scancode, int action, int mods);

    std::unordered_map<int, bool> keyStates;
    std::unordered_map<int, bool> previousKeyStates;
    std::unordered_map<int, bool> keyPressedOnFrame;
    std::unordered_map<int, bool> keyReleasedOnFrame;
};