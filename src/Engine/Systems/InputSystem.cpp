#include "TenshiEngine/Engine/Systems/InputSystem.hpp"

namespace te{
namespace systems{

InputSystem::InputSystem(Registry &registry, float &deltaTime) : VariableSystem(registry, deltaTime),
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
    const auto &entityIDs = mRegistry.view<components::PlayerInput>();
    for(auto entityID : entityIDs){
        for(auto &key : keys)
            keyPressed(key, entityID);
    }
}

void InputSystem::keyPressed(Key &key, EntityID entityID){
    components::PlayerInput *component = mRegistry.getComponent<components::PlayerInput>(entityID);
    if(key.inputType == InputType::MOUSE){
        sf::Mouse::Button mouseButton = static_cast<sf::Mouse::Button>(key.keyCode);
        if(sf::Mouse::isButtonPressed(mouseButton)){
            updatePlayerInput(key.keyBind, component, entityID);
        }
    } else if(key.inputType == InputType::KEYBOARD){ 
        sf::Keyboard::Key keyboardKey = static_cast<sf::Keyboard::Key>(key.keyCode);
        if(sf::Keyboard::isKeyPressed(keyboardKey)){
            updatePlayerInput(key.keyBind, component, entityID);
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

void InputSystem::updatePlayerInput(std::string &keyBind, components::PlayerInput *inputComponent, EntityID entityID){
    if(keyBind == "up" && !inputComponent->up)
        inputComponent->up = true;
    else if(keyBind == "down" && !inputComponent->down)
        inputComponent->down = true;
    if(keyBind == "left" && !inputComponent->left)
        inputComponent->left = true;
    else if(keyBind == "right" && !inputComponent->right)
        inputComponent->right = true;
    if(keyBind == "jump" && !inputComponent->jump)
        inputComponent->jump = true;
    if(keyBind == "sprint" && !inputComponent->sprint)
        inputComponent->sprint = true;
    else if(keyBind == "crouch" && !inputComponent->crouch)
        inputComponent->crouch = true;
    if(keyBind == "attack" && !inputComponent->attack)
        inputComponent->attack = true;
}
    
const std::string InputSystem::name = "InputSystem";

}   
}   
    
    
