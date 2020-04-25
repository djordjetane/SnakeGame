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

    // TestImage
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "grass", "..\\Data\\grass.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "snakeBody", "..\\Data\\snakebody.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "fruit", "..\\Data\\fruit.png");        
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "start", "..\\Data\\start.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "quit", "..\\Data\\quit.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "resume", "..\\Data\\resume.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "white", "..\\Data\\blank.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "black", "..\\Data\\black.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "transparent", "..\\Data\\transparent.png");
    // Stadium
    m_Stadium = std::make_unique<Stadium>();
    m_Stadium->Init(m_EntityManager.get(), m_TextureManager->GetTexture("grass"), m_TextureManager->GetTexture("black"));


    // Fruit 
    m_FruitController = std::make_unique<FruitController>(); // Importaint to be after Stadium to be drawn over it
    m_FruitController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("fruit"));

    // Player
    m_PlayerController = std::make_unique<PlayerController>();
    m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("snakeBody"));


    //Main Menu
    m_MainMenu = std::make_unique<MainMenu>();
    m_MainMenu->Init(m_EntityManager.get(), m_TextureManager->GetTexture("start"), m_TextureManager->GetTexture("quit"),
        m_TextureManager->GetTexture("white"), m_TextureManager->GetTexture("black"));
    //Pause Menu
    m_PauseMenu = std::make_unique<PauseMenu>();
    m_PauseMenu->Init(m_EntityManager.get(), m_TextureManager->GetTexture("resume"), m_TextureManager->GetTexture("quit"),
        m_TextureManager->GetTexture("white"), m_TextureManager->GetTexture("transparent"));

    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
    if (m_GameState == Engine::GameState::PlayingLevel) {
        m_PlayerController->Update(dt, m_EntityManager.get());
        m_CameraController->Update(dt, m_EntityManager.get(), &m_GameState);
        m_FruitController->Update(dt, m_EntityManager.get());
    }
    else if (m_GameState == Engine::GameState::PauseMenu) {
        m_PauseMenu->Update(dt, m_EntityManager.get(), &m_GameState);
    }
    else {
        m_MainMenu->Update(dt, m_EntityManager.get(), &m_GameState);
    }
}

bool Game::GameApp::GameSpecificShutdown()
{
    return true;
}
