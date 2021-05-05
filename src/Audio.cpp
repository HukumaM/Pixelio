#include "Audio.hpp"

namespace Engine
{
    Audio::Audio()
        : m_music(std::map<int16_t, std::unique_ptr<sf::Music>>()),
          m_sound(std::map<int16_t, std::unique_ptr<sf::Sound>>()),
          m_sound_buffer(std::map<int16_t, std::unique_ptr<sf::SoundBuffer>>())
    {
    }

    Audio::~Audio()
    {
    }

    void Audio::LoadMusic(int16_t id, const std::string &file_path,
                          bool loop)
    {
        auto music = std::make_unique<sf::Music>();

        if (music->openFromFile(file_path))
        {
            m_music[id] = std::move(music);
            m_music[id]->setLoop(loop);
        }
    }

    void Audio::LoadSound(int16_t id, const std::string &file_path)
    {
        auto sound_buffer = std::make_unique<sf::SoundBuffer>();
        auto sound = std::make_unique<sf::Sound>();

        if (sound_buffer->loadFromFile(file_path))
        {
            m_sound_buffer[id] = std::move(sound_buffer);
            sound->setBuffer(*(m_sound_buffer.at(id).get()));
            m_sound[id] = std::move(sound);
        }
    }

    sf::Music &Audio::GetMusic(int16_t id)
    {
        return *(m_music.at(id).get());
    }

    sf::Sound &Audio::GetSound(int16_t id)
    {
        return *(m_sound.at(id).get());
    }

    void Audio::VolumeMusicChanging(float value)
    {
        if (m_crt_volume.music + value < Volume::Max &&
            m_crt_volume.music + value > Volume::Min)
        {
            m_crt_volume.music += value;
        }
    }
    void Audio::VolumeSoundChanging(float value)
    {
        if (m_crt_volume.sound + value < Volume::Max &&
            m_crt_volume.sound + value > Volume::Min)
        {
            m_crt_volume.sound += value;
        }
    }

    void Audio::TurnOff()
    {
        m_svd_volume.music = m_crt_volume.music;
        m_crt_volume.music = Volume::Min;

        m_svd_volume.sound = m_crt_volume.sound;
        m_crt_volume.sound = Volume::Min;
    }

    void Audio::TurnOn()
    {
        m_crt_volume.music = m_svd_volume.music;
        m_crt_volume.sound = m_svd_volume.sound;
    }

} // namespace Engine