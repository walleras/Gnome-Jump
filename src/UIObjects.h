#ifndef UIOBJECTS_H
#define UIOBJECTS_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
    sf::Sprite sprite;
    sf::Text text;
public:
    Button(sf::Vector2f pos, const sf::Texture& texture, std::string label, sf::Font& font, float scale = 3.0f);
    bool isMouseOver(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void setTexture(const sf::Texture& texture);
};

#endif
