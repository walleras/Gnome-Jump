#include "datatypes.h"
#include "GameObjects.h"
#include <vector>

// From datatypes.h
int score = 0;
int highscore = 0;
UnlockGameMode gameMode = UnlockGameMode::CLASSIC;
unlocks availGameModes = {false, false, false, false, false, false};

// Volume settings
int masterVol = 100;
int musicVol = 100;
int sfxVol = 100;
bool mute = false;

// From game.h
std::vector <Obstacle> obstacles;
std::vector <Obstacle> clouds;
bool moonSpawn = false;
bool highscoreSpawn = false;
float scrolly = 0.0f;

// Screen shake system
float shakeOffsetX = 0.0f;
float shakeOffsetY = 0.0f;
float shakeIntensity = 0.0f;
float shakeTimer = 0.0f;
float shakeDuration = 0.25f; // 250ms shake duration

float maxMomentum = 0.0f;
float gravity = 0.5f;
int randStable = 0;
int randBouncy = 0;
int randBreakable = 0;
int randWeak = 0;
bool classic = true;
int obstacleNumber = 10;
float obstacleChange = 0.5f;
int obstacleSmallestNum = 1;
GameState currentState = GameState::MENU;

// Unlocking variables
int platformsJumpedOn = 0;
int bouncyJumpedOnRow = 0;
int weakJumpedOn = 0;


