#pragma once
#include "Scene.h"
namespace scenes{

class Scene1: public Scene{

public:
    Scene1();
    ~Scene1(){}

    // void OnUpdate(float deltaTime) override;
    // void OnRender() override;
    bool OnUIRender() override;
};

}