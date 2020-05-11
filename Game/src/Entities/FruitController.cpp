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
		
		Restart(entityManager_);						

		auto superFruit = std::make_unique<Engine::Entity>();
		superFruit->AddComponent<SuperFruitComponent>();
		superFruit->AddComponent<Engine::TransformComponent>(9000.f, 9000.f, 60.f, 60.f);
		superFruit->AddComponent<Engine::CollisionComponent>(58.f, 58.f);
		superFruit->AddComponent<Engine::SpriteComponent>().m_Image = m_superTextures[rand() % m_superTextures.size()];
		
		entityManager_->AddEntity(std::move(superFruit));
		
		

		return true;
	}

	// ********************************
	// * Updating state for new frame *
	// ********************************
	void FruitController::Update(float dt, Engine::EntityManager* entityManager_, Engine::SoundManager* soundManager_)
	{

		// LOG_INFO("Current time: " + std::to_string(dt));

		auto fruit = entityManager_->GetAllEntitiesWithComponent<FruitComponent>()[0]; // Limited to only one, no need to use vector
		auto sprite = fruit->GetComponent<Engine::SpriteComponent>();		
			
		auto collider = fruit->GetComponent<Engine::CollisionComponent>();

		if(collider->m_CollidedWith.size() > 0)			
			sprite->m_Active = false;		
		else
			sprite->m_Active = true;


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


		// ****************
		// * SuperFruit *
		// ****************
		auto superFruit = entityManager_->GetAllEntitiesWithComponent<SuperFruitComponent>()[0]; // Limited to only one at time
		
		if (!superFruit->GetComponent<SuperFruitComponent>()->m_shown && m_superChange > 360)
		{						
			m_superChange = 0;			

			auto superSprite = superFruit->GetComponent<Engine::SpriteComponent>();
			superSprite->m_Active = false;

			auto [x, y] = GetRandomPosition();
			auto transformator = superFruit->GetComponent<Engine::TransformComponent>();
			transformator->m_Position.x = x+10.f;
			transformator->m_Position.y = y+10.f;			

			while(Engine::CheckForCollision(fruit, superFruit))
			{
				std::tie(transformator->m_Position.x, transformator->m_Position.y) = GetRandomPosition();
			}

			superSprite->m_Image = m_superTextures[rand() % m_superTextures.size()];
			superSprite->m_Active = true;

			superFruit->GetComponent<SuperFruitComponent>()->m_shown = true;
		}		

		else if (superFruit->GetComponent<SuperFruitComponent>()->m_shown)
		{

			// SuperFruit Collision
			auto collider = superFruit->GetComponent<Engine::CollisionComponent>();
			auto superSprite = superFruit->GetComponent<Engine::SpriteComponent>();

			if(collider->m_CollidedWith.size() > 0)
				superSprite->m_Active = false;
			else
				superSprite->m_Active = true;

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

	inline void FruitController::Restart(Engine::EntityManager* entityManager_)
	{
		auto fruitControl = entityManager_->GetAllEntitiesWithComponent<FruitComponent>()[0];
		auto transform = fruitControl->GetComponent<Engine::TransformComponent>();
		auto collisionEntities = entityManager_->GetAllEntitiesWithComponents<HeadComponent, BodyComponent, BumperComponent>();

		int n = collisionEntities.size();

		for(int i = 0; i < n; i++)
		{
			while(Engine::CheckForCollision(fruitControl, collisionEntities[i]))
			{
				i = 0;
				std::tie(transform->m_Position.x, transform->m_Position.y) = GetRandomPosition();
			}
		}

		m_superChange = 0;
	}

} // Game