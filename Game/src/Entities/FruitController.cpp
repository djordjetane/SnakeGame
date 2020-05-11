#include "precomp.h"
#include "ScoreController.h"
#include "FruitController.h"

#include "GameComponents.h"

namespace Game {
	
	std::pair<float, float> GetRandomPosition()
	{
		int random_x = rand() % 16;
		int random_y = rand() % 9;
		int mlp_x = rand() % 2 ? 1 : -1;
		int mlp_y = rand() % 2 ? 1 : -1;

		float x = random_x * mlp_x * 40.f-20.f;
		float y = random_y * mlp_y * 40.f-20.f;

		return { x, y };
	}
	
	// *********************************
	// * Initializing fruit controller *
	// *********************************
	bool FruitController::Init(Engine::EntityManager* entityManager_, std::vector<Engine::Texture*>& textures_, std::vector<Engine::Texture*>& superTextures_)
	{
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to FruitController::Init()");
		ASSERT(textures_.size() != 0, "Must pass texture for fruit to FruitController::Init()");	
		ASSERT(superTextures_.size() != 0, "Must pass texture for superFruit to FruitController::Init()");

		for (auto& texture : textures_)
		{
			ASSERT(texture != nullptr, "Must pass a valid texture to FruitController::Init()");
		}

		for (auto& texture : superTextures_)
		{
			ASSERT(texture != nullptr, "Must pass a valid texture to FruitController::Init()");
		}


		m_textures = textures_;
		m_superTextures = superTextures_;

		auto fruit = std::make_unique<Engine::Entity>();

		fruit->AddComponent<FruitComponent>();
		auto [x, y] = GetRandomPosition();		
		fruit->AddComponent<Engine::CollisionComponent>(38.f, 38.f);
		fruit->AddComponent<Engine::SpriteComponent>().m_Image = m_textures[rand() % m_textures.size()];		
		fruit->AddComponent<Engine::TransformComponent>(x, y, 40.f, 40.f);						
		entityManager_->AddEntity(std::move(fruit));

		auto fruitControl = entityManager_->GetAllEntitiesWithComponent<FruitComponent>()[0];
		auto collider = fruitControl->GetComponent<Engine::CollisionComponent>();

		while (collider->m_CollidedWith.size() != 0)
		{
			auto [x, y] = GetRandomPosition();
			fruitControl->GetComponent<Engine::TransformComponent>()->m_Position.x = x;
			fruitControl->GetComponent<Engine::TransformComponent>()->m_Position.y = y;

			m_FruitPosition = {x, y};
		}

		auto superFruit = std::make_unique<Engine::Entity>();
		superFruit->AddComponent<SuperFruitComponent>();
		superFruit->AddComponent<Engine::TransformComponent>(9000.f, 9000.f, 60.f, 60.f);
		superFruit->AddComponent<Engine::CollisionComponent>(58.f, 58.f);
		superFruit->AddComponent<Engine::SpriteComponent>().m_Image = m_superTextures[rand() % m_superTextures.size()];
		
		entityManager_->AddEntity(std::move(superFruit));
		
		m_superChange = 0;

		return true;
	}

	// ********************************
	// * Updating state for new frame *
	// ********************************
	void FruitController::Update(float dt, Engine::EntityManager* entityManager_, Engine::SoundManager* soundManager_)
	{

		LOG_INFO("Current time: " + std::to_string(dt));

		auto fruits = entityManager_->GetAllEntitiesWithComponent<FruitComponent>();		

		for (auto& fruit : fruits)
		{			
			auto collider = fruit->GetComponent<Engine::CollisionComponent>();

			for (const auto& entity : collider->m_CollidedWith)
			{
				if (entity->HasComponent<HeadComponent>())
				{					
					entity->GetComponent<HeadComponent>()->m_HasEatenFruit = true;
					auto [x, y] = GetRandomPosition();
					auto transform = fruit->GetComponent<Engine::TransformComponent>();
					transform->m_Position.x = x;
					transform->m_Position.y = y;
					fruit->GetComponent<Engine::SpriteComponent>()->m_Image = m_textures[rand() % m_textures.size()];

					auto scoreEntity = entityManager_->GetAllEntitiesWithComponent<ScoreComponent>()[0];
					scoreEntity->GetComponent<ScoreComponent>()->m_Score++;
					soundManager_->PlaySound("eat", 0);
				}

				if (entity->HasComponent<BumperComponent>() || entity->HasComponent<BodyComponent>() || entity->HasComponent<SuperFruitComponent>())
				{
					auto [x, y] = GetRandomPosition();
					auto transform = fruit->GetComponent<Engine::TransformComponent>();
					transform->m_Position.x = x;
					transform->m_Position.y = y;
				}
			}					
		}		


		// ****************
		// * SuperFruit *
		// ****************
		auto superFruit = entityManager_->GetAllEntitiesWithComponent<SuperFruitComponent>().at(0); // Limited to only one at time
		
		if (!superFruit->GetComponent<SuperFruitComponent>()->m_shown && m_superChange > 360)
		{						
			m_superChange = 0;
			auto x = m_FruitPosition.x;
			auto y = m_FruitPosition.y;

			while(x == m_FruitPosition.x && y == m_FruitPosition.y)
			{
				std::tie(x, y) = GetRandomPosition();
			}
			
			auto transformator = superFruit->GetComponent<Engine::TransformComponent>();
			transformator->m_Position.x = x+10.f;
			transformator->m_Position.y = y+10.f;

			superFruit->GetComponent<Engine::SpriteComponent>()->m_Image = m_superTextures[rand() % m_superTextures.size()];

			superFruit->GetComponent<SuperFruitComponent>()->m_shown = true;
		}		

		else if (superFruit->GetComponent<SuperFruitComponent>()->m_shown)
		{

			// SuperFruit Collision
			auto collider = superFruit->GetComponent<Engine::CollisionComponent>();

			for (const auto& entity : collider->m_CollidedWith)
			{
				if (entity->HasComponent<HeadComponent>())
				{
					m_superChange = 391;
					entity->GetComponent<HeadComponent>()->m_HasEatenSuperFruit = true;
					auto scoreEntity = entityManager_->GetAllEntitiesWithComponent<ScoreComponent>()[0];
					scoreEntity->GetComponent<ScoreComponent>()->m_Score+=2;
					soundManager_->PlaySound("superfruit_1", 0);
				}

				if (entity->HasComponent<BumperComponent>() || entity->HasComponent<BodyComponent>() || entity->HasComponent<FruitComponent>())
				{
					auto [x, y] = GetRandomPosition();
					auto transform = superFruit->GetComponent<Engine::TransformComponent>();
					transform->m_Position.x = x+10.f;
					transform->m_Position.y = y+10.f;
				}
			}
			
			// TimeOut 
			if (m_superChange > 390)
			{
				auto transformator = superFruit->GetComponent<Engine::TransformComponent>();
				transformator->m_Position.x = 9000.f;
				transformator->m_Position.y = 9000.f;

				superFruit->GetComponent<SuperFruitComponent>()->m_shown = false;

				m_superChange = 0;
			}
		}
		
		m_superChange++;
	}

} // Game