#ifndef GAME_H
#define GAME_H

#include "datatypes.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "gameover.h"
#include "GameObjects.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdlib>
#include "resourceManager.h"
#include "pause.h"

extern float scrolly;
extern float maxMomentum;
extern float gravity;
extern GameState currentState;

// Screen shake system
extern float shakeOffsetX;
extern float shakeOffsetY;
extern float shakeIntensity;
extern float shakeTimer;

extern std::vector <Obstacle> obstacles;
extern std::vector <Obstacle> clouds;

sf::Color getAltitudeColor(float altitude);
void triggerScreenShake(float velocity);
GameState game(sf::RenderWindow& window);

// Game difficulty

extern int randStable;
extern int randBouncy;
extern int randBreakable;
extern int randWeak;
extern bool classic;
const int off = 0;
extern int obstacleNumber;
extern float obstacleChange;
extern int obstacleSmallestNum;

// Constants for changing background decorations

const float cloudLevel = 40000.0;
const float spaceLevel = 90000.0;
const float moonLevel = 300000.0;
const float sataliteStart = 95000.0;
const float sataliteEnd = 170000.0;
const int groundLevel = 582;
const float islandLevel = 50000.0;
const float maxislandLevel = 70000.0;
const float hotairballoonLevel = 10000.0;
const float maxhotairballoonLevel = 40000.0;
const float asteroidLevel = 350000.0;

// Checks so some things spawn once

extern bool moonSpawn;
extern bool highscoreSpawn;

// Unlocking variables

extern int platformsJumpedOn;
extern int bouncyJumpedOnRow;
extern int weakJumpedOn;

#endif