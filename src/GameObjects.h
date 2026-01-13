#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include "datatypes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <optional>
#include <string>
#include <vector>

using namespace std;

extern float scrolly;
extern float maxMomentum;
extern float gravity;

class Obstacle;

class Player {
public:
    sf::Sprite dude;
    int posX;
    int posY;
    float momentumY;
    float maxMomentum;
    float bouncy;
    sf::SoundBuffer bounce;
    optional<sf::Sound> bounceSound;
    sf::SoundBuffer superbounce;
    optional<sf::Sound> superbounceSound;
    sf::SoundBuffer crack;
    optional<sf::Sound> crackSound;

    Player(sf::Texture& texture, int x, int y);
    void move(float mousePosX, vector<Obstacle> obstacles);
    void draw(sf::RenderWindow& window);
};

class Obstacle {
public:
    sf::Sprite platform;
    int posY;
    int locScroll;
    float x;
    float y;
    float yDis;
    float momentumY;
    string type;

    Obstacle(float initialScrollY, int initialX, sf::Texture& texture, string obstacleType);
    void scroll(float scrolly);
    void collide(const Player& p, sf::Texture** breakableTextures);
};

#endif