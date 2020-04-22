#include "precomp.h"
#include "FruitController.h"

#include "GameComponents.h"

namespace Game {
	/*
	static float GetRandomPosition()
	{

	}
	*/
	bool FruitController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
	{
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to FruitController::Init()");
		ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to FruitController::Init()");

		auto fruit = std::make_unique<Engine::Entity>();

		fruit->AddComponent<FruitComponent>();
		fruit->AddComponent<Engine::TransformComponent>(0.f, 0.f, 16.f, 16.f);
		fruit->AddComponent<Engine::CollisionComponent>(16.f, 16.f);
		fruit->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

		m_texture = texture_;

		entityManager_->AddEntity(std::move(fruit));

		auto superFruit = std::make_unique<Engine::Entity>();
		superFruit->AddComponent<SuperFruitComponent>();
		superFruit->AddComponent<Engine::TransformComponent>(9000.f, 9000.f, 32.f, 32.f);
		superFruit->AddComponent<Engine::CollisionComponent>(32.f, 32.f);
		superFruit->AddComponent<Engine::SpriteComponent>().m_Image = texture_;
		
		entityManager_->AddEntity(std::move(superFruit));

		m_change = 0;
		m_superChange = 0;

		return true;
	}

	void FruitController::Update(float dt, Engine::EntityManager* entityManager_)
	{

		LOG_INFO("Current time: " + std::to_string(dt));

		auto fruits = entityManager_->GetAllEntitiesWithComponent<FruitComponent>();		

		for (auto& fruit : fruits)
		{			
			auto collider = fruit->GetComponent<Engine::CollisionComponent>();

			for (const auto& entity : collider->m_CollidedWith)
			{
				if (entity->HasComponent<Engine::PlayerComponent>())
				{
					m_change = 361;
				}
			}

			if(m_change > 360)
			{			
				m_change = 0;
				int random_x = rand() % 600;
				int random_y = rand() % 350;
				int mlp_x = rand() % 2 ? 1 : -1;
				int mlp_y = rand() % 2 ? 1 : -1;
				auto transform = fruit->GetComponent<Engine::TransformComponent>();
				transform->m_Position.x = (float)random_x*mlp_x;
				transform->m_Position.y = (float)random_y* mlp_y;
			}			
		}		

		auto superFruit = entityManager_->GetAllEntitiesWithComponent<SuperFruitComponent>().at(0); // Limited to only one at time

		if (!superFruit->GetComponent<SuperFruitComponent>()->m_shown && m_superChange > 240)
		{						
			m_superChange = 0;
			int random_x = rand() % 600;
			int random_y = rand() % 350;
			int mlp_x = rand() % 2 ? 1 : -1;
			int mlp_y = rand() % 2 ? 1 : -1;
			
			float x = (float)random_x * mlp_x;
			float y = (float)random_y * mlp_y;
			
			auto transformator = superFruit->GetComponent<Engine::TransformComponent>();
			transformator->m_Position.x = x;
			transformator->m_Position.y = y;

			superFruit->GetComponent<SuperFruitComponent>()->m_shown = true;
		}		

		else if (superFruit->GetComponent<SuperFruitComponent>()->m_shown)
		{

			auto collider = superFruit->GetComponent<Engine::CollisionComponent>();

			for (const auto& entity : collider->m_CollidedWith)
			{
				if (entity->HasComponent<Engine::PlayerComponent>())
				{
					m_superChange = 271;
				}
			}
			
			if (m_superChange > 270)
			{
				auto transformator = superFruit->GetComponent<Engine::TransformComponent>();
				transformator->m_Position.x = 9000.f;
				transformator->m_Position.y = 9000.f;

				superFruit->GetComponent<SuperFruitComponent>()->m_shown = false;

				m_superChange = 0;
			}
		}

		m_change++;
		m_superChange++;
	}

} // Game