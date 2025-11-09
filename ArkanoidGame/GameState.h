#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <utility>

namespace ArkanoidGame {

    enum class GameStateType {
        None = 0,
        MainMenu,
        Playing,
        GameOver,
        ExitDialog,
        Records,
    };

    class GameState {
    public:
        GameState() = default;
        GameState(GameStateType t, bool exclusive) noexcept;

        GameState(const GameState&) = delete;
        GameState& operator=(const GameState&) = delete;
        GameState(GameState&&) noexcept = default;
        GameState& operator=(GameState&&) noexcept = default;

        ~GameState() = default;

        GameStateType GetType() const noexcept { return type; }
        bool IsExclusivelyVisible() const noexcept { return isExclusivelyVisible; }

        template <class T>
        std::shared_ptr<T> GetData() const noexcept {
            return std::static_pointer_cast<T>(data);
        }

        template <class T>
        T* GetDataRaw() const noexcept {
            auto sp = std::static_pointer_cast<T>(data);
            return sp.get();
        }

        void Update(float timeDelta);
        void Draw(sf::RenderWindow& window);
        void HandleWindowEvent(sf::Event& event);

        template <class T, class... Args>
        void EmplaceData(Args&&... args) {
            data = std::make_shared<T>(std::forward<Args>(args)...);
        }
        template <class T>
        void SetData(std::shared_ptr<T> p) {
            data = std::static_pointer_cast<void>(std::move(p));
        }

    private:
        GameStateType type = GameStateType::None;
        std::shared_ptr<void> data{};
        bool isExclusivelyVisible = false;
    };

} 
