#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "datatypes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <optional>
#include <string>
#include "UIObjects.h"
#include "resourceManager.h"

enum GameState game_over(sf::RenderWindow& window, int score, sf::Color bgColor);

#endif