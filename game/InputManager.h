#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include "Single.h"
#include "af/Types.h"

namespace af
{
    class InputManager : public Single<InputManager>
    {
    public:
        InputManager();
        ~InputManager();

        bool init();

        void inputKey(int key, bool down);

        void shutdown();

        inline bool leftPressed() const { return leftPressed_; }

        inline bool rightPressed() const { return rightPressed_; }

    private:
        bool leftPressed_;
        bool rightPressed_;
    };

    extern InputManager inputManager;
}

#endif
