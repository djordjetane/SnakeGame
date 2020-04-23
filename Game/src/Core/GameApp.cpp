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
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "white", "..\\Data\\blank.png");
    m_TextureManager->CreateTexture(m_RenderSystem->GetRenderer(), "black", "..\\Data\\black.png");
    // Stadium
    m_Stadium = std::make_unique<Stadium>();
    m_Stadium->Init(m_EntityManager.get(), m_TextureManager->GetTexture("grass"));


    // Fruit 
    m_FruitController = std::make_unique<FruitController>(); // Importaint to be after Stadium to be drawn over it
    m_FruitController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("fruit"));

    // Player
    m_PlayerController = std::make_unique<PlayerController>();
    m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("snakeBody"));


    //Menu
    m_Menu = std::make_unique<Menu>();
    m_Menu->Init(m_EntityManager.get(), m_TextureManager->GetTexture("start"), m_TextureManager->GetTexture("quit"),
        m_TextureManager->GetTexture("white"), m_TextureManager->GetTexture("black"));

    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
    if (!m_Menu->is_shown) {
        m_PlayerController->Update(dt, m_EntityManager.get());
        m_CameraController->Update(dt, m_EntityManager.get());
        m_FruitController->Update(dt, m_EntityManager.get());
    }
    else {
        m_Menu->Update(dt, m_EntityManager.get());
        if (m_Menu->quit) {
           //TODO
        }
    }
}

bool Game::GameApp::GameSpecificShutdown()
{
    return true;
}
