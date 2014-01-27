#ifndef _SCENEOBJECTMANAGER_H_
#define _SCENEOBJECTMANAGER_H_

#include "Types.h"
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <set>

namespace af
{
    class Scene;

    class SceneObject;
    typedef boost::shared_ptr<SceneObject> SceneObjectPtr;

    enum SceneObjectType
    {
        SceneObjectTypeOther = 0,
        SceneObjectTypePlayer = 1,
    };

    class SceneObjectManager : boost::noncopyable
    {
    public:
        SceneObjectManager();
        virtual ~SceneObjectManager();

        void addObject(const SceneObjectPtr& obj);

        void removeObject(const SceneObjectPtr& obj);

        void removeAllObjects();

        SceneObjectPtr findObject(SceneObjectType type);

        void lock();

        void unlock();

        inline SceneObjectManager* parent() { return parent_; }
        inline void setParent(SceneObjectManager* value) { parent_ = value; }

        inline Scene* scene() { return scene_; }
        inline void setScene(Scene* value) { scene_ = value; }

        inline bool locked() const { return locked_; }

    private:
        virtual void doUnlock() = 0;

        void registerObject(const SceneObjectPtr& obj);

        void unregisterObject(const SceneObjectPtr& obj);

        SceneObjectManager* parent_;

        Scene* scene_;

        bool locked_;

        std::set<SceneObjectPtr> objects_;

        std::set<SceneObjectPtr> objectsToAdd_;
        std::set<SceneObjectPtr> objectsToRemove_;
    };
}

#endif
