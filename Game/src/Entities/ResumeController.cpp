#include "precomp.h"
#include "ResumeController.h"
#include "GameComponents.h"

namespace Game
{
    bool ResumeScreen::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_1,
        Engine::Texture* texture_2, Engine::Texture* texture_3, Engine::Texture* texture_4, Engine::Texture* texture_5)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to ResumeScreen::Init()");

        time_passed = 0.f;
        auto background = std::make_unique<Engine::Entity>();
        background->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 1280.f, 740.f);
        background->AddComponent<Engine::SpriteComponent>().m_Image = texture_5;
        background->AddComponent<ResumeScreenComponent>().numInQueue = 5;
        entityManager_->AddEntity(std::move(background));

        auto resume_1 = std::make_unique<Engine::Entity>();
        resume_1->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 300.f, 300.f);
        resume_1->AddComponent<Engine::SpriteComponent>().m_Image = texture_1;
        resume_1->AddComponent<ResumeScreenComponent>().numInQueue = 1;
        entityManager_->AddEntity(std::move(resume_1));

        auto resume_2 = std::make_unique<Engine::Entity>();
        resume_2->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 300.f, 300.f);
        resume_2->AddComponent<Engine::SpriteComponent>().m_Image = texture_2;
        resume_2->AddComponent<ResumeScreenComponent>().numInQueue=2;
        entityManager_->AddEntity(std::move(resume_2));

        auto resume_3 = std::make_unique<Engine::Entity>();
        resume_3->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 300.f, 300.f);
        resume_3->AddComponent<Engine::SpriteComponent>().m_Image = texture_3;
        resume_3->AddComponent<ResumeScreenComponent>().numInQueue = 3;
        entityManager_->AddEntity(std::move(resume_3));

        auto resume_go = std::make_unique<Engine::Entity>();
        resume_go->AddComponent<Engine::TransformComponent>(0.f, 9000.f, 300.f, 300.f);
        resume_go->AddComponent<Engine::SpriteComponent>().m_Image = texture_4;
        resume_go->AddComponent<ResumeScreenComponent>().numInQueue = 4;
        entityManager_->AddEntity(std::move(resume_go));

        return true;
    }

    void ResumeScreen::Update(float dt, Engine::EntityManager* entityManager_, Engine::CurrentGameState* gameState, Engine::GameStates gameMode)
    {
        time_passed += dt;
        auto resumeComponents = entityManager_->GetAllEntitiesWithComponents<ResumeScreenComponent, Engine::TransformComponent>();
        if (time_passed >= 2) {
            gameState->m_CurrentState = gameMode;
        }
        for (auto& entity : resumeComponents)
        {
            auto transform = entity->GetComponent<Engine::TransformComponent>();
            auto resum = entity->GetComponent<ResumeScreenComponent>();
            if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::ResumingLevel && resum->numInQueue == 5) {
                transform->m_Position.y = transform->m_Position.y - 9000.f;
            }
            if (time_passed <= 0.5) {
                if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::ResumingLevel && resum->numInQueue == 3) {
                    transform->m_Position.y = 0.f;
                }
            }
            else if (time_passed > 0.5 && time_passed <= 1.0) {
                if (gameState->m_CurrentState == Engine::GameStates::ResumingLevel && resum->numInQueue == 3) {
                    transform->m_Position.y = 9000.f;
                }
                if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::ResumingLevel && resum->numInQueue == 2) {
                    transform->m_Position.y = 0.f;
                }
            }
            else if (time_passed > 1.0 && time_passed <= 1.5) {
                if (gameState->m_CurrentState == Engine::GameStates::ResumingLevel && resum->numInQueue == 2) {
                    transform->m_Position.y = 9000.f;
                }
                if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::ResumingLevel && resum->numInQueue == 1) {
                    transform->m_Position.y = 0.f;
                }
            }
            else if (time_passed > 1.5) {
                if (gameState->m_CurrentState == Engine::GameStates::ResumingLevel && resum->numInQueue == 1) {
                    transform->m_Position.y = 9000.f;
                }
                if (transform->m_Position.y > 8000.f && gameState->m_CurrentState == Engine::GameStates::ResumingLevel && resum->numInQueue == 4) {
                    transform->m_Position.y = 0.f;
                }
            }

            if (time_passed >= 2) {
                if (gameState->m_CurrentState != Engine::GameStates::ResumingLevel) {
                    transform->m_Position.y = 9000.f;
                }
            }
        }
        if (time_passed >= 2) {
            time_passed = 0.f;
        }
        
    }
}