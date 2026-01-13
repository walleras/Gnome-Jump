#include "game.h"
#include "resourceManager.h"
#include "datatypes.h"
#include "fireworks.h"
#include "settingsLoader.h"

sf::Color getAltitudeColor(float altitude) {
    float t = std::min(altitude / 100000.0f, 1.0f);
    
    int r, g, b;
    
    if (t < 0.5f) {
        float segmentT = t / 0.5f;
        r = 135 * (1 - segmentT);
        g = 206 * (1 - segmentT);
        b = 245 - segmentT * 135;
    } else {
        float segmentT = (t - 0.5f) / 0.5f;
        r = 0;
        g = 0;
        b = 100 * (1 - segmentT);
    }
    
    return sf::Color(r, g, b);
}

void triggerScreenShake(float velocity) {
    float newIntensity = std::min(std::abs(velocity) * 0.2f, 5.0f);
    if (newIntensity > shakeIntensity) {
        shakeIntensity = newIntensity;
        shakeTimer = 0.25f; // Reset timer
    }
}

enum GameState gamestate;

enum GameState game(sf::RenderWindow& window) {

    // Set initial variables
    scrolly = 0;
    obstacleNumber = 25;
    obstacleChange = 0.001;
    obstacleSmallestNum = 15;
    gravity = 0.4;
    moonSpawn = false;
    highscoreSpawn = false;

    // Initialize screen shake variables
    shakeOffsetX = 0.0f;
    shakeOffsetY = 0.0f;
    shakeIntensity = 0.0f;
    shakeTimer = 0.0f;

    // Zero out acheivement variables

    platformsJumpedOn = 0;
    bouncyJumpedOnRow  = 0;
    weakJumpedOn = 0;

    // Set up game mode variables.

    switch(gameMode) {
        case UnlockGameMode::LOW_GRAVITY:
            gravity = 0.2;
            break;
        case UnlockGameMode::HIGH_GRAVITY:
            gravity = 0.5;
            obstacleChange = 0.002;
            break;
        case UnlockGameMode::ZEN:
            randStable = 80;
            randBreakable = off;
            randWeak = off;
            obstacleNumber = 30;
            obstacleChange = 0;
            break;
        case UnlockGameMode::BOUNCY_ONLY:
            randStable = off;
            randBreakable = off;
            randWeak = off;
            break;
        case UnlockGameMode::WEAK_ONLY:
            randStable = off;
            randBreakable = off;
            randWeak = 100;
            break;
        case UnlockGameMode::HARD:
            randStable = 40;
            randBreakable = 60;
            randWeak = 95;
            break;
        default:
            randStable = 60;
            randBreakable = 70;
            randWeak = 80;
            break;
    }

    // Get resources from ResourceManager
    sf::SoundBuffer& scream = ResourceManager::getSound("scream");
    sf::Sound screamSound(scream);
    screamSound.setVolume(100 * (masterVol / 100.0f) * (sfxVol / 100.0f));

    sf::Font& font = ResourceManager::getFont("arial");
    sf::Text text(font);
    text.setString("Score:");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color(224, 86, 0));
    text.setPosition({0.f, 0.f});

    // Get all textures from ResourceManager
    sf::Texture& dudeTexture = ResourceManager::getTexture("player");
    sf::Texture& bgTexture = ResourceManager::getTexture("background");
    sf::Texture& groundTexture = ResourceManager::getTexture("ground");
    sf::Texture& platformTexture = ResourceManager::getTexture("normal");
    sf::Texture& weakTexture = ResourceManager::getTexture("weak");
    sf::Texture& bouncyTexture = ResourceManager::getTexture("bouncy");
    sf::Texture& cloudTexture = ResourceManager::getTexture("cloud");
    sf::Texture& starTexture = ResourceManager::getTexture("star");
    sf::Texture& moonTexture = ResourceManager::getTexture("moon");
    sf::Texture& signTexture = ResourceManager::getTexture("sign");
    sf::Texture& islandTexture = ResourceManager::getTexture("island");
    sf::Texture& hotairballoonTexture = ResourceManager::getTexture("hotairballoon");
    sf::Texture& birdsTexture = ResourceManager::getTexture("birds");
    sf::Texture& newHighscoreBanner = ResourceManager::getTexture("newHighscoreBanner");

    // Achievement banner textures
    sf::Texture& lowGravityBannerTex = ResourceManager::getTexture("lowGravityBanner");
    sf::Texture& highGravityBannerTex = ResourceManager::getTexture("highGravityBanner");
    sf::Texture& zenBannerTex = ResourceManager::getTexture("zenBanner");
    sf::Texture& bounceBannerTex = ResourceManager::getTexture("bounceBanner");
    sf::Texture& weakBannerTex = ResourceManager::getTexture("weakBanner");

    // New highscore banner sprite and timer
    sf::Sprite bannerSprite(newHighscoreBanner);
    sf::Vector2u bannerSize = newHighscoreBanner.getSize();
    bannerSprite.setOrigin({bannerSize.x / 2.0f, bannerSize.y / 2.0f});
    bannerSprite.setPosition({200.f, 300.f});
    float bannerTimer = 0.0f;
    int fireworksSpawned = 0;

    // Achievement banner sprite and animation
    sf::Sprite achievementBanner(lowGravityBannerTex);
    float achievementBannerY = 700.0f;  // Start below screen
    float achievementBannerTargetY = 568.0f;  // End position near bottom of screen
    float achievementBannerTimer = 0.0f;
    enum class AchievementBannerState { IDLE, SLIDING_UP, HOLDING, SLIDING_DOWN };
    AchievementBannerState achievementBannerState = AchievementBannerState::IDLE;
    bool lowGravityTriggered = false;
    bool highGravityTriggered = false;
    bool zenTriggered = false;
    bool weakOnlyTriggered = false;
    bool bouncyOnlyTriggered = false;

    // Breakable textures array
    sf::Texture* breakableTextures[4] = {
        &ResourceManager::getTexture("breakable1"),
        &ResourceManager::getTexture("breakable2"),
        &ResourceManager::getTexture("breakable3"),
        &ResourceManager::getTexture("breakable4")
    };
    // Cloud textures array
    sf::Texture* cloudTextures[6] = {
        &ResourceManager::getTexture("cloud1"),
        &ResourceManager::getTexture("cloud2"),
        &ResourceManager::getTexture("cloud3"),
        &ResourceManager::getTexture("cloud4"),
        &ResourceManager::getTexture("cloud5"),
        &ResourceManager::getTexture("cloud6")
    };
    // Asteroid textures array
    sf::Texture* asteroidTextures[31] = {
        &ResourceManager::getTexture("asteroid1"),
        &ResourceManager::getTexture("asteroid2"),
        &ResourceManager::getTexture("asteroid3"),
        &ResourceManager::getTexture("asteroid4"),
        &ResourceManager::getTexture("asteroid5"),
        &ResourceManager::getTexture("asteroid6"),
        &ResourceManager::getTexture("asteroid7"),
        &ResourceManager::getTexture("asteroid8"),
        &ResourceManager::getTexture("asteroid9"),
        &ResourceManager::getTexture("asteroid10"),
        &ResourceManager::getTexture("asteroid11"),
        &ResourceManager::getTexture("asteroid12"),
        &ResourceManager::getTexture("asteroid13"),
        &ResourceManager::getTexture("asteroid14"),
        &ResourceManager::getTexture("asteroid15"),
        &ResourceManager::getTexture("asteroid16"),
        &ResourceManager::getTexture("asteroid17"),
        &ResourceManager::getTexture("asteroid18"),
        &ResourceManager::getTexture("asteroid19"),
        &ResourceManager::getTexture("asteroid20"),
        &ResourceManager::getTexture("asteroid21"),
        &ResourceManager::getTexture("asteroid22"),
        &ResourceManager::getTexture("asteroid23"),
        &ResourceManager::getTexture("asteroid24"),
        &ResourceManager::getTexture("asteroid25"),
        &ResourceManager::getTexture("asteroid26"),
        &ResourceManager::getTexture("asteroid27"),
        &ResourceManager::getTexture("asteroid28"),
        &ResourceManager::getTexture("asteroid29"),
        &ResourceManager::getTexture("asteroid30"),
        &ResourceManager::getTexture("asteroid31")
    };

    // Spawn the ground and background texture

    obstacles.push_back(Obstacle(300, 0, bgTexture, "background"));
    obstacles.push_back(Obstacle(groundLevel, 0, groundTexture, "stable"));

    // Spawn initial obstacles

    for (int i = 0; i < 16; ++i) {
        int maxY = 500;
        int typeRoll = rand() % 100;
        sf::Texture* selectedTexture;
        string type;

        if (typeRoll < randStable) {
            selectedTexture = &platformTexture;
            type = "stable";
        } else if (typeRoll < randBreakable) {
            selectedTexture = breakableTextures[0];
            type = "breakable";
        } else if (typeRoll < randWeak) {
            selectedTexture = &weakTexture;
            type = "weak";
        } else {
            selectedTexture = &bouncyTexture;
            type = "bouncy";
        }

        obstacles.push_back(Obstacle(scrolly + (rand() % maxY), rand() % (380), *selectedTexture, type));
    }


    // Spawn player and set background color

    Player dude(dudeTexture, 200, 500);
    sf::Color bgColor(135, 206, 235);

    // Play music

    sf::Music music;
    music.openFromFile("data/sound/game_music.wav");
    music.setVolume(100 * (masterVol / 100.0f) * (musicVol / 100.0f));
    music.play();
    music.setLooping(true);

    while (window.isOpen())
    {
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (event->is<sf::Event::FocusLost>()) {
                music.pause();
                gamestate = pause(window, score, bgColor);
                if(gamestate == GameState::MENU) {
                    return GameState::MENU;
                }
                music.play();
            }
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
                    gamestate = pause(window, score, bgColor);
                    music.pause();
                    if(gamestate == GameState::MENU) {
                        return GameState::MENU;
                    }
                    music.play();
                }
            }
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Acheivement check

        if(scrolly >= 300000.0 && !lowGravityTriggered && achievementBannerState == AchievementBannerState::IDLE) {
            availGameModes.lowGravity = true;
            lowGravityTriggered = true;
            achievementBanner.setTexture(lowGravityBannerTex);
            sf::Vector2u achBannerSize = lowGravityBannerTex.getSize();
            achievementBanner.setOrigin({achBannerSize.x / 2.0f, achBannerSize.y / 2.0f});
            achievementBannerY = 700.0f;
            achievementBannerState = AchievementBannerState::SLIDING_UP;
        }
        if(scrolly == 1000000.0 && !highGravityTriggered && achievementBannerState == AchievementBannerState::IDLE) {
            availGameModes.highGravity = true;
            highGravityTriggered = true;
            achievementBanner.setTexture(highGravityBannerTex);
            sf::Vector2u achBannerSize = highGravityBannerTex.getSize();
            achievementBanner.setOrigin({achBannerSize.x / 2.0f, achBannerSize.y / 2.0f});
            achievementBannerY = 700.0f;
            achievementBannerState = AchievementBannerState::SLIDING_UP;
        }
        if(platformsJumpedOn == 300 && !zenTriggered && achievementBannerState == AchievementBannerState::IDLE) {
            availGameModes.zen = true;
            zenTriggered = true;
            achievementBanner.setTexture(zenBannerTex);
            sf::Vector2u achBannerSize = zenBannerTex.getSize();
            achievementBanner.setOrigin({achBannerSize.x / 2.0f, achBannerSize.y / 2.0f});
            achievementBannerY = 700.0f;
            achievementBannerState = AchievementBannerState::SLIDING_UP;
        }
        if(weakJumpedOn == 50 && !weakOnlyTriggered && achievementBannerState == AchievementBannerState::IDLE) {
            availGameModes.weakOnly = true;
            weakOnlyTriggered = true;
            achievementBanner.setTexture(weakBannerTex);
            sf::Vector2u achBannerSize = weakBannerTex.getSize();
            achievementBanner.setOrigin({achBannerSize.x / 2.0f, achBannerSize.y / 2.0f});
            achievementBannerY = 700.0f;
            achievementBannerState = AchievementBannerState::SLIDING_UP;
        }
        if(bouncyJumpedOnRow == 5 && !bouncyOnlyTriggered && achievementBannerState == AchievementBannerState::IDLE) {
            availGameModes.bouncyOnly = true;
            bouncyOnlyTriggered = true;
            achievementBanner.setTexture(bounceBannerTex);
            sf::Vector2u achBannerSize = bounceBannerTex.getSize();
            achievementBanner.setOrigin({achBannerSize.x / 2.0f, achBannerSize.y / 2.0f});
            achievementBannerY = 700.0f;
            achievementBannerState = AchievementBannerState::SLIDING_UP;
        }

        // Spawn additional obstacles as needed
        std::cout << "Obstacle count: " << size(obstacles) << std::endl;

        if(size(obstacles) <= 20 ) {
            int typeRoll = rand() % 100;
            sf::Texture* selectedTexture;
            string type;

            if (typeRoll < randStable) {
                selectedTexture = &platformTexture;
                type = "stable";
            } else if (typeRoll < randBreakable) {
                selectedTexture = breakableTextures[0];
                type = "breakable";
            } else if (typeRoll < randWeak) {
                selectedTexture = &weakTexture;
                type = "weak";
            } else {
                selectedTexture = &bouncyTexture;
                type = "bouncy";
            }

            obstacles.push_back(Obstacle(scrolly - (rand() % 300), rand() % (380), *selectedTexture, type));
        }

        // Slowly turn the sky black as the gnome heads to space

        bgColor = getAltitudeColor(-scrolly);

        if(-scrolly < cloudLevel && size(clouds) < 6 && rand() % 100 == 1) {
            clouds.push_back(Obstacle(scrolly - (rand() % 1000), rand() % (360), *cloudTextures[static_cast<int>(rand() % 6)], "cloud"));
        }

        if(-scrolly > spaceLevel && size(clouds) < 30) {
            clouds.push_back(Obstacle(scrolly - (rand() % 1000), rand() % (360), starTexture, "star"));
        }

        if(-scrolly > moonLevel && moonSpawn == false) {
            clouds.push_back(Obstacle(scrolly - (rand() % 1000), rand() % (360), moonTexture, "moon"));
            moonSpawn = true;
        }
        if(-scrolly > asteroidLevel && size(clouds) < 50 && rand() % 50 == 1) {
            clouds.push_back(Obstacle(scrolly - (rand() % 1000), rand() % (360), *asteroidTextures[static_cast<int>(rand() % 31)], "asteroid"));
        }
        if(score > highscore && highscoreSpawn == false && highscore > 0 && score >= 300) {
            bannerTimer = 4.0f;
            fireworksSpawned = 0;
            obstacles.push_back(Obstacle(scrolly, 0, signTexture, "sign"));
            highscoreSpawn = true;
        }
        if(-scrolly > islandLevel && -scrolly < maxislandLevel && rand() % 800 == 1) {
            obstacles.push_back(Obstacle(scrolly - (rand() % 1000), rand() % (360), islandTexture, "island"));
        }
        if(-scrolly > hotairballoonLevel && -scrolly < maxhotairballoonLevel && rand() % 800 == 1) {
            string balloonType = (rand() % 2 == 0) ? "hotairballoonright" : "hotairballoonleft";
            int xPos = (balloonType == "hotairballoonright") ? 50 : 350;
            clouds.push_back(Obstacle(scrolly - 1500, xPos, hotairballoonTexture, balloonType));
        }
        if(-scrolly < cloudLevel && rand() % 200 == 1) {
            string birdType = (rand() % 2 == 0) ? "birdright" : "birdleft";
            int xPos = (birdType == "birdright") ? -100 : 500;
            clouds.push_back(Obstacle(scrolly - (rand() % 500), xPos, birdsTexture, birdType));
        }



        // Update screen shake
        if (shakeTimer > 0) {
            shakeTimer -= 1.0f / 60.0f;
            float progress = shakeTimer / 0.25f;
            float currentIntensity = shakeIntensity * progress;
            shakeOffsetX = ((rand() % 200 - 100) / 100.0f) * currentIntensity;
            shakeOffsetY = ((rand() % 200 - 100) / 100.0f) * currentIntensity;
        } else {
            shakeOffsetX = 0.0f;
            shakeOffsetY = 0.0f;
            shakeIntensity = 0.0f;
        }

        // Update banner timer and spawn staggered fireworks
        if (bannerTimer > 0) {
            bannerTimer -= 1.0f / 60.0f;
            // Spawn a firework every 0.4 seconds (every 24 frames)
            if (fireworksSpawned < 10 && (int)(bannerTimer * 60) % 24 == 0) {
                firework::create(400, 0, 601, 600);
                fireworksSpawned++;
            }
        }

        
        if (achievementBannerState == AchievementBannerState::SLIDING_UP) {
            achievementBannerY -= 0.5f;  
            if (achievementBannerY <= achievementBannerTargetY) {
                achievementBannerY = achievementBannerTargetY;
                achievementBannerState = AchievementBannerState::HOLDING;
                achievementBannerTimer = 5.0f;  
            }
        } else if (achievementBannerState == AchievementBannerState::HOLDING) {
            achievementBannerTimer -= 1.0f / 60.0f;
            if (achievementBannerTimer <= 0.0f) {
                achievementBannerState = AchievementBannerState::SLIDING_DOWN;
            }
        } else if (achievementBannerState == AchievementBannerState::SLIDING_DOWN) {
            achievementBannerY += 0.5f;
            if (achievementBannerY >= 700.0f) {
                achievementBannerY = 700.0f;
                achievementBannerState = AchievementBannerState::IDLE;
            }
        }

        
        if (achievementBannerState != AchievementBannerState::IDLE) {
            sf::Vector2u bannerTextureSize = achievementBanner.getTexture().getSize();
            float xPos = 400.0f - (bannerTextureSize.x / 2.0f) - 10.0f;  // 10px margin from right edge
            achievementBanner.setPosition({xPos, achievementBannerY});
        }

        window.clear(bgColor);

        score = (-scrolly) / 10;

        text.setString(std::string("Score:") + std::to_string(score));

        for (auto it = clouds.begin(); it != clouds.end(); ) {
            it->scroll(scrolly / 1.5);
            sf::Vector2f originalPos = it->platform.getPosition();
            it->platform.setPosition({originalPos.x + shakeOffsetX, originalPos.y + shakeOffsetY});
            window.draw(it->platform);
            it->platform.setPosition(originalPos);
            if(it->y > 620) {
                it = clouds.erase(it);
            } else {
                ++it;
            }
        }

        firework::update();

        if(dude.posY > 610) {
            music.stop();
            updateUnlocks(availGameModes);
            screamSound.play();
            while(screamSound.getStatus() == sf::Sound::Status::Playing) {
            }
            for (auto it = obstacles.begin(); it != obstacles.end(); ) {
                it = obstacles.erase(it);
            }
            if(score > highscore) {
                highscore = score;
                saveHighscore();
            }
            gamestate = game_over(window, score, bgColor);
            if(gamestate == GameState::MENU) {
                return GameState::MENU;
            } else if(gamestate == GameState::GAME) {
                return GameState::GAME;
            }            
        }


        for (auto it = obstacles.begin(); it != obstacles.end(); ) {
            it->collide(dude, breakableTextures);
            it->scroll(scrolly);
            sf::Vector2f originalPos = it->platform.getPosition();
            it->platform.setPosition({originalPos.x + shakeOffsetX, originalPos.y + shakeOffsetY});
            window.draw(it->platform);
            it->platform.setPosition(originalPos);
            std::cout << it->type;
            if(it->y > 610) {
                it = obstacles.erase(it);
            } else {
                ++it;
            }
        }



        dude.move(mousePos.x, obstacles);
        dude.draw(window);
        

        sf::Vector2f originalTextPos = text.getPosition();
        text.setPosition({originalTextPos.x + shakeOffsetX, originalTextPos.y + shakeOffsetY});
        window.draw(text);
        text.setPosition(originalTextPos);
        firework::render(window);

        // Draw banner if timer is active
        if (bannerTimer > 0) {
            window.draw(bannerSprite);
        }

        // Draw achievement banner if active
        if (achievementBannerState != AchievementBannerState::IDLE) {
            window.draw(achievementBanner);
        }

        window.display();
    }

    return GameState::EXIT;
}