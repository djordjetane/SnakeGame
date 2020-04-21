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

    // Stadium
    m_Stadium = std::make_unique<Stadium>();
    m_Stadium->Init(m_EntityManager.get(), m_TextureManager->GetTexture("grass"));


    // Fruit 
    m_FruitController = std::make_unique<FruitController>(); // Importaint to be after Stadium to be drawn over it
    m_FruitController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("fruit"));

    // Player
    m_PlayerController = std::make_unique<PlayerController>();
    m_PlayerController->Init(m_EntityManager.get(), m_TextureManager->GetTexture("snakeBody"));

    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
    m_PlayerController->Update(dt, m_EntityManager.get());
    m_CameraController->Update(dt, m_EntityManager.get());
    m_FruitController->Update(dt, m_EntityManager.get());
}

bool Game::GameApp::GameSpecificShutdown()
{
    return true;
}
