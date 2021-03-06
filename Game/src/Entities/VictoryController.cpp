#include "precomp.h"
#include "VictoryController.h"
#include "GameComponents.h"

namespace Game
{
    bool VictoryScreen::Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to VictoryScreen::Init()");


        auto youWin = std::make_unique<Engine::Entity>();
        youWin->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 1280.f, 720.f);
        youWin->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("win_screen");
        youWin->AddComponent<WinScreenComponent>();
        entityManager_->AddEntity(std::move(youWin));

        auto select = std::make_unique<Engine::Entity>();
        select->AddComponent<Engine::TransformComponent>(-200.f, 9250.f, 290.f, 95.f);
        select->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("white");
        select->AddComponent<Engine::InputComponent>();
        select->AddComponent<WinScreenSelectionComponent>();
        auto input = select->GetComponent<Engine::InputComponent>();

        input->inputActions.push_back({ fmt::format("Select"), Engine::EInputActionState::JustPressed });
        input->inputActions.push_back({ fmt::format("Player1MoveLeft"), Engine::EInputActionState::JustPressed });
        input->inputActions.push_back({ fmt::format("Player1MoveRight"), Engine::EInputActionState::JustPressed });

        entityManager_->AddEntity(std::move(select));

        auto next_level = std::make_unique<Engine::Entity>();
        next_level->AddComponent<Engine::TransformComponent>(-200.f, 9250.f, 300.f, 95.f);
        next_level->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("next_level");
        next_level->AddComponent<WinScreenComponent>();
        entityManager_->AddEntity(std::move(next_level));

        auto menu = std::make_unique<Engine::Entity>();
        menu->AddComponent<Engine::TransformComponent>(200.f, 9250.f, 300.f, 95.f);
        menu->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("main_menu");
        menu->AddComponent<WinScreenComponent>();
        entityManager_->AddEntity(std::move(menu));

        return true;
    }

    void VictoryScreen::Update(float dt, Engine::EntityManager* entityManager_, Engine::SoundManager* soundManager_, Engine::CurrentGameState* gameState, Engine::GameStates gameMode)
    {

        auto winComponents = entityManager_->GetAllEntitiesWithComponents<WinScreenComponent, Engine::TransformComponent>();
        auto select = entityManager_->GetAllEntitiesWithComponents<WinScreenSelectionComponent, Engine::TransformComponent, Engine::InputComponent>();
 
        for (auto& entity : select) {
            auto transform = entity->GetComponent<Engine::TransformComponent>();
            auto input = entity->GetComponent<Engine::InputComponent>();

            bool moveLeftInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveLeft"));
            bool moveRightInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveRight"));
            bool select = Engine::InputManager::IsActionActive(input, fmt::format("Select"));

            if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::LevelWon) {
                transform->m_Position.y = 250.f;
            }

            if (moveLeftInput) {
                transform->m_Position.x = -200.f;
                soundManager_->PlaySound("click", 0);
            }

            if (moveRightInput) {
                transform->m_Position.x = 200.f;
                soundManager_->PlaySound("click", 0);
            }

            if (select) {
                if (transform->m_Position.x == -200.f) {
                    gameState->m_CurrentState = gameMode;
                    soundManager_->PlaySound("select", 0);
                }
                else if (transform->m_Position.x == 200.f) {
                    gameState->m_CurrentState = Engine::GameStates::MainMenu;
                    soundManager_->PlaySound("select", 0);
                }
            }

            if (gameState->m_CurrentState != Engine::GameStates::LevelWon) {
                transform->m_Position.y = 9250.f;
                transform->m_Position.x = -200.f;
            }
        }

        for (auto& entity : winComponents)
        {
            auto transform = entity->GetComponent<Engine::TransformComponent>();
            if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::LevelWon) {
                transform->m_Position.y = transform->m_Position.y - 9000.f;
            }

            if (gameState->m_CurrentState != Engine::GameStates::LevelWon) {
                transform->m_Position.y = transform->m_Position.y + 9000.f;
            }
        }

    }
}