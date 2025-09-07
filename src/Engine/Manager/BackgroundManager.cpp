#include "TenshiEngine/Engine/Manager/BackgroundManager.hpp"

namespace te{
namespace managers{

BackgroundManager::BackgroundManager(std::shared_ptr<sf::Texture> defaultTexture, sf::Vector2f windowSize)
    : mWindowSize(windowSize), mTexture(std::move(defaultTexture)), mBackground(*mTexture), mParallaxFactor(0.f){

    mBackground.setScale(changeScale());

    Logger::info(name, "Default background created");
}

void BackgroundManager::setBackground(std::shared_ptr<sf::Texture> texture){
    mTexture = std::move(texture);

    mBackground.setTexture(*mTexture, true);
    mBackground.setScale(changeScale());

    LOG_DEBUG(name, "Background changed");
}

void BackgroundManager::setBackground(std::shared_ptr<sf::Texture> texture, float parallaxFactor){
    mParallaxFactor = parallaxFactor;

    if(mParallaxFactor == 0){
        setBackground(std::move(texture));
        return;
    }

    mTexture = std::move(texture);
    mTexture->setRepeated(true);

    mBackground.setTexture(*mTexture, true);
    sf::IntRect textureRect({0, 0}, static_cast<sf::Vector2i>(mTexture->getSize())*2);
    mBackground.setTextureRect(textureRect);
    mBackground.setScale(changeScale() * 2.f);

    LOG_DEBUG(name, "Background changed");
}

sf::Sprite &BackgroundManager::getBackground(){
    return mBackground;
}

void BackgroundManager::update(sf::Vector2f &move){
    if(mParallaxFactor == 0){
        return;
    }

    mBackground.move(move * mParallaxFactor);

    auto size = mBackground.getGlobalBounds().size;
    if(0 < mBackground.getPosition().x){
        mBackground.move({-size.x/2, 0.f});
    }
    else if(mBackground.getPosition().x < -size.x/2){
        mBackground.move({size.x/2, 0.f});
    }

    if(0 < mBackground.getPosition().y){
        mBackground.move({0.f, -size.y/2});
    }
    else if(mBackground.getPosition().y < -size.y/2){
        mBackground.move({0.f, size.y/2});
    }
}

sf::Vector2f BackgroundManager::changeScale(){
    float scale = mWindowSize.x / mBackground.getLocalBounds().size.x;
    if(mWindowSize.y > mBackground.getLocalBounds().size.y * scale){
        scale = mWindowSize.y / mBackground.getLocalBounds().size.y;
    }

    return {scale, scale};
}

const std::string BackgroundManager::name = "BackgroundManager";

}
}
