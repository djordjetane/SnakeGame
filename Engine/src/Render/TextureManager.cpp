#include "precomp.h"
#include "TextureManager.h"

#include "Render/Texture.h"
#include "Render/Renderer.h"

namespace Engine
{

    bool TextureManager::CreateTexture(Renderer* renderer_, std::string name_, std::string path_)
    {
        if (m_Textures.find(name_) != m_Textures.end()) {
            LOG_ERROR("Attempting to create a texture twice! name: {}, path: {}", name_, path_);
            return false;
        }

        m_Textures.emplace(name_, std::make_unique<Texture>(renderer_, path_));

        return m_Textures.at(name_)->m_Texture != nullptr;
    }

    bool TextureManager::CreateTextTexture(Renderer* renderer_, std::string name_, std::string text_)
    {
        if (m_Textures.find(name_) != m_Textures.end()) {
            LOG_ERROR("Attempting to create a texture twice! name: {}, path: {}", name_, text_);
            return false;
        }

        auto texturePtr = std::make_unique<Texture>();
        texturePtr->LoadTextTexture(renderer_, text_);

        m_Textures.emplace(name_, std::move(texturePtr));

        return m_Textures.at(name_)->m_Texture != nullptr;
    }

    Texture* TextureManager::GetTexture(std::string name_)
    {
        if (m_Textures.find(name_) == m_Textures.end()) {
            LOG_ERROR("Attempting to get a texture that doesn't exist! name: {}", name_);
            return nullptr;
        }

        return m_Textures.at(name_).get();
    }

    void TextureManager::RemoveTexture(std::string name_)
    {
        if (m_Textures.find(name_) == m_Textures.end()) {
            LOG_ERROR("Attempting to remove a texture that doesn't exist! name: {}", name_);
            return;
        }

        m_Textures.erase(name_);
    }
}
