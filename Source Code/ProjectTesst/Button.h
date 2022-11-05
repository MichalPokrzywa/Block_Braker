#pragma once
#include <SFML/Graphics.hpp>

class Button
{
	std::shared_ptr<sf::Texture> chosen;
	std::shared_ptr<sf::Texture> notChosen;
	sf::Sprite sprite;
public:
	bool isChosen;
	Button(std::shared_ptr<sf::Texture>& texture1, std::shared_ptr<sf::Texture>& texture2);
	void SetTexture();
	sf::Sprite& GetSprite();

};

