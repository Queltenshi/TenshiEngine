#pragma once

#include "TenshiEngine/Engine/Entity/Entity.hpp"

namespace te{

class Registry;

namespace systems{

class System{
public:
    System(Registry &registry): mRegistry(registry){}

    virtual void update() = 0;

protected:
    Registry &mRegistry;
};

class FixedSystem : public System{
public:
    FixedSystem(Registry &registry, const float deltaTime): System(registry), mDeltaTime(deltaTime){} 

protected:
    const float mDeltaTime;
};

class VariableSystem : public System{
public:
    VariableSystem(Registry &registry, float &deltaTime): System(registry), mDeltaTime(deltaTime){} 

protected:
    float &mDeltaTime;
};
}
}
