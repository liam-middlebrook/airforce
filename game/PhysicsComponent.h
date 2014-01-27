#ifndef _PHYSICSCOMPONENT_H_
#define _PHYSICSCOMPONENT_H_

#include "PhysicsComponentManager.h"

namespace af
{
    class PhysicsComponent : public Component
    {
    public:
        PhysicsComponent()
        : manager_(NULL)
        {
        }

        virtual ~PhysicsComponent() {}

        virtual PhysicsComponentManager* manager() { return manager_; }
        inline void setManager(PhysicsComponentManager* value)
        {
            if (!manager_ && value) {
                manager_ = value;
                onRegister();
            } else if (manager_ && !value) {
                onUnregister();
                manager_ = NULL;
            } else {
                assert(false);
            }
        }

    private:
        virtual void onRegister() = 0;

        virtual void onUnregister() = 0;

        PhysicsComponentManager* manager_;
    };
}

#endif
