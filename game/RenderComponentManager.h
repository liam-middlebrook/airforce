#ifndef _RENDERCOMPONENTMANAGER_H_
#define _RENDERCOMPONENTMANAGER_H_

#include "ComponentManager.h"
#include <Box2D/Box2D.h>
#include <set>
#include <list>
#include <map>
#include <vector>

namespace af
{
    class RenderComponentManager : public ComponentManager
    {
    public:
        RenderComponentManager();
        ~RenderComponentManager();

        virtual void addComponent(const ComponentPtr& component);

        virtual void removeComponent(const ComponentPtr& component);

        virtual void update(float dt);

        SInt32 addAABB(RenderComponent* component,
                       const b2AABB& aabb,
                       void* data);

        void moveAABB(SInt32 cookie,
                      const b2AABB& aabb,
                      const b2Vec2& displacement);

        void removeAABB(SInt32 cookie);

        /*
         * For internal use only.
         */
        bool QueryCallback(SInt32 cookie);

    private:
        struct ProxyData
        {
            std::list<ProxyData>::iterator it;
            RenderComponent* component;
            void* data;
        };

        typedef std::list<ProxyData> ProxyDataList;

        typedef std::map< RenderComponent*, std::vector<void*> > QueryResults;

        typedef std::map<int, QueryResults> QueryResultMap;

        std::set<RenderComponentPtr> components_;

        ProxyDataList proxyDataList_;

        b2DynamicTree tree_;

        QueryResultMap queryResultsMap_;
    };
}

#endif
