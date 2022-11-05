#include "PowerUp.h"

void PowerUp::SetPosition(float x, float y)
{
	buff.setPosition(sf::Vector2f(x, y));

}

void PowerUp::SetSize(float width, float height)
{
	buff.setSize(sf::Vector2f(width , height));
	buff.setOrigin(buff.getSize() / 2.0f);
}

void PowerUp::Initiate()
{
	if(buffType ==0)
		buff.setFillColor(sf::Color::White);
	if(buffType ==1)
		buff.setFillColor(sf::Color::Red);
	if(buffType ==2)
		buff.setFillColor(sf::Color::Green);
	if (buffType == 3)
		buff.setFillColor(sf::Color::Yellow);
	if (buffType == 4)
		buff.setFillColor(sf::Color::Cyan);
}
