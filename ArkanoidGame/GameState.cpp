#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"
#include <cassert>
#include <memory> 

namespace ArkanoidGame
{

    GameState::GameState(GameStateType type, bool isExclusivelyVisible) noexcept
        : type(type), isExclusivelyVisible(isExclusivelyVisible)
    {
        switch (type)
        {
        case GameStateType::MainMenu:
        {
            data = std::make_shared<GameStateMainMenuData>();
            std::static_pointer_cast<GameStateMainMenuData>(data)->Init();
            break;
        }
        case GameStateType::Playing:
        {
            data = std::make_shared<GameStatePlayingData>();
            std::static_pointer_cast<GameStatePlayingData>(data)->Init();
            break;
        }
        case GameStateType::GameOver:
        {
            data = std::make_shared<GameStateGameOverData>();
            std::static_pointer_cast<GameStateGameOverData>(data)->Init();
            break;
        }
        case GameStateType::ExitDialog:
        {
            data = std::make_shared<GameStatePauseMenuData>();
            std::static_pointer_cast<GameStatePauseMenuData>(data)->Init();
            break;
        }
        case GameStateType::Records:
        {
            data = std::make_shared<GameStateRecordsData>();
            std::static_pointer_cast<GameStateRecordsData>(data)->Init();
            break;
        }
        default:
            assert(false && "Unhandled GameStateType");
            break;
        }
    }


    void GameState::Update(float timeDelta)
    {
        switch (type)
        {
        case GameStateType::MainMenu:
            std::static_pointer_cast<GameStateMainMenuData>(data)->Update(timeDelta);
            break;
        case GameStateType::Playing:
            std::static_pointer_cast<GameStatePlayingData>(data)->Update(timeDelta);
            break;
        case GameStateType::GameOver:
            std::static_pointer_cast<GameStateGameOverData>(data)->Update(timeDelta);
            break;
        case GameStateType::ExitDialog:
            std::static_pointer_cast<GameStatePauseMenuData>(data)->Update(timeDelta);
            break;
        case GameStateType::Records:
            std::static_pointer_cast<GameStateRecordsData>(data)->Update(timeDelta);
            break;
        default:
            assert(false && "Unhandled GameStateType");
            break;
        }
    }

    void GameState::Draw(sf::RenderWindow& window)
    {
        switch (type)
        {
        case GameStateType::MainMenu:
            std::static_pointer_cast<GameStateMainMenuData>(data)->Draw(window);
            break;
        case GameStateType::Playing:
            std::static_pointer_cast<GameStatePlayingData>(data)->Draw(window);
            break;
        case GameStateType::GameOver:
            std::static_pointer_cast<GameStateGameOverData>(data)->Draw(window);
            break;
        case GameStateType::ExitDialog:
            std::static_pointer_cast<GameStatePauseMenuData>(data)->Draw(window);
            break;
        case GameStateType::Records:
            std::static_pointer_cast<GameStateRecordsData>(data)->Draw(window);
            break;
        default:
            assert(false && "Unhandled GameStateType");
            break;
        }
    }

    void GameState::HandleWindowEvent(sf::Event& event)
    {
        switch (type)
        {
        case GameStateType::MainMenu:
            std::static_pointer_cast<GameStateMainMenuData>(data)->HandleWindowEvent(event);
            break;
        case GameStateType::Playing:
            std::static_pointer_cast<GameStatePlayingData>(data)->HandleWindowEvent(event);
            break;
        case GameStateType::GameOver:
            std::static_pointer_cast<GameStateGameOverData>(data)->HandleWindowEvent(event);
            break;
        case GameStateType::ExitDialog:
            std::static_pointer_cast<GameStatePauseMenuData>(data)->HandleWindowEvent(event);
            break;
        case GameStateType::Records:
            std::static_pointer_cast<GameStateRecordsData>(data)->HandleWindowEvent(event);
            break;
        default:
            assert(false && "Unhandled GameStateType");
            break;
        }
    }

} 