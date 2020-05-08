#pragma once

namespace Game{
	class ScoreController
	{
	public:		
		bool Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_, Engine::Renderer* renderer_);
		bool Update(float dt);
		void RestartScore();		
	private:		
		Engine::EntityManager* m_EntityManager;
		Engine::TextureManager* m_TextureManager;
		Engine::Renderer* m_Renderer;
	};
} // Game