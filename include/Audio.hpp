#pragma once

#include <map>
#include <memory>

#include <SFML/System/Time.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

namespace Engine
{
    enum Volume
    {
        Min = 0,
        Max = 100
    };

    enum MusicID
    {
        Music,
    };

    enum SoundID
    {
        Click,
        DeleteCell,
        Winning,
        GameOver
    };

    class Audio
    {
    private:
        struct VolumeControl
        {
            float music;
            float sound;
            VolumeControl() : music(Volume::Max), sound(Volume::Max) {}
        };

        // Variable that stores the volume of music
        VolumeControl m_crt_volume;

        // Variable that stores the volume of sounds
        VolumeControl m_svd_volume;

    private:
        //  Variables that stores a map of the music ID values and a pointer to it
        std::map<int16_t, std::unique_ptr<sf::Music>> m_music;

        //  Variables that stores a map of the sound ID values and a pointer to it
        std::map<int16_t, std::unique_ptr<sf::Sound>> m_sound;

        //  Variables that stores a map of the sound buffer ID values and a pointer to it
        std::map<int16_t, std::unique_ptr<sf::SoundBuffer>> m_sound_buffer;

    public:
        Audio();
        ~Audio();

    public:
        // Uploads music to the map by its ID and the path to the source file
        // @param id            Music ID
        // @param file_path     The path to the specified music.
        //                      Must be specified relative to the current project folder
        // @param loop          The need to loop the music
        // @return void
        void LoadMusic(int16_t id, const std::string &file_path,
                       bool loop = false);

        // Uploads sound to the map by its ID and the path to the source file
        // @param id            Sound ID
        // @param file_path     The path to the specified sound.
        //                      Must be specified relative to the current project folder
        // @return void
        void LoadSound(int16_t id, const std::string &file_path);

        //  Returns the music by specified id
        //  @param id           Music ID
        //  @return             Reference to the music of the corresponding identifier
        sf::Music &GetMusic(int16_t id);

        //  Returns the sound by specified id
        //  @param id            Sound ID
        //  @return              Reference to the sound of the corresponding identifier
        sf::Sound &GetSound(int16_t id);

        //

        void VolumeMusicChanging(float value);
        void VolumeSoundChanging(float value);

        inline float
        GetMusicVolume() { return m_crt_volume.music; }

        inline float
        GetSoundVolume() { return m_crt_volume.sound; }

        void TurnOff();
        void TurnOn();
    };

}; //   namespace Engine