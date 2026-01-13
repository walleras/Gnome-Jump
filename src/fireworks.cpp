#include "fireworks.h"

// Define static member
std::vector<firework*> firework::fireworkVector;

void firework::create(int maxX, int minX, int maxY, int minY) {
    firework* fw = new firework();

    FireworkColor fireworkColor;
    fireworkColor = getRandomFireworkColor();;
    fw->hasExploded = false;
    sf::Texture* texture = nullptr;

    switch(fireworkColor) {
        case FireworkColor::ORANGE:
            fw->ssdata = getFireworkData(FireworkType::ROCKET_ORANGE);
            texture = &ResourceManager::getTexture(getFireworkTextureName(FireworkType::ROCKET_ORANGE));
            break;
        case FireworkColor::BLUE:
            fw->ssdata = getFireworkData(FireworkType::ROCKET_BLUE);
            texture = &ResourceManager::getTexture(getFireworkTextureName(FireworkType::ROCKET_BLUE));
            break;
        case FireworkColor::GREEN:
            fw->ssdata = getFireworkData(FireworkType::ROCKET_BLUE);
            texture = &ResourceManager::getTexture(getFireworkTextureName(FireworkType::ROCKET_BLUE));
            break;
        default:
            std::cout << "That wasn't supposed to happen. Returned result outside enum." << std::endl;
            break;
    }

    // Set position
    fw->x = fw->randInt(minX, maxX);
    fw->y = fw->randInt(minY, maxY);
    fw->velY = rocket_velocity;
    fw->fuse = fw->randInt(min_fuse, max_fuse);
    fw->fireworkSprite = new sf::Sprite(*texture);
    fw->fireworkSprite->setTextureRect({{fw->textureIterator * fw->ssdata.frameWidth, 0}, {fw->ssdata.frameWidth, fw->ssdata.frameHeight}});
    fw->fireworkSprite->setOrigin({fw->ssdata.frameWidth / 2.0f, fw->ssdata.frameHeight / 2.0f});
    fw->fireworkSprite->setScale({2.0f, 2.0f});
    fw->fireworkSprite->setPosition({fw->x, fw->y});
    fireworkVector.push_back(fw);
}

void firework::update() {
    // Update all fireworks
    for(auto& fw : fireworkVector) {
        if(fw->fuse >= 0 && !fw->hasExploded) {

            fw->y = fw->y + fw->velY;
            fw->fireworkSprite->setPosition({fw->x, fw->y});
            fw->fuse--;

            fw->textureIterator++;

        } else {
            // Explosion phase
            if(!fw->hasExploded) {
                FireworkExplosion explosionType = getRandomFireworkExplosion();
                FireworkColor color = getRandomFireworkColor();
                fw->hasExploded = true;
                fw->textureIterator = 1;

                switch(explosionType) {
                    case FireworkExplosion::CRYSTAL:
                        switch(color) {
                            case FireworkColor::ORANGE:
                                fw->currentType = FireworkType::EXPLOSION_CRYSTALS_ORANGE;
                                break;
                            case FireworkColor::BLUE:
                                fw->currentType = FireworkType::EXPLOSION_CRYSTALS_BLUE;
                                break;
                            case FireworkColor::GREEN:
                                fw->currentType = FireworkType::EXPLOSION_CRYSTALS_GREEN;
                                break;
                        }
                        break;

                    case FireworkExplosion::DEFAULT:
                        switch(color) {
                            case FireworkColor::ORANGE:
                                fw->currentType = FireworkType::EXPLOSION_DEFAULT_ORANGE;
                                break;
                            case FireworkColor::BLUE:
                                fw->currentType = FireworkType::EXPLOSION_DEFAULT_BLUE;
                                break;
                            case FireworkColor::GREEN:
                                fw->currentType = FireworkType::EXPLOSION_DEFAULT_GREEN;
                                break;
                        }
                        break;

                    case FireworkExplosion::LONG:
                        switch(color) {
                            case FireworkColor::ORANGE:
                                fw->currentType = FireworkType::EXPLOSION_LONG_ORANGE;
                                break;
                            case FireworkColor::BLUE:
                                fw->currentType = FireworkType::EXPLOSION_LONG_BLUE;
                                break;
                            case FireworkColor::GREEN:
                                fw->currentType = FireworkType::EXPLOSION_LONG_GREEN;
                                break;
                        }
                        break;
                }

                // Get sprite sheet data and texture for explosion
                fw->ssdata = getFireworkData(fw->currentType);
                sf::Texture& texture = ResourceManager::getTexture(getFireworkTextureName(fw->currentType));
                delete fw->fireworkSprite;
                fw->fireworkSprite = new sf::Sprite(texture);
                fw->fireworkSprite->setTextureRect({{fw->textureIterator * fw->ssdata.frameWidth, 0}, {fw->ssdata.frameWidth, fw->ssdata.frameHeight}});
                fw->fireworkSprite->setOrigin({fw->ssdata.frameWidth / 2.0f, fw->ssdata.frameHeight / 2.0f});
                fw->fireworkSprite->setScale({2.0f, 2.0f});
                fw->fireworkSprite->setPosition({fw->x, fw->y});
            } else {
                fw->textureIterator++;
            }
        }
    }

    // Remove finished fireworks
    for(auto it = fireworkVector.begin(); it != fireworkVector.end();) {
        if((*it)->isFinished()) {
            delete (*it)->fireworkSprite;
            delete *it;
            it = fireworkVector.erase(it);
        } else {
            ++it;
        }
    }
}

void firework::render(sf::RenderWindow &window) {
    for(auto& fw : fireworkVector) {
        if(fw->textureIterator > fw->ssdata.frameCount) {
            fw->textureIterator = 1;
        }
        fw->fireworkSprite->setTextureRect({{fw->textureIterator * fw->ssdata.frameWidth, 0}, {fw->ssdata.frameWidth, fw->ssdata.frameHeight}});
        window.draw(*fw->fireworkSprite);
    }
}
