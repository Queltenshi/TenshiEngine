#include "TenshiEngine/Engine/Core/Registry.hpp"
#include <memory>

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
     * Steering, HorizontalMovement, Jump, Velocity, Grounded, Rigidbody, Collider
     *
     * @param registry Registry
     * @param texture Texture to display
     */
    static Entity PlatformerPlayer(Registry &registry, std::shared_ptr<sf::Texture> texture){
        Entity entity = registry.createEntity(texture);
        registry.addComponent(entity.id, components::Steering());
        registry.addComponent(entity.id, components::HorizontalMovement());
        registry.addComponent(entity.id, components::Jump());
        registry.addComponent(entity.id, components::Velocity());
        registry.addComponent(entity.id, components::Grounded());
        registry.addComponent(entity.id, components::Rigidbody());
        auto sprite = registry.getComponent<components::Sprite>(entity.id);
        auto spriteSize = sprite->sprite.getGlobalBounds().size;
        registry.addComponent(entity.id, components::Collider(spriteSize));
        return entity;
    }
    /**
     * @brief creates platformer player with animation
     *
     * creates new entity with given texture and animationData and adds
     * Steering, HorizontalMovement, Jump, Velocity, Grounded, Rigidbody, Collider
     *
     * @param registry Registry
     * @param texture Texture to display
     * @param animationData json data used for animation
     */
    static Entity PlatformerPlayer(Registry &registry, std::shared_ptr<sf::Texture> texture, std::shared_ptr<json> animationData){
        Entity entity = registry.createEntity(texture, animationData);
        registry.addComponent(entity.id, components::Steering());
        registry.addComponent(entity.id, components::HorizontalMovement());
        registry.addComponent(entity.id, components::Jump());
        registry.addComponent(entity.id, components::Velocity());
        registry.addComponent(entity.id, components::Grounded());
        registry.addComponent(entity.id, components::Rigidbody());
        auto sprite = registry.getComponent<components::Sprite>(entity.id);
        auto spriteSize = sprite->sprite.getGlobalBounds().size;
        registry.addComponent(entity.id, components::Collider(spriteSize));
        return entity;
    }
};

}
