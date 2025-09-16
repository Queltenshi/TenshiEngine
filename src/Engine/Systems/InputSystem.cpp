#include "TenshiEngine/Engine/Systems/InputSystem.hpp"

namespace te{
namespace systems{

InputSystem::InputSystem(Registry &registry, float &deltaTime, std::unordered_map<Action, Key> configKeyBinds) : VariableSystem(registry, deltaTime){
    for(auto configKeyBind : configKeyBinds){
        auto action = configKeyBind.first;
        auto key = configKeyBind.second;
        if(key == Key::MOUSE_LEFT || key == Key::MOUSE_RIGHT){
            KeyBind keyBind(InputType::MOUSE, action, key);
            keyBinds.push_back(keyBind);
        }
        else{
            KeyBind keyBind(InputType::KEYBOARD, action, key);
            keyBinds.push_back(keyBind);
        }
    }

    for(auto &keyBind: keyBinds){
        keyBind.keyCode = keyToCode(keyBind.key);
    }
}  

void InputSystem::update(){
    const auto &entityIDs = mRegistry.view<components::Steering>();
    for(auto entityID : entityIDs){
        for(auto &keyBind : keyBinds)
            keyPressed(keyBind, entityID);
    }
}

void InputSystem::keyPressed(KeyBind &keyBind, EntityID entityID){
    components::Steering *component = mRegistry.getComponent<components::Steering>(entityID);
    if(keyBind.inputType == InputType::MOUSE){
        sf::Mouse::Button mouseButton = static_cast<sf::Mouse::Button>(keyBind.keyCode);
        if(sf::Mouse::isButtonPressed(mouseButton)){
            updateSteering(keyBind.action, component, entityID);
        }
    } else if(keyBind.inputType == InputType::KEYBOARD){ 
        sf::Keyboard::Key keyboardKey = static_cast<sf::Keyboard::Key>(keyBind.keyCode);
        if(sf::Keyboard::isKeyPressed(keyboardKey)){
            updateSteering(keyBind.action, component, entityID);
        }
    }
}

uint8_t InputSystem::keyToCode(Key key){
    if(key == Key::Q)
        return static_cast<uint8_t>(sf::Keyboard::Key::Q);
    else if(key == Key::W)
        return static_cast<uint8_t>(sf::Keyboard::Key::W);
    else if(key == Key::E)
        return static_cast<uint8_t>(sf::Keyboard::Key::E);
    else if(key == Key::R)
        return static_cast<uint8_t>(sf::Keyboard::Key::R);
    else if(key == Key::T)
        return static_cast<uint8_t>(sf::Keyboard::Key::T);
    else if(key == Key::Z)
        return static_cast<uint8_t>(sf::Keyboard::Key::Z);
    else if(key == Key::U)
        return static_cast<uint8_t>(sf::Keyboard::Key::U);
    else if(key == Key::I)
        return static_cast<uint8_t>(sf::Keyboard::Key::I);
    else if(key == Key::O)
        return static_cast<uint8_t>(sf::Keyboard::Key::O);
    else if(key == Key::P)
        return static_cast<uint8_t>(sf::Keyboard::Key::P);
    else if(key == Key::A)
        return static_cast<uint8_t>(sf::Keyboard::Key::A);
    else if(key == Key::S)
        return static_cast<uint8_t>(sf::Keyboard::Key::S);
    else if(key == Key::D)
        return static_cast<uint8_t>(sf::Keyboard::Key::D);
    else if(key == Key::F)
        return static_cast<uint8_t>(sf::Keyboard::Key::F);
    else if(key == Key::G)
        return static_cast<uint8_t>(sf::Keyboard::Key::G);
    else if(key == Key::H)
        return static_cast<uint8_t>(sf::Keyboard::Key::H);
    else if(key == Key::J)
        return static_cast<uint8_t>(sf::Keyboard::Key::J);
    else if(key == Key::K)
        return static_cast<uint8_t>(sf::Keyboard::Key::K);
    else if(key == Key::L)
        return static_cast<uint8_t>(sf::Keyboard::Key::L);
    else if(key == Key::Y)
        return static_cast<uint8_t>(sf::Keyboard::Key::Y);
    else if(key == Key::X)
        return static_cast<uint8_t>(sf::Keyboard::Key::X);
    else if(key == Key::C)
        return static_cast<uint8_t>(sf::Keyboard::Key::C);
    else if(key == Key::V)
        return static_cast<uint8_t>(sf::Keyboard::Key::V);
    else if(key == Key::B)
        return static_cast<uint8_t>(sf::Keyboard::Key::B);
    else if(key == Key::N)
        return static_cast<uint8_t>(sf::Keyboard::Key::N);
    else if(key == Key::M)
        return static_cast<uint8_t>(sf::Keyboard::Key::M);
    else if(key == Key::NUM0)
        return static_cast<uint8_t>(sf::Keyboard::Key::Num0);
    else if(key == Key::NUM1)
        return static_cast<uint8_t>(sf::Keyboard::Key::Num1);
    else if(key == Key::NUM2)
        return static_cast<uint8_t>(sf::Keyboard::Key::Num2);
    else if(key == Key::NUM3)
        return static_cast<uint8_t>(sf::Keyboard::Key::Num3);
    else if(key == Key::NUM4)
        return static_cast<uint8_t>(sf::Keyboard::Key::Num4);
    else if(key == Key::NUM5)
        return static_cast<uint8_t>(sf::Keyboard::Key::Num5);
    else if(key == Key::NUM6)
        return static_cast<uint8_t>(sf::Keyboard::Key::Num6);
    else if(key == Key::NUM7)
        return static_cast<uint8_t>(sf::Keyboard::Key::Num7);
    else if(key == Key::NUM8)
        return static_cast<uint8_t>(sf::Keyboard::Key::Num8);
    else if(key == Key::NUM9)
        return static_cast<uint8_t>(sf::Keyboard::Key::Num9);
    else if(key == Key::SPACE)
        return static_cast<uint8_t>(sf::Keyboard::Key::Space);
    else if(key == Key::L_SHIFT)
        return static_cast<uint8_t>(sf::Keyboard::Key::LShift);
    else if(key == Key::L_CONTROL)
        return static_cast<uint8_t>(sf::Keyboard::Key::LControl);
    else if(key == Key::MOUSE_LEFT)
        return static_cast<uint8_t>(sf::Mouse::Button::Left);
    else if(key == Key::MOUSE_RIGHT)
        return static_cast<uint8_t>(sf::Mouse::Button::Right);
    return 0;
}

void InputSystem::updateSteering(Action &action, components::Steering *steering, EntityID entityID){
    if(action == Action::MOVELEFT && !steering->left)
        steering->left = true;
    else if(action == Action::MOVERIGHT && !steering->right)
        steering->right = true;
    if(action == Action::JUMP && !steering->jump)
        steering->jump = true;
    if(action == Action::SPRINT && !steering->sprint)
        steering->sprint = true;
    else if(action == Action::CROUCH && !steering->crouch)
        steering->crouch = true;
    if(action == Action::ATTACK && !steering->attack)
        steering->attack = true;
}
    
const std::string InputSystem::name = "InputSystem";

}   
}   
    
    
