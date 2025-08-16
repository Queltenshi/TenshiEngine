#pragma once

#include <cstdint>

namespace te{

using EntityID = std::uint32_t;

class Registry;

///Entity
struct Entity{
private:
    explicit Entity(EntityID id): id(id){} 

public:
    Entity() = default;

    ///ID of the Entity
    EntityID id;
    
    friend class Registry;
};

}
