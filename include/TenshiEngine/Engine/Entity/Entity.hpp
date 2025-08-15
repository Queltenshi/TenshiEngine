#pragma once

#include <cstdint>

namespace te{

using EntityID = std::uint32_t;

class Registry;

struct Entity{
private:
    explicit Entity(EntityID id): id(id){} 

public:
    Entity() = default;

    EntityID id;
    
    friend class Registry;
};

}
