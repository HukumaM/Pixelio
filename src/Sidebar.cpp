#include "Sidebar.hpp"

Sidebar::Sidebar()
    : m_width(10),
      m_height(10),
      m_complexity(3),
      m_sidebar_rect(sf::Vector2i(800, 0), sf::Vector2i(200, 800))
{
}

Sidebar::~Sidebar()
{
}

bool Sidebar::validWidth(int16_t value)
{
    return m_width + value <= AcceptableValue::SizeMax &&
           m_width + value >= AcceptableValue::SizeMin;
}
bool Sidebar::validHeight(int16_t value)
{
    return m_height + value <= AcceptableValue::SizeMax &&
           m_height + value >= AcceptableValue::SizeMin;
}
bool Sidebar::validComplexity(int16_t value)
{
    return m_complexity + value <= AcceptableValue::ComplexityMax &&
           m_complexity + value >= AcceptableValue::ComplexityMin;
}

int16_t Sidebar::getWidth() const
{
    return m_width;
}
int16_t Sidebar::getHeight() const
{
    return m_height;
}
int16_t Sidebar::getComplexity() const
{
    return m_complexity;
}

[[maybe_unused]] bool Sidebar::increaseWidth(int16_t value)
{
    if (validWidth(value))
    {
        m_width += value;
        return true;
    }
    return false;
}
[[maybe_unused]] bool Sidebar::increaseHeight(int16_t value)
{
    if (validHeight(value))
    {
        m_height += value;
        return true;
    }
    return false;
}
[[maybe_unused]] bool Sidebar::increaseComplexity(int16_t value)
{
    if (validComplexity(value))
    {
        m_complexity += value;
        return true;
    }
    return false;
}

bool Sidebar::onSidebar(const sf::Vector2i &position)
{
    return sf::IntRect(position, sf::Vector2i(1, 1))
        .intersects(m_sidebar_rect);
}

//void Sidebar::enablingButtons(const sf::Vector2i &position){}

void Sidebar::controlPanel(const sf::Vector2i &position)
{
    btn_crt->onButton(position);
    btn_inc_clr->onButton(position);
    btn_dec_clr->onButton(position);
    btn_inc_width->onButton(position);
    btn_dec_width->onButton(position);
    btn_inc_height->onButton(position);
    btn_dec_height->onButton(position);
}

void Sidebar::Init(const sf::Font &font)
{
    btn_crt = std::make_unique<Button>("CREATE", font, 25,
                                       sf::Vector2f(200.f, 50.f),
                                       sf::Vector2f(900.f, 25.f));
    btn_clr = std::make_unique<Button>("COLOR { " + std::to_string(getComplexity()) + " }", font, 25,
                                       sf::Vector2f(200.f, 50.f),
                                       sf::Vector2f(900.f, 75.f));
    btn_inc_clr = std::make_unique<Button>("+", font, 25,
                                           sf::Vector2f(100.f, 50.f),
                                           sf::Vector2f(850.f, 125.f));
    btn_dec_clr = std::make_unique<Button>("-", font, 25,
                                           sf::Vector2f(100.f, 50.f),
                                           sf::Vector2f(950.f, 125.f));

    btn_map_size = std::make_unique<Button>("\t  SIZE\nWIDTH { " +
                                                std::to_string(getWidth()) +
                                                " }\nHEIGHT { " +
                                                std::to_string(getHeight()) + " }",
                                            font, 20,
                                            sf::Vector2f(200.f, 100.f),
                                            sf::Vector2f(900.f, 200.f));
    btn_inc_width = std::make_unique<Button>("+", font, 25,
                                             sf::Vector2f(50.f, 50.f),
                                             sf::Vector2f(825.f, 275.f));
    btn_dec_width = std::make_unique<Button>("-", font, 25,
                                             sf::Vector2f(50.f, 50.f),
                                             sf::Vector2f(875.f, 275.f));
    btn_inc_height = std::make_unique<Button>("+", font, 25,
                                              sf::Vector2f(50.f, 50.f),
                                              sf::Vector2f(925.f, 275.f));
    btn_dec_height = std::make_unique<Button>("-", font, 25,
                                              sf::Vector2f(50.f, 50.f),
                                              sf::Vector2f(975.f, 275.f));
}

void Sidebar::Draw(sf::RenderWindow &window)
{
    btn_crt->Draw(window);

    btn_clr->Draw(window);
    btn_inc_clr->Draw(window);
    btn_dec_clr->Draw(window);

    btn_map_size->Draw(window);
    btn_inc_width->Draw(window);
    btn_dec_width->Draw(window);

    btn_inc_height->Draw(window);
    btn_dec_height->Draw(window);
}
