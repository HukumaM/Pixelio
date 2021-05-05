#include <iostream>

#include "Pixelio.hpp"

#include <SFML/Window/Event.hpp>

Pixelio::Pixelio()
    : m_assets(std::make_unique<Engine::AssetManager>()),
      m_window(std::make_unique<sf::RenderWindow>()),
      m_audio(std::make_unique<Engine::Audio>()),
      m_field(std::make_unique<Field>()),
      m_sidebar(std::make_unique<Sidebar>()),
      m_field_rect(sf::IntRect(0, 0, 800, 800)),
      m_pause(true),
      m_game_over(false),
      m_winning(false)
{
    m_window->create(sf::VideoMode(1000, 800), "Pixelio",
                     sf::Style::Titlebar |
                         sf::Style::Close);

    m_window->setPosition(sf::Vector2i(660, 180));

    m_audio->LoadSound(Engine::SoundID::Click, "click.wav");
    m_audio->LoadSound(Engine::SoundID::DeleteCell, "deletecell.wav");
    m_audio->GetSound(Engine::SoundID::DeleteCell).setPitch(0.7f);
    m_audio->LoadSound(Engine::SoundID::Winning, "winning.wav");
    m_audio->LoadSound(Engine::SoundID::GameOver, "gameover.wav");

    m_assets->LoadFont(AssetID::Font, "Oswald-Regular.ttf");
    m_sidebar->Init(m_assets->GetFont(AssetID::Font));
    m_field->Init();

    m_btn_timer = std::make_unique<Button>("00:00", m_assets->GetFont(AssetID::Font),
                                           25, sf::Vector2f(200.f, 50.f),
                                           sf::Vector2f(900.f, 325.f));
    m_btn_restart = std::make_unique<Button>("PIXELIO", m_assets->GetFont(AssetID::Font),
                                             25, sf::Vector2f(200.f, 50.f),
                                             sf::Vector2f(900.f, 375.f));

    m_game_time = sf::Time::Zero;
}

Pixelio::~Pixelio()
{
}

void Pixelio::Run()
{
    //  The clock variable required to determine the elapsed time per cycle
    sf::Clock clock;
    //  A variable required to store the time elapsed since the last frame
    sf::Time time_since_last_frame{sf::Time::Zero};

    while (m_window->isOpen())
    {
        time_since_last_frame += clock.restart();
        while (time_since_last_frame > TIME_PER_FRAME)
        {
            time_since_last_frame -= TIME_PER_FRAME;

            this->ProcessInput();
            this->Update(TIME_PER_FRAME);
            this->Draw();
        }
    }
}

void Pixelio::ProcessInput()
{
    sf::Event event;
    while (m_window->pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::EventType::Closed:
        {
            m_window->close();
            break;
        }
        case sf::Event::EventType::LostFocus:
        {
            if (!this->getGameOver() && !this->getWinning())
            {
                setPause(true);
            }
            break;
        }
        case sf::Event::EventType::GainedFocus:
        {
            if (!this->getGameOver() && !this->getWinning())
            {
                setPause(false);
            }
            break;
        }
        case sf::Event::EventType::KeyPressed:
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Key::Escape:
            {
                m_window->close();
                break;
            }
            case sf::Keyboard::Key::Z:
            {
                if (event.key.control)
                {
                    m_audio->GetSound(Engine::SoundID::Click).play();
                    m_sidebar->increaseWidth(-5);
                    m_sidebar->increaseHeight(-5);
                    m_sidebar->btn_map_size
                        ->setString("\t  SIZE\nWIDTH { " +
                                    std::to_string(m_sidebar->getWidth()) +
                                    " }\nHEIGHT { " +
                                    std::to_string(m_sidebar->getHeight()) + " }");
                }
                break;
            }
            case sf::Keyboard::Key::X:
            {
                if (event.key.control)
                {
                    m_audio->GetSound(Engine::SoundID::Click).play();
                    m_sidebar->increaseWidth(5);
                    m_sidebar->increaseHeight(5);
                    m_sidebar->btn_map_size
                        ->setString("\t  SIZE\nWIDTH { " +
                                    std::to_string(m_sidebar->getWidth()) +
                                    " }\nHEIGHT { " +
                                    std::to_string(m_sidebar->getHeight()) + " }");
                }
                break;
            }
            case sf::Keyboard::Key::C:
            {
                m_audio->GetSound(Engine::SoundID::Click).play();
                m_field->createField(m_sidebar->getWidth(),
                                     m_sidebar->getHeight(),
                                     m_sidebar->getComplexity());
                m_game_time = sf::Time::Zero;

                m_btn_restart->setString("PIXELIO");
                this->setGameOver(false);
                this->setWinning(false);
                this->setPause(false);

                break;
            }
            default:
                break;
            }
        }
        case sf::Event::EventType::MouseMoved:
        {
            if (event.mouseMove.x > 800)
            {
                m_sidebar->controlPanel(sf::Mouse::getPosition(*m_window));
            }
            break;
        }
        case sf::Event::EventType::MouseButtonPressed:
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                sf::Vector2i mouse_position(sf::Mouse::getPosition(*m_window));
                sf::IntRect mouse(mouse_position, sf::Vector2i(1, 1));

                if (m_sidebar->btn_crt->onButton(mouse_position))
                {
                    m_audio->GetSound(Engine::SoundID::Click).play();
                    m_field->createField(m_sidebar->getWidth(),
                                         m_sidebar->getHeight(),
                                         m_sidebar->getComplexity());
                    m_game_time = sf::Time::Zero;

                    m_btn_restart->setString("PIXELIO");
                    this->setGameOver(false);
                    this->setWinning(false);
                    this->setPause(false);
                }
                else if (m_sidebar->btn_inc_clr->onButton(mouse_position))
                {
                    m_audio->GetSound(Engine::SoundID::Click).play();
                    if (m_sidebar->increaseComplexity(1))
                    {
                        m_sidebar->btn_clr
                            ->setString("COLOR { " +
                                        std::to_string(m_sidebar->getComplexity()) + " }");
                    }
                }
                else if (m_sidebar->btn_dec_clr->onButton(mouse_position))
                {
                    m_audio->GetSound(Engine::SoundID::Click).play();
                    if (m_sidebar->increaseComplexity(-1))
                    {
                        m_sidebar->btn_clr
                            ->setString("COLOR { " +
                                        std::to_string(m_sidebar->getComplexity()) + " }");
                    }
                }
                else if (m_sidebar->btn_inc_width->onButton(mouse_position))
                {
                    m_audio->GetSound(Engine::SoundID::Click).play();
                    if (m_sidebar->increaseWidth(1))
                    {
                        m_sidebar->btn_map_size
                            ->setString("\t  SIZE\nWIDTH { " +
                                        std::to_string(m_sidebar->getWidth()) +
                                        " }\nHEIGHT { " +
                                        std::to_string(m_sidebar->getHeight()) + " }");
                    }
                }
                else if (m_sidebar->btn_dec_width->onButton(mouse_position))
                {
                    m_audio->GetSound(Engine::SoundID::Click).play();
                    if (m_sidebar->increaseWidth(-1))
                    {
                        m_sidebar->btn_map_size
                            ->setString("\t  SIZE\nWIDTH { " +
                                        std::to_string(m_sidebar->getWidth()) +
                                        " }\nHEIGHT { " +
                                        std::to_string(m_sidebar->getHeight()) + " }");
                    }
                }
                else if (m_sidebar->btn_inc_height->onButton(mouse_position))
                {
                    m_audio->GetSound(Engine::SoundID::Click).play();
                    if (m_sidebar->increaseHeight(1))
                    {
                        m_sidebar->btn_map_size
                            ->setString("\t  SIZE\nWIDTH { " +
                                        std::to_string(m_sidebar->getWidth()) +
                                        " }\nHEIGHT { " +
                                        std::to_string(m_sidebar->getHeight()) + " }");
                    }
                }
                else if (m_sidebar->btn_dec_height->onButton(mouse_position))
                {
                    m_audio->GetSound(Engine::SoundID::Click).play();
                    if (m_sidebar->increaseHeight(-1))
                    {
                        m_sidebar->btn_map_size
                            ->setString("\t  SIZE\nWIDTH { " +
                                        std::to_string(m_sidebar->getWidth()) +
                                        " }\nHEIGHT { " +
                                        std::to_string(m_sidebar->getHeight()) + " }");
                    }
                }

                if (!this->getPause() && !this->getGameOver() &&
                    !this->getWinning())
                {
                    if (mouse.intersects(m_field_rect))
                    {
                        if (m_field->deleteCell(sf::Mouse::getPosition(*m_window)))
                        {
                            m_audio->GetSound(Engine::SoundID::DeleteCell).play();
                            setGameOver(m_field->isGameOver());
                            setWinning(m_field->isWinning());
                        }
                    }
                }
            }
            break;
        }
        default:
            break;
        }
    }
}

void Pixelio::Update(sf::Time delta_time)
{
    if (!this->getPause())
    {
        if (!this->getGameOver() && !this->getWinning())
        {
            m_game_time += delta_time;

            auto minutes = static_cast<int>(m_game_time.asSeconds()) / 60;
            auto seconds = static_cast<int>(m_game_time.asSeconds()) % 60;

            m_btn_timer->setString(getValidTime(minutes) + ":" +
                                   getValidTime(seconds));
        }

        if (this->getGameOver())
        {
            m_audio->GetSound(Engine::SoundID::GameOver).play();
            m_btn_restart->setString("YOU LOSE!");
            this->setPause(true);
        }
        if (this->getWinning())
        {
            m_audio->GetSound(Engine::SoundID::Winning).play();
            m_btn_restart->setString("YOU WIN!");
            this->setPause(true);
        }
    }
}

void Pixelio::Draw()
{
    m_window->clear(sf::Color(35, 39, 43));
    m_field->Draw(*m_window);
    m_sidebar->Draw(*m_window);
    m_btn_restart->Draw(*m_window);
    m_btn_timer->Draw(*m_window);
    m_window->display();
}

const std::string Pixelio::getValidTime(int time)
{
    return (time < 10 ? "0" + std::to_string(time) : std::to_string(time));
}

void Pixelio::setPause(bool state)
{
    m_pause = state;
}

void Pixelio::setGameOver(bool state)
{
    m_game_over = state;
}

void Pixelio::setWinning(bool state)
{
    m_winning = state;
}
