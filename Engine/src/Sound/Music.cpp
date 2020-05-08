#include "precomp.h"
#include "Music.h"

namespace Engine
{

    bool Music::LoadMusic(std::string music_path)
    {
        if (m_Music != nullptr)
        {
            LOG_WARNING("Overwriting already loaded music with: {}", music_path);
            Mix_FreeMusic(m_Music);
        }

        m_Music = Mix_LoadMUS(music_path.c_str());

        if (m_Music == nullptr)
        {
            LOG_ERROR("Unable to load music: {}, Mix_LoadMUS returned error {}", music_path, Mix_GetError());
            return false;
        }

        return true;
    }

    Music::Music(std::string music_path)
    {
        LoadMusic(music_path);
    }

    Music::~Music()
    {
        if (m_Music != nullptr)
        {
            Mix_FreeMusic(m_Music);
            m_Music = nullptr;
        }
    }
}