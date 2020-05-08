#include "precomp.h"
#include "Sound.h"

#include <SDL_mixer.h>

namespace Engine
{
    
    bool Sound::LoadSound(std::string sound_path)
    {
        if (m_Sound != nullptr)
        {
            LOG_WARNING("Overwriting already loaded sound with: {}", sound_path);
            Mix_FreeChunk(m_Sound);
        }

        m_Sound = Mix_LoadWAV_RW(SDL_RWFromFile(sound_path.c_str(), "rb"), 1);

        if (m_Sound == nullptr)
        {
            LOG_ERROR("Unable to load sound: {}, Mix_LoadWAV_RW returned error {}", sound_path, Mix_GetError());
            return false;
        }

        return true;
    }

    Sound::Sound(std::string sound_path)
    {
        LoadSound(sound_path);
    }

    Sound::~Sound()
    {
        if (m_Sound != nullptr)
        {
            Mix_FreeChunk(m_Sound);
            m_Sound = nullptr;
        }
    }
}