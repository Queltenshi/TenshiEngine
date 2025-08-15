#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>
#include <typeindex>
#include <memory>
#include <vector>
#include "TenshiEngine/Engine/Entity/Entity.hpp"
#include "TenshiEngine/Engine/Components/Components.hpp"
#include "TenshiEngine/Engine/Core/Logger.hpp"
#include "TenshiEngine/Engine/Systems/System.hpp"

namespace te{

class Registry{
public:
    Registry(): mNextId(0){}

    Entity createEntity(sf::Texture &texture){
        Entity entity(mNextId++);
        addComponent(entity.id, components::SpriteComponent(texture));
        addComponent(entity.id, components::TransformComponent());
        return entity;
    }

    template<typename Component>
    void addComponent(EntityID entityID, const Component &component){
        mComponents[typeid(Component)][entityID] = std::make_shared<Component>(component);

        //Debug Info
        if(Logger::currentLevel == LogLevel::DEBUG){
            Logger::debug("Registry", component.name()  + " added to Entity " + std::to_string(entityID) + " " + component.toString());
        }
    }

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

    /*template<typename Component>
    void UpdateComponent(const std::string &systemName, EntityID entityID, Component& newComponent) {
        Component *currentComponent = getComponent<Component>(entityID);
        if (currentComponent != &newComponent) {
            currentComponent = &newComponent;

            //Debug Info
            LOG_DEBUG(systemName, newComponent.name()  + " changed for Entity " + std::to_string(entityID) + " " + newComponent.toString());
        }
    }*/

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

    template<typename TSystem, typename... Args>
    void addSystem(Args&&... args) {
        auto system = std::make_unique<TSystem>(*this, std::forward<Args>(args)...);
        mSystems.push_back(std::move(system));
    }

    void updateSystems() {
        for (auto& system : mSystems) {
            system->update();
        }
    }


private:
    EntityID mNextId;
    std::unordered_map<std::type_index, std::unordered_map<EntityID, std::shared_ptr<void>>> mComponents;
    std::vector<std::unique_ptr<systems::System>> mSystems;
};

}
