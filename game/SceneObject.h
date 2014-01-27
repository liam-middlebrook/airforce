#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include "SceneObjectManager.h"
#include "Component.h"
#include <Box2D/Box2D.h>
#include <set>

namespace af
{
    class SceneObject : public SceneObjectManager
    {
    public:
        explicit SceneObject(SceneObjectType type,
                             const b2Vec2& pos = b2Vec2(0.0f, 0.0f),
                             float angle = 0.0f);
        virtual ~SceneObject();

        void addComponent(const ComponentPtr& component);

        void removeComponent(const ComponentPtr& component);

        inline std::set<ComponentPtr>& components() { return components_; }

        template <class T>
        inline boost::shared_ptr<T> findComponent()
        {
            for (std::set<ComponentPtr>::iterator it = components_.begin();
                 it != components_.end();
                 ++it ) {
                const boost::shared_ptr<T>& component =
                    boost::dynamic_pointer_cast<T>(*it);
                if (component) {
                    return component;
                }
            }
            return boost::shared_ptr<T>();
        }

        inline SceneObjectType type() const { return type_; }

        void setBody(b2Body* value);

        const b2BodyDef& bodyDef() const { return bodyDef_; }

        b2Transform getTransform() const;
        void setTransform(const b2Vec2& pos, float32 angle);

        const b2Vec2& pos() const;
        void setPos(const b2Vec2& value);

        float angle() const;
        void setAngle(float value);

        const b2Vec2& linearVelocity() const;
        void setLinearVelocity(const b2Vec2& value);

        float angularVelocity() const;
        void setAngularVelocity(float value);

        float linearDamping() const;
        void setLinearDamping(float value);

        float angularDamping() const;
        void setAngularDamping(float value);

    private:
        virtual void doUnlock();

        SceneObjectType type_;

        b2BodyDef bodyDef_;
        b2Body* body_;

        std::set<ComponentPtr> components_;

        std::set<ComponentPtr> componentsToAdd_;
        std::set<ComponentPtr> componentsToRemove_;
    };
}

#endif
