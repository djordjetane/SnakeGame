#include "precomp.h"
#include "PlayerController.h"
#include "GameComponents.h"


namespace Game
{
    bool PlayerController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to PlayerController::Init()");
        ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to PlayerController::Init()");

        m_framerate = 10;
        m_passedTime;

        auto data = std::make_unique<Engine::Entity>();;
        data->AddComponent<PositionComponent>();

        auto player = std::make_unique<Engine::Entity>();

        //initializing head entity
        player->AddComponent<Engine::TransformComponent>(-300.f, 20.f, 40.f, 40.f);
        player->AddComponent<Engine::CollisionComponent>(38.f, 38.f);
        player->AddComponent<Engine::PlayerComponent>(200.f);
        player->AddComponent<Engine::InputComponent>();
        player->AddComponent<Engine::MoverComponent>();
        player->AddComponent<HeadComponent>(EHeadDirection::Right);
        player->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

        auto inputComp = player->GetComponent<Engine::InputComponent>();

        inputComp->inputActions.push_back({ fmt::format("Player1MoveUp") });
        inputComp->inputActions.push_back({ fmt::format("Player1MoveDown") });
        inputComp->inputActions.push_back({ fmt::format("Player1MoveLeft") });
        inputComp->inputActions.push_back({ fmt::format("Player1MoveRight") });

        entityManager_->AddEntity(std::move(player));        

        //initializing body part entities
        for (int i = 1; i < 100; i++) {
        
            player=std::make_unique<Engine::Entity>();
            player->AddComponent<Engine::TransformComponent>(-300.0f-40.f*i, 20.f, 40.f, 40.f);
            player->AddComponent<Engine::CollisionComponent>(38.f, 38.f);
            player->AddComponent<Engine::PlayerComponent>(200.f);
            player->AddComponent<BodyComponent>(i);
            player->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

            //body parts longer than starting length are deactivated
            if (i > 2) {
                player->GetComponent<Engine::SpriteComponent>()->m_Active = false;
                player->GetComponent<Engine::CollisionComponent>()->m_Active = false;
            }
           
            entityManager_->AddEntity(std::move(player));
        }
        entityManager_->AddEntity(std::move(data));

        // *** Helper Component ***
        auto tmpEntity = std::make_unique<Engine::Entity>();
        tmpEntity->AddComponent<HelperComponent>();
        tmpEntity->AddComponent<Engine::TransformComponent>(-300.f, 20.f, 40.f, 40.f);
        tmpEntity->AddComponent<Engine::CollisionComponent>(38.f, 38.f);
        entityManager_->AddEntity(std::move(tmpEntity));

        return !(entityManager_->GetAllEntitiesWithComponent<Engine::PlayerComponent>().empty());
    }

    void PlayerController::Update(float dt, Engine::EntityManager* entityManager_)
    {
        //count passed time
        m_passedTime += dt;
        float timeThreshold = 1.f / m_framerate;

        int snakeLength;

        auto headEntities = entityManager_->GetAllEntitiesWithComponents<Engine::PlayerComponent, Engine::MoverComponent, Engine::InputComponent, Engine::TransformComponent>();
        auto bodyEntities = entityManager_->GetAllEntitiesWithComponents<BodyComponent,Engine::PlayerComponent, Engine::TransformComponent>();
        auto dataEntities = entityManager_->GetAllEntitiesWithComponent<PositionComponent>();

        //update head for input and movement
        for (auto& entity : headEntities)
        {
            auto move = entity->GetComponent<Engine::MoverComponent>();
            auto input = entity->GetComponent<Engine::InputComponent>();
            auto player = entity->GetComponent<Engine::PlayerComponent>();
            auto transform = entity->GetComponent<Engine::TransformComponent>();    

            auto speed = player->m_PlayerSpeed;
            auto direction = entity->GetComponent<HeadComponent>()->m_Direction;
            auto position = transform->m_Position;

            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveUp"));
            bool moveDownInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveDown"));
            bool moveLeftInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveLeft"));
            bool moveRightInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveRight"));

            for (auto& data : dataEntities) {
                data->GetComponent<PositionComponent>()->m_Positions[0] = position;
            }

            if (moveUpInput && !(direction == EHeadDirection::Down)) {
                entity->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Up;
            }
            else if (moveDownInput && !(direction == EHeadDirection::Up)) {
                entity->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Down;
            }
            else if (moveLeftInput && !(direction == EHeadDirection::Right)) {
                entity->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Left;
            }
            else if (moveRightInput && !(direction == EHeadDirection::Left)) {
                entity->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Right;
            }

            direction = entity->GetComponent<HeadComponent>()->m_Direction;

            //if enough time has passed we can activate the system
            if (m_passedTime > timeThreshold) {
                
                //Movement
                move->m_TranslationSpeed = { 0.f,0.f };

                // Collision/movement with window edges
                if (transform->m_Position.x < -620.f){
                    transform->m_Position.x = 620.f;
                }
                else if(transform->m_Position.x > 620.f){
                    transform->m_Position.x = -620.f;
                }
                else if (transform->m_Position.y < -340.f){
                    transform->m_Position.y = 340.f;
                }
                else if (transform->m_Position.y > 340.f){
                    transform->m_Position.y = -340.f;
                }
                else {
                    //update speed
                    move->m_TranslationSpeed.x = 40 * ((direction == EHeadDirection::Left ? -1.0f : 0.0f) + (direction == EHeadDirection::Right ? 1.0f : 0.0f));
                    move->m_TranslationSpeed.y = 40 * ((direction == EHeadDirection::Up ? -1.0f : 0.0f) + (direction == EHeadDirection::Down ? 1.0f : 0.0f));
                }

                //Collision

                //if head collided with fruit append it if it collided with superfruit increase speed/framerate
                if (entity->GetComponent<HeadComponent>()->m_HasEatenFruit) {
                    AppendSnake(entityManager_, 1);
                    entity->GetComponent<HeadComponent>()->m_HasEatenFruit = false;
                }
                if (entity->GetComponent<HeadComponent>()->m_HasEatenSuperFruit) {
                    m_framerate +=4;
                    entity->GetComponent<HeadComponent>()->m_HasEatenSuperFruit = false;
                }
    
                auto collider = entity->GetComponent<Engine::CollisionComponent>();

                for (const auto& entityCollided : collider->m_CollidedWith)
                {
                    //if snake hit itself reset game
                    if (entityCollided->HasComponent<BodyComponent>()) {
                        ResetSnake(entityManager_);
                    }

                    //================================================//
                    // Collision with Walls
                    //================================================//
                    if (entityCollided->HasComponent<BumperComponent>())
                    {                         
                        
                        auto position = entity->GetComponent<Engine::TransformComponent>()->m_Position;                                 
                        auto helpEntity = entityManager_->GetAllEntitiesWithComponent<HelperComponent>()[0];

                        auto transform = helpEntity->GetComponent<Engine::TransformComponent>();
                        transform->m_Position = position;
                        auto collider = helpEntity->GetComponent<Engine::CollisionComponent>();

                        switch (direction)
                        {
                        case EHeadDirection::Left:
                            transform->m_Position.y = position.y < 0 ? position.y + 40.f : position.y - 40.f;
                            direction = EHeadDirection::Down;
                            for (const auto& collision : collider->m_CollidedWith)
                            {                                
                                if (collision->HasComponent<BumperComponent>())
                                    direction = EHeadDirection::Up;
                            }                            
                            break;

                        case EHeadDirection::Right:                            
                            transform->m_Position.y = position.y < 0 ? position.y + 40.f : position.y - 40.f;
                            direction = EHeadDirection::Down;
                            for (const auto& collision : collider->m_CollidedWith)
                            {                                                                
                                if (collision->HasComponent<BumperComponent>())
                                    direction = EHeadDirection::Up;
                            }                            
                            break;

                        case EHeadDirection::Up:
                            transform->m_Position.x = position.x < 0 ? position.x + 40.f : position.x - 40.f;
                            direction = EHeadDirection::Right;
                            for (const auto& collision : collider->m_CollidedWith)
                            {                                
                                if (collision->HasComponent<BumperComponent>())
                                    direction = EHeadDirection::Left;
                            }
                            break;

                        case EHeadDirection::Down:
                            transform->m_Position.x = position.x < 0 ? position.x + 40.f : position.x - 40.f;
                            direction = EHeadDirection::Right;
                            for (const auto& collision : collider->m_CollidedWith)
                            {                                
                                if (collision->HasComponent<BumperComponent>())
                                    direction = EHeadDirection::Left;
                            }
                            break;

                        default:
                            break;
                        }

                        entity->GetComponent<HeadComponent>()->m_Direction = direction;                        
                    }
                    //================================================//
                }
            }
            //if not enough time passed just stay in place 
            else {
                move->m_TranslationSpeed = { 0.f,0.f };
            }
        }
      
        //save current positions first
        for (auto& entity : bodyEntities) {
            auto index = entity->GetComponent<BodyComponent>()->m_Index;
            auto position = entity->GetComponent<Engine::TransformComponent>()->m_Position;
            
            for (auto& data : dataEntities) {
                data->GetComponent<PositionComponent>()->m_Positions[index] = position;
            }
        }

        //update other body parts
        for (auto& entity : bodyEntities) {
            //if enough time has passed set new position
            if (m_passedTime > timeThreshold) {
                auto index = entity->GetComponent<BodyComponent>()->m_Index;
                auto position = entity->GetComponent<Engine::TransformComponent>()->m_Position;
 
                for (auto& data : dataEntities) {
                    entity->GetComponent<Engine::TransformComponent>()->m_Position = data->GetComponent<PositionComponent>()->m_Positions[index - 1];
                }
            }
        }

        if (m_passedTime > timeThreshold) {
            //reset time counter
            m_passedTime = 0;
        }
    }
    void PlayerController::ActivateBodyPart(Engine::EntityManager* entityManager_, int index, vec2 position)
    {   
        auto bodyEntities = entityManager_->GetAllEntitiesWithComponent<BodyComponent>();
        for (auto entity : bodyEntities) {
            if (entity->GetComponent<BodyComponent>()->m_Index == index) {
                entity->GetComponent<BodyComponent>()->m_Index = index;
                entity->GetComponent<Engine::SpriteComponent>()->m_Active = true;
                entity->GetComponent<Engine::CollisionComponent>()->m_Active = true;
                entity->GetComponent<Engine::TransformComponent>()->m_Position = position;

                break;
            }
        }
    }
    void PlayerController::AppendSnake(Engine::EntityManager* entityManager_, int length)
    {
        auto dataEntities = entityManager_->GetAllEntitiesWithComponent<PositionComponent>();

        //append snake for length num of parts
        for (auto& data : dataEntities) {
            auto snakeLength = data->GetComponent<PositionComponent>()->m_CurrentLength;
            for (int i = 0; i < length; i++) {
                ActivateBodyPart(entityManager_, snakeLength, data->GetComponent<PositionComponent>()->m_Positions[snakeLength - 1]);
                data->GetComponent<PositionComponent>()->m_CurrentLength = ++snakeLength;
            }
        }
    }
    void PlayerController::ResetSnake(Engine::EntityManager* entityManager_)
    {
        auto headEntity = entityManager_->GetAllEntitiesWithComponent<HeadComponent>();
        auto bodyEntities = entityManager_->GetAllEntitiesWithComponent<BodyComponent>();
        auto dataEntity = entityManager_->GetAllEntitiesWithComponent<PositionComponent>();

        for (auto head : headEntity) {
            head->GetComponent<Engine::TransformComponent>()->m_Position = { -320.f,20.f };
            head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Right;
            
            head->GetComponent<Engine::MoverComponent>()->m_TranslationSpeed = { 0.f,0.f };
        }

        for (auto part : bodyEntities) {
            auto index = part->GetComponent<BodyComponent>()->m_Index;
            if (index < 3) {
                part->GetComponent<Engine::TransformComponent>()->m_Position = { -320.f-40*index,20.f };
            }
            else {
                part->GetComponent<Engine::SpriteComponent>()->m_Active = false;
                part->GetComponent<Engine::CollisionComponent>()->m_Active = false;
            }
        }

        for (auto data : dataEntity) {
            data->GetComponent<PositionComponent>()->m_CurrentLength = 3;
        }

        m_framerate = 10;
    }
}
