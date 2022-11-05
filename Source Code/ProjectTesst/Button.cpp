#include "Button.h"

Button::Button(std::shared_ptr<sf::Texture>& texture1, std::shared_ptr<sf::Texture>& texture2)
{
	notChosen = texture1;
	chosen = texture2;
	sprite.setTexture(*chosen);
	isChosen = false;
}

void Button::SetTexture()
{
	if (isChosen)
	{
		sprite.setTexture(*chosen);
	}
	else
	{
		sprite.setTexture(*notChosen);
	}
}

sf::Sprite& Button::GetSprite()
{
	return sprite;
}
