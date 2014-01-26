#ifndef _PHYSICSCOMPONENT_H_
#define _PHYSICSCOMPONENT_H_

#include "PhysicsComponentManager.h"

namespace af
{
    class PhysicsComponent : public Component
    {
    public:
        typedef std::list<PhysicsComponentPtr>::iterator ManagerCookie;

        PhysicsComponent()
        : manager_(NULL)
        {
        }

        virtual ~PhysicsComponent()
        {
        }

        virtual PhysicsComponentManager* manager() { return manager_; }
        inline void setManager(PhysicsComponentManager* value,
                               const ManagerCookie& cookie = ManagerCookie())
        {
            if (!manager_ && value) {
                manager_ = value;
                managerCookie_ = cookie;
                onAdd();
            } else if (manager_ && !value) {
                manager_ = NULL;
                managerCookie_ = ManagerCookie();
                onRemove();
            } else {
                assert(false);
            }
        }

        inline ManagerCookie managerCookie() const { return managerCookie_; }

    private:
        virtual void onAdd() = 0;

        virtual void onRemove() = 0;

        PhysicsComponentManager* manager_;
        ManagerCookie managerCookie_;
    };
}

#endif
