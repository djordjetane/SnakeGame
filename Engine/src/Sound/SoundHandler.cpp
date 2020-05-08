#include "precomp.h"
#include "SoundHandler.h"

#include <SDL.h>
#include <SDL_mixer.h>

namespace Engine
{
	bool SoundHandler::Init() {

		if (SDL_Init(SDL_INIT_AUDIO) < 0) {
			LOG_CRITICAL("Unable to init SDL Audio {}", SDL_GetError());
			return false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
			LOG_CRITICAL("Mix_OpenAudio Error {}", Mix_GetError());
			return false;
		}
		return true;
	}

	bool SoundHandler::Shutdown() {

		if (Mix_PlayingMusic() == 1) {
			Mix_HaltMusic();
		}

		Mix_Quit();

		return true;
	}
}