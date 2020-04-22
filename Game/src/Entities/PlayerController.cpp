#include "precomp.h"
#include "PlayerController.h"
#include "GameComponents.h"

namespace Game
{
    bool PlayerController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to PlayerController::Init()");
        ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to PlayerController::Init()");
        
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

        return !(entityManager_->GetAllEntitiesWithComponent<Engine::PlayerComponent>().empty());
    }

    void PlayerController::Update(float dt, Engine::EntityManager* entityManager_)
    {
        auto entitiesToMove = entityManager_->GetAllEntitiesWithComponents<Engine::PlayerComponent, Engine::MoverComponent, Engine::InputComponent, Engine::TransformComponent>();
        
        for (auto& entity : entitiesToMove)
        {
            auto move = entity->GetComponent<Engine::MoverComponent>();
            auto input = entity->GetComponent<Engine::InputComponent>();
            auto player = entity->GetComponent<Engine::PlayerComponent>();
            auto transform = entity->GetComponent<Engine::TransformComponent>();    

            auto speed = player->m_PlayerSpeed;
            auto direction = entity->GetComponent<HeadComponent>()->m_Direction;

            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveUp"));
            bool moveDownInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveDown"));
            bool moveLeftInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveLeft"));
            bool moveRightInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveRight"));

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

            move->m_TranslationSpeed.x = speed * ((direction == EHeadDirection::Left ? -1.0f : 0.0f) + (direction == EHeadDirection::Right ? 1.0f : 0.0f));
            move->m_TranslationSpeed.y = speed * ((direction == EHeadDirection::Up ? -1.0f : 0.0f) + (direction == EHeadDirection::Down ? 1.0f : 0.0f));


            // Not to fall out of the window
            if (transform->m_Position.x <= -640.f)
                transform->m_Position.x = 640.f;
            else if(transform->m_Position.x >= 640.f)
                transform->m_Position.x = -640.f;

            if (transform->m_Position.y <= -360.f)
                transform->m_Position.y = 360.f;
            else if (transform->m_Position.y >= 360.f)
                transform->m_Position.y = -360.f;
        }
    }
}
