#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <optional>
#include "datatypes.h"
#include "UIObjects.h"
#include "resourceManager.h"

GameState pause(sf::RenderWindow& window, int score, sf::Color bgColor); 