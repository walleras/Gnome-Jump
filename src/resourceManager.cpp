#include "resourceManager.h"

// Define static members
std::map<std::string, sf::Texture> ResourceManager::textureMap;
std::map<std::string, sf::SoundBuffer> ResourceManager::soundMap;
std::map<std::string, sf::Font> ResourceManager::fontMap;

void ResourceManager::loadTextures() {
    // Sprites
    textureMap["player"].loadFromFile("data/img/sprites/dude.png");
    textureMap["normal"].loadFromFile("data/img/sprites/platform_normal.png");
    textureMap["weak"].loadFromFile("data/img/sprites/platform_weak.png");
    textureMap["bouncy"].loadFromFile("data/img/sprites/bouncy_platform.png");
    textureMap["cloud"].loadFromFile("data/img/sprites/cloud.png");
    textureMap["ground"].loadFromFile("data/img/sprites/ground.png");
    textureMap["island"].loadFromFile("data/img/sprites/floatingisland.png");

    // Broken platform animations
    textureMap["breakable1"].loadFromFile("data/img/broken_platform_anim/frame_1.png");
    textureMap["breakable2"].loadFromFile("data/img/broken_platform_anim/frame_2.png");
    textureMap["breakable3"].loadFromFile("data/img/broken_platform_anim/frame_3.png");
    textureMap["breakable4"].loadFromFile("data/img/broken_platform_anim/frame_4.png");

    // Background elements
    textureMap["background"].loadFromFile("data/img/background/background.png");
    textureMap["moon"].loadFromFile("data/img/background/moon.png");
    textureMap["star"].loadFromFile("data/img/background/star.png");
    textureMap["birds"].loadFromFile("data/img/background/birds.png");
    textureMap["cloud1"].loadFromFile("data/img/background/cloud1.png");
    textureMap["cloud2"].loadFromFile("data/img/background/cloud2.png");
    textureMap["cloud3"].loadFromFile("data/img/background/cloud3.png");
    textureMap["cloud4"].loadFromFile("data/img/background/cloud4.png");
    textureMap["cloud5"].loadFromFile("data/img/background/cloud5.png");
    textureMap["cloud6"].loadFromFile("data/img/background/cloud6.png");
    textureMap["hotairballoon"].loadFromFile("data/img/background/hot_air_balloon.png");
    textureMap["asteroid1"].loadFromFile("data/img/background/Space Asteroids_g198.png");
    textureMap["asteroid2"].loadFromFile("data/img/background/Space Asteroids_g199.png");
    textureMap["asteroid3"].loadFromFile("data/img/background/Space Asteroids_g200.png");
    textureMap["asteroid4"].loadFromFile("data/img/background/Space Asteroids_g201.png");
    textureMap["asteroid5"].loadFromFile("data/img/background/Space Asteroids_g202.png");
    textureMap["asteroid6"].loadFromFile("data/img/background/Space Asteroids_g203.png");
    textureMap["asteroid7"].loadFromFile("data/img/background/Space Asteroids_g204.png");
    textureMap["asteroid8"].loadFromFile("data/img/background/Space Asteroids_g205.png");
    textureMap["asteroid9"].loadFromFile("data/img/background/Space Asteroids_g206.png");
    textureMap["asteroid10"].loadFromFile("data/img/background/Space Asteroids_g207.png");
    textureMap["asteroid11"].loadFromFile("data/img/background/Space Asteroids_g208.png");
    textureMap["asteroid12"].loadFromFile("data/img/background/Space Asteroids_g209.png");
    textureMap["asteroid13"].loadFromFile("data/img/background/Space Asteroids_g210.png");
    textureMap["asteroid14"].loadFromFile("data/img/background/Space Asteroids_g211.png");
    textureMap["asteroid15"].loadFromFile("data/img/background/Space Asteroids_g212.png");
    textureMap["asteroid16"].loadFromFile("data/img/background/Space Asteroids_g213.png");
    textureMap["asteroid17"].loadFromFile("data/img/background/Space Asteroids_g214.png");
    textureMap["asteroid18"].loadFromFile("data/img/background/Space Asteroids_g215.png");
    textureMap["asteroid19"].loadFromFile("data/img/background/Space Asteroids_g216.png");
    textureMap["asteroid20"].loadFromFile("data/img/background/Space Asteroids_g217.png");
    textureMap["asteroid21"].loadFromFile("data/img/background/Space Asteroids_g218.png");
    textureMap["asteroid22"].loadFromFile("data/img/background/Space Asteroids_g219.png");
    textureMap["asteroid23"].loadFromFile("data/img/background/Space Asteroids_g220.png");
    textureMap["asteroid24"].loadFromFile("data/img/background/Space Asteroids_g221.png");
    textureMap["asteroid25"].loadFromFile("data/img/background/Space Asteroids_g222.png");
    textureMap["asteroid26"].loadFromFile("data/img/background/Space Asteroids_g223.png");
    textureMap["asteroid27"].loadFromFile("data/img/background/Space Asteroids_g224.png");
    textureMap["asteroid28"].loadFromFile("data/img/background/Space Asteroids_g225.png");
    textureMap["asteroid29"].loadFromFile("data/img/background/Space Asteroids_g226.png");
    textureMap["asteroid30"].loadFromFile("data/img/background/Space Asteroids_g227.png");
    textureMap["asteroid31"].loadFromFile("data/img/background/Space Asteroids_g228.png");
    textureMap["sign"].loadFromFile("data/img/sprites/highscore_sign.png");

    // UI elements
    textureMap["smallButton"].loadFromFile("data/img/ui/score_button.png");
    textureMap["bigButton"].loadFromFile("data/img/ui/big_button.png");
    textureMap["introText"].loadFromFile("data/img/ui/introText.png");
    textureMap["newHighscoreBanner"].loadFromFile("data/img/ui/newHighscoreBanner.png");
    textureMap["mutedIcon"].loadFromFile("data/img/ui/Volume Mute1.png");
    textureMap["loudIcon"].loadFromFile("data/img/ui/Volume4.png");

    // Game mode icons
    textureMap["lowGravityIcon"].loadFromFile("data/img/ui/LowGravityIcon.png");
    textureMap["highGravityIcon"].loadFromFile("data/img/ui/HighGravityIcon.png");
    textureMap["zenIcon"].loadFromFile("data/img/ui/ZenIcon.png");
    textureMap["bounceIcon"].loadFromFile("data/img/ui/BounceIcon.png");
    textureMap["weakIcon"].loadFromFile("data/img/ui/WeakIcon.png");

    // Game mode banners
    textureMap["lowGravityBanner"].loadFromFile("data/img/ui/LowGravityBanner.png");
    textureMap["highGravityBanner"].loadFromFile("data/img/ui/HighGravityBanner.png");
    textureMap["zenBanner"].loadFromFile("data/img/ui/ZenBanner.png");
    textureMap["bounceBanner"].loadFromFile("data/img/ui/BounceBanner.png");
    textureMap["weakBanner"].loadFromFile("data/img/ui/WeakBanner.png");

    // Fireworks - Auto-generated from spritesheetdocumentation.csv
    textureMap["rocketOrange"].loadFromFile("data/img/sprites/Fireworks/Rocket_Orange-sheet.png");
    textureMap["rocketBlue"].loadFromFile("data/img/sprites/Fireworks/Rocket_Blue.png-sheet.png");
    textureMap["explosionLongOrange"].loadFromFile("data/img/sprites/Fireworks/Explosion_Long_Orange-sheet.png");
    textureMap["explosionLongGreen"].loadFromFile("data/img/sprites/Fireworks/Explosion_Long_Green-sheet.png");
    textureMap["explosionLongBlue"].loadFromFile("data/img/sprites/Fireworks/Explosion_Long_Blue-sheet.png");
    textureMap["explosionDefaultOrange"].loadFromFile("data/img/sprites/Fireworks/Explosion_Default_Orange-sheet.png");
    textureMap["explosionDefaultGreen"].loadFromFile("data/img/sprites/Fireworks/Explosion_Default_Green-sheet.png");
    textureMap["explosionDefaultBlue"].loadFromFile("data/img/sprites/Fireworks/Explosion_Default_Blue-sheet.png");
    textureMap["explosionCrystalsOrange"].loadFromFile("data/img/sprites/Fireworks/Explosion_Crystals_Orange-sheet.png");
    textureMap["explosionCrystalsGreen"].loadFromFile("data/img/sprites/Fireworks/Explosion_Crystals_Green-sheet.png");
    textureMap["explosionCrystalsBlue"].loadFromFile("data/img/sprites/Fireworks/Explosion_Crystals_Blue-sheet.png");
    textureMap["explosionCrystalsWhite"].loadFromFile("data/img/sprites/Fireworks/Explosion_Crystals_White-sheet.png");

}

void ResourceManager::loadSounds() {
    soundMap["scream"].loadFromFile("data/sound/falling.wav");
    soundMap["bounce"].loadFromFile("data/sound/bounce.wav");
    soundMap["superbounce"].loadFromFile("data/sound/superbounce.wav");
    soundMap["crack"].loadFromFile("data/sound/crack.wav");
    soundMap["click"].loadFromFile("data/sound/click.wav");
}

void ResourceManager::loadFonts() {
    fontMap["arial"].openFromFile("data/fonts/arial.ttf");
}

void ResourceManager::loadAll() {
    loadTextures();
    loadSounds();
    loadFonts();
}

sf::Texture& ResourceManager::getTexture(const std::string& name) {
    return textureMap[name];
}

sf::SoundBuffer& ResourceManager::getSound(const std::string& name) {
    return soundMap[name];
}

sf::Font& ResourceManager::getFont(const std::string& name) {
    return fontMap[name];
}
