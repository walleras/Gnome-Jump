#include "GameObjects.h"
#include "resourceManager.h"
#include "game.h"
#include "datatypes.h"

extern float shakeOffsetX;
extern float shakeOffsetY;

Player::Player(sf::Texture& texture, int x, int y) : dude(texture), posX(x), posY(y) {
    bouncy = 1.4;
    momentumY = 1;
    maxMomentum = 10;
    bounce = ResourceManager::getSound("bounce");
    bounceSound.emplace(bounce);
    superbounce = ResourceManager::getSound("superbounce");
    superbounceSound.emplace(superbounce);
    crack = ResourceManager::getSound("crack");
    crackSound.emplace(crack);
}

void Player::move(float mousePosX, vector<Obstacle> obstacles) {
    momentumY = momentumY + ((maxMomentum - momentumY) * 0.1) * gravity;
    sf::FloatRect particleBounds = dude.getGlobalBounds();

    for(auto& obs : obstacles) {
        sf::FloatRect surfBounds = obs.platform.getGlobalBounds();

        if(particleBounds.findIntersection(surfBounds)) {
            float overlapLeft = (particleBounds.position.x + particleBounds.size.x) - surfBounds.position.x;
            float overlapRight = (surfBounds.position.x + surfBounds.size.x) - particleBounds.position.x;
            float overlapTop = (particleBounds.position.y + particleBounds.size.y) - surfBounds.position.y;
            float overlapBottom = (surfBounds.position.y + surfBounds.size.y) - particleBounds.position.y;

            float minOverlapX = min(overlapLeft, overlapRight);
            float minOverlapY = min(overlapTop, overlapBottom);
            if (obs.type == "stable" || obs.type == "island") {
                if (minOverlapY < minOverlapX) {
                    if (overlapTop < overlapBottom && momentumY > 0) {
                        momentumY = -(momentumY * bouncy) - 5;
                        posY -= overlapTop;
                        triggerScreenShake(momentumY);
                        bounceSound->setVolume(30 * (masterVol / 100.0f) * (sfxVol / 100.0f));
                        bounceSound->play();
                        bouncyJumpedOnRow = 0;
                        platformsJumpedOn++;
                    }
                }
            } else if(obs.type == "bouncy") {
                if (minOverlapY < minOverlapX) {
                    if (overlapTop < overlapBottom && momentumY > 0) {
                        momentumY = -(momentumY * bouncy * 3) - 5;
                        posY -= overlapTop;
                        triggerScreenShake(momentumY);
                        superbounceSound->setVolume(100 * (masterVol / 100.0f) * (sfxVol / 100.0f));
                        superbounceSound->play();
                        bouncyJumpedOnRow++;
                        platformsJumpedOn++;
                    }
                }
            } else if(obs.type == "weak") {
                if (minOverlapY < minOverlapX) {
                    if (overlapTop < overlapBottom && momentumY > 0) {
                        momentumY = -(momentumY * bouncy) - 5;
                        posY -= overlapTop;
                        triggerScreenShake(momentumY);
                        bounceSound->setVolume(30 * (masterVol / 100.0f) * (sfxVol / 100.0f));
                        bounceSound->play();
                        crackSound->setVolume(80 * (masterVol / 100.0f) * (sfxVol / 100.0f));
                        crackSound->play();
                        bouncyJumpedOnRow = 0;
                        weakJumpedOn++;
                        platformsJumpedOn++;
                    }
                }
            } else if(obs.type == "breakable") {
                if (minOverlapY < minOverlapX) {
                    if (overlapTop < overlapBottom && momentumY > 0) {
                        triggerScreenShake(momentumY);
                        crackSound->setVolume(80 * (masterVol / 100.0f) * (sfxVol / 100.0f));
                        crackSound->play();
                        bouncyJumpedOnRow = 0;
                        platformsJumpedOn++;
                    }
                }
            }
        }
    }

    posY = posY + momentumY;
    if(posY < 100) {
        scrolly = scrolly + momentumY;
        posY = 100;
    }
    dude.setPosition({static_cast<float>(mousePosX), posY});
}

void Player::draw(sf::RenderWindow& window){
    sf::Vector2f originalPos = dude.getPosition();
    dude.setPosition({originalPos.x + shakeOffsetX, originalPos.y + shakeOffsetY});
    window.draw(dude);
    dude.setPosition(originalPos);
}

Obstacle::Obstacle(float initialScrollY, int initialX, sf::Texture& texture, string obstacleType) : platform(texture), type(obstacleType) {
    x = initialX;
    y = initialScrollY;
    platform.setPosition({x, y});
    locScroll = initialScrollY;
    yDis = 0;
    momentumY = 0;
}

void Obstacle::scroll(float scrolly) {
    y = (locScroll - scrolly) + yDis;
    if(type == "cloud") {
        y = (locScroll - scrolly / 3) + yDis;
    }
    if(type == "star") {
        y = (locScroll - scrolly / 6) + yDis;
    }
    if(type == "birdright") {
        y = (locScroll - scrolly / 1.5) + yDis;
        x = x + 2;
    }
    if(type == "birdleft") {
        y = (locScroll - scrolly / 1.5) + yDis;
        x = x - 2;
    }
    if(type == "hotairballoonright") {
        y = y + 0.5f;
        x = x + 0.5f;
    }
    if(type == "hotairballoonleft") {
        y = y + 0.5f;
        x = x - 0.5f;
    }
    if(type == "asteroid") {
        y =(locScroll - scrolly / 4) + yDis;
    }
    yDis = yDis + momentumY;
    platform.setPosition({x, y});
}

void Obstacle::collide(const Player& p, sf::Texture ** breakableTextures) {
    sf::FloatRect dudeBounds = p.dude.getGlobalBounds();
    sf::FloatRect platformBounds = platform.getGlobalBounds();
    if(dudeBounds.findIntersection(platformBounds)) {
        if(type == "weak" && momentumY == 0 && p.momentumY > 0) {
            momentumY = 1;
        }
        if(type == "breakable" && momentumY == 0 && p.momentumY > 0) {
            momentumY = 1;
            platform.setTexture(*breakableTextures[2]);
        }
    }
    if(momentumY > 0) {
        momentumY = momentumY + ((14 - momentumY) * 0.25) * gravity;
    }
}
