#pragma  once

#include "TenshiEngine/Engine/Entity/Entity.hpp"
#include <SFML/Graphics/View.hpp>
#include <string>

namespace te{

/**
 * @brief Camera with current view
 *
 * stores the current view which is attached to a entity
 */
struct Camera{
public:
    enum class Movement{HORIZONTAL, VERTICAL, FREE};

    /**
     * @brief Constructor
     *
     * creates the camera with given position, size, entityID and
     * sets movement direction to default (Horizontal)
     *
     * @param position Position for the camera
     * @param size Size for the camera
     * @param entityID ID of attached entity
     */
    Camera(sf::Vector2f position, sf::Vector2f size, EntityID entityID)
        : entityID(entityID), position(position), size(size), view(position, size), movement(Movement::HORIZONTAL){}

    /**
     * @brief Constructor
     *
     * creates the camera with given position, size, entityID, movement
     *
     * @param position Position for the camera
     * @param size Size for the camera
     * @param entityID ID of attached entity
     * @param movement Movement direction of camera
     */
    Camera(sf::Vector2f position, sf::Vector2f size, EntityID entityID, Movement movement)
        : entityID(entityID), position(position), size(size), view(position, size), movement(movement){}

    /**
     * @brief shows data as a string
     *
     * converts the data into a string,
     */
    std::string toString() const{
        return "(position.x: " + std::to_string(position.x) + " | " +
               "position.y: " + std::to_string(position.y) + " | " +
               "size.x: " + std::to_string(size.x) + " | " +
               "size.y: " + std::to_string(size.y) + " | " +
               "Entity: " + std::to_string(entityID) + " | " +
               "movement: " + MovementToString(movement) + ")";
    };

    ///Attached entityID
    EntityID entityID;

    ///Position of camera
    sf::Vector2f position;

    ///Size of camera
    sf::Vector2f size;

    ///View of camera
    sf::View view;

    ///Movement direction of camera
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
