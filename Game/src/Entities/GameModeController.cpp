#include "precomp.h"
#include "GameModeController.h"
#include "GameComponents.h"

namespace Game
{
    bool GameModeMenu::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_1,
        Engine::Texture* texture_2, Engine::Texture* texture_3, Engine::Texture* texture_4, Engine::Texture* texture_5, 
        Engine::Texture* texture_6, Engine::Texture* texture_7, Engine::Texture* texture_8, Engine::Texture* texture_9, 
        Engine::Texture* texture_10)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to Menu::Init()");

        m_isUpKeyReleased = true;
        m_isDownKeyReleased = true;
        m_isEnterKeyReleased = true;
        m_isSpaceKeyReleased = true;

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

        input1->inputActions.push_back({ fmt::format("Player1MoveUp") });
        input1->inputActions.push_back({ fmt::format("Player1MoveDown") });
        entityManager_->AddEntity(std::move(selectionSquare));

        auto highlightSquare1 = std::make_unique<Engine::Entity>();
        highlightSquare1->AddComponent<Engine::TransformComponent>(-140.f, 8800.f, 240.f, 75.f);
        highlightSquare1->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        highlightSquare1->AddComponent<Engine::InputComponent>();
        highlightSquare1->AddComponent<GameModeMenuHighlightComponent>().numOfHighlight = 1;
        auto input2 = highlightSquare1->GetComponent<Engine::InputComponent>();

        input2->inputActions.push_back({ fmt::format("Player1MoveLeft") });
        input2->inputActions.push_back({ fmt::format("Player1MoveRight") });
        entityManager_->AddEntity(std::move(highlightSquare1));

        auto highlightSquare2 = std::make_unique<Engine::Entity>();
        highlightSquare2->AddComponent<Engine::TransformComponent>(-140.f, 8950.f, 240.f, 75.f);
        highlightSquare2->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        highlightSquare2->AddComponent<Engine::InputComponent>();
        highlightSquare2->AddComponent<GameModeMenuHighlightComponent>().numOfHighlight = 2;
        auto input3 = highlightSquare2->GetComponent<Engine::InputComponent>();

        input3->inputActions.push_back({ fmt::format("Player1MoveLeft") });
        input3->inputActions.push_back({ fmt::format("Player1MoveRight") });
        entityManager_->AddEntity(std::move(highlightSquare2));

        auto highlightSquare3 = std::make_unique<Engine::Entity>();
        highlightSquare3->AddComponent<Engine::TransformComponent>(-140.f, 9100.f, 240.f, 75.f);
        highlightSquare3->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        highlightSquare3->AddComponent<Engine::InputComponent>();
        highlightSquare3->AddComponent<GameModeMenuHighlightComponent>().numOfHighlight = 3;
        auto input4 = highlightSquare3->GetComponent<Engine::InputComponent>();

        input4->inputActions.push_back({ fmt::format("Player1MoveLeft") });
        input4->inputActions.push_back({ fmt::format("Player1MoveRight") });
        entityManager_->AddEntity(std::move(highlightSquare3));

        auto highlightSquare4 = std::make_unique<Engine::Entity>();
        highlightSquare4->AddComponent<Engine::TransformComponent>(0.f, 7500.f, 240.f, 75.f);
        highlightSquare4->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        highlightSquare4->AddComponent<Engine::InputComponent>();
        highlightSquare4->AddComponent<GameModeMenuHighlightComponent>().numOfHighlight = 4;
        auto input5 = highlightSquare4->GetComponent<Engine::InputComponent>();

        input5->inputActions.push_back({ fmt::format("Select") });
        entityManager_->AddEntity(std::move(highlightSquare4));

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
        button21->AddComponent<Engine::TransformComponent>(-140.f, 8950.f, 253.f, 80.f);
        button21->AddComponent<Engine::SpriteComponent>().m_Image = texture_7;
        button21->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(button21));

        auto button22 = std::make_unique<Engine::Entity>();
        button22->AddComponent<Engine::TransformComponent>(140.f, 8950.f, 253.f, 80.f);
        button22->AddComponent<Engine::SpriteComponent>().m_Image = texture_8;
        button22->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(button22));

        auto button31 = std::make_unique<Engine::Entity>();
        button31->AddComponent<Engine::TransformComponent>(-140.f, 9100.f, 253.f, 80.f);
        button31->AddComponent<Engine::SpriteComponent>().m_Image = texture_5;
        button31->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(button31));

        auto button32 = std::make_unique<Engine::Entity>();
        button32->AddComponent<Engine::TransformComponent>(140.f, 9100.f, 253.f, 80.f);
        button32->AddComponent<Engine::SpriteComponent>().m_Image = texture_6;
        button32->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(button32));

        auto buttonStart = std::make_unique<Engine::Entity>();
        buttonStart->AddComponent<Engine::TransformComponent>(0.f, 9250.f, 253.f, 80.f);
        buttonStart->AddComponent<Engine::SpriteComponent>().m_Image = texture_10;
        buttonStart->AddComponent<GameModeMenuComponent>();
        entityManager_->AddEntity(std::move(buttonStart));

        return true;
    }

    void GameModeMenu::Update(float dt, Engine::EntityManager* entityManager_, Engine::GameState* gameState, Engine::GameState gameMode, Engine::GameModeSettings* gameModeSettings)
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

            if (transform->m_Position.y > 8000.f && *gameState == Engine::GameState::GameModeMenu) {
                transform->m_Position.y = transform->m_Position.y - 9000.f;
            }
            if (selected == 4 && transform->m_Position.y == 7500.f) {
                transform->m_Position.y = 250.f;
            }
            if (selected != 4 && transform->m_Position.y == 250.f) {
                transform->m_Position.y = 7500.f;
            }

            if (select) {
                if (selected == 4) {
                    *gameState = Engine::GameState::PlayingLevel;
                    if (highlight->numOfHighlight != 4) {
                        transform->m_Position.y = transform->m_Position.y + 9000.f;
                    }
                    else {
                        transform->m_Position.y = 7500.f;
                    }
                }
            }

            if (moveLeftInput) {
                if (selected == 1 && transform->m_Position.y == -200.f) {
                    if (transform->m_Position.x == 140.f) {
                        transform->m_Position.x = -140.f;
                        gameModeSettings->borders = 1;
                    }
                }
                else if (selected == 2 && transform->m_Position.y == -50.f) {
                    if (transform->m_Position.x == 140.f) {
                        transform->m_Position.x = -140.f;
                        gameModeSettings->bumpers = 1;
                    }
                }
                else if (selected == 3 && transform->m_Position.y == 100.f) {
                    if (transform->m_Position.x == 140.f) {
                        transform->m_Position.x = -140.f;
                        gameModeSettings->difficulty = 1;
                    }
                }
            }

            if (moveRightInput) {
                if (selected == 1 && transform->m_Position.y == -200.f) {
                    if (transform->m_Position.x == -140.f) {
                        transform->m_Position.x = 140.f;
                        gameModeSettings->borders = 2;
                    }
                }
                else if (selected == 2 && transform->m_Position.y == -50.f) {
                    if (transform->m_Position.x == -140.f) {
                        transform->m_Position.x = 140.f;
                        gameModeSettings->bumpers = 2;
                    }
                }
                else if (selected == 3 && transform->m_Position.y == 100.f) {
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

            if (transform->m_Position.y == 9000.f && *gameState == Engine::GameState::GameModeMenu) {
                transform->m_Position.y = -200.f;
            }

            if (!moveUpInput && !m_isUpKeyReleased) {
                m_isUpKeyReleased = true;
            }
            if (!moveDownInput && !m_isDownKeyReleased) {
                m_isDownKeyReleased = true;
            }

            if (moveUpInput && m_isUpKeyReleased) {
                if (transform->m_Position.y == -200.f || transform->m_Position.y == -50.f) {
                    transform->m_Position.y = -200.f;
                    selected = 1;
                }
                else if (transform->m_Position.y == 100.f) {
                    transform->m_Position.y = -50.f;
                    selected = 2;
                }
                else if (transform->m_Position.y == 7500.f) {
                    transform->m_Position.y = 100.f;
                    selected = 3;
                }
                m_isUpKeyReleased = false;
            }
            else if (moveDownInput && m_isDownKeyReleased) {
                if (transform->m_Position.y == -50.f) {
                    transform->m_Position.y = 100.f;
                    selected = 3;
                }
                else if (transform->m_Position.y == -200.f) {
                    transform->m_Position.y = -50.f;
                    selected = 2;
                }
                else if (transform->m_Position.y == 100.f) {
                    transform->m_Position.y = 7500.f;
                    selected = 4;
                }
                m_isDownKeyReleased = false;
            }

            if (*gameState != Engine::GameState::GameModeMenu) {
                transform->m_Position.y = 9000.f;
                selected = 1;
            }

        }

        

        for (auto& entity : menuStuff)
        {

            auto transform = entity->GetComponent<Engine::TransformComponent>();

            if (transform->m_Position.y > 8000.f && *gameState == Engine::GameState::GameModeMenu) {
                transform->m_Position.y = transform->m_Position.y - 9000.f;
            }

            if (*gameState != Engine::GameState::GameModeMenu) {
                transform->m_Position.y = transform->m_Position.y + 9000.f;
            }
        }

        if (*gameState != Engine::GameState::GameModeMenu) {
            for (auto& entity : highlightBoxes) {
                auto transform = entity->GetComponent<Engine::TransformComponent>();
                if (transform->m_Position.y < 7000.f) {
                    transform->m_Position.y = transform->m_Position.y + 9000.f;
                }
            }
        }

    }
}