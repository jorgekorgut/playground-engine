#pragma once
#include "Engine.h"
#include "Model.h"
#include "ModelPlane.h"
#include "Transform.h"
#include "ecs/ComponentManager.h"

class GameObject {
    public:
    friend class Engine;
    GameObject();
    ~GameObject();

    template <typename T>
    void AddComponent(T& component) {
        Engine::GetInstance().componentManager.AddComponent<T>(id, component);

        auto signature = Engine::GetInstance().entityManager.GetSignature(id);

        signature.set(Engine::GetInstance().componentManager.GetComponentType<T>(), true);

        Engine::GetInstance().entityManager.SetSignature(id, signature);

        Engine::GetInstance().systemManager.EntitySignatureChanged(id, signature);
    }

    template <typename T>
    T& GetComponent() {
        return Engine::GetInstance().componentManager.GetComponent<T>(id);
    }

    private:
    Entity id;
};
