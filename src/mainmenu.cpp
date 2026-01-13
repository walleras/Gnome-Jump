#include "mainmenu.h"
#include "settingsLoader.h"

enum GameState mainMenu(sf::RenderWindow& window) {

    // Get resources from ResourceManager
    sf::Texture& scoreButton = ResourceManager::getTexture("smallButton");
    sf::Texture& introTexture = ResourceManager::getTexture("introText");
    sf::Texture& mutedIcon = ResourceManager::getTexture("mutedIcon");
    sf::Texture& loudIcon = ResourceManager::getTexture("loudIcon");
    sf::Font& font = ResourceManager::getFont("arial");
    sf::SoundBuffer& click = ResourceManager::getSound("click");

    // Create intro text sprite
    sf::Sprite introText(introTexture);
    introText.setPosition({50.0f, 50.0f});

    Button tryAgain({centerScore, (160.0)}, scoreButton, "Start Game", font);
    Button highScore({centerScore, 280.0}, scoreButton, "Select Mode", font);
    Button closeGame({centerScore, 400.0}, scoreButton, "Quit Game", font);
    Button muteButton({350.0,20.0}, mute ? mutedIcon : loudIcon, "", font);

    sf::Sound clickSound(click);
    clickSound.setVolume(100 * (masterVol / 100.0f) * (sfxVol / 100.0f));

    sf::Music music;
    music.openFromFile("data/sound/mainmenu_music.wav");
    music.setVolume(100 * (masterVol / 100.0f) * (musicVol / 100.0f));
    music.play();
    music.setLooping(true);

    while (window.isOpen())
    {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return GameState::EXIT;
            }

            if (event.has_value() && event->is<sf::Event::MouseButtonPressed>()) {
                const auto& mouseButton = event->getIf<sf::Event::MouseButtonPressed>();
                    if (mouseButton->button == sf::Mouse::Button::Left) {
                        if (tryAgain.isMouseOver(window)) {
                            music.stop();
                            clickSound.play();
                            return GameState::GAME;
                        }
                        if (closeGame.isMouseOver(window)) {
                            music.stop();
                            clickSound.play();
                            window.close();
                            return GameState::EXIT;
                        }
                        if (highScore.isMouseOver(window)) {
                            music.stop();
                            clickSound.play();
                            return GameState::GAMEPICK;
                        }
                        if (muteButton.isMouseOver(window)) {
                            clickSound.play();
                            if(mute) {
                                mute = false;
                                masterVol = 100;
                                muteButton.setTexture(loudIcon);
                            } else if(!mute) {
                                mute = true;
                                masterVol = 0;
                                muteButton.setTexture(mutedIcon);
                            }
                            saveSettings();
                        }
                    }
                }

            }
        clickSound.setVolume(100 * (masterVol / 100.0f) * (sfxVol / 100.0f));
        music.setVolume(100 * (masterVol / 100.0f) * (musicVol / 100.0f));
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        window.clear(sf::Color(135, 206, 245));
        window.draw(introText);
        tryAgain.draw(window);
        highScore.draw(window);
        closeGame.draw(window);
        muteButton.draw(window);
        window.display();
    }

    return GameState::EXIT;
}