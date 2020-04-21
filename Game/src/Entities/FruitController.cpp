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
					m_change = 180;
				}
			}

			if(m_change > 180)
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

		auto superFruits = entityManager_->GetAllEntitiesWithComponent<SuperFruitComponent>();

		if (superFruits.empty() && m_superChange > 240)
		{
			auto fruit = std::make_unique<Engine::Entity>();

			fruit->AddComponent<SuperFruitComponent>();
			
			m_superChange = 0;
			int random_x = rand() % 600;
			int random_y = rand() % 350;
			int mlp_x = rand() % 2 ? 1 : -1;
			int mlp_y = rand() % 2 ? 1 : -1;
			
			float x = (float)random_x * mlp_x;
			float y = (float)random_y * mlp_y;
			fruit->AddComponent<Engine::TransformComponent>(x, y, 32.f, 32.f);
			fruit->AddComponent<Engine::CollisionComponent>(32.f, 32.f);
			fruit->AddComponent<Engine::SpriteComponent>().m_Image = m_texture;
			

			entityManager_->AddEntity(std::move(fruit));
		}		

		else if (!superFruits.empty() && m_superChange > 60)
		{
			
			superFruits[0]->RemoveComponent<Engine::SpriteComponent>();
			superFruits[0]->RemoveComponent<Engine::CollisionComponent>();
			superFruits[0]->RemoveComponent<Engine::TransformComponent>();
			superFruits[0]->RemoveComponent<SuperFruitComponent>();
						
			m_superChange = 0;			
		}

		m_change++;
		m_superChange++;
	}

} // Game