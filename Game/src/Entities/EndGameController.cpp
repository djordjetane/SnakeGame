#include "precomp.h"
#include "EndGameController.h"
#include "GameComponents.h"

namespace Game
{
    bool EndGameScreen::Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to VictoryScreen::Init()");


        auto congratulations = std::make_unique<Engine::Entity>();
        congratulations->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 1300.f, 740.f);
        congratulations->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("black");
        congratulations->AddComponent<EndGameComponent>();
        entityManager_->AddEntity(std::move(congratulations));

        auto select = std::make_unique<Engine::Entity>();
        select->AddComponent<Engine::TransformComponent>(-200.f, 9250.f, 295.f, 95.f);
        select->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("white");
        select->AddComponent<Engine::InputComponent>();
        select->AddComponent<EndGameSelectionComponent>();
        auto input = select->GetComponent<Engine::InputComponent>();

        input->inputActions.push_back({ fmt::format("Select"), Engine::EInputActionState::JustPressed });
        input->inputActions.push_back({ fmt::format("Player1MoveLeft"), Engine::EInputActionState::JustPressed });
        input->inputActions.push_back({ fmt::format("Player1MoveRight"), Engine::EInputActionState::JustPressed });

        entityManager_->AddEntity(std::move(select));

        auto infinite_level = std::make_unique<Engine::Entity>();
        infinite_level->AddComponent<Engine::TransformComponent>(-200.f, 9250.f, 300.f, 95.f);
        infinite_level->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("infinite_runner");
        infinite_level->AddComponent<EndGameComponent>();
        entityManager_->AddEntity(std::move(infinite_level));

        auto menu = std::make_unique<Engine::Entity>();
        menu->AddComponent<Engine::TransformComponent>(200.f, 9250.f, 300.f, 95.f);
        menu->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("main_menu");
        menu->AddComponent<EndGameComponent>();
        entityManager_->AddEntity(std::move(menu));

        return true;
    }

    void EndGameScreen::Update(float dt, Engine::EntityManager* entityManager_, Engine::SoundManager* soundManager_, Engine::CurrentGameState* gameState)
    {

        auto endComponents = entityManager_->GetAllEntitiesWithComponents<EndGameComponent, Engine::TransformComponent>();
        auto select = entityManager_->GetAllEntitiesWithComponents<EndGameSelectionComponent, Engine::TransformComponent, Engine::InputComponent>();

        for (auto& entity : select) {
            auto transform = entity->GetComponent<Engine::TransformComponent>();
            auto input = entity->GetComponent<Engine::InputComponent>();

            bool moveLeftInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveLeft"));
            bool moveRightInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveRight"));
            bool select = Engine::InputManager::IsActionActive(input, fmt::format("Select"));

            if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::EndGameScreen) {
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
                    gameState->m_CurrentState = Engine::GameStates::PlayingInfiniteLevel;
                    soundManager_->PlaySound("select", 0);
                }
                else if (transform->m_Position.x == 200.f) {
                    gameState->m_CurrentState = Engine::GameStates::MainMenu;
                    soundManager_->PlaySound("select", 0);
                }
            }

            if (gameState->m_CurrentState != Engine::GameStates::EndGameScreen) {
                transform->m_Position.y = 9250.f;
                transform->m_Position.x = -200.f;
            }
        }

        for (auto& entity : endComponents)
        {
            auto transform = entity->GetComponent<Engine::TransformComponent>();
            if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::EndGameScreen) {
                transform->m_Position.y = transform->m_Position.y - 9000.f;
            }

            if (gameState->m_CurrentState != Engine::GameStates::EndGameScreen) {
                transform->m_Position.y = transform->m_Position.y + 9000.f;
            }
        }

    }
}