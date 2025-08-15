#pragma once

#include "TenshiEngine/Engine/Entity/Entity.hpp"
#include <string>

namespace te{

class Registry;

namespace systems{

class System{
public:    
    System(Registry &registry, std::string name): 
        mRegistry(registry), mName(name){}

    virtual void update() = 0;

protected:
    Registry &mRegistry;
    std::string mName;
};

}
}
