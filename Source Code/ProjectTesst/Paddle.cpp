#include "Paddle.h"

void Paddle::SetPosition(float x, float y)
{
	platform.setPosition(sf::Vector2f(x, y));
}

void Paddle::SetSize(float width, float height)
{
	platform.setSize(sf::Vector2f(width, height));
	platform.setOrigin(platform.getSize() / 2.0f);
}

void Paddle::Initiate()
{
	platform.setFillColor(sf::Color::White);
}

