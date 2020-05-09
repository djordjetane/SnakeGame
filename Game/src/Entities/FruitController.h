#pragma once

namespace Engine {

	class EntityManager;
	class TextureManager;
}

namespace Game {

	class FruitController
	{
	public:
		bool Init(Engine::EntityManager* entityManager_, std::vector<Engine::Texture*>& textures_);
		void Update(float dt, Engine::EntityManager* entityManager_, Engine::SoundManager* soundManager_);
	private:		
		int m_superChange;
		std::vector<Engine::Texture*> m_textures;		
	};
}