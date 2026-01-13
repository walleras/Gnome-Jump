#include "GameSelect.h"

// External global variables
extern int masterVol;
extern int sfxVol;
extern UnlockGameMode gameMode;
extern unlocks availGameModes;

enum GameState gameSelect(sf::RenderWindow& window) {

    sf::Font& font = ResourceManager::getFont("arial");
    sf::SoundBuffer& click = ResourceManager::getSound("click");

    sf::Texture& lowGravityIcon = ResourceManager::getTexture("lowGravityIcon");
    sf::Texture& highGravityIcon = ResourceManager::getTexture("highGravityIcon");
    sf::Texture& zenIcon = ResourceManager::getTexture("zenIcon");
    sf::Texture& bounceIcon = ResourceManager::getTexture("bounceIcon");
    sf::Texture& weakIcon = ResourceManager::getTexture("weakIcon");
    sf::Texture& scoreButton = ResourceManager::getTexture("smallButton");

    
    // Grid: 3 columns, starting at x=50, y=100, spacing=120
    const float startX = 50.0f;
    const float startY = 100.0f;
    const float spacingX = 120.0f;
    const float spacingY = 140.0f;

    // Row 1
    sf::Sprite classicSprite(lowGravityIcon); // Placeholder for classic
    classicSprite.setPosition({startX, startY});

    sf::Sprite lowGravitySprite(lowGravityIcon);
    lowGravitySprite.setPosition({startX + spacingX, startY});

    sf::Sprite highGravitySprite(highGravityIcon);
    highGravitySprite.setPosition({startX + spacingX * 2, startY});

    // Row 2
    sf::Sprite zenSprite(zenIcon);
    zenSprite.setPosition({startX, startY + spacingY});

    sf::Sprite bounceSprite(bounceIcon);
    bounceSprite.setPosition({startX + spacingX, startY + spacingY});

    sf::Sprite weakSprite(weakIcon);
    weakSprite.setPosition({startX + spacingX * 2, startY + spacingY});

    // Row 3
    sf::Sprite hardSprite(lowGravityIcon); // Placeholder for hard mode
    hardSprite.setPosition({startX, startY + spacingY * 2});

    // Create text labels for each game mode
    const float iconSize = 64.0f;  // Approximate icon width for centering

    sf::Text classicText(font, "Classic", 16);
    classicText.setFillColor(sf::Color::Black);
    sf::FloatRect classicBounds = classicText.getLocalBounds();
    classicText.setPosition({startX + (iconSize - classicBounds.size.x) / 2, startY + 85.0f});

    sf::Text lowGravityText(font, "Low Gravity", 16);
    lowGravityText.setFillColor(sf::Color::Black);
    sf::FloatRect lowGravityBounds = lowGravityText.getLocalBounds();
    lowGravityText.setPosition({startX + spacingX + (iconSize - lowGravityBounds.size.x) / 2, startY + 85.0f});

    sf::Text highGravityText(font, "High Gravity", 16);
    highGravityText.setFillColor(sf::Color::Black);
    sf::FloatRect highGravityBounds = highGravityText.getLocalBounds();
    highGravityText.setPosition({startX + spacingX * 2 + (iconSize - highGravityBounds.size.x) / 2, startY + 85.0f});

    sf::Text zenText(font, "Zen", 16);
    zenText.setFillColor(sf::Color::Black);
    sf::FloatRect zenBounds = zenText.getLocalBounds();
    zenText.setPosition({startX + (iconSize - zenBounds.size.x) / 2, startY + spacingY + 85.0f});

    sf::Text bounceText(font, "Bouncy Only", 16);
    bounceText.setFillColor(sf::Color::Black);
    sf::FloatRect bounceBounds = bounceText.getLocalBounds();
    bounceText.setPosition({startX + spacingX + (iconSize - bounceBounds.size.x) / 2, startY + spacingY + 85.0f});

    sf::Text weakText(font, "Weak Only", 16);
    weakText.setFillColor(sf::Color::Black);
    sf::FloatRect weakBounds = weakText.getLocalBounds();
    weakText.setPosition({startX + spacingX * 2 + (iconSize - weakBounds.size.x) / 2, startY + spacingY + 85.0f});

    sf::Text hardText(font, "Hard", 16);
    hardText.setFillColor(sf::Color::Black);
    sf::FloatRect hardBounds = hardText.getLocalBounds();
    hardText.setPosition({startX + (iconSize - hardBounds.size.x) / 2, startY + spacingY * 2 + 85.0f});

    Button mainMenu({centerScore - 60.0, 480.0}, scoreButton, "Back", font, 3.0f);

    sf::Sound clickSound(click);
    clickSound.setVolume(100 * (masterVol / 100.0f) * (sfxVol / 100.0f));

    // Set all locked game modes to grayscale

    if (availGameModes.lowGravity == false) {
        lowGravitySprite.setColor(sf::Color(100,100,100));
        lowGravityText.setFillColor(sf::Color(100,100,100));
    }

    if (availGameModes.highGravity == false) {
        highGravitySprite.setColor(sf::Color(100,100,100));
        highGravityText.setFillColor(sf::Color(100,100,100));
    }

    if (availGameModes.zen == false) {
        zenSprite.setColor(sf::Color(100,100,100));
        zenText.setFillColor(sf::Color(100,100,100));
    }

    if (availGameModes.bouncyOnly == false) {
        bounceSprite.setColor(sf::Color(100,100,100));
        bounceText.setFillColor(sf::Color(100,100,100));
    }

    if (availGameModes.weakOnly == false) {
        weakSprite.setColor(sf::Color(100,100,100));
        weakText.setFillColor(sf::Color(100,100,100));
    }

    if (availGameModes.hardMode == false) {
        hardSprite.setColor(sf::Color(100,100,100));
        hardText.setFillColor(sf::Color(100,100,100));
    }

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
                    sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

                    // Check which game mode was clicked
                    if (classicSprite.getGlobalBounds().contains(mousePos)) {
                        gameMode = UnlockGameMode::CLASSIC;
                        clickSound.play();
                    }
                    if (lowGravitySprite.getGlobalBounds().contains(mousePos) && availGameModes.lowGravity == true) {
                        gameMode = UnlockGameMode::LOW_GRAVITY;
                        clickSound.play();
                    }
                    if (highGravitySprite.getGlobalBounds().contains(mousePos) && availGameModes.highGravity == true) {
                        gameMode = UnlockGameMode::HIGH_GRAVITY;
                        clickSound.play();
                    }
                    if (zenSprite.getGlobalBounds().contains(mousePos) && availGameModes.zen == true) {
                        gameMode = UnlockGameMode::ZEN;
                        clickSound.play();
                    }
                    if (bounceSprite.getGlobalBounds().contains(mousePos) && availGameModes.bouncyOnly == true) {
                        gameMode = UnlockGameMode::BOUNCY_ONLY;
                        clickSound.play();
                    }
                    if (weakSprite.getGlobalBounds().contains(mousePos) && availGameModes.weakOnly == true) {
                        gameMode = UnlockGameMode::WEAK_ONLY;
                        clickSound.play();
                    }
                    if (hardSprite.getGlobalBounds().contains(mousePos) && availGameModes.hardMode == true) {
                        gameMode = UnlockGameMode::HARD;
                        clickSound.play();
                    }
                    if (mainMenu.isMouseOver(window)) {
                        clickSound.play();
                        return GameState::MENU;
                    }
                }
            }
        }

        // Hover highlighting
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        // Reset all unlocked colors to white
        classicSprite.setColor(sf::Color::White);
        if (availGameModes.lowGravity) {
            lowGravitySprite.setColor(sf::Color::White);
        }
        if (availGameModes.highGravity) {
            highGravitySprite.setColor(sf::Color::White);
        }
        if (availGameModes.zen) {
            zenSprite.setColor(sf::Color::White);
        }
        if (availGameModes.bouncyOnly) {
            bounceSprite.setColor(sf::Color::White);
        }
        if (availGameModes.weakOnly) {
            weakSprite.setColor(sf::Color::White);
        }
        if (availGameModes.hardMode) {
            hardSprite.setColor(sf::Color::White);
        }

        // Highlight hovered sprite with yellow tint
        if (classicSprite.getGlobalBounds().contains(mousePos)) {
            classicSprite.setColor(sf::Color(255, 255, 150));
        }
        if (lowGravitySprite.getGlobalBounds().contains(mousePos) && availGameModes.lowGravity) {
            lowGravitySprite.setColor(sf::Color(255, 255, 150));
        }
        if (highGravitySprite.getGlobalBounds().contains(mousePos) && availGameModes.highGravity) {
            highGravitySprite.setColor(sf::Color(255, 255, 150));
        }
        if (zenSprite.getGlobalBounds().contains(mousePos) && availGameModes.zen) {
            zenSprite.setColor(sf::Color(255, 255, 150));
        }
        if (bounceSprite.getGlobalBounds().contains(mousePos) && availGameModes.bouncyOnly) {
            bounceSprite.setColor(sf::Color(255, 255, 150));
        }
        if (weakSprite.getGlobalBounds().contains(mousePos) && availGameModes.weakOnly) {
            weakSprite.setColor(sf::Color(255, 255, 150));
        }
        if (hardSprite.getGlobalBounds().contains(mousePos) && availGameModes.hardMode) {
            hardSprite.setColor(sf::Color(255, 255, 150));
        }

        window.clear(sf::Color(135, 206, 245));

        // Helper lambda to draw sprite with outline if selected
        auto drawWithOutline = [&](sf::Sprite& sprite, bool isSelected) {
            if (isSelected) {
                // Save original color and position
                sf::Color originalColor = sprite.getColor();
                sf::Vector2f originalPos = sprite.getPosition();

                // Draw outline (8 directions)
                sprite.setColor(sf::Color::Black);
                for (int x = -2; x <= 2; x += 2) {
                    for (int y = -2; y <= 2; y += 2) {
                        if (x == 0 && y == 0) continue;
                        sprite.setPosition({originalPos.x + x, originalPos.y + y});
                        window.draw(sprite);
                    }
                }

                // Restore and draw main sprite
                sprite.setColor(originalColor);
                sprite.setPosition(originalPos);
            }
            window.draw(sprite);
        };

        // Draw all sprites with outline on selected mode
        drawWithOutline(classicSprite, gameMode == UnlockGameMode::CLASSIC);
        drawWithOutline(lowGravitySprite, gameMode == UnlockGameMode::LOW_GRAVITY);
        drawWithOutline(highGravitySprite, gameMode == UnlockGameMode::HIGH_GRAVITY);
        drawWithOutline(zenSprite, gameMode == UnlockGameMode::ZEN);
        drawWithOutline(bounceSprite, gameMode == UnlockGameMode::BOUNCY_ONLY);
        drawWithOutline(weakSprite, gameMode == UnlockGameMode::WEAK_ONLY);
        drawWithOutline(hardSprite, gameMode == UnlockGameMode::HARD);

        // Draw all text labels
        window.draw(classicText);
        window.draw(lowGravityText);
        window.draw(highGravityText);
        window.draw(zenText);
        window.draw(bounceText);
        window.draw(weakText);
        window.draw(hardText);

        // Draw main menu button
        mainMenu.draw(window);

        window.display();
    }

    return GameState::EXIT;
}
