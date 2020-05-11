#include "precomp.h"
#include "Texture.h"
#include "Render/Renderer.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace Engine
{
    bool Texture::LoadTexture(Renderer* renderer_, std::string path_)
    {
        if (m_Texture != nullptr)
        {
            LOG_WARNING("Overwriting already loaded texture with: {}", path_);
            SDL_DestroyTexture(m_Texture);
        }

        m_Texture = IMG_LoadTexture(renderer_->GetNativeRenderer(), path_.c_str());

        if (m_Texture == nullptr)
        {
            LOG_ERROR("Unable to load texture: {}, SDL_Image returned error {}", path_, IMG_GetError());
            return false;
        }

        return true;
    }

    bool Texture::LoadTextTexture(Renderer* renderer_, std::string text_)
    {
        if (m_Texture != nullptr)
        {
            LOG_WARNING("Overwriting already loaded texture with: {}", text_);
            SDL_DestroyTexture(m_Texture);
        }

        auto font = TTF_OpenFont("..\\Data\\Fonts\\Sans.ttf", 48);

        SDL_Color White = {255, 255, 255};  

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text_.c_str(), White); 
        m_Texture = SDL_CreateTextureFromSurface(renderer_->GetNativeRenderer(), surfaceMessage);

        SDL_FreeSurface(surfaceMessage);
        TTF_CloseFont(font);

        return true;
    }

    Texture::Texture(Renderer* renderer_, std::string path_)
    {
        LoadTexture(renderer_, path_);
    }

    Texture::~Texture()
    {
        if (m_Texture != nullptr)
        {
            SDL_DestroyTexture(m_Texture);
        }
    }
}
