#ifndef _RENDERCOMPONENT_H_
#define _RENDERCOMPONENT_H_

#include "RenderComponentManager.h"
#include <list>
#include <vector>

namespace af
{
    class RenderComponent : public Component
    {
    public:
        typedef std::list<RenderComponentPtr>::iterator ManagerCookie;

        explicit RenderComponent(int zOrder = 0)
        : manager_(NULL),
          zOrder_(zOrder)
        {
        }

        virtual ~RenderComponent() {}

        virtual RenderComponentManager* manager() { return manager_; }
        inline void setManager(RenderComponentManager* value,
                               const ManagerCookie& cookie = ManagerCookie())
        {
            manager_ = value;
            managerCookie_ = cookie;
        }

        inline ManagerCookie managerCookie() const { return managerCookie_; }

        inline int zOrder() const { return zOrder_; }
        inline void setZOrder(int value) { zOrder_ = value; }

        virtual void update(float dt) = 0;

        virtual void render(float dt, const std::vector<void*>& parts) = 0;

    private:
        RenderComponentManager* manager_;
        ManagerCookie managerCookie_;

        int zOrder_;
    };
}

#endif
