#include "Boss.h"

void Boss::SetPosition(float x, float y)
{
	boss.setPosition(sf::Vector2f(x, y));
}

void Boss::SetSize(float width, float height)
{
	boss.setSize(sf::Vector2f(width, height));
	boss.setOrigin(boss.getSize() / 2.0f);
}

void Boss::Initiate()
{
	boss.setFillColor(sf::Color::White);
}

bool Boss::Hit()
{
	health--;
	if (health == 0)
	{
		isAlive = false;
		return true;
	}
	return false;
}
