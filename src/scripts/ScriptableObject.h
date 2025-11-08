#pragma once
#include "Engine.h"

class ScriptableObject {
    public:
    ScriptableObject() {
        Engine::GetInstance().AddScriptableObject(this);
    }

    virtual ~ScriptableObject() {
        Engine::GetInstance().RemoveScriptableObject(this);
    }

    virtual void Start() {
    }

    virtual void Update() {
    }
};
