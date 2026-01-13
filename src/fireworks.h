#ifndef FIREWORKS_H
#define FIREWORKS_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include "resourceManager.h"

const float rocket_velocity = -2.0;
const int max_fuse = 280;
const int min_fuse = 180;

// Enum for colors and then explosions. Using the blue rocket for green because.... 

enum class FireworkType {
    ROCKET_ORANGE,
    ROCKET_BLUE,
    EXPLOSION_LONG_ORANGE,
    EXPLOSION_LONG_GREEN,
    EXPLOSION_LONG_BLUE,
    EXPLOSION_DEFAULT_ORANGE,
    EXPLOSION_DEFAULT_GREEN,
    EXPLOSION_DEFAULT_BLUE,
    EXPLOSION_CRYSTALS_ORANGE,
    EXPLOSION_CRYSTALS_GREEN,
    EXPLOSION_CRYSTALS_BLUE
};

enum class FireworkColor {
    ORANGE,
    BLUE,
    GREEN,
    COUNT  
};

enum class FireworkExplosion {
    CRYSTAL,
    DEFAULT,
    LONG,
    COUNT
};

struct SpriteSheetData {
    std::string filename;
    int frameCount;
    int frameWidth;
    int frameHeight;

    SpriteSheetData() : filename(""), frameCount(0), frameWidth(0), frameHeight(0) {}
    SpriteSheetData(const std::string& file, int frames, int w, int h)
        : filename(file), frameCount(frames), frameWidth(w), frameHeight(h) {}
};

// I really fucking hate the guy that sold me these assets. Look at them! Yeah I vibe coded it, and no I don't give a single care
inline const std::map<FireworkType, SpriteSheetData> FIREWORK_DATA = {
    {FireworkType::ROCKET_ORANGE,           {"data/img/sprites/Fireworks/Rocket_Orange-sheet.png", 40, 7, 51}},
    {FireworkType::ROCKET_BLUE,             {"data/img/sprites/Fireworks/Rocket_Blue.png-sheet.png", 50, 7, 52}},
    {FireworkType::EXPLOSION_LONG_ORANGE,   {"data/img/sprites/Fireworks/Explosion_Long_Orange-sheet.png", 57, 92, 94}},
    {FireworkType::EXPLOSION_LONG_GREEN,    {"data/img/sprites/Fireworks/Explosion_Long_Green-sheet.png", 54, 83, 86}},
    {FireworkType::EXPLOSION_LONG_BLUE,     {"data/img/sprites/Fireworks/Explosion_Long_Blue-sheet.png", 57, 80, 93}},
    {FireworkType::EXPLOSION_DEFAULT_ORANGE, {"data/img/sprites/Fireworks/Explosion_Default_Orange-sheet.png", 62, 93, 92}},
    {FireworkType::EXPLOSION_DEFAULT_GREEN,  {"data/img/sprites/Fireworks/Explosion_Default_Green-sheet.png", 61, 99, 99}},
    {FireworkType::EXPLOSION_DEFAULT_BLUE,   {"data/img/sprites/Fireworks/Explosion_Default_Blue-sheet.png", 62, 93, 100}},
    {FireworkType::EXPLOSION_CRYSTALS_ORANGE, {"data/img/sprites/Fireworks/Explosion_Crystals_Orange-sheet.png", 80, 72, 68}},
    {FireworkType::EXPLOSION_CRYSTALS_GREEN,  {"data/img/sprites/Fireworks/Explosion_Crystals_Green-sheet.png", 81, 83, 84}},
    {FireworkType::EXPLOSION_CRYSTALS_BLUE,   {"data/img/sprites/Fireworks/Explosion_Crystals_Blue-sheet.png", 83, 86, 86}}
};

inline FireworkColor getRandomFireworkColor() {
    return static_cast<FireworkColor>(rand() % static_cast<int>(FireworkColor::COUNT));
}

inline FireworkExplosion getRandomFireworkExplosion() {
    return static_cast<FireworkExplosion>(rand() % static_cast<int>(FireworkExplosion::COUNT));
}

inline const SpriteSheetData& getFireworkData(FireworkType type) {
    return FIREWORK_DATA.at(type);
}

inline std::string getFireworkTextureName(FireworkType type) {
    switch(type) {
        case FireworkType::ROCKET_ORANGE: return "rocketOrange";
        case FireworkType::ROCKET_BLUE: return "rocketBlue";
        case FireworkType::EXPLOSION_LONG_ORANGE: return "explosionLongOrange";
        case FireworkType::EXPLOSION_LONG_GREEN: return "explosionLongGreen";
        case FireworkType::EXPLOSION_LONG_BLUE: return "explosionLongBlue";
        case FireworkType::EXPLOSION_DEFAULT_ORANGE: return "explosionDefaultOrange";
        case FireworkType::EXPLOSION_DEFAULT_GREEN: return "explosionDefaultGreen";
        case FireworkType::EXPLOSION_DEFAULT_BLUE: return "explosionDefaultBlue";
        case FireworkType::EXPLOSION_CRYSTALS_ORANGE: return "explosionCrystalsOrange";
        case FireworkType::EXPLOSION_CRYSTALS_GREEN: return "explosionCrystalsGreen";
        case FireworkType::EXPLOSION_CRYSTALS_BLUE: return "explosionCrystalsBlue";
        default: return "";
    }
}

// firework class
class firework {
private:
    float x;
    float y;
    float velY;
    int fuse;
    static std::vector<firework*> fireworkVector;
    sf::Sprite* fireworkSprite = nullptr;

    int textureIterator = 1;
    FireworkType currentType;
    bool hasExploded = false;
    SpriteSheetData ssdata;

    int randInt(int min, int max) {
        return min + rand() % (max - min + 1);
    }

    float randFloat(float min, float max) {
        return min + (rand() / (float)RAND_MAX) * (max - min);
    }

    bool isFinished() {
        return hasExploded && textureIterator >= ssdata.frameCount;
    }

public:
    static void create(int maxX, int minX, int maxY, int minY);
    static void update();
    static void render(sf::RenderWindow &window);
};

#endif
