#pragma once
#include <memory>
#include "Types.h"
#include <unordered_map>
#include "System.h"

class SystemManager {
    public:
    template <typename T>
    void RegisterSystem(T* system, Signature& signature) {
        const char* typeName = typeid(T).name();

        assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once.");

        mSystems.insert({ typeName, system });

        SetSignature<T>(signature);
    }

    template <typename T>
    void SetSignature(Signature& signature) {
        const char* typeName = typeid(T).name();

        assert(mSystems.find(typeName) != mSystems.end() && "System used before registered.");

        // Set the signature for this system
        mSignatures.insert({ typeName, signature });
    }

    void EntityDestroyed(Entity entity) {
        // Erase a destroyed entity from all system lists
        // mEntities is a set so no check needed
        for(auto const& pair : mSystems) {
            auto const& system = pair.second;

            system->mEntities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature) {
        // Notify each system that an entity's signature changed
        for(auto const& pair : mSystems) {
            auto const& type            = pair.first;
            auto const& system          = pair.second;
            auto const& systemSignature = mSignatures[type];

            // Entity signature matches system signature - insert into set
            if((entitySignature & systemSignature) == systemSignature) {
                system->mEntities.insert(entity);
            }
            // Entity signature does not match system signature - erase from set
            else {
                system->mEntities.erase(entity);
            }
        }
    }

    private:
    // Map from system type string pointer to a signature
    std::unordered_map<const char*, Signature> mSignatures{};

    // Map from system type string pointer to a system pointer
    std::unordered_map<const char*, System*> mSystems{};
};
