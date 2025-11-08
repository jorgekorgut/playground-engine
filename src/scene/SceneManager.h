#pragma once
#include "Camera.h"
#include <vector>
#include "Sky.h"

class SceneManager {
    public:
    SceneManager() {
    }
    Camera camera;
    Sky sky;
};
