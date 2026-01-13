#include "UIObjects.h"

Button::Button(sf::Vector2f pos, const sf::Texture& texture, std::string label, sf::Font& font, float scale)
    : sprite(texture), text(font, label, static_cast<unsigned int>(24 * (scale / 3.0f))) {
    sprite.setPosition(pos);
    sprite.setScale({scale, scale});
    text.setFillColor(sf::Color::Black);
    text.setString(label);
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect spriteBounds = sprite.getGlobalBounds();
    text.setPosition({
        pos.x + (spriteBounds.size.x - textBounds.size.x) / 2,
        pos.y + (spriteBounds.size.y - (textBounds.size.y + 10)) / 2
    });
}

bool Button::isMouseOver(sf::RenderWindow& window) {
    return sprite.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    window.draw(text);
}

void Button::setTexture(const sf::Texture& texture) {
    sprite.setTexture(texture);
}
