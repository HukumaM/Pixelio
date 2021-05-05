#include "AssetManager.hpp"

namespace Engine
{
    AssetManager::AssetManager()
    {
    }
    
    AssetManager::~AssetManager()
    {
    }

    void
    AssetManager::LoadTexture(int16_t id, const std::string &file_path,
                             bool want_repeated)
    {
        auto texture = std::make_unique<sf::Texture>();

        if(texture->loadFromFile(file_path))
        {
            texture->setRepeated(want_repeated);
            this->m_textures[id] = std::move(texture);
        }
    }

    void
    AssetManager::LoadFont(int16_t id, const std::string &file_path)
    {
        auto font = std::make_unique<sf::Font>();

        if (font->loadFromFile(file_path))
        {
            this->m_fonts[id] = std::move(font);
        }
    }

    const sf::Texture &
    AssetManager::GetTexture(int16_t id) const
    {
        return *(this->m_textures.at(id).get());
    }

    const sf::Font &
    AssetManager::GetFont(int16_t id) const
    {
        return *(this->m_fonts.at(id).get());
    }

} // namespace Engine