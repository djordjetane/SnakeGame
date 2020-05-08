#include "precomp.h"
#include "SoundManager.h"

#include "Sound/Sound.h"
#include "Sound/Music.h"
#include <SDL_mixer.h>

namespace Engine
{

    bool SoundManager::CreateSound(std::string name_, std::string path_)
    {
        if (m_Sounds.find(name_) != m_Sounds.end()) {
            LOG_ERROR("Attempting to create a sound twice! name: {}, path: {}", name_, path_);
            return false;
        }

        m_Sounds.emplace(name_, std::make_unique<Sound>(path_));

        return m_Sounds.at(name_)->m_Sound != nullptr;
    }

    bool SoundManager::CreateMusic(std::string name_, std::string path_)
    {
        if (m_Music.find(name_) != m_Music.end()) {
            LOG_ERROR("Attempting to create a music twice! name: {}, path: {}", name_, path_);
            return false;
        }

        m_Music.emplace(name_, std::make_unique<Music>(path_));

        return m_Music.at(name_)->m_Music != nullptr;
    }

    Sound* SoundManager::GetSound(std::string name_)
    {
        if (m_Sounds.find(name_) == m_Sounds.end()) {
            LOG_ERROR("Attempting to get a sound that doesn't exist! name: {}", name_);
            return nullptr;
        }

        return m_Sounds.at(name_).get();
    }

    Music* SoundManager::GetMusic(std::string name_)
    {
        if (m_Music.find(name_) == m_Music.end()) {
            LOG_ERROR("Attempting to get a music that doesn't exist! name: {}", name_);
            return nullptr;
        }

        return m_Music.at(name_).get();
    }

    void SoundManager::PlaySound(std::string name_, int loops) {
        auto sound = GetSound(name_);
        if (sound == nullptr) {
            LOG_ERROR("Attempting to get a sound that doesn't exist! name: {}", name_);
        }
        else {
            
            Mix_PlayChannel(-1, sound->m_Sound, loops);
        }
    }

    void SoundManager::PlayMusic(std::string name_,int loops) {
        auto music = GetMusic(name_);
        if (music == nullptr) {
            LOG_ERROR("Attempting to get a music that doesn't exist! name: {}", name_);
        }
        else {
            Mix_PlayMusic(music->m_Music, loops);
        }
    }

    void SoundManager::StopMusic() {
        if (Mix_PlayingMusic() == 1) {
            Mix_HaltMusic();
        }
    }

    void SoundManager::PauseMusic() {
        if (Mix_PlayingMusic() == 1) {
            Mix_PauseMusic();
        }
    }

    int SoundManager::ResumeMusic() {
        if (Mix_PausedMusic() == 1) {
            Mix_ResumeMusic();
            return 1;
        }
        return 0;
    }

    void SoundManager::ShutDown() {
        if (Mix_PlayingMusic() == 1) {
            Mix_HaltMusic();
        }
        for (auto it = m_Music.begin(); it != m_Music.end(); ++it) {
            if (it->second->m_Music != nullptr) {
                Mix_FreeMusic(it->second->m_Music);
                it->second->m_Music = nullptr;
            }
        }
    }

}
