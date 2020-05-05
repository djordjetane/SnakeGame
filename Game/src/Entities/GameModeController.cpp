#include "precomp.h"
#include "GameModeController.h"
#include "GameComponents.h"

namespace Game
{
    bool GameModeMenu::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_1,
        Engine::Texture* texture_2, Engine::Texture* texture_3, Engine::Texture* texture_4, Engine::Texture* texture_5, 
        Engine::Texture* texture_6, Engine::Texture* texture_7, Engine::Texture* texture_8, Engine::Texture* texture_9, 
        Engine::Texture* texture_10, Engine::Texture* texture_11, Engine::Texture* texture_12, Engine::Texture* texture_13,
        Engine::Texture* texture_14)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to GameModeMenu::Init()");

        auto background = std::make_unique<Engine::Entity>();
        background->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 1280.f, 740.f);
        background->AddComponent<Engine::SpriteComponent>().m_Image = texture_9;
        background->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(background));

        auto selectionSquare = std::make_unique<Engine::Entity>();
        selectionSquare->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 570.f, 110.f);
        selectionSquare->AddComponent<Engine::SpriteComponent>().m_Image = texture_1;
        selectionSquare->AddComponent<Engine::InputComponent>();
        selectionSquare->AddComponent<GameModeMenuSelectionComponent>();
        auto input1 = selectionSquare->GetComponent<Engine::InputComponent>();

        input1->inputActions.push_back({ fmt::format("Player1MoveUp"), Engine::EInputActionState::JustPressed });
        input1->inputActions.push_back({ fmt::format("Player1MoveDown"), Engine::EInputActionState::JustPressed });
        entityManager_->AddEntity(std::move(selectionSquare));

        auto highlightSquare1 = std::make_unique<Engine::Entity>();
        highlightSquare1->AddComponent<Engine::TransformComponent>(-140.f, 8800.f, 240.f, 75.f);
        highlightSquare1->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        highlightSquare1->AddComponent<Engine::InputComponent>();
        highlightSquare1->AddComponent<GameModeMenuHighlightComponent>().numOfHighlight = 1;
        auto input2 = highlightSquare1->GetComponent<Engine::InputComponent>();

        input2->inputActions.push_back({ fmt::format("Player1MoveLeft"), Engine::EInputActionState::JustPressed });
        input2->inputActions.push_back({ fmt::format("Player1MoveRight"), Engine::EInputActionState::JustPressed });
        entityManager_->AddEntity(std::move(highlightSquare1));

        auto highlightSquare2 = std::make_unique<Engine::Entity>();
        highlightSquare2->AddComponent<Engine::TransformComponent>(-140.f, 8960.f, 240.f, 75.f);
        highlightSquare2->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        highlightSquare2->AddComponent<Engine::InputComponent>();
        highlightSquare2->AddComponent<GameModeMenuHighlightComponent>().numOfHighlight = 2;
        auto input3 = highlightSquare2->GetComponent<Engine::InputComponent>();

        input3->inputActions.push_back({ fmt::format("Player1MoveLeft"), Engine::EInputActionState::JustPressed});
        input3->inputActions.push_back({ fmt::format("Player1MoveRight"), Engine::EInputActionState::JustPressed });
        entityManager_->AddEntity(std::move(highlightSquare2));

        auto highlightSquare3 = std::make_unique<Engine::Entity>();
        highlightSquare3->AddComponent<Engine::TransformComponent>(-140.f, 9120.f, 240.f, 75.f);
        highlightSquare3->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        highlightSquare3->AddComponent<Engine::InputComponent>();
        highlightSquare3->AddComponent<GameModeMenuHighlightComponent>().numOfHighlight = 3;
        auto input4 = highlightSquare3->GetComponent<Engine::InputComponent>();

        input4->inputActions.push_back({ fmt::format("Player1MoveLeft"), Engine::EInputActionState::JustPressed });
        input4->inputActions.push_back({ fmt::format("Player1MoveRight"), Engine::EInputActionState::JustPressed });
        entityManager_->AddEntity(std::move(highlightSquare3));

        auto highlightSquare4 = std::make_unique<Engine::Entity>();
        highlightSquare4->AddComponent<Engine::TransformComponent>(0.f, 7500.f, 240.f, 75.f);
        highlightSquare4->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        highlightSquare4->AddComponent<Engine::InputComponent>();
        highlightSquare4->AddComponent<GameModeMenuHighlightComponent>().numOfHighlight = 4;
        auto input5 = highlightSquare4->GetComponent<Engine::InputComponent>();

        input5->inputActions.push_back({ fmt::format("Select"), Engine::EInputActionState::JustPressed });
        entityManager_->AddEntity(std::move(highlightSquare4));

        auto highlightSquare5 = std::make_unique<Engine::Entity>();
        highlightSquare5->AddComponent<Engine::TransformComponent>(-540.f, 7500.f, 140.f, 45.f);
        highlightSquare5->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        highlightSquare5->AddComponent<Engine::InputComponent>();
        highlightSquare5->AddComponent<GameModeMenuHighlightComponent>().numOfHighlight = 5;
        auto input6 = highlightSquare5->GetComponent<Engine::InputComponent>();

        input6->inputActions.push_back({ fmt::format("Select"), Engine::EInputActionState::JustPressed });
        entityManager_->AddEntity(std::move(highlightSquare5));

        auto button11 = std::make_unique<Engine::Entity>();
        button11->AddComponent<Engine::TransformComponent>(-140.f, 8800.f, 253.f, 80.f);
        button11->AddComponent<Engine::SpriteComponent>().m_Image = texture_3;
        button11->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(button11));

        auto button12 = std::make_unique<Engine::Entity>();
        button12->AddComponent<Engine::TransformComponent>(140.f, 8800.f, 253.f, 80.f);
        button12->AddComponent<Engine::SpriteComponent>().m_Image = texture_4;
        button12->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(button12));

        auto button21 = std::make_unique<Engine::Entity>();
        button21->AddComponent<Engine::TransformComponent>(-140.f, 8960.f, 253.f, 80.f);
        button21->AddComponent<Engine::SpriteComponent>().m_Image = texture_7;
        button21->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(button21));

        auto button22 = std::make_unique<Engine::Entity>();
        button22->AddComponent<Engine::TransformComponent>(140.f, 8960.f, 253.f, 80.f);
        button22->AddComponent<Engine::SpriteComponent>().m_Image = texture_8;
        button22->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(button22));

        auto button31 = std::make_unique<Engine::Entity>();
        button31->AddComponent<Engine::TransformComponent>(-140.f, 9120.f, 253.f, 80.f);
        button31->AddComponent<Engine::SpriteComponent>().m_Image = texture_5;
        button31->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(button31));

        auto button32 = std::make_unique<Engine::Entity>();
        button32->AddComponent<Engine::TransformComponent>(140.f, 9120.f, 253.f, 80.f);
        button32->AddComponent<Engine::SpriteComponent>().m_Image = texture_6;
        button32->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(button32));

        auto buttonStart = std::make_unique<Engine::Entity>();
        buttonStart->AddComponent<Engine::TransformComponent>(0.f, 9260.f, 253.f, 80.f);
        buttonStart->AddComponent<Engine::SpriteComponent>().m_Image = texture_10;
        buttonStart->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(buttonStart));

        auto buttonBack = std::make_unique<Engine::Entity>();
        buttonBack->AddComponent<Engine::TransformComponent>(-540.f, 8690.f, 150.f, 50.f);
        buttonBack->AddComponent<Engine::SpriteComponent>().m_Image = texture_14;
        buttonBack->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(buttonBack));;

        auto text_1 = std::make_unique<Engine::Entity>();
        text_1->AddComponent<Engine::TransformComponent>(0.f, 8720.f, 900.f, 60.f);
        text_1->AddComponent<Engine::SpriteComponent>().m_Image = texture_11;
        text_1->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(text_1));

        auto text_2 = std::make_unique<Engine::Entity>();
        text_2->AddComponent<Engine::TransformComponent>(0.f, 8880.f, 900.f, 60.f);
        text_2->AddComponent<Engine::SpriteComponent>().m_Image = texture_12;
        text_2->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(text_2));

        auto text_3 = std::make_unique<Engine::Entity>();
        text_3->AddComponent<Engine::TransformComponent>(0.f, 9040.f, 900.f, 60.f);
        text_3->AddComponent<Engine::SpriteComponent>().m_Image = texture_13;
        text_3->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(text_3));

        return true;
    }

    void GameModeMenu::Update(float dt, Engine::EntityManager* entityManager_, Engine::CurrentGameState* gameState, Engine::GameStates gameMode, Engine::GameModeSettings* gameModeSettings)
    {
        auto selectionBox = entityManager_->GetAllEntitiesWithComponents<GameModeMenuSelectionComponent, Engine::InputComponent, Engine::TransformComponent>();
        auto menuStuff = entityManager_->GetAllEntitiesWithComponents<GameModeMenuComponent, Engine::TransformComponent>();
        auto highlightBoxes = entityManager_->GetAllEntitiesWithComponents<GameModeMenuHighlightComponent, Engine::InputComponent, Engine::TransformComponent>();
        
        for (auto& entity : highlightBoxes)
        {
            auto input = entity->GetComponent<Engine::InputComponent>();
            auto transform = entity->GetComponent<Engine::TransformComponent>();
            auto highlight = entity->GetComponent<GameModeMenuHighlightComponent>();

            bool moveLeftInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveLeft"));
            bool moveRightInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveRight"));
            bool select = Engine::InputManager::IsActionActive(input, fmt::format("Select"));

            if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::GameModeMenu) {
                transform->m_Position.y = transform->m_Position.y - 9000.f;
            }
            if (selected == 4 && highlight->numOfHighlight == 4 && transform->m_Position.y == 7500.f) {
                transform->m_Position.y = 260.f;
            }
            if (selected != 4 && highlight->numOfHighlight == 4 && transform->m_Position.y == 260.f) {
                transform->m_Position.y = 7500.f;
            }

            if (selected == 5 && highlight->numOfHighlight == 5 && transform->m_Position.y == 7500.f) {
                transform->m_Position.y = -310.f;
            }
            if (selected != 5 && highlight->numOfHighlight == 5 && transform->m_Position.y == -310.f) {
                transform->m_Position.y = 7500.f;
            }


            if (select) {
                if (selected == 4) {
                    gameState->m_CurrentState = Engine::GameStates::PlayingLevel;
                    if (!(highlight->numOfHighlight == 4 || highlight->numOfHighlight == 5)) {
                        transform->m_Position.y = transform->m_Position.y + 9000.f;
                    }
                    else {
                        transform->m_Position.y = 7500.f;
                    }
                }
                if (selected == 5) {
                    gameState->m_CurrentState = Engine::GameStates::MainMenu;
                    if (!(highlight->numOfHighlight == 4 || highlight->numOfHighlight == 5)) {
                        transform->m_Position.y = transform->m_Position.y + 9000.f;
                    }
                    else {
                        transform->m_Position.y = 7500.f;
                    }
                }
            }

            if (moveLeftInput) {
                if (selected == 1 && highlight->numOfHighlight == selected) {
                    if (transform->m_Position.x == 140.f) {
                        transform->m_Position.x = -140.f;
                        gameModeSettings->borders = 1;
                    }
                }
                else if (selected == 2 && highlight->numOfHighlight == selected) {
                    if (transform->m_Position.x == 140.f) {
                        transform->m_Position.x = -140.f;
                        gameModeSettings->bumpers = 1;
                    }
                }
                else if (selected == 3 && highlight->numOfHighlight == selected) {
                    if (transform->m_Position.x == 140.f) {
                        transform->m_Position.x = -140.f;
                        gameModeSettings->difficulty = 1;
                    }
                }
            }

            if (moveRightInput) {
                if (selected == 1 && highlight->numOfHighlight == selected) {
                    if (transform->m_Position.x == -140.f) {
                        transform->m_Position.x = 140.f;
                        gameModeSettings->borders = 2;
                    }
                }
                else if (selected == 2 && highlight->numOfHighlight == selected) {
                    if (transform->m_Position.x == -140.f) {
                        transform->m_Position.x = 140.f;
                        gameModeSettings->bumpers = 2;
                    }
                }
                else if (selected == 3 && highlight->numOfHighlight == selected) {
                    if (transform->m_Position.x == -140.f) {
                        transform->m_Position.x = 140.f;
                        gameModeSettings->difficulty = 2;
                    }
                }
            }
        }
        
        for (auto& entity : selectionBox)
        {
            auto input = entity->GetComponent<Engine::InputComponent>();
            auto transform = entity->GetComponent<Engine::TransformComponent>();

            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveUp"));
            bool moveDownInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveDown"));

            if (transform->m_Position.y == 9000.f && gameState->m_CurrentState == Engine::GameStates::GameModeMenu) {
                transform->m_Position.y = -200.f;
            }

            if (moveUpInput) {
                if (transform->m_Position.y == -40.f) {
                    transform->m_Position.y = -200.f;
                    selected = 1;
                }
                else if (transform->m_Position.y == 120.f) {
                    transform->m_Position.y = -40.f;
                    selected = 2;
                }
                else if (transform->m_Position.y == 7500.f) {
                    transform->m_Position.y = 120.f;
                    selected = 3;
                }
                else if (transform->m_Position.y == -200.f) {
                    transform->m_Position.y = 7600.f;
                    selected = 5;
                }
            }
            else if (moveDownInput) {
                if (transform->m_Position.y == -40.f) {
                    transform->m_Position.y = 120.f;
                    selected = 3;
                }
                else if (transform->m_Position.y == -200.f) {
                    transform->m_Position.y = -40.f;
                    selected = 2;
                }
                else if (transform->m_Position.y == 120.f) {
                    transform->m_Position.y = 7500.f;
                    selected = 4;
                }
                else if (transform->m_Position.y == 7600.f) {
                    transform->m_Position.y = -200.f;
                    selected = 1;
                }
            }

            if (gameState->m_CurrentState != Engine::GameStates::GameModeMenu) {
                transform->m_Position.y = 9000.f;
                selected = 1;
            }

        }

        

        for (auto& entity : menuStuff)
        {

            auto transform = entity->GetComponent<Engine::TransformComponent>();

            if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::GameModeMenu) {
                transform->m_Position.y = transform->m_Position.y - 9000.f;
            }

            if (gameState->m_CurrentState != Engine::GameStates::GameModeMenu) {
                transform->m_Position.y = transform->m_Position.y + 9000.f;
            }
        }

        if (gameState->m_CurrentState != Engine::GameStates::GameModeMenu) {
            for (auto& entity : highlightBoxes) {
                auto transform = entity->GetComponent<Engine::TransformComponent>();
                if (transform->m_Position.y < 7000.f) {
                    transform->m_Position.y = transform->m_Position.y + 9000.f;
                }
            }
        }

    }
}