#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>

#include "Sidebar.hpp"
#include "Field.hpp"
#include "Audio.hpp"
#include "AssetManager.hpp"
#include "Button.hpp"

//  An enumeration that stores asset IDs
enum AssetID
{
    Font
};

class Pixelio
{
private:
    //  A variable that stores a time value equal to one frame
    const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);
    sf::Time m_game_time;

private:
    //  Pointer to context assets
    std::unique_ptr<Engine::AssetManager> m_assets;
    //  Pointer to render window
    std::unique_ptr<sf::RenderWindow> m_window;
    // Pointer to context audio
    std::unique_ptr<Engine::Audio> m_audio;
    // Pointer to context field
    std::unique_ptr<Field> m_field;
    std::unique_ptr<Sidebar> m_sidebar;

private:
    sf::IntRect m_field_rect;

public:
    Pixelio();
    ~Pixelio();

private:
    //  Method for initialization class data
    void Init();

    //  Method for processing keystrokes and mouse clicks
    void ProcessInput();

    //  Method for updating the position of sprites, texts
    //  @param  delta_time  time elapsed since the last function call
    void Update(sf::Time delta_time);

    //  Method for drawing sprites and text
    void Draw();

public:
    //  Game launch function
    void Run();

private:
    bool m_pause;
    void setPause(bool state);
    inline bool
    getPause() const { return m_pause; }

    bool m_game_over;
    void setGameOver(bool state);
    inline bool
    getGameOver() const { return m_game_over; }

    bool m_winning;
    void setWinning(bool state);
    inline bool
    getWinning() const { return m_winning; }

private:
    const std::string getValidTime(int time);

private:
    std::unique_ptr<Button> m_btn_restart;
    std::unique_ptr<Button> m_btn_timer;
};
