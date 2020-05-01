#include "precomp.h"
#include "CameraController.h"

namespace Game
{

    bool CameraController::Init(Engine::EntityManager* entityManager_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to CameraController::Init()");

        auto camera = std::make_unique<Engine::Entity>();
        camera->AddComponent<Engine::TransformComponent>();
        camera->AddComponent<Engine::CameraComponent>(100.f);
        camera->AddComponent<Engine::InputComponent>();        

        auto transformComp = camera->GetComponent<Engine::TransformComponent>();
        transformComp->m_Size = { 1280.f, 720.f };

        auto inputComp = camera->GetComponent<Engine::InputComponent>();

        inputComp->inputActions.push_back({ "PauseGame" });

        entityManager_->AddEntity(std::move(camera));

        return !(entityManager_->GetAllEntitiesWithComponent<Engine::CameraComponent>().empty());
    }

    void CameraController::Update(float dt, Engine::EntityManager* entityManager_, Engine::GameState* gameState)
    {
        auto camera = entityManager_->GetAllEntitiesWithComponent<Engine::CameraComponent>()[0]; // Only one camera        
        auto input = camera->GetComponent<Engine::InputComponent>();

        bool pauseGameInput = Engine::InputManager::IsActionActive(input, "PauseGame");            

        if (pauseGameInput) 
        {
            *gameState = Engine::GameState::PauseMenu;
        }       
    }
}
