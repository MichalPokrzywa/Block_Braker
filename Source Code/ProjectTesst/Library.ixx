module;

#include <random>
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
#include "PowerUp.h"
#include "Boss.h"
#include <numbers>
#include <windows.h>
std::random_device rd;   // non-deterministic generator
std::mt19937 gen(rd());  // to seed mersenne twister

export module Library;

export int DistanceX(int fWidth)
{
	std::uniform_int_distribution<int> distantWindowX(200, fWidth - 200);
	return distantWindowX(gen);
}
export int DistanceY(int fHeight)
{
	std::uniform_int_distribution<int> distantWindowY(500, fHeight - 400);
	return distantWindowY(gen);
}
export int BuffType()
{
	std::uniform_int_distribution<int> buffType(0, 3);
	return buffType(gen);
}
export void ResizeBuffVector(std::vector<std::shared_ptr<PowerUp> >& powerUps)
{
	auto new_end = std::remove_if(powerUps.begin(), powerUps.end(),
		[](std::shared_ptr<PowerUp>& p)
		{
			return p->isPowerUp == false && p->buffTime.asSeconds() < sf::Time::Zero.asSeconds();
		}
	);
	powerUps.resize(new_end - powerUps.begin());
}
export void ResizeBulletVector(std::vector<std::shared_ptr<Ball> >& Bullet)
{
	auto new_end = std::remove_if(Bullet.begin(), Bullet.end(),
		[](std::shared_ptr<Ball>& Bullet)
		{
			return Bullet->ball.getPosition().y > GetSystemMetrics(SM_CYSCREEN);
		}
		);
	Bullet.resize(new_end - Bullet.begin());
}
export void BounceFromPlatform(Ball& ball2, Paddle& paddle)
{
	float platformCenter = paddle.platform.getPosition().x;
	float ballCenter = ball2.ball.getPosition().x;
	ball2.angle = std::lerp(-90.0f, -150.0f, (platformCenter - ballCenter) / 90.0f) * (std::numbers::pi / 180);
	ball2.speed.x = cos(ball2.angle) * ball2.deafultSpeed;
	ball2.speed.y = sin(ball2.angle) * ball2.deafultSpeed;
}
export void StartFromPlatform(Ball& ball2)
{
	ball2.angle = (-20 - rand() % 140) * (std::numbers::pi / 180);
	ball2.speed.x = cos(ball2.angle) * ball2.deafultSpeed;
	ball2.speed.y = sin(ball2.angle) * ball2.deafultSpeed;
}
export sf::FloatRect BallGlobalBounds(Ball& ball2)
{
	return ball2.ball.getGlobalBounds();
}
export sf::FloatRect BulletGlobalBounds(std::shared_ptr<Ball>& ball2)
{
	return ball2->ball.getGlobalBounds();
}
export sf::FloatRect PaddleGlobalBounds(Paddle& paddle)
{
	return paddle.platform.getGlobalBounds();
}
export sf::FloatRect BlockGlobalBounds(std::shared_ptr<Brick>& block)
{
	return block->block.getGlobalBounds();
}
export sf::FloatRect PowerUpGlobalBounds(std::shared_ptr<PowerUp>& buff)
{
	return buff->buff.getGlobalBounds();
}
export sf::FloatRect BossGlobalBounds(Boss& boss)
{
	return boss.boss.getGlobalBounds();
}
export void UpdateNextPosition(Ball& ball2,float deltaTime)
{
	ball2.nextPos = BallGlobalBounds(ball2);
	ball2.nextPos.left += ball2.speed.x * deltaTime;
	ball2.nextPos.top += ball2.speed.y * deltaTime;
}
export void UpdateBulletNextPosition(std::shared_ptr<Ball>& ball2, float deltaTime)
{
	ball2->nextPos = BulletGlobalBounds(ball2);
	ball2->nextPos.left += ball2->speed.x * deltaTime;
	ball2->nextPos.top += ball2->speed.y * deltaTime;
}