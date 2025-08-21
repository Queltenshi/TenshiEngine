#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <utility>
#include <vector>
#include "TenshiEngine/Engine/Entity/Entity.hpp"
#include "TenshiEngine/Components.hpp"
#include "TenshiEngine/Engine/Core/Logger.hpp"
#include "TenshiEngine/Engine/Systems/System.hpp"
#include "TenshiEngine/Engine/Systems/RenderSystem.hpp"

namespace te{

namespace systems{struct RenderSystem;}

/**
 * @brief Managing entities and components
 *
 * Creates entities, adds components,
 * shows components and entities,
 * adds systems, update systems
 */
class Registry{
public:

    /** @brief Constructor
     *  
     *  @param mNextId used for automatically adding IDs to entities
     */
    Registry(): mNextId(0){}

    /**
     * @brief creates new entity
     *
     * creates new entity with given texture and adds
     * new ID, transform, sprite and rigidbody
     *
     * @param texture Texture to display
     */
    Entity createEntity(sf::Texture &texture){
        Entity entity(mNextId++);
        addComponent(entity.id, components::Sprite(texture));
        addComponent(entity.id, components::Transform(getComponent<components::Sprite>(entity.id)->sprite.getGlobalBounds().size));
        addComponent(entity.id, components::Rigidbody());
        return entity;
    }

    /**
     * @brief creates new entity
     *
     * creates new entity with given texture, scale and adds
     * new ID, transform, sprite and rigidbody
     *
     * @param texture Texture to display
     * @param scale scaling of sprite
     */
    Entity createEntity(sf::Texture &texture, sf::Vector2f scale){
        Entity entity(mNextId++);
        addComponent(entity.id, components::Sprite(texture));
        addComponent(entity.id, components::Transform(getComponent<components::Sprite>(entity.id)->sprite.getGlobalBounds().size, scale));
        addComponent(entity.id, components::Rigidbody());
        return entity;
    }

    /**
     * @brief adds new component
     *
     * adds new component to given entityID
     *
     * @param entityID ID of entity
     * @param component component to add
     */
    template<typename Component>
    void addComponent(EntityID entityID, const Component &component){
        mComponents[typeid(Component)][entityID] = std::make_shared<Component>(component);

        //Debug Info
        if(Logger::currentLevel == LogLevel::DEBUG){
            Logger::debug("Registry", component.name  + " added to Entity " + std::to_string(entityID) + " " + component.toString());
        }
    }

    /**
     * @brief shows component of entity
     *
     * shows the specified component of a given entityID
     *
     * @param entityID ID of entity
     */
    template<typename Component>
    Component* getComponent(EntityID entityID){
        auto it = mComponents.find(typeid(Component));
        if(it != mComponents.end()){
            auto entityIt = it->second.find(entityID);
            if(entityIt != it->second.end()){
                return std::static_pointer_cast<Component>(entityIt->second).get();
            }
        }
        return nullptr;
    }

    /**
     * @brief shows if entity has a component
     *
     * shows if the given entity has the specified component
     *
     * @param entityID ID of entity
     */
    template<typename Component>
    bool hasComponent(EntityID entityID) const{
        auto it = mComponents.find(typeid(Component));
        return it != mComponents.end() && it->second.count(entityID) > 0;
    }

    /**
     * @brief Lists entities
     *
     * lists entities with specified components
     */
    template<typename... Components>
    std::vector<EntityID> view(){
        std::vector<EntityID> result;
        if(sizeof...(Components) == 0)
            return result;

        using FirstComponent = std::tuple_element_t<0, std::tuple<Components...>>;
        
        auto firstComponentIt = mComponents.find(typeid(FirstComponent));
        if (firstComponentIt == mComponents.end())
                return result;

        const auto& firstComponentEntities = firstComponentIt->second;

        for (const auto& [entityId, _] : firstComponentEntities) {
            bool hasAll = (... && (mComponents[typeid(Components)].count(entityId) > 0));
            if (hasAll)
                result.push_back(entityId);
        }

        return result;
    }

    /** 
     * @brief adds system
     *
     * adds new system
     *
     * @param args arguments of the specified system to create
     */
    template<typename TSystem, typename... Args>
    void addSystem(Args&&... args) {
        if(std::is_same_v<TSystem, systems::RenderSystem>){
            mRenderSystem = std::make_unique<TSystem>(*this, std::forward<Args>(args)...);
        } else{ 
            auto system = std::make_unique<TSystem>(*this, std::forward<Args>(args)...);
            mSystems.push_back(std::move(system));
        }
    }

    /**
     * @brief updates all systems
     *
     * updates all the systems
     */
    void updateSystems() {
        for (auto& system : mSystems) {
            system->update();
        }
    }

    /**
     * @brief updates the render system
     *
     * updates the render system
     */
    void updateRenderSystem(){
        mRenderSystem->update();
    }


private:
    EntityID mNextId;
    std::unordered_map<std::type_index, std::unordered_map<EntityID, std::shared_ptr<void>>> mComponents;
    std::vector<std::unique_ptr<systems::System>> mSystems;
    std::unique_ptr<systems::System> mRenderSystem;
};

}
