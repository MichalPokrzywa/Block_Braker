#include "Brick.h"

void Brick::SetSize(float width, float height)
{//set the size of the brick
	
	block.setSize(sf::Vector2f(width, height));
	block.setOrigin(block.getSize() / 2.0f);
}

void Brick::SetPosition(float x, float y)
{
	block.setPosition(sf::Vector2f(x, y));
}

void Brick::Initiate()
{
	block.setFillColor(sf::Color::White);
}

bool Brick::Hit()
{
	health--;
	if (health == 0)
	{
		isDestroyed = true;
		return true;
	}
	return false;
}

