#pragma once
#include <functional>

class UIObject {
    public:
    UIObject(std::function<void(void)> callback = nullptr) {
        this->callback = std::move(callback);
    }

    std::function<void(void)> callback;
};
