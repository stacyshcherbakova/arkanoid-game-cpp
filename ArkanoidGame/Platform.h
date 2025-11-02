#pragma once
#include "SFML/Graphics.hpp"

namespace ArkanoidGame
{
	class Ball;

	class Platform
	{
	public:
		void Init();
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		void Move(float speed);
		sf::FloatRect GetRect() const { return sprite.getGlobalBounds(); }

		bool CheckCollisionWithBall(const Ball& ball);

	private:
		sf::Sprite sprite;
		sf::Texture texture;
	};
}