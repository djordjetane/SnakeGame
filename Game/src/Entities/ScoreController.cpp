#include "precomp.h"
#include "ScoreController.h"

#include "GameComponents.h"


namespace Game{

	bool ScoreController::Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_, Engine::Renderer* renderer_)
	{		
		m_EntityManager = entityManager_;
		m_TextureManager = textureManager_;
		m_Renderer = renderer_;

		auto entity = std::make_unique<Engine::Entity>();
		entity->AddComponent<ScoreComponent>().m_Score = 0;
		entity->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("score");
		entity->AddComponent<Engine::TransformComponent>() = {590.f, -320.f, 80.f, 80.f};

		entityManager_->AddEntity(std::move(entity));

		return true;
	}

	bool ScoreController::Update(float dt)
	{		
		auto entity = m_EntityManager->GetAllEntitiesWithComponent<ScoreComponent>()[0];
		int score = entity->GetComponent<ScoreComponent>()->m_Score;
		m_TextureManager->RemoveTexture("score");
		m_TextureManager->CreateTextTexture(m_Renderer, "score", std::to_string(score));
		entity->GetComponent<Engine::SpriteComponent>()->m_Image = m_TextureManager->GetTexture("score");

		return true;
	}

	void ScoreController::RestartScore()
	{
		auto entity = m_EntityManager->GetAllEntitiesWithComponent<ScoreComponent>()[0];
		entity->GetComponent<ScoreComponent>()->m_Score = 0;
	}

} // Game