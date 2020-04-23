#include "precomp.h"
#include "MenuController.h"
#include "GameComponents.h"

namespace Game
{
    bool Menu::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_1, 
        Engine::Texture* texture_2, Engine::Texture* texture_3, Engine::Texture* texture_4)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to Menu::Init()");

        auto background = std::make_unique<Engine::Entity>();
        background->AddComponent<Engine::TransformComponent>(0.f, 0.f, 1280.f, 740.f);
        background->AddComponent<Engine::SpriteComponent>().m_Image = texture_4;
        background->AddComponent<MenuComponent>();
        entityManager_->AddEntity(std::move(background));

        auto selectionSquare = std::make_unique<Engine::Entity>();
        selectionSquare->AddComponent<Engine::TransformComponent>(0.f, -100.f, 290.f, 80.f);
        selectionSquare->AddComponent<Engine::SpriteComponent>().m_Image = texture_3;
        selectionSquare->AddComponent<Engine::InputComponent>();
        selectionSquare->AddComponent<SelectionComponent>();
        auto input = selectionSquare->GetComponent<Engine::InputComponent>();

        input->inputActions.push_back({ fmt::format("Player1MoveUp") });
        input->inputActions.push_back({ fmt::format("Player1MoveDown") });
        input->inputActions.push_back({ fmt::format("Select") });
        entityManager_->AddEntity(std::move(selectionSquare));

        auto menuItem1 = std::make_unique<Engine::Entity>();
        menuItem1->AddComponent<Engine::TransformComponent>(0.f, -100.f, 300.f, 95.f);
        menuItem1->AddComponent<Engine::SpriteComponent>().m_Image = texture_1;
        menuItem1->AddComponent<MenuComponent>();
        entityManager_->AddEntity(std::move(menuItem1));

        auto menuItem2 = std::make_unique<Engine::Entity>();
        menuItem2->AddComponent<Engine::TransformComponent>(0.f, 100.f, 300.f, 95.f);
        menuItem2->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        menuItem2->AddComponent<MenuComponent>();
        entityManager_->AddEntity(std::move(menuItem2));

       
        return true;
    }

    void Menu::Update(float dt, Engine::EntityManager* entityManager_)
    {
        auto selectionBox = entityManager_->GetAllEntitiesWithComponents<SelectionComponent>();
        auto menuStuff = entityManager_->GetAllEntitiesWithComponents<MenuComponent>();
        for (auto& entity : selectionBox)
        {
            auto input = entity->GetComponent<Engine::InputComponent>();
            auto transform = entity->GetComponent<Engine::TransformComponent>();

            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveUp"));
            bool moveDownInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveDown"));
            bool select = Engine::InputManager::IsActionActive(input, fmt::format("Select"));
            
            if (select) {
                if (transform->m_Position.y == -100.f) {
                    is_shown = false;
                    entity->RemoveAllComponents();
                }
                else {
                    quit = true;
                }
            }
            
            if (moveUpInput) {
                transform->m_Position.y= -100.f;
            }
            else if (moveDownInput) {
                transform->m_Position.y = 100.f;
            }
            
        }
        if (!is_shown) {
            for (auto& entity : menuStuff)
            {
                auto transform = entity->GetComponent<Engine::TransformComponent>();
                entity->RemoveAllComponents();
            }
        }
    }
}