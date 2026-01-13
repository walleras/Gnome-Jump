#ifndef DATATYPES_H
#define DATATYPES_H

enum class GameState {MENU, GAME, DEAD, PAUSE, SETTINGS, HIGHSCORE, EXIT,GAMEPICK};

//Initilize score with zero
extern int score;
extern int highscore;

//Unlocks
enum class UnlockGameMode {CLASSIC, LOW_GRAVITY, HIGH_GRAVITY, ZEN, BOUNCY_ONLY, WEAK_ONLY, HARD};
extern UnlockGameMode gameMode;

struct unlocks {
	bool lowGravity;
	bool highGravity;
	bool zen;
	bool bouncyOnly;
	bool weakOnly;
	bool hardMode;
};

extern unlocks availGameModes;

//Center constant
const float centerScore = (200 - (27 * 3));
const float centerBig = (200 - (39 * 3));

// Volume settings
extern int masterVol;
extern int musicVol;
extern int sfxVol;
extern bool mute;

#endif
