#include "precomp.h"
#include "StadiumController.h"

#include "Entities/GameComponents.h"

namespace Game
{
    bool Stadium::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to BallController::Init()");

        auto grid = std::make_unique<Engine::Entity>(); 
        grid->AddComponent<Engine::TransformComponent>(0.f, 0.f, 1280.f, 736.f);
        grid->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

        entityManager_->AddEntity(std::move(grid));

        return true;
    }
}