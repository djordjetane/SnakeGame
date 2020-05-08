#pragma once


namespace Engine
{
    struct Sound;
    struct Music;

    class SoundManager
    {
    public:
        bool CreateSound(std::string name_, std::string path_);
        Sound* GetSound(std::string name_);
        void PlaySound(std::string name_, int loops);

        bool CreateMusic(std::string name_, std::string path_);
        Music* GetMusic(std::string name_);
        void PlayMusic(std::string name_, int loops);
        void StopMusic();
        void PauseMusic();
        int ResumeMusic();
        void ShutDown();

        SoundManager() = default;
    private:
        std::unordered_map<std::string, std::unique_ptr<Sound>> m_Sounds{};
        std::unordered_map<std::string, std::unique_ptr<Music>> m_Music{};
        SoundManager(const SoundManager& other) = delete;
        SoundManager& operator=(SoundManager& other) = delete;
    };
}