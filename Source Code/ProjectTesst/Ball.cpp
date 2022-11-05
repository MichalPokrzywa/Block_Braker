#include "Ball.h"

void Ball::SetRadius(float radius)
{
	ball.setRadius(radius);
	ball.setOrigin(ball.getRadius(), ball.getRadius());
}

void Ball::SetPosition(float x, float y)
{
	ball.setPosition(sf::Vector2f(x, y));
}
void Ball::SetSize(float width, float height)
{

}

void Ball::Initiate()
{
	ball.setFillColor(sf::Color::White);
}

bool Ball::BallLeft(sf::FloatRect player, sf::FloatRect block)
{
	if (player.left > block.left
		&& player.left + player.width > block.left + block.width
		&& player.top < block.top + block.height
		&& player.top + player.height > block.top)
		return true;
	else
		return false;
}

bool Ball::BallRight(sf::FloatRect player, sf::FloatRect block)
{
	if (player.left < block.left
		&& player.left + player.width < block.left + block.width
		&& player.top < block.top + block.height
		&& player.top + player.height > block.top)
		return true;
	else
		return false;
}

bool Ball::BallUp(sf::FloatRect player, sf::FloatRect block)
{
	if (player.top > block.top
		&& player.top + player.height > block.top + block.height
		&& player.left < block.left + block.width
		&& player.left + player.width > block.left)
		return true;
	else
		return false;
}

bool Ball::BallBottom(sf::FloatRect player, sf::FloatRect block)
{
	if (player.top < block.top
		&& player.top + player.height < block.top + block.height
		&& player.left < block.left + block.width
		&& player.left + player.width > block.left)
		return true;
	else
		return false;
}