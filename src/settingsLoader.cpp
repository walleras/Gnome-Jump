#include "settingsLoader.h"
#include "json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void loadSettings() {
    std::ifstream file("data/settings.json");

    if (!file.is_open()) {
        // If file doesn't exist, initialize with default values
        availGameModes.lowGravity = false;
        availGameModes.highGravity = false;
        availGameModes.zen = false;
        availGameModes.bouncyOnly = false;
        availGameModes.weakOnly = false;
        availGameModes.hardMode = false;
        masterVol = 100;
        musicVol = 100;
        sfxVol = 100;
        highscore = 0;
        return;
        std::cout << "Settings File not found" << std::endl;
    }

    try {
        json settings;
        file >> settings;

        if (settings.contains("unlocks")) {
            json unlocks = settings["unlocks"];
            if (unlocks.contains("lowGravity")) {
                availGameModes.lowGravity = unlocks["lowGravity"].get<bool>();
            }
            if (unlocks.contains("highGravity")) {
                availGameModes.highGravity = unlocks["highGravity"].get<bool>();
            }
            if (unlocks.contains("zen")) {
                availGameModes.zen = unlocks["zen"].get<bool>();
            }
            if (unlocks.contains("bouncyOnly")) {
                availGameModes.bouncyOnly = unlocks["bouncyOnly"].get<bool>();
            }
            if (unlocks.contains("weakOnly")) {
                availGameModes.weakOnly = unlocks["weakOnly"].get<bool>();
            }
            if (unlocks.contains("hardMode")) {
                availGameModes.hardMode = unlocks["hardMode"].get<bool>();
            }
        }

        // Load volume settings
        if (settings.contains("masterVol")) {
            masterVol = settings["masterVol"].get<int>();
        }
        if (settings.contains("musicVol")) {
            musicVol = settings["musicVol"].get<int>();
        }
        if (settings.contains("sfxVol")) {
            sfxVol = settings["sfxVol"].get<int>();
        }
        highscore = settings["highscore"].get<int>();
        if (masterVol == 0) {
            mute = true;
        }

    } catch (const json::exception& e) {
        std::cerr << "Error parsing settings.json." << std::endl;
    }

    file.close();
}

void saveSettings() {
    std::ifstream file("data/settings.json");

    try {
        json settings;
        file >> settings;

        settings["masterVol"] = masterVol;
        settings["musicVol"] = musicVol;
        settings["sfxVol"] = sfxVol;

        std::ofstream outFile("data/settings.json");
        outFile << settings.dump(2);
        outFile.close();
        file.close();


    } catch (const json::exception& e) {
        std::cerr << "Error saving settings.json." << std::endl;
    }
}

void saveHighscore() {
    std::ifstream file("data/settings.json");

    try {
        json settings;
        file >> settings;

        settings["highscore"] = highscore;

        std::ofstream outFile("data/settings.json");
        outFile << settings.dump(2);
        outFile.close();
        file.close();
    } catch (const json::exception& e) {
        std::cerr << "Error saving settings.json." << std::endl;
    }
}

void updateUnlocks(unlocks Unlocks) {
    json settings;

    // Read existing settings
    std::ifstream inFile("data/settings.json");
    if (inFile.is_open()) {
        inFile >> settings;
        inFile.close();
    }

    try {
        // Update unlock values
        settings["unlocks"]["lowGravity"] = Unlocks.lowGravity;
        settings["unlocks"]["highGravity"] = Unlocks.highGravity;
        settings["unlocks"]["zen"] = Unlocks.zen;
        settings["unlocks"]["bouncyOnly"] = Unlocks.bouncyOnly;
        settings["unlocks"]["weakOnly"] = Unlocks.weakOnly;
        settings["unlocks"]["hardMode"] = Unlocks.hardMode;

        // Write back to file
        std::ofstream outFile("data/settings.json");
        outFile << settings.dump(2);
        outFile.close();

    } catch (const json::exception& e) {
        std::cerr << "Error updating unlocks in settings.json: " << e.what() << std::endl;
    }
}