#include "precomp.h"
#include "Entities.h"

#include "GameApp.h"

#include <Engine.h>
#include <Core/EntryPoint.h>


void Game::GameApp::GameSpecificWindowData()
{
    Engine::WindowData gameSpecificWindowData;
    gameSpecificWindowData.m_Title = "Snake Game";
    gameSpecificWindowData.m_Width = 1280;
    gameSpecificWindowData.m_Height = 720;
    gameSpecificWindowData.m_Vsync = true;
    SetWindowData(gameSpecificWindowData);
}

bool Game::GameApp::GameSpecificInit()
{
    m_RenderSystem->SetBackgroundColor(0, 0, 0, 1);

    m_CameraController = std::make_unique<CameraController>();
    m_CameraController->Init(m_EntityManager.get());

    srand(time(NULL));

    // TestImage
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "grass", "..\\Data\\grass_1.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "snakeBody", "..\\Data\\snakebody.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "red", "..\\Data\\red.png");

    //menu textures
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "game_mode_menu", "..\\Data\\game_mode_menu.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "main menu", "..\\Data\\main menu.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "pause_menu", "..\\Data\\pause_menu.png");

    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "start", "..\\Data\\start.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "quit", "..\\Data\\quit.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "resume", "..\\Data\\resume.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "main_menu", "..\\Data\\main_menu.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "story_mode", "..\\Data\\story_mode.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "infinite_runner", "..\\Data\\infinite_runner.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "yes", "..\\Data\\yes.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "no", "..\\Data\\no.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "easy", "..\\Data\\easy.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "hard", "..\\Data\\hard.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "death", "..\\Data\\death.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "bounce_off", "..\\Data\\bounce_off.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "white", "..\\Data\\blank.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "black", "..\\Data\\black.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "transparent", "..\\Data\\transparent.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "resume_1", "..\\Data\\1.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "resume_2", "..\\Data\\2.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "resume_3", "..\\Data\\3.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "resume_go", "..\\Data\\go.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "selection_border", "..\\Data\\selection_border.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "text_1", "..\\Data\\text_1.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "text_2", "..\\Data\\text_2.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "text_3", "..\\Data\\text_3.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "back_button", "..\\Data\\back_button.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "you_died", "..\\Data\\you_died.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "stripe", "..\\Data\\stripe.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "retry", "..\\Data\\retry.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "win_screen", "..\\Data\\win_screen.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "next_level", "..\\Data\\next_level.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall", "..\\Data\\wall.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "congratulations", "..\\Data\\congratulations.png");

    // Wall Textures
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall_240x80", "..\\Data\\walls\\wall_240x80.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall_80x240", "..\\Data\\walls\\wall_80x240.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall_160x240", "..\\Data\\walls\\wall_160x240.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall_400x160", "..\\Data\\walls\\wall_400x160.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall_80x160", "..\\Data\\walls\\wall_80x160.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall_80x80", "..\\Data\\walls\\wall_80x80.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall_80x400", "..\\Data\\walls\\wall_80x400.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall_80x200", "..\\Data\\walls\\wall_80x200.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall_200x80", "..\\Data\\walls\\wall_200x80.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "wall_200x100", "..\\Data\\walls\\wall_200x100.png");

    // Fruit Textures
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "fruit1", "..\\Data\\fruit1.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "fruit2", "..\\Data\\fruit2.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "fruit3", "..\\Data\\fruit3.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "fruit4", "..\\Data\\fruit4.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "fruit5", "..\\Data\\fruit5.png");

    m_TextureManager->CreateTextTexture(m_RenderSystem->GetRenderer(), "score", "");

    m_SoundManager->CreateSound("you_died_sound", "..\\Data\\Sounds\\you_died_sound.ogg");
    m_SoundManager->CreateSound("click", "..\\Data\\Sounds\\click.wav");
    m_SoundManager->CreateSound("select", "..\\Data\\Sounds\\select.wav");
    m_SoundManager->CreateSound("count", "..\\Data\\Sounds\\count.ogg");
    m_SoundManager->CreateSound("go", "..\\Data\\Sounds\\go.ogg");
    m_SoundManager->CreateSound("eat", "..\\Data\\Sounds\\eat.ogg");
    m_SoundManager->CreateSound("super_fruit", "..\\Data\\Sounds\\super_fruit.ogg");
    m_SoundManager->CreateSound("move", "..\\Data\\Sounds\\move_1.wav");
    m_SoundManager->CreateSound("bounce", "..\\Data\\Sounds\\bounce_1.wav");
    m_SoundManager->CreateSound("death", "..\\Data\\Sounds\\death_1.wav");
    m_SoundManager->CreateSound("superfruit_1", "..\\Data\\Sounds\\superfruit_1.wav");
    m_SoundManager->CreateSound("pause_in", "..\\Data\\Sounds\\pause7_in.wav");

    m_SoundManager->CreateMusic("main_menu_music", "..\\Data\\Sounds\\menu_music.mp3");
    m_SoundManager->CreateMusic("play_music", "..\\Data\\Sounds\\play_music.mp3");
    m_SoundManager->CreateMusic("level_1", "..\\Data\\Sounds\\level_1.wav");
    m_SoundManager->CreateMusic("level_2", "..\\Data\\Sounds\\level_2.wav");
    m_SoundManager->CreateMusic("level_3", "..\\Data\\Sounds\\level_3.wav");
    m_SoundManager->CreateMusic("congratulations", "..\\Data\\Sounds\\congratulations.wav");
    m_SoundManager->CreateMusic("victory", "..\\Data\\Sounds\\victory.ogg");

    std::vector<Engine::Texture*> fruitTextures{};
    fruitTextures.push_back(m_TextureManager->GetTexture("fruit2"));
    fruitTextures.push_back(m_TextureManager->GetTexture("fruit5"));

    std::vector<Engine::Texture*> superFruitTextures{};
    superFruitTextures.push_back(m_TextureManager->GetTexture("fruit1"));
    superFruitTextures.push_back(m_TextureManager->GetTexture("fruit3"));
    superFruitTextures.push_back(m_TextureManager->GetTexture("fruit4"));
    
    m_GameModeSettings = std::make_unique<Engine::GameModeSettings>();
    m_GameModeSettings->areBordersDeath = true;
    m_GameModeSettings->areBumpersDeath = false;
    m_GameModeSettings->difficulty = 1;

    m_firstLoad = true;
    m_firstResumeLoad = true;
    m_firstPauseLoad = true;
    m_level = 1;

    m_GameMode = Engine::GameStates::PlayingLevel;
    // Stadium
    m_Stadium = std::make_unique<Stadium>();
    m_Stadium->Init(m_EntityManager.get(), m_TextureManager->GetTexture("grass"), m_TextureManager.get()); 

    // Fruit 
    m_FruitController = std::make_unique<FruitController>(); // Important to be after Stadium to be drawn over it
    m_FruitController->Init(m_EntityManager.get(), fruitTextures, superFruitTextures);

    // Player
    m_PlayerController = std::make_unique<PlayerController>();
    m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("snakeBody"));

    // Score
    m_ScoreController = std::make_unique<ScoreController>();
    m_ScoreController->Init(m_EntityManager.get(), m_TextureManager.get(), m_RenderSystem->GetRenderer());

    //Main Menu
    m_MainMenu = std::make_unique<MainMenu>();
    m_MainMenu->Init(m_EntityManager.get(), m_TextureManager.get());
    //Game Mode Menu
    m_GameModeMenu = std::make_unique<GameModeMenu>();
    m_GameModeMenu->Init(m_EntityManager.get(), m_TextureManager.get());
    //Pause Menu
    m_PauseMenu = std::make_unique<PauseMenu>();
    
    //Resume Screen
    m_ResumeScreen = std::make_unique<ResumeScreen>();
  
    //Death Screen
    m_DeathScreen = std::make_unique<DeathScreen>();
    m_DeathScreen->Init(m_EntityManager.get(), m_TextureManager.get());
    //Victory Screen
    m_VictoryScreen = std::make_unique<VictoryScreen>();
    m_VictoryScreen->Init(m_EntityManager.get(), m_TextureManager.get());    

    //End Screen
    m_EndGameScreen = std::make_unique<EndGameScreen>();
    m_EndGameScreen->Init(m_EntityManager.get(), m_TextureManager.get());

    m_SoundManager->PlayMusic("main_menu_music", -1);
    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
    if (m_CurrentGameState->m_CurrentState == Engine::GameStates::PlayingLevel) {
        if (m_firstLoad) {
            m_ScoreController->RestartScore();
            switch (m_level) {
            case 1:
                m_Stadium->InitLvl1(m_EntityManager.get());
                break;
            case 2:
                m_Stadium->InitLvl2(m_EntityManager.get());
                break;
            case 3:
                m_Stadium->InitLvlCpp(m_EntityManager.get());
                break;
            default:
                break;
            }
            
            m_GameMode = Engine::GameStates::PlayingLevel;
            m_CurrentGameState->m_CurrentState = Engine::GameStates::ResumingLevel;
            m_firstLoad = false;
        }

        m_PlayerController->Update(dt, m_EntityManager.get(), m_GameModeSettings.get(), m_CurrentGameState.get(), m_GameMode, m_SoundManager.get());
        m_FruitController->Update(dt, m_EntityManager.get(), m_SoundManager.get());
        m_ScoreController->Update(dt);
        m_CameraController->Update(dt, m_EntityManager.get(), m_SoundManager.get(), m_CurrentGameState.get());

        if (m_CurrentGameState->m_CurrentState == Engine::GameStates::LevelLost) {
            m_ScoreController->RestartScore();
            m_Stadium->Destroy(m_EntityManager.get());
            m_firstLoad = true;
        }

        if (m_CurrentGameState->m_CurrentState == Engine::GameStates::LevelWon) {
            m_Stadium->Destroy(m_EntityManager.get());
            m_ScoreController->RestartScore();
            m_PlayerController->ResetSnake(m_EntityManager.get());
            m_SoundManager.get()->StopMusic();
            
            m_firstLoad = true;

            if (m_level < 3) {
                m_level++;
                m_SoundManager.get()->PlayMusic("victory", 1);
            }
            else {
                m_level = 1;
                m_SoundManager.get()->PlayMusic("congratulations", -1);
                m_CurrentGameState->m_CurrentState = Engine::GameStates::EndGameScreen;
            }
        }
    }
    else if (m_CurrentGameState->m_CurrentState == Engine::GameStates::PlayingInfiniteLevel) {
        if (m_firstLoad) {
            m_ScoreController->RestartScore();
            m_GameMode = Engine::GameStates::PlayingInfiniteLevel;
            m_CurrentGameState->m_CurrentState = Engine::GameStates::ResumingLevel;
            m_firstLoad = false;
        }

        m_PlayerController->Update(dt, m_EntityManager.get(), m_GameModeSettings.get(), m_CurrentGameState.get(), m_GameMode, m_SoundManager.get());
        m_FruitController->Update(dt, m_EntityManager.get(), m_SoundManager.get());
        m_ScoreController->Update(dt);
        m_CameraController->Update(dt, m_EntityManager.get(), m_SoundManager.get(), m_CurrentGameState.get());

        if (m_CurrentGameState->m_CurrentState == Engine::GameStates::LevelLost) {
            m_ScoreController->RestartScore();
            m_firstLoad = true;
        }
    }
    else if (m_CurrentGameState->m_CurrentState == Engine::GameStates::PauseMenu) {
        if (m_firstPauseLoad) {
            m_PauseMenu->Init(m_EntityManager.get(), m_TextureManager.get());
            m_firstPauseLoad = false;
        }

        m_PauseMenu->Update(dt, m_EntityManager.get(), m_SoundManager.get(), m_CurrentGameState.get(), m_GameMode);
        m_PlayerController->Update(dt, m_EntityManager.get(), m_GameModeSettings.get(), m_CurrentGameState.get(), m_GameMode, m_SoundManager.get());
        
        if (m_CurrentGameState->m_CurrentState != Engine::GameStates::PauseMenu) {
            m_PauseMenu->Destroy(m_EntityManager.get());
            m_firstPauseLoad = true;
        }

        if (m_CurrentGameState->m_CurrentState == Engine::GameStates::MainMenu) {
            m_ScoreController->RestartScore();
            m_PlayerController->ResetSnake(m_EntityManager.get());
            m_Stadium->Destroy(m_EntityManager.get());
            m_firstLoad = true;
        }
    }
    else if (m_CurrentGameState->m_CurrentState == Engine::GameStates::ResumingLevel) {
        if (m_firstResumeLoad) {
            m_ResumeScreen->Init(m_EntityManager.get(), m_TextureManager.get());
            m_firstResumeLoad = false;
        }
        
        m_ResumeScreen->Update(dt, m_EntityManager.get(), m_SoundManager.get(), m_CurrentGameState.get(), m_GameMode, m_level);

        if (m_CurrentGameState->m_CurrentState != Engine::GameStates::ResumingLevel) {
            m_ResumeScreen->Destroy(m_EntityManager.get());
            m_firstResumeLoad = true;
        }
    }
    else if (m_CurrentGameState->m_CurrentState == Engine::GameStates::GameModeMenu) {
        m_GameModeMenu->Update(dt, m_EntityManager.get(), m_CurrentGameState.get(), m_SoundManager.get(), m_GameMode, m_GameModeSettings.get());
    }
    else if (m_CurrentGameState->m_CurrentState == Engine::GameStates::LevelLost) {
        m_ScoreController->RestartScore();
        m_DeathScreen->Update(dt, m_EntityManager.get(), m_SoundManager.get(), m_CurrentGameState.get(), m_GameMode);

        if (m_CurrentGameState->m_CurrentState == Engine::GameStates::MainMenu) {            
            m_PlayerController->ResetSnake(m_EntityManager.get());
            m_Stadium->Destroy(m_EntityManager.get());
            m_firstLoad = true;
        }
    }
    else if (m_CurrentGameState->m_CurrentState == Engine::GameStates::LevelWon) {
        
        m_VictoryScreen->Update(dt, m_EntityManager.get(), m_SoundManager.get(), m_CurrentGameState.get(), m_GameMode);

        if (m_CurrentGameState->m_CurrentState != Engine::GameStates::LevelWon) {
            m_SoundManager.get()->StopMusic();
        }

        if (m_CurrentGameState->m_CurrentState == Engine::GameStates::MainMenu) {
            m_ScoreController->RestartScore();
            m_PlayerController->ResetSnake(m_EntityManager.get());
            m_Stadium->Destroy(m_EntityManager.get());
            m_firstLoad = true;
            m_SoundManager->PlayMusic("main_menu_music", -1);
        }
    }
    else if (m_CurrentGameState->m_CurrentState == Engine::GameStates::EndGameScreen) {
        
        m_EndGameScreen->Update(dt, m_EntityManager.get(), m_SoundManager.get(), m_CurrentGameState.get());

        if (m_CurrentGameState->m_CurrentState != Engine::GameStates::EndGameScreen) {
            m_SoundManager.get()->StopMusic();
        }

        if (m_CurrentGameState->m_CurrentState == Engine::GameStates::MainMenu) {
            m_SoundManager->PlayMusic("main_menu_music", -1);
        }
    }
    else {
        m_MainMenu->Update(dt, m_EntityManager.get(), m_SoundManager.get(), m_CurrentGameState.get());
    }
}

bool Game::GameApp::GameSpecificShutdown()
{
    return true;
}
