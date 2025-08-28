#pragma once

#include "TenshiEngine/Engine/Components/Component.hpp"
#include <SFML/System/Vector2.hpp>

namespace te{
namespace components{

/**
 * @brief component with size
 *
 * stores the size used for colliding
 */
struct Collider : public Component{
public:
    /**
     * @brief Default Constructor
     *
     * creates the component with given size
     *
     * @param size size of collider
     */
    Collider(sf::Vector2f size): size(size){}

    std::string toString() const override{
        return "(size.x: " + std::to_string(size.x) + " | " +
               "size.y: " + std::to_string(size.y) + ")";
    };

    //Size of collider
    sf::Vector2f size; 

    ///Name of component
    inline static const std::string name = "Collider";
};

}
}
