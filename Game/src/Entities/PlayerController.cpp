#include "precomp.h"
#include "PlayerController.h"
#include "GameComponents.h"


namespace Game
{
    bool PlayerController::Init(Engine::EntityManager* entityManager_, Engine::Texture* texture_)
    {
        ASSERT(entityManager_ != nullptr, "Must pass valid pointer to entitymanager to PlayerController::Init()");
        ASSERT(texture_ != nullptr, "Must pass valid pointer to texture to PlayerController::Init()");

        m_framerate = START_SNAKE_SPEED;
        m_passedTime;

        auto data = std::make_unique<Engine::Entity>();;
        data->AddComponent<PositionComponent>();

        auto player = std::make_unique<Engine::Entity>();

        //initializing head entity
        player->AddComponent<Engine::TransformComponent>(START1_SNAKE_POS_X, START1_SNAKE_POS_Y, SNAKE_PART_SIZE, SNAKE_PART_SIZE);
        player->AddComponent<Engine::CollisionComponent>(SNAKE_PART_SIZE, SNAKE_PART_SIZE);
        player->AddComponent<Engine::PlayerComponent>();
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
        for (int i = 1; i < MAX_SNAKE_LENGTH; i++) {
        
            player=std::make_unique<Engine::Entity>();
            player->AddComponent<Engine::TransformComponent>(START1_SNAKE_POS_X - PART_SIZE*i, START1_SNAKE_POS_Y, SNAKE_PART_SIZE, SNAKE_PART_SIZE);
            player->AddComponent<Engine::CollisionComponent>(SNAKE_PART_SIZE, SNAKE_PART_SIZE);
            player->AddComponent<Engine::PlayerComponent>();
            player->AddComponent<BodyComponent>(i);
            player->AddComponent<Engine::SpriteComponent>().m_Image = texture_;

            //body parts longer than starting length are deactivated
            if (i >= START_SNAKE_LENGTH ) {
                player->GetComponent<Engine::SpriteComponent>()->m_Active = false;
                player->GetComponent<Engine::CollisionComponent>()->m_Active = false;
            }
           
            entityManager_->AddEntity(std::move(player));
        }
        entityManager_->AddEntity(std::move(data));

        // *** Helper Component ***
        auto tmpEntity = std::make_unique<Engine::Entity>();
        tmpEntity->AddComponent<HelperComponent>();
        tmpEntity->AddComponent<Engine::TransformComponent>(START1_SNAKE_POS_X, START1_SNAKE_POS_Y, SNAKE_PART_SIZE, SNAKE_PART_SIZE);
        tmpEntity->AddComponent<Engine::CollisionComponent>(SNAKE_PART_SIZE, SNAKE_PART_SIZE);
        entityManager_->AddEntity(std::move(tmpEntity));

        return !(entityManager_->GetAllEntitiesWithComponent<Engine::PlayerComponent>().empty());
    }

    void PlayerController::Update(float dt, Engine::EntityManager* entityManager_, Engine::GameModeSettings* gameModeSettings, Engine::CurrentGameState* gameState, Engine::GameStates gameMode, Engine::SoundManager* soundManager_)
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

            //if game is not playing set head speed to 0 and return
            if (gameState->m_CurrentState != Engine::GameStates::PlayingInfiniteLevel && gameState->m_CurrentState != Engine::GameStates::PlayingLevel) {
                move->m_TranslationSpeed = { 0,0 };
                return;
            }

            //saving previous position
            auto prevPosition = dataEntity->GetComponent<PositionComponent>()->m_Positions[0];

            direction = head->GetComponent<HeadComponent>()->m_Direction;

            //collision with other entities 
            auto collider = head->GetComponent<Engine::CollisionComponent>();

            for (const auto& entityCollided : collider->m_CollidedWith)
            {
                //if snake hit itself reset game
                if (entityCollided->HasComponent<BodyComponent>()) {
                    soundManager_->PlaySound("death", 0);
                    ResetSnake(entityManager_);
                    gameState->m_CurrentState = Engine::GameStates::LevelLost;
                    return;
                }

                // Collision with Bumpers
                if (entityCollided->HasComponent<BumperComponent>())
                {
                    m_inputDelay = 2;

                    //if bumpers are death reset snake
                    if (gameModeSettings->areBumpersDeath) {
                        soundManager_->PlaySound("death", 0);
                        ResetSnake(entityManager_);
                        gameState->m_CurrentState = Engine::GameStates::LevelLost;
                        return;
                    }
                    //else move snake in appropriate direciton 
                    else {
                        hasHitBumper = true;

                        soundManager_->PlaySound("bounce", 0);

                        auto position = head->GetComponent<Engine::TransformComponent>()->m_Position;
                        auto helpEntity = entityManager_->GetAllEntitiesWithComponent<HelperComponent>()[0];
                        transform->m_Position = prevPosition;

                        auto helperTransform = helpEntity->GetComponent<Engine::TransformComponent>();
                        helperTransform->m_Position = prevPosition;
                        auto helperCollider = helpEntity->GetComponent<Engine::CollisionComponent>();

                        auto bumperEntites = entityManager_->GetAllEntitiesWithComponent<BumperComponent>();

                        // Coordinates of snake head
                        float x, y;

                        switch (direction)
                        {
                        case EHeadDirection::Left:
                            y = prevPosition.y;
                            helperTransform->m_Position.x = prevPosition.x;
                            helperTransform->m_Position.y = y < 0 ? y + PART_SIZE : y - PART_SIZE;
                            direction = y < helperTransform->m_Position.y ? EHeadDirection::Down : EHeadDirection::Up;

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
                            y = prevPosition.y;
                            helperTransform->m_Position.x = prevPosition.x;
                            helperTransform->m_Position.y = y < 0 ? y + PART_SIZE : y - PART_SIZE;
                            direction = y < helperTransform->m_Position.y ? EHeadDirection::Down : EHeadDirection::Up;

                            for (auto bumper : bumperEntites)
                            {
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
                            x = prevPosition.x;
                            helperTransform->m_Position.y = prevPosition.y;
                            helperTransform->m_Position.x = x < 0 ? x + PART_SIZE : x - PART_SIZE;
                            direction = x < helperTransform->m_Position.x ? EHeadDirection::Right : EHeadDirection::Left;

                            for (auto bumper : bumperEntites)
                            {
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
                            x = prevPosition.x;
                            helperTransform->m_Position.y = prevPosition.y;
                            helperTransform->m_Position.x = x < 0 ? x + PART_SIZE : x - PART_SIZE;
                            direction = x < helperTransform->m_Position.x ? EHeadDirection::Right : EHeadDirection::Left;

                            for (auto bumper : bumperEntites)
                            {
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
                        transform->m_Position.x += PART_SIZE * ((direction == EHeadDirection::Left ? -1.0f : 0.0f) + (direction == EHeadDirection::Right ? 1.0f : 0.0f));
                        transform->m_Position.y += PART_SIZE * ((direction == EHeadDirection::Up ? -1.0f : 0.0f) + (direction == EHeadDirection::Down ? 1.0f : 0.0f));
                    }
                }//end of bumper collision
            }//end of collision

            if (!m_inputDelay) {
                bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveUp"));
                bool moveDownInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveDown"));
                bool moveLeftInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveLeft"));
                bool moveRightInput = Engine::InputManager::IsActionActive(input, fmt::format("Player1MoveRight"));

                if (moveUpInput && !(direction == EHeadDirection::Down)) {
                    head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Up;
                    m_inputDelay = 1;
                }
                else if (moveDownInput && !(direction == EHeadDirection::Up)) {
                    head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Down;
                    m_inputDelay = 1;
                }
                else if (moveLeftInput && !(direction == EHeadDirection::Right)) {
                    head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Left;
                    m_inputDelay = 1;
                }
                else if (moveRightInput && !(direction == EHeadDirection::Left)) {
                    head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Right;
                    m_inputDelay = 1;
                }
            }//end of input processing


            //if enough time has passed we can activate movement and rest of collision
            if (m_passedTime > timeThreshold) {

                //update waiting to read input
                if (m_inputDelay) {
                    m_inputDelay--;
                }

                //Collision

                //if head collided with fruit append it and check if level is won
                if (head->GetComponent<HeadComponent>()->m_HasEatenFruit) {
                    AppendSnake(entityManager_, 1);
                    head->GetComponent<HeadComponent>()->m_HasEatenFruit = false;

                    if (gameMode == Engine::GameStates::PlayingLevel && CheckWinCondition(entityManager_,gameModeSettings)) {
                        gameState->m_CurrentState = Engine::GameStates::LevelWon;
                    }
                }
                //if it collided with superfruit increase speed / framerate and check if level is won
                if (head->GetComponent<HeadComponent>()->m_HasEatenSuperFruit) {
                    m_framerate += 2;
                    head->GetComponent<HeadComponent>()->m_HasEatenSuperFruit = false;

                    if (gameMode == Engine::GameStates::PlayingLevel && CheckWinCondition(entityManager_, gameModeSettings)) {
                        gameState->m_CurrentState = Engine::GameStates::LevelWon;
                    }
                }


                // Collision/movement with window edges
                if (transform->m_Position.x < -620.f){

                    if (gameModeSettings->areBordersDeath && gameMode==Engine::GameStates::PlayingLevel) {
                        soundManager_->PlaySound("death", 0);
                        ResetSnake(entityManager_);
                        gameState->m_CurrentState = Engine::GameStates::LevelLost;
                        return;
                    }
                    else {
                        transform->m_Position.x = 620.f;
                        hasHitWall = true;
                    }
                }
                else if(transform->m_Position.x > 620.f){
                    if (gameModeSettings->areBordersDeath && gameMode == Engine::GameStates::PlayingLevel) {
                        soundManager_->PlaySound("death", 0);
                        ResetSnake(entityManager_);
                        gameState->m_CurrentState = Engine::GameStates::LevelLost;
                        return;
                    }
                    else {
                        transform->m_Position.x = -620.f;
                        hasHitWall = true;
                    }
                }
                else if (transform->m_Position.y < -340.f){
                    if (gameModeSettings->areBordersDeath && gameMode == Engine::GameStates::PlayingLevel) {
                        soundManager_->PlaySound("death", 0);
                        ResetSnake(entityManager_);
                        gameState->m_CurrentState = Engine::GameStates::LevelLost;
                        return;
                    }
                    else {
                        transform->m_Position.y = 340.f;
                        hasHitWall = true;
                    }
                }
                else if (transform->m_Position.y > 340.f){
                    if (gameModeSettings->areBordersDeath && gameMode == Engine::GameStates::PlayingLevel) {
                        soundManager_->PlaySound("death", 0);
                        ResetSnake(entityManager_);
                        gameState->m_CurrentState = Engine::GameStates::LevelLost;
                        return;
                    }
                    else {
                        transform->m_Position.y = -340.f;
                        hasHitWall = true;
                    }
                }

                //Movement

                //save previous position
                dataEntity->GetComponent<PositionComponent>()->m_Positions[0] = position;

                //update speed
                if (!hasHitBumper && !hasHitWall) {
                    move->m_TranslationSpeed.x = PART_SIZE * ((direction == EHeadDirection::Left ? -1.0f : 0.0f) + (direction == EHeadDirection::Right ? 1.0f : 0.0f));
                    move->m_TranslationSpeed.y = PART_SIZE * ((direction == EHeadDirection::Up ? -1.0f : 0.0f) + (direction == EHeadDirection::Down ? 1.0f : 0.0f));
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
            head->GetComponent<Engine::TransformComponent>()->m_Position = { START1_SNAKE_POS_X,START1_SNAKE_POS_Y };
            head->GetComponent<HeadComponent>()->m_Direction = EHeadDirection::Right;
            
            head->GetComponent<Engine::MoverComponent>()->m_TranslationSpeed = { 0.f,0.f };
        }

        for (auto part : bodyEntities) {
            auto index = part->GetComponent<BodyComponent>()->m_Index;
            if (index < START_SNAKE_LENGTH) {
                part->GetComponent<Engine::TransformComponent>()->m_Position = { START1_SNAKE_POS_X - PART_SIZE*index, START1_SNAKE_POS_Y };
            }
            else {
                part->GetComponent<Engine::SpriteComponent>()->m_Active = false;
                part->GetComponent<Engine::CollisionComponent>()->m_Active = false;
            }
        }

        for (auto data : dataEntity) {
            data->GetComponent<PositionComponent>()->m_CurrentLength = 3;
        }

        m_framerate = START_SNAKE_SPEED;
    }
    bool PlayerController::CheckWinCondition(Engine::EntityManager* entityManager_, Engine::GameModeSettings* gameModeSettings)
    {
        auto scoreEntity = entityManager_->GetAllEntitiesWithComponent<ScoreComponent>()[0];
        auto score = scoreEntity->GetComponent<ScoreComponent>()->m_Score;
        auto difficulty = gameModeSettings->difficulty;
        if ((difficulty == EASY_MODE && score >= WIN_SCORE_EASY) || (difficulty == HARD_MODE && score >= WIN_SCORE_HARD)) {
            return true;
        }
        return false;
    }
}
