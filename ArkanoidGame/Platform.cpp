#include "Platform.h"
#include "Ball.h"
#include "Sprite.h"
#include "GameSettings.h"
#include <cassert>
#include <algorithm>

namespace ArkanoidGame
{
	void Platform::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + "platform.png"));
		InitSprite(sprite, PLATFORM_WIDTH, PLATFORM_HEIGHT, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT / 2.f });
	}

	void Platform::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}

	void Platform::Update(float timeDelta) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Move(timeDelta * PLATFORM_SPEED);

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Move(timeDelta * -PLATFORM_SPEED);
		}
	}

	void Platform::Move(float speed) {
		sf::Vector2f position = sprite.getPosition();
		position.x = std::clamp(position.x + speed, PLATFORM_WIDTH / 2.f, SCREEN_WIDTH - PLATFORM_WIDTH / 2.f);
		sprite.setPosition(position);
	}

	bool Platform::CheckCollisionWithBall(const Ball& ball) {
		const float r = BALL_SIZE * 0.5f;

		const auto platform_bound = sprite.getGlobalBounds();
		const auto ball_centr = ball.GetPosition();

		const float left = platform_bound.left;
		const float right = platform_bound.left + platform_bound.width;
		const float top = platform_bound.top;
		const float bottom = platform_bound.top + platform_bound.height;

		const float closestX = std::clamp(ball_centr.x, left, right);
		const float closestY = std::clamp(ball_centr.y, top, bottom);

		const float dx = ball_centr.x - closestX;
		const float dy = ball_centr.y - closestY;

		return dx * dx + dy * dy <= r * r;
	}
}
