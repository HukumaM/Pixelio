#pragma once

#include <SFML/Graphics.hpp>
#include "Button.hpp"

class Sidebar
{
private:
    int16_t m_width;
    int16_t m_height;
    int16_t m_complexity;

    enum AcceptableValue
    {
        SizeMax = 50,
        SizeMin = 10,
        ComplexityMax = 5,
        ComplexityMin = 2
    };

private:
    sf::IntRect m_sidebar_rect;

public:
    // button create
    std::unique_ptr<Button> btn_crt;

    // button color
    std::unique_ptr<Button> btn_clr;
    // button increase color
    std::unique_ptr<Button> btn_inc_clr;
    // button decrease color
    std::unique_ptr<Button> btn_dec_clr;

    // button map size
    std::unique_ptr<Button> btn_map_size;

    std::unique_ptr<Button> btn_inc_width;
    std::unique_ptr<Button> btn_dec_width;
    std::unique_ptr<Button> btn_inc_height;
    std::unique_ptr<Button> btn_dec_height;

public:
    Sidebar();
    ~Sidebar();

    bool onSidebar(const sf::Vector2i &position);
    void controlPanel(const sf::Vector2i &position);
    void Init(const sf::Font &font);
    void Draw(sf::RenderWindow &window);

private:
    bool validWidth(int16_t value);
    bool validHeight(int16_t value);
    bool validComplexity(int16_t value);

public:
    int16_t getWidth() const;
    int16_t getHeight() const;
    int16_t getComplexity() const;

    [[maybe_unused]] bool
    increaseWidth(int16_t value);
    [[maybe_unused]] bool
    increaseHeight(int16_t value);
    [[maybe_unused]] bool
    increaseComplexity(int16_t value);
};