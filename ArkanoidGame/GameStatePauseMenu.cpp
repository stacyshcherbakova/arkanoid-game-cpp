#include "GameStatePauseMenu.h"
#include "Application.h"
#include "Game.h"
#include <cassert>
#include <memory>

namespace ArkanoidGame {

    void GameStatePauseMenuData::Init()
    {
        assert(font.loadFromFile(RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

        auto startGame = std::make_unique<MenuItem>();
        startGame->GetText().setString("Start Game");
        startGame->GetText().setFont(font);
        startGame->GetText().setCharacterSize(24);
        startGame->set_on_press([](MenuItem&) {
            Application::Instance().GetGame().SwitchStateTo(GameStateType::Playing);
            });

        const bool isInfiniteApples =
            Application::Instance().GetGame().IsEnableOptions(GameOptions::InfiniteApples);

        auto optionsInfiniteApplesItem = std::make_unique<MenuItem>();
        optionsInfiniteApplesItem->GetText().setString(
            "Infinite Apples: " + std::string(isInfiniteApples ? "On" : "Off"));
        optionsInfiniteApplesItem->GetText().setFont(font);
        optionsInfiniteApplesItem->GetText().setCharacterSize(24);
        optionsInfiniteApplesItem->set_on_press([](MenuItem& item) {
            Game& game = Application::Instance().GetGame();
            bool newVal = !game.IsEnableOptions(GameOptions::InfiniteApples);
            game.SetOption(GameOptions::InfiniteApples, newVal);
            item.GetText().setString("Infinite Apples: " + std::string(newVal ? "On" : "Off"));
            });

        const bool isWithAcceleration =
            Application::Instance().GetGame().IsEnableOptions(GameOptions::WithAcceleration);

        auto optionsWithAccelerationItem = std::make_unique<MenuItem>();
        optionsWithAccelerationItem->GetText().setString(
            "With Acceleration: " + std::string(isWithAcceleration ? "On" : "Off"));
        optionsWithAccelerationItem->GetText().setFont(font);
        optionsWithAccelerationItem->GetText().setCharacterSize(24);
        optionsWithAccelerationItem->set_on_press([](MenuItem& item) {
            Game& game = Application::Instance().GetGame();
            bool newVal = !game.IsEnableOptions(GameOptions::WithAcceleration);
            game.SetOption(GameOptions::WithAcceleration, newVal);
            item.GetText().setString("With Acceleration: " + std::string(newVal ? "On" : "Off"));
            });

        auto options = std::make_unique<MenuItem>();
        options->GetText().setString("Options");
        options->GetText().setFont(font);
        options->GetText().setCharacterSize(24);
        options->HintText().setString("Options");
        options->HintText().setFont(font);
        options->HintText().setCharacterSize(48);
        options->HintText().setFillColor(sf::Color::Red);
        options->set_children_orientation(Orientation::Vertical);
        options->set_children_alignment(Alignment::Middle);
        options->set_children_spacing(10.f);

        options->add_child(std::move(optionsInfiniteApplesItem));
        options->add_child(std::move(optionsWithAccelerationItem));

        auto recordsItem = std::make_unique<MenuItem>();
        recordsItem->GetText().setString("Records");
        recordsItem->GetText().setFont(font);
        recordsItem->GetText().setCharacterSize(24);
        recordsItem->set_on_press([](MenuItem&) {
            Application::Instance().GetGame().PushState(GameStateType::Records, true);
            });

        auto yesItem = std::make_unique<MenuItem>();
        yesItem->GetText().setString("Yes");
        yesItem->GetText().setFont(font);
        yesItem->GetText().setCharacterSize(24);
        yesItem->set_on_press([](MenuItem&) {
            Application::Instance().GetGame().SwitchStateTo(GameStateType::None);
            });

        auto noItem = std::make_unique<MenuItem>();
        noItem->GetText().setString("No");
        noItem->GetText().setFont(font);
        noItem->GetText().setCharacterSize(24);
        noItem->set_on_press([this](MenuItem&) {
            menu.GoBack();
            });

        auto exitGameItem = std::make_unique<MenuItem>();
        exitGameItem->GetText().setString("Exit Game");
        exitGameItem->GetText().setFont(font);
        exitGameItem->GetText().setCharacterSize(24);
        exitGameItem->HintText().setString("Are you sure?");
        exitGameItem->HintText().setFont(font);
        exitGameItem->HintText().setCharacterSize(48);
        exitGameItem->HintText().setFillColor(sf::Color::Red);
        exitGameItem->set_children_orientation(Orientation::Horizontal);
        exitGameItem->set_children_alignment(Alignment::Middle);
        exitGameItem->set_children_spacing(10.f);
        exitGameItem->add_child(std::move(yesItem));
        exitGameItem->add_child(std::move(noItem));

        auto mainMenu = std::make_unique<MenuItem>();
        mainMenu->HintText().setString("Arkanoid Game");
        mainMenu->HintText().setFont(font);
        mainMenu->HintText().setCharacterSize(48);
        mainMenu->HintText().setFillColor(sf::Color::Red);
        mainMenu->set_children_orientation(Orientation::Vertical);
        mainMenu->set_children_alignment(Alignment::Middle);
        mainMenu->set_children_spacing(10.f);

        mainMenu->add_child(std::move(startGame));
        mainMenu->add_child(std::move(options));
        mainMenu->add_child(std::move(recordsItem));
        mainMenu->add_child(std::move(exitGameItem));

        menu.SetRoot(std::move(mainMenu)); 
}

    void GameStatePauseMenuData::HandleWindowEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape) {
                menu.GoBack();
            }
            else if (event.key.code == sf::Keyboard::Enter) {
                menu.PressOnSelectedItem();
            }

            Orientation orientation = menu.GetCurrentContext().get_children_orientation();

            if ((orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up) ||
                (orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left))
            {
                menu.SwitchToPreviousMenuItem();
            }
            else if ((orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down) ||
                (orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right))
            {
                menu.SwitchToNextMenuItem();
            }
        }
    }

    void GameStatePauseMenuData::Update(float timeDelta) {}

    void GameStatePauseMenuData::Draw(sf::RenderWindow& window)
    {
        sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

        sf::Text* hint = &menu.GetCurrentContext().HintText();
        hint->setOrigin(GetTextOrigin(*hint, { 0.5f, 0.f }));
        hint->setPosition(viewSize.x / 2.f, 150.f);
        window.draw(*hint);

        menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
    }
}