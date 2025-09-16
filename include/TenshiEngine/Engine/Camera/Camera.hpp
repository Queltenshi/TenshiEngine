#pragma  once

#include "TenshiEngine/Engine/Entity/Entity.hpp"
#include <SFML/Graphics/View.hpp>
#include <string>

namespace te{

struct Camera{
public:
    enum class Movement{HORIZONTAL, VERTICAL, FREE};

    Camera(sf::Vector2f position, sf::Vector2f size, EntityID entityID)
        : entityID(entityID), position(position), size(size), view(position, size), movement(Movement::HORIZONTAL){}

    Camera(sf::Vector2f position, sf::Vector2f size, EntityID entityID, Movement movement)
        : entityID(entityID), position(position), size(size), view(position, size), movement(movement){}

    std::string toString() const{
        return "(position.x: " + std::to_string(position.x) + " | " +
               "position.y: " + std::to_string(position.y) + " | " +
               "size.x: " + std::to_string(size.x) + " | " +
               "size.y: " + std::to_string(size.y) + " | " +
               "Entity: " + std::to_string(entityID) + " | " +
               "movement: " + MovementToString(movement) + ")";
    };

    EntityID entityID;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::View view;
    Movement movement;

private:
    static std::string MovementToString(Movement movement) {
        switch (movement) {
            case Movement::HORIZONTAL: return "HORIZONTAL";
            case Movement::VERTICAL:  return "VERTICAL";
            case Movement::FREE:  return "FREE";
            default: return "UNKNOWN";
        }
    }
};

}
