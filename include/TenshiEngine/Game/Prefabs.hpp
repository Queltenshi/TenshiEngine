#include "TenshiEngine/Engine/Core/Registry.hpp"

namespace te{

/**
 * @brief Creating entities with prefabs
 *
 * Creates entities through different prefabs with predefined components
 */
class Prefabs{
public:
    Prefabs()=delete;
    Prefabs(const Prefabs&)=delete;
    Prefabs(Prefabs&&)=delete; 

    /**
     * @brief creates platformer player
     *
     * creates new entity with given texture and adds
     * PlayerInput, HorizontalMovement, Jump, Velocity, Grounded, Rigidbody
     *
     * @param registry Registry
     * @param texture Texture to display
     */
    static Entity PlatformerPlayer(Registry &registry, sf::Texture &texture){
        Entity entity = registry.createEntity(texture);
        registry.addComponent(entity.id, components::PlayerInput());
        registry.addComponent(entity.id, components::HorizontalMovement());
        registry.addComponent(entity.id, components::Jump());
        registry.addComponent(entity.id, components::Velocity());
        registry.addComponent(entity.id, components::Grounded());
        registry.addComponent(entity.id, components::Rigidbody());
        return entity;
    }
    /**
     * @brief creates platformer player with animation
     *
     * creates new entity with given texture and textureData and adds
     * PlayerInput, HorizontalMovement, Jump, Velocity, Grounded, Rigidbody
     *
     * @param registry Registry
     * @param texture Texture to display
     * @param textureData json data used for animation
     */
    static Entity PlatformerPlayer(Registry &registry, sf::Texture &texture, json &textureData){
        Entity entity = registry.createEntity(texture, textureData);
        registry.addComponent(entity.id, components::PlayerInput());
        registry.addComponent(entity.id, components::HorizontalMovement());
        registry.addComponent(entity.id, components::Jump());
        registry.addComponent(entity.id, components::Velocity());
        registry.addComponent(entity.id, components::Grounded());
        registry.addComponent(entity.id, components::Rigidbody());
        return entity;
    }
};

}
