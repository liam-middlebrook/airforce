#include "Scene.h"
#include "SceneObject.h"
#include "PhasedComponentManager.h"
#include "PhysicsComponentManager.h"
#include "RenderComponentManager.h"
#include "PhasedComponent.h"
#include "CameraComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include <boost/make_shared.hpp>
#include <vector>

namespace af
{
    namespace
    {
        class RegisterComponentVisitor : public ComponentVisitor
        {
        public:
            RegisterComponentVisitor()
            {
            }

            explicit RegisterComponentVisitor(const std::vector<ComponentManagerPtr>& componentManagers)
            {
                phasedComponentManagers_[PhaseThink] = componentManagers.at(0);
                physicsComponentManager_ = componentManagers.at(1);
                phasedComponentManagers_[PhasePostPhysics] = componentManagers.at(2);
                phasedComponentManagers_[PhasePreRender] = componentManagers.at(3);
                renderComponentManager_ = componentManagers.at(4);
            }

            ~RegisterComponentVisitor()
            {
            }

            virtual void visitPhasedComponent(const PhasedComponentPtr& component)
            {
                phasedComponentManagers_[component->phase()]->addComponent(component);
            }

            virtual void visitPhysicsComponent(const PhysicsComponentPtr& component)
            {
                physicsComponentManager_->addComponent(component);
            }

            virtual void visitRenderComponent(const RenderComponentPtr& component)
            {
                renderComponentManager_->addComponent(component);
            }

        private:
            ComponentManagerPtr phasedComponentManagers_[PhaseMax + 1];
            ComponentManagerPtr physicsComponentManager_;
            ComponentManagerPtr renderComponentManager_;
        };
    }

    class Scene::Impl
    {
    public:
        Impl()
        {
            componentManagers_.push_back(boost::make_shared<PhasedComponentManager>());
            componentManagers_.push_back(boost::make_shared<PhysicsComponentManager>());
            componentManagers_.push_back(boost::make_shared<PhasedComponentManager>());
            componentManagers_.push_back(boost::make_shared<PhasedComponentManager>());
            componentManagers_.push_back(boost::make_shared<RenderComponentManager>());

            registerComponentVisitor_ = RegisterComponentVisitor(componentManagers_);
        }

        ~Impl()
        {
        }

        std::vector<ComponentManagerPtr> componentManagers_;

        RegisterComponentVisitor registerComponentVisitor_;

        SceneObjectPtr camera_;
    };

    Scene::Scene(float cameraWidth, float cameraHeight)
    : impl_(new Impl())
    {
        setScene(this);

        for (std::vector<ComponentManagerPtr>::iterator it = impl_->componentManagers_.begin();
             it != impl_->componentManagers_.end();
             ++it ) {
            (*it)->setScene(this);
        }

        impl_->camera_ = boost::make_shared<SceneObject>(SceneObjectTypeOther);

        impl_->camera_->addComponent(boost::make_shared<CameraComponent>(cameraWidth, cameraHeight));

        addObject(impl_->camera_);
    }

    Scene::~Scene()
    {
        removeAllObjects();

        delete impl_;
    }

    void Scene::registerComponent(const ComponentPtr& component)
    {
        component->accept(impl_->registerComponentVisitor_);
    }

    void Scene::unregisterComponent(const ComponentPtr& component)
    {
        component->manager()->removeComponent(component);
    }

    void Scene::update(float dt)
    {
        lock();

        for (std::vector<ComponentManagerPtr>::iterator it = impl_->componentManagers_.begin();
             it != impl_->componentManagers_.end();
             ++it ) {
            (*it)->update(dt);
        }

        unlock();
    }

    SceneObjectPtr& Scene::camera()
    {
        return impl_->camera_;
    }

    void Scene::doUnlock()
    {
    }
}
