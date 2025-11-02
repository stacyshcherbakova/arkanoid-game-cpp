#include "Ball.h"
#include "GameSettings.h"
#include "Sprite.h"
#include <assert.h>


namespace ArkanoidGame
{
	void Ball::Init()
	{
		assert(texture.loadFromFile(TEXTURES_PATH + "ball.png"));
		InitSprite(sprite, BALL_SIZE, BALL_SIZE, texture);
		sprite.setPosition({ SCREEN_WIDTH / 2.0, SCREEN_HEIGHT - PLATFORM_HEIGHT - BALL_SIZE / 2.f });

		const float angle = 45.f + rand() % 90;
		const float PI = std::acos(-1.f);
		const float rad = angle * (PI / 180.f);
		direction.x = cos(rad);
		direction.y = -sin(rad);
	}

	void Ball::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + BALL_SPEED * timeDelta * direction;
		sprite.setPosition(pos);

		if (pos.x <= 0 || pos.x >= SCREEN_WIDTH) {
			direction.x *= -1;
		}

		if (pos.y <= 0 || pos.y >= SCREEN_HEIGHT) {
			direction.y *= -1;
		}
	}

	void Ball::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}

	void Ball::BounceFromPlatform()
	{
		direction.y *= -1;
	}
}