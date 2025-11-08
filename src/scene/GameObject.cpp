#include "GameObject.h"
#include <Engine.h>


GameObject::GameObject() {
    id = Engine::GetInstance().entityManager.CreateEntity();
}

GameObject::~GameObject() {
}
