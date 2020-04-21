#pragma once

namespace Engine {

	class EntityManager;
	class TextureManager;
}

namespace Game {

	class FruitController
	{
	public:
		bool Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_);
		void Update(float dt, Engine::EntityManager* entityManager_);
	private:
		int m_change;
		int m_superChange;
		Engine::Texture* m_texture;
	};
}