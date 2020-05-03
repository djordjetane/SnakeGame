#include "precomp.h"
#include "PauseMenuController.h"
#include "GameComponents.h"

namespace Game
{
    bool PauseMenu::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_1,
        Engine::Texture* texture_2, Engine::Texture* texture_3, Engine::Texture* texture_4, Engine::Texture* texture_5)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to Menu::Init()");

        m_isUpKeyReleased = true;
        m_isDownKeyReleased = true;

        auto background = std::make_unique<Engine::Entity>();
        background->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 1280.f, 740.f);
        background->AddComponent<Engine::SpriteComponent>().m_Image = texture_4;
        background->AddComponent<PauseMenuComponent>();
        entityManager_->AddEntity(std::move(background));

        auto selectionSquare = std::make_unique<Engine::Entity>();
        selectionSquare->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 290.f, 80.f);
        selectionSquare->AddComponent<Engine::SpriteComponent>().m_Image = texture_3;
        selectionSquare->AddComponent<Engine::InputComponent>();
        selectionSquare->AddComponent<PauseSelectionComponent>();
        auto input = selectionSquare->GetComponent<Engine::InputComponent>();

        input->inputActions.push_back({ fmt::format("Player1MoveUp") });
        input->inputActions.push_back({ fmt::format("Player1MoveDown") });
        input->inputActions.push_back({ fmt::format("Select") });
        entityManager_->AddEntity(std::move(selectionSquare));

        auto menuItem1 = std::make_unique<Engine::Entity>();
        menuItem1->AddComponent<Engine::TransformComponent>(0.f, 8900.f, 300.f, 95.f);
        menuItem1->AddComponent<Engine::SpriteComponent>().m_Image = texture_1;
        menuItem1->AddComponent<PauseMenuComponent>();
        entityManager_->AddEntity(std::move(menuItem1));

        auto menuItem2 = std::make_unique<Engine::Entity>();
        menuItem2->AddComponent<Engine::TransformComponent>(0.f, 9100.f, 300.f, 95.f);
        menuItem2->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        menuItem2->AddComponent<PauseMenuComponent>();
        entityManager_->AddEntity(std::move(menuItem2));

        auto menuItem3 = std::make_unique<Engine::Entity>();
        menuItem3->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 300.f, 95.f);
        menuItem3->AddComponent<Engine::SpriteComponent>().m_Image = texture_5;
        menuItem3->AddComponent<PauseMenuComponent>();
        entityManager_->AddEntity(std::move(menuItem3));

        return true;
    }

    void PauseMenu::Update(float dt, Engine::EntityManager* entityManager_, Engine::GameState* gameState, Engine::GameState gameMode)
    {
        auto selectionBox = entityManager_->GetAllEntitiesWithComponents<PauseSelectionComponent, Engine::InputComponent, Engine::TransformComponent>();
        auto menuStuff = entityManager_->GetAllEntitiesWithComponents<PauseMenuComponent, Engine::TransformComponent>();
        for (auto& entity : selectionBox)
        {
            auto input = entity->GetComponent<Engine::InputComponent>();
            auto transform = entity->GetComponent<Engine::TransformComponent>();

            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveUp"));
            bool moveDownInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveDown"));
            bool select = Engine::InputManager::IsActionActive(input, fmt::format("Select"));

            if (transform->m_Position.y == 9000.f && *gameState == Engine::GameState::PauseMenu) {
                transform->m_Position.y = -100.f;
            }

            if (select) {
                if (transform->m_Position.y == -100.f) {
                    *gameState = Engine::GameState::ResumingLevel;
                    transform->m_Position.y = 9000.f;
                }
                else if (transform->m_Position.y == 0.f) {
                    *gameState = Engine::GameState::MainMenu;
                    transform->m_Position.y = 9000.f;
                }
                else {
                    *gameState = Engine::GameState::QuitGame;
                }
            }

            if (!moveUpInput && !m_isUpKeyReleased) {
                m_isUpKeyReleased = true;
            }
            if (!moveDownInput && !m_isDownKeyReleased) {
                m_isDownKeyReleased = true;
            }

            if (moveUpInput && m_isUpKeyReleased) {
                if (transform->m_Position.y == -100.f || transform->m_Position.y == 0.f) {
                    transform->m_Position.y = -100.f;
                }
                else if (transform->m_Position.y == 100.f) {
                    transform->m_Position.y = 0.f;
                }
                m_isUpKeyReleased = false;
            }
            else if (moveDownInput && m_isDownKeyReleased) {
                if (transform->m_Position.y == 100.f || transform->m_Position.y == 0.f) {
                    transform->m_Position.y = 100.f;
                }
                else if (transform->m_Position.y == -100.f) {
                    transform->m_Position.y = 0.f;
                }
                m_isDownKeyReleased = false;
            }

        }
        
        for (auto& entity : menuStuff)
        {

            auto transform = entity->GetComponent<Engine::TransformComponent>();

            if (transform->m_Position.y > 8000.f && *gameState == Engine::GameState::PauseMenu) {
                transform->m_Position.y = transform->m_Position.y - 9000.f;
            }

            if (*gameState != Engine::GameState::PauseMenu) {
                transform->m_Position.y = transform->m_Position.y+9000.f;
            }
        }
        
    }
}