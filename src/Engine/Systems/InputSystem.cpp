#include "TenshiEngine/Engine/Systems/InputSystem.hpp"

namespace te{
namespace systems{

InputSystem::InputSystem(Registry &registry) : System(registry, "InputSystem"),
    playerUp(InputType::KEYBOARD, "W", "up"),
    playerDown(InputType::KEYBOARD, "S", "down"),
    playerLeft(InputType::KEYBOARD, "A", "left"),
    playerRight(InputType::KEYBOARD, "D", "right"),
    playerJump(InputType::KEYBOARD, "Space", "jump"),
    playerSprint(InputType::KEYBOARD, "LShift", "sprint"),
    playerCrouch(InputType::KEYBOARD, "LControl", "crouch"),
    playerAttack(InputType::MOUSE, "MouseButtonLeft", "attack"),
    keys{&playerUp, &playerDown, &playerLeft, &playerRight, &playerJump, &playerSprint, &playerCrouch, &playerAttack}{
}  

void InputSystem::update(){
    const auto &entityIDs = mRegistry.view<components::PlayerInputComponent>();
    for(auto entityID : entityIDs){
        for(auto key : keys)
            keyPressed(*key, entityID);
    }
}

void InputSystem::keyPressed(Key &key, EntityID entityID){
    components::PlayerInputComponent *component = mRegistry.getComponent<components::PlayerInputComponent>(entityID);
    if(key.inputType == InputType::MOUSE){
        sf::Mouse::Button mouseButton = static_cast<sf::Mouse::Button>(keyNameToCode(key.keyName));
        if(sf::Mouse::isButtonPressed(mouseButton)){
            updateComponent(key.keyBind, component, entityID);
        }
    } else if(key.inputType == InputType::KEYBOARD){ 
        sf::Keyboard::Key keyboardKey = static_cast<sf::Keyboard::Key>(keyNameToCode(key.keyName));
        if(sf::Keyboard::isKeyPressed(keyboardKey)){
            updateComponent(key.keyBind, component, entityID);
        }
    } else LOG_DEBUG(mName, "Unknown InputType");
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

    LOG_DEBUG(mName, "Unknown KeyName");
    return 0;
}

void InputSystem::updateComponent(std::string &keyBind, components::PlayerInputComponent *component, EntityID entityID){
    if(keyBind == "up" && component->up == false)
        component->up = true;
    else if(keyBind == "down" && component->down == false)
        component->down = true;
    else if(keyBind == "left" && component->left == false)
        component->left = true;
    else if(keyBind == "right" && component->right == false)
        component->right = true;
    else if(keyBind == "jump" && component->jump == false)
        component->jump = true;
    else if(keyBind == "sprint" && component->sprint == false)
        component->sprint = true;
    else if(keyBind == "crouch" && component->crouch == false)
        component->crouch = true;
    else if(keyBind == "attack" && component->attack == false)
        component->attack = true;
    else return;

    LOG_DEBUG(mName, component->name()  + " changed for Entity " + std::to_string(entityID) + " " + component->toString());
}
    
}   
}   
    
    
