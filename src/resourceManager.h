#pragma once

#include "datatypes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameObjects.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include <map>


class ResourceManager {
public:
    static std::map<std::string, sf::Texture> textureMap;
    static std::map<std::string, sf::SoundBuffer> soundMap;
    static std::map<std::string, sf::Font> fontMap;

    static void loadTextures();
    static void loadSounds();
    static void loadFonts();
    static void loadAll();

    static sf::Texture& getTexture(const std::string& name);
    static sf::SoundBuffer& getSound(const std::string& name);
    static sf::Font& getFont(const std::string& name);
};

