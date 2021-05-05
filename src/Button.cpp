#include "Button.hpp"

Button::Button()
    : text(),
      rectangle()
{
}

Button::Button(const sf::String &string,
               const sf::Font &font,
               uint16_t character_size,
               const sf::Vector2f &size,
               const sf::Vector2f &position)
    : text(string, font, character_size),
      rectangle(size)
{
    rectangle.setOrigin(rectangle.getSize().x / 2,
                        rectangle.getSize().y / 2);
    text.setOrigin(text.getLocalBounds().width / 2,
                   text.getLocalBounds().height / 2);
    rectangle.setPosition(position);
    text.setPosition(position);

    rectangle.setFillColor(sf::Color(35, 39, 43));
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(-2.f);

    text.setStyle(sf::Text::Style::Bold);
    text.setFillColor(sf::Color::White);
}

Button::~Button()
{
}

[[maybe_unused]] bool 
Button::onButton(const sf::Vector2i &mouse_position)
{
    sf::IntRect mouse(mouse_position, sf::Vector2i(1, 1));
    sf::IntRect button(
        getPosition().x - getSize().x / 2,
        getPosition().y - getSize().y / 2,
        getSize().x,
        getSize().y);
    
    if(mouse.intersects(button))
    {
        rectangle.setFillColor(sf::Color(122, 135, 147));
        return true;
    }
    else 
    {
        rectangle.setFillColor(sf::Color(35, 39, 43));
        return false;
    }
}

void Button::setFont(const sf::Font &font)
{
    text.setFont(font);
}

void Button::setString(const sf::String &string)
{
    text.setString(string);
}
void Button::setCharacterSize(uint16_t size)
{
    text.setCharacterSize(size);
}
void Button::setFillColor(const sf::Color &color)
{
    rectangle.setFillColor(color);
}
void Button::setOutlineColor(const sf::Color &color)
{
    rectangle.setOutlineColor(color);
}
void Button::setOutlineThickness(float thickness)
{
    rectangle.setOutlineThickness(thickness);
}
const sf::Vector2f &Button::getPosition() const
{
    return rectangle.getPosition();
}
void Button::setPosition(const sf::Vector2f &position)
{
    rectangle.setPosition(position);
    text.setPosition(position);
}
void Button::setSize(const sf::Vector2f &size)
{
    rectangle.setSize(size);
    text.setPosition(rectangle.getOrigin());
}

const sf::Vector2f &Button::getSize()
{
    return rectangle.getSize();
}

void Button::Draw(sf::RenderWindow &window)
{
    window.draw(rectangle);
    window.draw(text);
}