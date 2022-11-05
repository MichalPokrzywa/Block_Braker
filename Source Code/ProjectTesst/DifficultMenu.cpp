#include "DifficultMenu.h"

void DifficultMenu::Draw(std::shared_ptr<sf::RenderWindow>& window)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (currentButton == i)
		{
			buttons[i]->isChosen = true;
			buttons[i]->SetTexture();
			buttons[i]->GetSprite().setOrigin(buttons[i]->GetSprite().getGlobalBounds().width / 2, buttons[i]->GetSprite().getGlobalBounds().height / 2);
			buttons[i]->GetSprite().setPosition((windowWidth / 2) - 15, 300 + i * 200);
		}
		else
		{
			buttons[i]->isChosen = false;
			buttons[i]->SetTexture();
			buttons[i]->GetSprite().setOrigin(buttons[i]->GetSprite().getGlobalBounds().width / 2, buttons[i]->GetSprite().getGlobalBounds().height / 2);
			buttons[i]->GetSprite().setPosition(windowWidth / 2, 300 + i * 200);
		}
		window->draw(buttons[i]->GetSprite());
	}
}

void DifficultMenu::Initialize()
{
	GetTextures(GetFileTextures("Textures\\DifficultMenu"));
	for (int i = 0; i < textures.size() - 1; i = i + 2)
	{
		std::shared_ptr<Button> button = std::make_shared<Button>(textures[i], textures[i + 1]);
		buttons.push_back(button);
	}
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->GetSprite().setOrigin(buttons[i]->GetSprite().getGlobalBounds().width / 2, buttons[i]->GetSprite().getGlobalBounds().height / 2);
		buttons[i]->GetSprite().setPosition(windowWidth / 2, 300 + i * 200);
	}
	currentButton = 0;
}

void DifficultMenu::GetTextures(const std::vector<std::shared_ptr<sf::Texture>> texture)
{
	for (int i = 0; i < texture.size(); i++)
	{
		textures.push_back(texture[i]);
	}
}