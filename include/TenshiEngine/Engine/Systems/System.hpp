#pragma once

#include <string>
#include "TenshiEngine/Engine/Entity/Entity.hpp"

namespace te{

class Registry;

namespace systems{

/**
 * @brief Base system
 */
class System{
public:
    /**
     * @brief Constructor
     *
     * Creates a system
     *
     * @param registry reference to the Registry
     */
    System(Registry &registry): mRegistry(registry){}

    /**
     * @brief updates the system
     *
     * Used for updating and handling the logic,
     * systems do override this method
     */
    virtual void update() = 0;

protected:
    ///Reference to the registry
    Registry &mRegistry;
};

/**
 * @brief Fixed system
 */
class FixedSystem : public System{
public:
    /**
     * @brief Constructor
     *
     * Creates a system with fixed deltaTime
     *
     * @param registry reference to the Registry
     * @param deltaTime Fixed deltaTime
     */
    FixedSystem(Registry &registry, const float deltaTime): System(registry), mDeltaTime(deltaTime){} 

protected:
    ///Fixed deltaTime
    const float mDeltaTime;
};

/**
 * @brief Variable system
 */
class VariableSystem : public System{
public:
    /**
     * @brief Constructor
     *
     * Creates a variable system
     *
     * @param registry reference to the Registry
     * @param deltaTime Reference to frame deltaTime
     */
    VariableSystem(Registry &registry, float &deltaTime): System(registry), mDeltaTime(deltaTime){} 

protected:
    ///Frame deltaTime
    float &mDeltaTime;
};
}
}
