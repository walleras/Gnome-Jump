#include "gameover.h"
#include "settingsLoader.h"

enum GameState game_over(sf::RenderWindow& window, int score, sf::Color bgColor) {

    // Check and save new high score
    if (score > highscore) {
        highscore = score;
        saveHighscore();
    }

    // Get resources from ResourceManager
    sf::Texture& scoreButton = ResourceManager::getTexture("smallButton");
    sf::Texture& bigButton = ResourceManager::getTexture("bigButton");
    sf::Texture& mutedIcon = ResourceManager::getTexture("mutedIcon");
    sf::Texture& loudIcon = ResourceManager::getTexture("loudIcon");
    sf::Font& font = ResourceManager::getFont("arial");
    sf::SoundBuffer& click = ResourceManager::getSound("click");

    Button scoreDisplay({centerScore, (80.0)}, scoreButton, "Score: " + std::to_string(score), font);
    Button tryAgain({centerScore, (280.0)}, scoreButton, "Play Again", font);
    Button mainMenuBtn({centerScore,(390.0)}, scoreButton, "Main Menu", font);
    Button muteButton({350.0,20.0}, mute ? mutedIcon : loudIcon, "", font);

    sf::Sound clickSound(click);
    clickSound.setVolume(100 * (masterVol / 100.0f) * (sfxVol / 100.0f));

    sf::Music music;
    music.openFromFile("data/sound/gameover_music.wav");
    music.setVolume(100 * (masterVol / 100.0f) * (musicVol / 100.0f));
    music.play();
    music.setLooping(true);

    while (window.isOpen())
    {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (event.has_value() && event->is<sf::Event::MouseButtonPressed>()) {
                const auto& mouseButton = event->getIf<sf::Event::MouseButtonPressed>();
                    if (mouseButton->button == sf::Mouse::Button::Left) {
                        if (tryAgain.isMouseOver(window)) {
                            music.stop();
                            clickSound.play();
                            return GameState::GAME;
                        }
                        if (mainMenuBtn.isMouseOver(window)) {
                            music.stop();
                            clickSound.play();
                            return GameState::MENU;
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

        window.clear(bgColor);
        scoreDisplay.draw(window);
        tryAgain.draw(window);
        mainMenuBtn.draw(window);
        muteButton.draw(window);
        window.display();
    }

    return GameState::EXIT;

}