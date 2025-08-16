#include "TenshiEngine/Engine/Systems/InputSystem.hpp"

namespace te{
namespace systems{

InputSystem::InputSystem(Registry &registry) : System(registry, "InputSystem"),
    keys{{InputType::KEYBOARD, "W", "up"}, 
         {InputType::KEYBOARD, "S", "down"},
         {InputType::KEYBOARD, "A", "left"},
         {InputType::KEYBOARD, "D", "right"},
         {InputType::KEYBOARD, "Space", "jump"},
         {InputType::KEYBOARD, "LShift", "sprint"},
         {InputType::KEYBOARD, "LControl", "crouch"},
         {InputType::MOUSE, "MouseButtonLeft", "attack"}}{
    for(auto &key: keys){
        key.keyCode = keyNameToCode(key.keyName);
    }
}  

void InputSystem::update(){
    const auto &entityIDs = mRegistry.view<components::PlayerInputComponent>();
    for(auto entityID : entityIDs){
        for(auto key : keys)
            keyPressed(key, entityID);
    }
}

void InputSystem::keyPressed(Key &key, EntityID entityID){
    components::PlayerInputComponent *component = mRegistry.getComponent<components::PlayerInputComponent>(entityID);
    if(key.inputType == InputType::MOUSE){
        sf::Mouse::Button mouseButton = static_cast<sf::Mouse::Button>(key.keyCode);
        if(sf::Mouse::isButtonPressed(mouseButton)){
            updateComponent(key.keyBind, component, entityID);
        }
    } else if(key.inputType == InputType::KEYBOARD){ 
        sf::Keyboard::Key keyboardKey = static_cast<sf::Keyboard::Key>(key.keyCode);
        if(sf::Keyboard::isKeyPressed(keyboardKey)){
            updateComponent(key.keyBind, component, entityID);
        }
    }
}

uint8_t InputSystem::keyNameToCode(std::string &keyName){
    if(keyName == "W")
        return static_cast<uint8_t>(sf::Keyboard::Key::W);
    else if(keyName == "S")
        return static_cast<uint8_t>(sf::Keyboard::Key::S);
    else if(keyName == "A")
        return static_cast<uint8_t>(sf::Keyboard::Key::A);
    else if(keyName == "D")
        return static_cast<uint8_t>(sf::Keyboard::Key::D);
    else if(keyName == "Space")
        return static_cast<uint8_t>(sf::Keyboard::Key::Space);
    else if(keyName == "LShift")
        return static_cast<uint8_t>(sf::Keyboard::Key::LShift);
    else if(keyName == "LControl")
        return static_cast<uint8_t>(sf::Keyboard::Key::LControl);
    else if(keyName == "MouseButtonLeft")
        return static_cast<uint8_t>(sf::Mouse::Button::Left);
    return 0;
}

void InputSystem::updateComponent(std::string &keyBind, components::PlayerInputComponent *component, EntityID entityID){
    if(keyBind == "up" && !component->up)
        component->up = true;
    else if(keyBind == "down" && !component->down)
        component->down = true;
    else if(keyBind == "left" && !component->left)
        component->left = true;
    else if(keyBind == "right" && !component->right)
        component->right = true;
    else if(keyBind == "jump" && !component->jump)
        component->jump = true;
    else if(keyBind == "sprint" && !component->sprint)
        component->sprint = true;
    else if(keyBind == "crouch" && !component->crouch)
        component->crouch = true;
    else if(keyBind == "attack" && !component->attack)
        component->attack = true;
    else return;

    LOG_DEBUG(mName, component->name  + " changed for Entity " + std::to_string(entityID) + " " + component->toString());
}
    
}   
}   
    
    
