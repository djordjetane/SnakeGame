#pragma once

struct Mix_Chunk;

namespace Engine
{
    struct Sound {
        Mix_Chunk* m_Sound{};

        Sound() = default;
        Sound(std::string sound_path);
        bool LoadSound(std::string sound_path);
        ~Sound();
    };
}
