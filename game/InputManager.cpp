#include "InputManager.h"
#define XK_MISCELLANY
#include <X11/keysymdef.h>
#include <iostream>

namespace af
{
    InputManager inputManager;

    template <>
    Single<InputManager>* Single<InputManager>::single = NULL;

    InputManager::InputManager()
    : leftPressed_(false),
      rightPressed_(false)
    {
    }

    InputManager::~InputManager()
    {
    }

    bool InputManager::init()
    {
        return true;
    }

    void InputManager::inputKey(int key, bool down)
    {
        switch (key) {
        case XK_Left:
            leftPressed_ = down;
            break;
        case XK_Right:
            rightPressed_ = down;
            break;
        default:
            break;
        }
    }

    void InputManager::shutdown()
    {
    }
}
