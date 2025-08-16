#pragma once

#include "TenshiEngine/Engine/Entity/Entity.hpp"
#include <string>

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
     * Creates a system with given name
     *
     * @param registry reference to the Registry
     * @param name name of the System
     */
    System(Registry &registry, std::string name): 
        mRegistry(registry), mName(name){}

    /**
     * @brief updates the system
     *
     * Used for updating and handling the logic,
     * systems do override this method
     */
    virtual void update() = 0;

protected:
    Registry &mRegistry;
    std::string mName;
};

}
}
