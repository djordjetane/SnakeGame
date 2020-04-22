#include "precomp.h"
#include "PlayerController.h"
#include "GameComponents.h"

namespace Game
{
    bool PlayerController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to PlayerController::Init()");
        ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to PlayerController::Init()");

        m_framerate = 10;
        m_passedTime;

        auto player = std::make_unique<Engine::Entity>();

        player->AddComponent<Engine::TransformComponent>(-300.0f, 0.f, 20.f, 20.f);
        player->AddComponent<Engine::CollisionComponent>(20.f, 20.f);
        player->AddComponent<Engine::PlayerComponent>(200.f);
        player->AddComponent<Engine::InputComponent>();
        player->AddComponent<Engine::MoverComponent>();
        player->AddComponent<HeadComponent>(EHeadDirection::Right);
        player->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

        auto inputComp = player->GetComponent<Engine::InputComponent>();

        inputComp->inputActions.push_back({ fmt::format("Player1MoveUp") });
        inputComp->inputActions.push_back({ fmt::format("Player1MoveDown") });
        inputComp->inputActions.push_back({ fmt::format("Player1MoveLeft") });
        inputComp->inputActions.push_back({ fmt::format("Player1MoveRight") });

        entityManager_->AddEntity(std::move(player));        

        for (int i = 1; i < 25; i++) {
        
            player=std::make_unique<Engine::Entity>();
            player->AddComponent<Engine::TransformComponent>(-300.0f-20.f*i, 0.f, 20.f, 20.f);
            player->AddComponent<Engine::CollisionComponent>(20.f, 20.f);
            player->AddComponent<Engine::PlayerComponent>(200.f);
            player->AddComponent<Engine::MoverComponent>();
            player->AddComponent<BodyComponent>(i);
            player->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

            if (i > 4) {
                player->GetComponent<Engine::SpriteComponent>()->m_Active = false;
            }

            entityManager_->AddEntity(std::move(player));
        
        }

        auto data = std::make_unique<Engine::Entity>();;
        data->AddComponent<PositionComponent>();

        entityManager_->AddEntity(std::move(data));

        return !(entityManager_->GetAllEntitiesWithComponent<Engine::PlayerComponent>().empty());
    }

    void PlayerController::Update(float dt, Engine::EntityManager* entityManager_)
    {
        //count passed time
        m_passedTime += dt;
        float timeTreshold = 1.f / m_framerate;

        int snakeLength;

        auto headEntities = entityManager_->GetAllEntitiesWithComponents<Engine::PlayerComponent, Engine::MoverComponent, Engine::InputComponent, Engine::TransformComponent>();
        auto bodyEntities = entityManager_->GetAllEntitiesWithComponents<BodyComponent,Engine::PlayerComponent, Engine::TransformComponent>();
        auto dataEntities=entityManager_->GetAllEntitiesWithComponent<PositionComponent>();

        for (auto& entity : headEntities)
        {
            auto move = entity->GetComponent<Engine::MoverComponent>();
            auto input = entity->GetComponent<Engine::InputComponent>();
            auto player = entity->GetComponent<Engine::PlayerComponent>();
            auto transform = entity->GetComponent<Engine::TransformComponent>();    

            auto speed = player->m_PlayerSpeed;
            auto direction = entity->GetComponent<HeadComponent>()->m_Direction;
            auto position = transform->m_Position;

            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveUp"));
            bool moveDownInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveDown"));
            bool moveLeftInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveLeft"));
            bool moveRightInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveRight"));

            for (auto& data : dataEntities) {
                data->GetComponent<PositionComponent>()->m_Positions[0] = position;
                snakeLength = data->GetComponent<PositionComponent>()->m_CurrentLength;
            }

            if (moveUpInput && !(direction == EHeadDirection::Down)) {
                entity->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Up;
            }
            else if (moveDownInput && !(direction == EHeadDirection::Up)) {
                entity->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Down;
            }
            else if (moveLeftInput && !(direction == EHeadDirection::Right)) {
                entity->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Left;
            }
            else if (moveRightInput && !(direction == EHeadDirection::Left)) {
                entity->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Right;
            }

            direction = entity->GetComponent<HeadComponent>()->m_Direction;
            //if enough time has passed we can activate the system
            if (m_passedTime > timeTreshold) {
                move->m_TranslationSpeed.x = 20 * ((direction == EHeadDirection::Left ? -1.0f : 0.0f) + (direction == EHeadDirection::Right ? 1.0f : 0.0f));
                move->m_TranslationSpeed.y = 20 * ((direction == EHeadDirection::Up ? -1.0f : 0.0f) + (direction == EHeadDirection::Down ? 1.0f : 0.0f));
            
                auto collider = entity->GetComponent<Engine::CollisionComponent>();

                for (const auto& entity : collider->m_CollidedWith)
                {
                    if (entity->HasComponent<FruitComponent>())
                    {
                        ActivateBodyPart(entityManager_,snakeLength);
                        for (auto& data : dataEntities) {
                            data->GetComponent<PositionComponent>()->m_CurrentLength = ++snakeLength;
                        }
                    }
                }
            
            }
            else {
                move->m_TranslationSpeed = { 0.f,0.f };
            }
        }

        for (auto& entity : bodyEntities) {
            auto index = entity->GetComponent<BodyComponent>()->m_Index;
            auto position = entity->GetComponent<Engine::TransformComponent>()->m_Position;
            
            for (auto& data : dataEntities) {
                data->GetComponent<PositionComponent>()->m_Positions[index] = position;
            }
        }

        //if enough time has passed we can activate the system
        
        for (auto& entity : bodyEntities) {
            if (m_passedTime > timeTreshold) {
                auto index = entity->GetComponent<BodyComponent>()->m_Index;
                auto position = entity->GetComponent<Engine::TransformComponent>()->m_Position;
 
                for (auto& data : dataEntities) {
                    entity->GetComponent<Engine::MoverComponent>()->m_TranslationSpeed = data->GetComponent<PositionComponent>()->m_Positions[index - 1] - position;
                }
            }
            else {
                entity->GetComponent<Engine::MoverComponent>()->m_TranslationSpeed = { 0.f,0.f };
            }
        }

        if (m_passedTime > timeTreshold) {
            //reset time counter
            m_passedTime = 0;
        }
    }
    void PlayerController::ActivateBodyPart(Engine::EntityManager* entityManager_, int index)
    {
        auto bodyPartEntities = entityManager_->GetAllEntitiesWithComponent<BodyComponent>();

        for (auto entity : bodyPartEntities) {
            if (entity->GetComponent<BodyComponent>()->m_Index == index) {
                entity->GetComponent<Engine::SpriteComponent>()->m_Active = true;
            }
        }
    }
}
