#pragma once

#include <typeindex>
#include "TenshiEngine/Components.hpp"
#include "TenshiEngine/Engine/Systems/System.hpp"

namespace te{

namespace systems{
struct RenderSystem;
}

/**
 * @brief Managing entities and components
 *
 * Creates entities, adds components,
 * shows components and entities,
 * adds systems, update systems
 * Is created automatically in the GameBase
 */
class Registry{
public:

    /** @brief Constructor
     */
    Registry(): mNextId(0){}

    /**
     * @brief creates new entity
     *
     * creates new Entity with given texture and adds
     * new ID, Transform, Sprite
     *
     * @param texture Texture to display
     */
    Entity createEntity(std::shared_ptr<sf::Texture> texture){
        Entity entity(mNextId++);
        addComponent(entity.id, components::Sprite(texture));
        addComponent(entity.id, components::Transform());
        return entity;
    }

    /**
     * @brief creates new entity
     *
     * creates new Entity with given texture and size and adds
     * new ID, Transform, Sprite
     *
     * @param texture Texture to display
     */
    Entity createEntity(std::shared_ptr<sf::Texture> texture, sf::Vector2i size){
        Entity entity(mNextId++);
        sf::IntRect rectangle({0, 0}, size);
        addComponent(entity.id, components::Sprite(texture, rectangle));
        addComponent(entity.id, components::Transform());
        return entity;
    }

    /**
     * @brief creates new entity with animation
     *
     * creates new Entity with given texture and animationData and adds
     * new ID, Transform, Sprite, Animation, State
     *
     * @param texture Texture to display
     * @param animationData json data used for animation
     */
    Entity createEntity(std::shared_ptr<sf::Texture> texture, std::shared_ptr<json> animationData){
        Entity entity(mNextId++);
        auto animation = addComponent(entity.id, components::Animation(animationData));
        addComponent(entity.id, components::Sprite(texture, animation->rectangle));
        addComponent(entity.id, components::Transform());
        addComponent(entity.id, te::components::State());
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
    Component* addComponent(EntityID entityID, const Component &component){
        //LOG_DEBUG(name, component.name  + " added to Entity " + std::to_string(entityID) + " " + component.toString());

        mComponents[typeid(Component)][entityID] = std::make_shared<Component>(component);
        return static_cast<Component*>(mComponents[typeid(Component)][entityID].get());
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
        if constexpr (std::is_same_v<TSystem, systems::RenderSystem>){
            mRenderSystem = std::make_unique<TSystem>(*this, std::forward<Args>(args)...);
        } 
        else if constexpr (std::is_base_of_v<systems::FixedSystem, TSystem>) {
            auto fixedSystem = std::make_unique<TSystem>(*this, std::forward<Args>(args)...);
            mFixedSystems.push_back(std::move(fixedSystem));
        }
        else if constexpr (std::is_base_of_v<systems::VariableSystem, TSystem>) {
            auto variableSystem = std::make_unique<TSystem>(*this, std::forward<Args>(args)...);
            mVariableSystems.push_back(std::move(variableSystem));
        }
    }

    /**
     * @brief updates all fixed systems
     *
     * updates all the fixed systems
     */
    void updateFixedSystems() {
        for (auto& fixedSystem : mFixedSystems) {
            fixedSystem->update();
        }
    }

    /**
     * @brief updates all variable systems
     *
     * updates all the variable systems
     */
    void updateVariableSystems() {
        for (auto& variableSystem : mVariableSystems) {
            variableSystem->update();
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
    std::vector<std::unique_ptr<systems::FixedSystem>> mFixedSystems;
    std::vector<std::unique_ptr<systems::VariableSystem>> mVariableSystems;
    std::unique_ptr<systems::VariableSystem> mRenderSystem;

    inline const static std::string name = "Registry";
};

}
