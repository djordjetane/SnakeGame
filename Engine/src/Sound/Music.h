#pragma once

#include <SDL_mixer.h>

namespace Engine
{
    struct Music {
        Mix_Music* m_Music{};

        Music() = default;
        Music(std::string music_path);
        bool LoadMusic(std::string music_path);
        ~Music();
    };
}
