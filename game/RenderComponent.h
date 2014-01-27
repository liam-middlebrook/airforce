#ifndef _RENDERCOMPONENT_H_
#define _RENDERCOMPONENT_H_

#include "RenderComponentManager.h"
#include <vector>

namespace af
{
    class RenderComponent : public Component
    {
    public:
        explicit RenderComponent(int zOrder = 0)
        : manager_(NULL),
          zOrder_(zOrder)
        {
        }

        virtual ~RenderComponent() {}

        virtual RenderComponentManager* manager() { return manager_; }
        inline void setManager(RenderComponentManager* value)
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

        inline int zOrder() const { return zOrder_; }
        inline void setZOrder(int value) { zOrder_ = value; }

        virtual void update(float dt) = 0;

        virtual void render(float dt, const std::vector<void*>& parts) = 0;

    private:
        virtual void onRegister() = 0;

        virtual void onUnregister() = 0;

        RenderComponentManager* manager_;

        int zOrder_;
    };
}

#endif
