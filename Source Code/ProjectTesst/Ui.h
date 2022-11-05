#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Button.h";
#include <iostream>
import WindowSettings;
import FileStream;
class Ui
{
protected:
	std::vector<std::shared_ptr<sf::Texture>> textures;
	public:

	virtual void Draw(std::shared_ptr<sf::RenderWindow>& window) = 0;
	virtual void Initialize() = 0;
	virtual void GetTextures(std::vector<std::shared_ptr<sf::Texture>> texture) = 0;


};

