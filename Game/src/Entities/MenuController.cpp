#include "precomp.h"
#include "MenuController.h"
#include "GameComponents.h"

namespace Game
{
    bool MainMenu::Init(Engine::EntityManager* entityManager_, Engine::TextureManager* textureManager_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to Menu::Init()");

        auto background = std::make_unique<Engine::Entity>();
        background->AddComponent<Engine::TransformComponent>(0.f, 0.f, 1280.f, 740.f);
        background->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("black");
        background->AddComponent<MainMenuComponent>();
        entityManager_->AddEntity(std::move(background));

        auto selectionSquare = std::make_unique<Engine::Entity>();
        selectionSquare->AddComponent<Engine::TransformComponent>(0.f, -100.f, 290.f, 80.f);
        selectionSquare->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("white");
        selectionSquare->AddComponent<Engine::InputComponent>();
        selectionSquare->AddComponent<SelectionComponent>();
        auto input = selectionSquare->GetComponent<Engine::InputComponent>();

        input->inputActions.push_back({ fmt::format("Player1MoveUp"), Engine::EInputActionState::JustPressed});
        input->inputActions.push_back({ fmt::format("Player1MoveDown"), Engine::EInputActionState::JustPressed });
        input->inputActions.push_back({ fmt::format("Select"), Engine::EInputActionState::JustPressed });
        entityManager_->AddEntity(std::move(selectionSquare));

        auto menuItem1 = std::make_unique<Engine::Entity>();
        menuItem1->AddComponent<Engine::TransformComponent>(0.f, -100.f, 300.f, 95.f);
        menuItem1->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("story_mode");
        menuItem1->AddComponent<MainMenuComponent>();
        entityManager_->AddEntity(std::move(menuItem1));

        auto menuItem2 = std::make_unique<Engine::Entity>();
        menuItem2->AddComponent<Engine::TransformComponent>(0.f, 0.f, 300.f, 95.f);
        menuItem2->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("infinite_runner");
        menuItem2->AddComponent<MainMenuComponent>();
        entityManager_->AddEntity(std::move(menuItem2));
        
        auto menuItem3 = std::make_unique<Engine::Entity>();
        menuItem3->AddComponent<Engine::TransformComponent>(0.f, 100.f, 300.f, 95.f);
        menuItem3->AddComponent<Engine::SpriteComponent>().m_Image = textureManager_->GetTexture("quit");
        menuItem3->AddComponent<MainMenuComponent>();
        entityManager_->AddEntity(std::move(menuItem3));
       
        return true;
    }

    void MainMenu::Update(float dt, Engine::EntityManager* entityManager_, Engine::CurrentGameState* gameState)
    {
        auto selectionBox = entityManager_->GetAllEntitiesWithComponents<SelectionComponent, Engine::InputComponent, Engine::TransformComponent>();
        auto menuStuff = entityManager_->GetAllEntitiesWithComponents<MainMenuComponent, Engine::TransformComponent>();
        for (auto& entity : selectionBox)
        {
            auto input = entity->GetComponent<Engine::InputComponent>();
            auto transform = entity->GetComponent<Engine::TransformComponent>();

            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveUp"));
            bool moveDownInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveDown"));
            bool select = Engine::InputManager::IsActionActive(input, fmt::format("Select"));

            if (transform->m_Position.y == 9000.f && gameState->m_CurrentState == Engine::GameStates::MainMenu) {
                transform->m_Position.y = -100.f;
            }


            if (select) {
                if (transform->m_Position.y == -100.f) {
                    gameState->m_CurrentState = Engine::GameStates::GameModeMenu;
                    transform->m_Position.y = 9000.f;
                }
                else if (transform->m_Position.y == 0.f) {
                    gameState->m_CurrentState = Engine::GameStates::PlayingInfiniteLevel;
                    transform->m_Position.y = 9000.f;
                }
                else {
                    gameState->m_CurrentState = Engine::GameStates::QuitGame;
                }
            }

            if (moveUpInput) {
                if (transform->m_Position.y == -100.f || transform->m_Position.y == 0.f) {
                    transform->m_Position.y = -100.f;
                }
                else if (transform->m_Position.y == 100.f) {
                    transform->m_Position.y = 0.f;
                }

            }
            else if (moveDownInput) {
                if (transform->m_Position.y == 100.f || transform->m_Position.y == 0.f) {
                    transform->m_Position.y = 100.f;
                }
                else if (transform->m_Position.y == -100.f) {
                    transform->m_Position.y = 0.f;
                }
            }
            
        }
        {
            for (auto& entity : menuStuff)
            {
                auto transform = entity->GetComponent<Engine::TransformComponent>();
                if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::MainMenu) {
                    transform->m_Position.y = transform->m_Position.y - 9000.f;
                }
                if (gameState->m_CurrentState != Engine::GameStates::MainMenu) {
                    transform->m_Position.y = transform->m_Position.y + 9000.f;
                }
            }
        }
    }
}