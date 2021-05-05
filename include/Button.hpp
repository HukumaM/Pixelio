#pragma once

#include <SFML/Graphics.hpp>

class Button
{
private:
    sf::Text text;
    sf::RectangleShape rectangle;

public:
    Button();
    Button(const sf::String &string,
           const sf::Font &font,
           uint16_t character_size,
           const sf::Vector2f &size,
           const sf::Vector2f &position = sf::Vector2f(0.f, 0.f));
    ~Button();

    [[maybe_unused]] bool
    onButton(const sf::Vector2i &mouse_position);
    
    void setFont(const sf::Font &font);
    void setString(const sf::String &string);
    void setCharacterSize(uint16_t size);

    void setFillColor(const sf::Color &color);
    void setOutlineColor(const sf::Color &color);
    void setOutlineThickness(float thickness);

    void setSize(const sf::Vector2f &size);
    void setPosition(const sf::Vector2f &position);
    
    const sf::Vector2f &getSize();
    const sf::Vector2f &getPosition() const;

    void Draw(sf::RenderWindow &window);
};