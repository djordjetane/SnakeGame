#include "precomp.h"
#include "DeathScreenController.h"
#include "GameComponents.h"

namespace Game
{
    bool DeathScreen::Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to ResumeScreen::Init()");

        time_passed = 0.f;
        auto background = std::make_unique<Engine::Entity>();
        background->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 1280.f, 740.f);
        background->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("black");
        background->AddComponent<DeathScreenComponent>();
        entityManager_->AddEntity(std::move(background));

        auto stripe = std::make_unique<Engine::Entity>();
        stripe->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 1280.f, 400.f);
        stripe->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("stripe");
        stripe->AddComponent<DeathScreenComponent>();
        entityManager_->AddEntity(std::move(stripe));

        auto youDied = std::make_unique<Engine::Entity>();
        youDied->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 600.f, 450.f);
        youDied->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("you_died");
        youDied->AddComponent<Engine::AlphaComponent>().m_Alpha = 0;
        youDied->AddComponent<DeathScreenComponent>();
        entityManager_->AddEntity(std::move(youDied));

        auto select = std::make_unique<Engine::Entity>();
        select->AddComponent<Engine::TransformComponent>(-200.f, 9250.f, 290.f, 95.f);
        select->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("white");
        select->AddComponent<Engine::InputComponent>();
        select->AddComponent<DeathSelectComponent>();
        auto input = select->GetComponent<Engine::InputComponent>();

        input->inputActions.push_back({ fmt::format("Select"), Engine::EInputActionState::JustPressed });
        input->inputActions.push_back({ fmt::format("Player1MoveLeft"), Engine::EInputActionState::JustPressed });
        input->inputActions.push_back({ fmt::format("Player1MoveRight"), Engine::EInputActionState::JustPressed });

        entityManager_->AddEntity(std::move(select));

        auto retry = std::make_unique<Engine::Entity>();
        retry->AddComponent<Engine::TransformComponent>(-200.f, 9250.f, 300.f, 95.f);
        retry->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("retry");
        retry->AddComponent<DeathScreenComponent>();
        entityManager_->AddEntity(std::move(retry));

        auto menu = std::make_unique<Engine::Entity>();
        menu->AddComponent<Engine::TransformComponent>(200.f, 9250.f, 300.f, 95.f);
        menu->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("main_menu");
        menu->AddComponent<DeathScreenComponent>();
        entityManager_->AddEntity(std::move(menu));

        return true;
    }

    void DeathScreen::Update(float dt, Engine::EntityManager* entityManager_, Engine::CurrentGameState* gameState, Engine::GameStates gameMode)
    {
        
        if (time_passed <= 2) {
            time_passed += dt;
        }
        auto deathComponents = entityManager_->GetAllEntitiesWithComponents<DeathScreenComponent, Engine::TransformComponent>();
        auto select = entityManager_->GetAllEntitiesWithComponents<DeathSelectComponent, Engine::TransformComponent, Engine::InputComponent>();
        auto youDied = entityManager_->GetAllEntitiesWithComponents <DeathScreenComponent, Engine::TransformComponent,Engine::AlphaComponent>()[0];

        auto alpha = youDied->GetComponent<Engine::AlphaComponent>();
        alpha->m_Alpha = static_cast<uint8_t>((time_passed / 2) * 250);
        auto deathTrasform = youDied->GetComponent<Engine::TransformComponent>();
        deathTrasform->m_Size.x = 600.f + time_passed * 100.f;
        deathTrasform->m_Size.y = 450.f + time_passed * 75.f;

        for (auto& entity : select) {
            auto transform = entity->GetComponent<Engine::TransformComponent>();
            auto input = entity->GetComponent<Engine::InputComponent>();

            bool moveLeftInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveLeft"));
            bool moveRightInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveRight"));
            bool select = Engine::InputManager::IsActionActive(input, fmt::format("Select"));

            if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::LevelLost) {
                transform->m_Position.y = 250.f;
            }

            if (moveLeftInput) {
               transform->m_Position.x = -200.f;
            }

            if (moveRightInput) {
                transform->m_Position.x = 200.f;
            }

            if (select) {
                if (transform->m_Position.x == -200.f) {
                    gameState->m_CurrentState = gameMode;
                }
                else if (transform->m_Position.x == 200.f) {
                    gameState->m_CurrentState = Engine::GameStates::MainMenu;
                }
            }

            if (gameState->m_CurrentState != Engine::GameStates::LevelLost) {
                transform->m_Position.y = 9250.f;
                transform->m_Position.x = -200.f;
            }
        }

        for (auto& entity : deathComponents)
        {
            auto transform = entity->GetComponent<Engine::TransformComponent>();
            if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::LevelLost) {
                transform->m_Position.y = transform->m_Position.y - 9000.f;
            }

            if (gameState->m_CurrentState != Engine::GameStates::LevelLost) {
                transform->m_Position.y = transform->m_Position.y + 9000.f;
                time_passed = 0.f;
            }
        }

        if (gameState->m_CurrentState != Engine::GameStates::LevelLost) {
            auto transform = youDied->GetComponent<Engine::TransformComponent>();
            transform->m_Size.x = 600.f;
            transform->m_Size.y = 450.f;
        }

    }
}