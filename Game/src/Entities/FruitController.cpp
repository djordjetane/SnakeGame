#include "precomp.h"
#include "FruitController.h"

#include "GameComponents.h"

namespace Game {
	
	std::pair<float, float> GetRandomPosition()
	{
		int random_x = rand() % 600;
		int random_y = rand() % 350;
		int mlp_x = rand() % 2 ? 1 : -1;
		int mlp_y = rand() % 2 ? 1 : -1;

		float x = random_x * mlp_x;
		float y = random_y * mlp_y;

		return { x, y };
	}
	
	bool FruitController::Init(Engine::EntityManager* entityManager_, std::vector<Engine::Texture*>& textures_)
	{
		ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to FruitController::Init()");
		ASSERT(textures_.size() != 0, "Must pass texture to FruitController::Init()");

		for (auto& texture : textures_)
		{
			ASSERT(texture != nullptr, "Must pass a valid texture to FruitController::Init()");
		}

		m_textures = textures_;

		auto fruit = std::make_unique<Engine::Entity>();

		fruit->AddComponent<FruitComponent>();
		auto [x, y] = GetRandomPosition();
		fruit->AddComponent<Engine::TransformComponent>(x, y, 16.f, 16.f);
		fruit->AddComponent<Engine::CollisionComponent>(16.f, 16.f);
		fruit->AddComponent<Engine::SpriteComponent>().m_Image = m_textures[rand() % m_textures.size()];		

		entityManager_->AddEntity(std::move(fruit));

		auto superFruit = std::make_unique<Engine::Entity>();
		superFruit->AddComponent<SuperFruitComponent>();
		superFruit->AddComponent<Engine::TransformComponent>(9000.f, 9000.f, 32.f, 32.f);
		superFruit->AddComponent<Engine::CollisionComponent>(32.f, 32.f);
		superFruit->AddComponent<Engine::SpriteComponent>().m_Image = m_textures[rand() % m_textures.size()];
		
		entityManager_->AddEntity(std::move(superFruit));
		
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
				if (entity->HasComponent<HeadComponent>())
				{					
					entity->GetComponent<HeadComponent>()->m_HasEatenFruit = true;
					auto [x, y] = GetRandomPosition();
					auto transform = fruit->GetComponent<Engine::TransformComponent>();
					transform->m_Position.x = x;
					transform->m_Position.y = y;
					fruit->GetComponent<Engine::SpriteComponent>()->m_Image = m_textures[rand() % m_textures.size()];
				}
			}					
		}		

		auto superFruit = entityManager_->GetAllEntitiesWithComponent<SuperFruitComponent>().at(0); // Limited to only one at time

		if (!superFruit->GetComponent<SuperFruitComponent>()->m_shown && m_superChange > 360)
		{						
			m_superChange = 0;
			auto [x, y] = GetRandomPosition();
			
			auto transformator = superFruit->GetComponent<Engine::TransformComponent>();
			transformator->m_Position.x = x;
			transformator->m_Position.y = y;

			superFruit->GetComponent<Engine::SpriteComponent>()->m_Image = m_textures[rand() % m_textures.size()];

			superFruit->GetComponent<SuperFruitComponent>()->m_shown = true;
		}		

		else if (superFruit->GetComponent<SuperFruitComponent>()->m_shown)
		{

			auto collider = superFruit->GetComponent<Engine::CollisionComponent>();

			for (const auto& entity : collider->m_CollidedWith)
			{
				if (entity->HasComponent<HeadComponent>())
				{
					m_superChange = 391;
					entity->GetComponent<HeadComponent>()->m_HasEatenSuperFruit = true;
				}
			}
			
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