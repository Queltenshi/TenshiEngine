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

}
}
