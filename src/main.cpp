#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <optional>
#include "datatypes.h"
#include "game.h"
#include "mainmenu.h"
#include "resourceManager.h"
#include "settingsLoader.h"
#include "GameSelect.h"


using namespace std;
using namespace sf;

/*
.
       /#\
      /###\
     / o o \
    |   v   |
     \     /
    __|___|__
   /  /   \  \
  |  |     |  |
  |  |     |  |
   \_|     |_/
     |     |
     |_____|
    /|     |\
   /_|_____|_\

    Gnome Jump

*/


int main()
{

    // Set up window and framerate
    sf::RenderWindow window(sf::VideoMode({400, 600}), "Jump Game");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    // Load all assets at startup
    ResourceManager::loadAll();

    // Load settings from JSON
    loadSettings();

    // State Machine
    while(window.isOpen()) {
        switch(currentState) {
            case GameState::MENU:
                currentState = mainMenu(window);
                break;
            case GameState::GAME:
                currentState = game(window);
                break;
            case GameState::DEAD:
                // Idk if I'll need this 
                break;
            case GameState::SETTINGS:
                // To do
                break;
            case GameState::GAMEPICK:
                currentState = gameSelect(window);
                break;
            case GameState::EXIT:
                window.close();
                break;
        }
    }


    return EXIT_SUCCESS;
}
