#include "precomp.h"
#include "PlayerController.h"
#include "GameComponents.h"


namespace Game
{
    bool PlayerController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to PlayerController::Init()");
        ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to PlayerController::Init()");

        m_framerate = 8;
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

        bool hasHitBumper = false;
        bool hasHitWall = false;

        auto headEntities = entityManager_->GetAllEntitiesWithComponents<Engine::PlayerComponent, Engine::MoverComponent, Engine::InputComponent, Engine::TransformComponent>();
        auto bodyEntities = entityManager_->GetAllEntitiesWithComponents<BodyComponent,Engine::PlayerComponent, Engine::TransformComponent>();
        auto dataEntity = entityManager_->GetAllEntitiesWithComponent<PositionComponent>()[0];

        //update head for input and movement
        for (auto& head : headEntities)
        {
            auto move = head->GetComponent<Engine::MoverComponent>();
            auto input = head->GetComponent<Engine::InputComponent>();
            auto player = head->GetComponent<Engine::PlayerComponent>();
            auto transform = head->GetComponent<Engine::TransformComponent>();    

            auto speed = player->m_PlayerSpeed;
            auto direction = head->GetComponent<HeadComponent>()->m_Direction;
            auto position = transform->m_Position;

            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveUp"));
            bool moveDownInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveDown"));
            bool moveLeftInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveLeft"));
            bool moveRightInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveRight"));
            
            //saving previous position
            auto prevPosition = dataEntity->GetComponent<PositionComponent>()->m_Positions[0];

            if (moveUpInput && !(direction == EHeadDirection::Down)) {
                head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Up;
            }
            else if (moveDownInput && !(direction == EHeadDirection::Up)) {
                head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Down;
            }
            else if (moveLeftInput && !(direction == EHeadDirection::Right)) {
                head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Left;
            }
            else if (moveRightInput && !(direction == EHeadDirection::Left)) {
                head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Right;
            }

            direction = head->GetComponent<HeadComponent>()->m_Direction;

            //collision with other entities 
            auto collider = head->GetComponent<Engine::CollisionComponent>();

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
                    hasHitBumper = true;

                    auto position = head->GetComponent<Engine::TransformComponent>()->m_Position;
                    auto helpEntity = entityManager_->GetAllEntitiesWithComponent<HelperComponent>()[0];
                    transform->m_Position = prevPosition;

                    auto helperTransform = helpEntity->GetComponent<Engine::TransformComponent>();
                    helperTransform->m_Position = prevPosition;
                    auto helperCollider = helpEntity->GetComponent<Engine::CollisionComponent>();

                    auto bumperEntites = entityManager_->GetAllEntitiesWithComponent<BumperComponent>();

                    float x, y; // Coordinates of snake head

                    switch (direction)
                    {
                    case EHeadDirection::Left:
                        y = position.y;
                        helperTransform->m_Position.x = position.x;
                        helperTransform->m_Position.y = y < 0 ? y + 40.f : y - 40.f;
                        direction = y > helperTransform->m_Position.y ? EHeadDirection::Down : EHeadDirection::Up;

                        //for (const auto& collision : helperCollider->m_CollidedWith)
                        //{                                
                            //if (collision->HasComponent<BumperComponent>())
                        for (auto bumper : bumperEntites) {
                            if (Engine::CheckForCollision(helpEntity, bumper))
                            {
                                if (direction == EHeadDirection::Down)
                                    direction = EHeadDirection::Up;
                                else
                                    direction = EHeadDirection::Down;
                            }
                        }
                        break;

                    case EHeadDirection::Right:
                        y = position.y;
                        helperTransform->m_Position.x = position.x;
                        helperTransform->m_Position.y = y < 0 ? y + 40.f : y - 40.f;
                        direction = y > helperTransform->m_Position.y ? EHeadDirection::Down : EHeadDirection::Up;

                        //for (const auto& collision : helperCollider->m_CollidedWith)
                        for (auto bumper : bumperEntites)
                        {
                            //if (collision->HasComponent<BumperComponent>())
                            if (Engine::CheckForCollision(helpEntity, bumper))
                            {
                                if (direction == EHeadDirection::Down)
                                    direction = EHeadDirection::Up;
                                else
                                    direction = EHeadDirection::Down;
                            }
                        }
                        break;

                    case EHeadDirection::Up:
                        x = position.x;
                        helperTransform->m_Position.y = position.y;
                        helperTransform->m_Position.x = x < 0 ? x + 40.f : x - 40.f;
                        direction = x > helperTransform->m_Position.x ? EHeadDirection::Right : EHeadDirection::Left;

                        //for (const auto& collision : helperCollider->m_CollidedWith)
                        for (auto bumper : bumperEntites)
                        {
                            //if (collision->HasComponent<BumperComponent>())
                            if (Engine::CheckForCollision(helpEntity, bumper))
                            {
                                if (direction == EHeadDirection::Left)
                                    direction = EHeadDirection::Right;
                                else
                                    direction = EHeadDirection::Left;
                            }
                        }
                        break;

                    case EHeadDirection::Down:
                        x = position.x;
                        helperTransform->m_Position.y = position.y;
                        helperTransform->m_Position.x = x < 0 ? x + 40.f : x - 40.f;
                        direction = x > helperTransform->m_Position.x ? EHeadDirection::Right : EHeadDirection::Left;

                        //for (const auto& collision : helperCollider->m_CollidedWith)
                        for (auto bumper : bumperEntites)
                        {
                            //if (collision->HasComponent<BumperComponent>())
                            if (Engine::CheckForCollision(helpEntity, bumper))
                            {
                                if (direction == EHeadDirection::Left)
                                    direction = EHeadDirection::Right;
                                else
                                    direction = EHeadDirection::Left;
                            }
                        }
                        break;

                    default:
                        break;
                    }

                    head->GetComponent<HeadComponent>()->m_Direction = direction;
                    transform->m_Position.x += 40 * ((direction == EHeadDirection::Left ? -1.0f : 0.0f) + (direction == EHeadDirection::Right ? 1.0f : 0.0f));
                    transform->m_Position.y += 40 * ((direction == EHeadDirection::Up ? -1.0f : 0.0f) + (direction == EHeadDirection::Down ? 1.0f : 0.0f));
                }
                //================================================//
            }

            //if enough time has passed we can activate the system
            if (m_passedTime > timeThreshold) {

                //Collision

                //if head collided with fruit append it if it collided with superfruit increase speed/framerate
                if (head->GetComponent<HeadComponent>()->m_HasEatenFruit) {
                    AppendSnake(entityManager_, 1);
                    head->GetComponent<HeadComponent>()->m_HasEatenFruit = false;
                }
                if (head->GetComponent<HeadComponent>()->m_HasEatenSuperFruit) {
                    m_framerate += 2;
                    head->GetComponent<HeadComponent>()->m_HasEatenSuperFruit = false;
                }


                // Collision/movement with window edges
                if (transform->m_Position.x < -620.f){
                    transform->m_Position.x = 620.f;
                    hasHitWall = true;
                }
                else if(transform->m_Position.x > 620.f){
                    transform->m_Position.x = -620.f;
                    hasHitWall = true;
                }
                else if (transform->m_Position.y < -340.f){
                    transform->m_Position.y = 340.f;
                    hasHitWall = true;
                }
                else if (transform->m_Position.y > 340.f){
                    transform->m_Position.y = -340.f;
                    hasHitWall = true;
                }

                //Movement

                //save previous position
                dataEntity->GetComponent<PositionComponent>()->m_Positions[0] = position;

                //update speed
                if (!hasHitBumper && !hasHitWall) {
                    move->m_TranslationSpeed.x = 40 * ((direction == EHeadDirection::Left ? -1.0f : 0.0f) + (direction == EHeadDirection::Right ? 1.0f : 0.0f));
                    move->m_TranslationSpeed.y = 40 * ((direction == EHeadDirection::Up ? -1.0f : 0.0f) + (direction == EHeadDirection::Down ? 1.0f : 0.0f));
                }
            }
            //if not enough time passed just stay in place 
            else {
                move->m_TranslationSpeed = { 0.f,0.f };
            }
        }
      
        //save current positions first
        if (m_passedTime > timeThreshold && !hasHitBumper) {
            for (auto& entity : bodyEntities) {
                auto index = entity->GetComponent<BodyComponent>()->m_Index;
                auto position = entity->GetComponent<Engine::TransformComponent>()->m_Position;

                dataEntity->GetComponent<PositionComponent>()->m_Positions[index] = position;
            }
        }

        //update other body parts
        //if enough time has passed set new position
        if (m_passedTime > timeThreshold && !hasHitBumper) {
            for (auto& entity : bodyEntities) {
                auto index = entity->GetComponent<BodyComponent>()->m_Index;
                auto position = entity->GetComponent<Engine::TransformComponent>()->m_Position;
 
                entity->GetComponent<Engine::TransformComponent>()->m_Position = dataEntity->GetComponent<PositionComponent>()->m_Positions[index - 1];    
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
        auto dataEntity = entityManager_->GetAllEntitiesWithComponent<PositionComponent>()[0];

        //append snake for length num of parts
        auto snakeLength = dataEntity->GetComponent<PositionComponent>()->m_CurrentLength;
        for (int i = 0; i < length; i++) {
            ActivateBodyPart(entityManager_, snakeLength, dataEntity->GetComponent<PositionComponent>()->m_Positions[snakeLength - 1]);
            dataEntity->GetComponent<PositionComponent>()->m_CurrentLength = ++snakeLength;
        }
        
    }

    void PlayerController::ResetSnake(Engine::EntityManager* entityManager_)
    {
        auto headEntity = entityManager_->GetAllEntitiesWithComponent<HeadComponent>();
        auto bodyEntities = entityManager_->GetAllEntitiesWithComponent<BodyComponent>();
        auto dataEntity = entityManager_->GetAllEntitiesWithComponent<PositionComponent>();

        for (auto head : headEntity) {
            head->GetComponent<Engine::TransformComponent>()->m_Position = { -300.f,20.f };
            head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Right;
            
            head->GetComponent<Engine::MoverComponent>()->m_TranslationSpeed = { 0.f,0.f };
        }

        for (auto part : bodyEntities) {
            auto index = part->GetComponent<BodyComponent>()->m_Index;
            if (index < 3) {
                part->GetComponent<Engine::TransformComponent>()->m_Position = { -300.f-40*index,20.f };
            }
            else {
                part->GetComponent<Engine::SpriteComponent>()->m_Active = false;
                part->GetComponent<Engine::CollisionComponent>()->m_Active = false;
            }
        }

        for (auto data : dataEntity) {
            data->GetComponent<PositionComponent>()->m_CurrentLength = 3;
        }

        m_framerate = 8;
    }
}
