#include "../../include/Utils/Input.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{

}

void InputManager::SetKeyCallback(GLFWwindow* window)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetKeyCallback(window, StaticKeyCallback);
}

void InputManager::StaticKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    InputManager* inputManager = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
    
    if (inputManager)
    {
        inputManager->KeyCallback(key, scancode, action, mods);
    }
}

void InputManager::KeyCallback(int key, int scancode, int action, int mods)
{
    Update();
    
    if(action == GLFW_PRESS)
    {
        keyStates[key] = true;
        keyPressedOnFrame[key] = true;
    }
    else if(action == GLFW_RELEASE)
    {
        keyStates[key] = false;
        keyReleasedOnFrame[key] = true;
    }
}

void InputManager::Update()
{
    previousKeyStates = keyStates;

    keyPressedOnFrame.clear();
    keyReleasedOnFrame.clear();
}

bool InputManager::IsKeyDown(int key)
{
    if(keyStates[key] && keyPressedOnFrame[key] && previousKeyStates[key] != true)
        return true;
    else
        return false;
}

bool InputManager::IsKeyPressed(int key)
{
    return keyPressedOnFrame[key];
}

bool InputManager::IsKeyReleased(int key)
{
    return keyReleasedOnFrame[key];
}