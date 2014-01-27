#include "RenderComponentManager.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "Renderer.h"
#include "SceneObject.h"
#include "Scene.h"

namespace af
{
    RenderComponentManager::RenderComponentManager()
    {
    }

    RenderComponentManager::~RenderComponentManager()
    {
        assert(components_.empty());
    }

    void RenderComponentManager::addComponent(const ComponentPtr& component)
    {
        RenderComponentPtr renderComponent = boost::dynamic_pointer_cast<RenderComponent>(component);
        assert(renderComponent);

        assert(!component->manager());

        components_.insert(renderComponent);
        renderComponent->setManager(this);
    }

    void RenderComponentManager::removeComponent(const ComponentPtr& component)
    {
        RenderComponentPtr renderComponent = boost::dynamic_pointer_cast<RenderComponent>(component);
        assert(renderComponent);

        if (components_.erase(renderComponent)) {
            renderComponent->setManager(NULL);
        }
    }

    void RenderComponentManager::update(float dt)
    {
        for (std::set<RenderComponentPtr>::iterator it = components_.begin();
             it != components_.end();
             ++it ) {
            (*it)->update(dt);
        }

        tree_.Query(this, scene()->camera()->findComponent<CameraComponent>()->getAABB());

        renderer.clear();

        for (QueryResultMap::const_iterator it = queryResultsMap_.begin();
             it != queryResultsMap_.end();
             ++it) {
            for (QueryResults::const_iterator jt = it->second.begin();
                 jt != it->second.end();
                 ++jt) {
                jt->first->render(dt, jt->second);
            }
        }

        renderer.swapBuffers();

        queryResultsMap_.clear();
    }

    SInt32 RenderComponentManager::addAABB(RenderComponent* component,
                                           const b2AABB& aabb,
                                           void* data)
    {
        ProxyDataList::iterator it = proxyDataList_.insert(proxyDataList_.end(),
                                                           ProxyData());

        ProxyData& pd = proxyDataList_.back();

        pd.it = it;
        pd.component = component;
        pd.data = data;

        return tree_.CreateProxy(aabb, &pd);
    }

    void RenderComponentManager::moveAABB(SInt32 cookie,
                                          const b2AABB& aabb,
                                          const b2Vec2& displacement)
    {
        tree_.MoveProxy(cookie, aabb, displacement);
    }

    void RenderComponentManager::removeAABB(SInt32 cookie)
    {
        ProxyData* pd = reinterpret_cast<ProxyData*>(tree_.GetUserData(cookie));

        proxyDataList_.erase(pd->it);

        tree_.DestroyProxy(cookie);
    }

    bool RenderComponentManager::QueryCallback(SInt32 cookie)
    {
        ProxyData* pd = reinterpret_cast<ProxyData*>(tree_.GetUserData(cookie));

        QueryResults& res = queryResultsMap_[pd->component->zOrder()];

        res[pd->component].push_back(pd->data);

        return true;
    }
}
