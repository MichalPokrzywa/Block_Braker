#include "SettingMenu.h"

void SettingMenu::Draw(std::shared_ptr<sf::RenderWindow>& window)
{
	for (int i = 0; i < buttons.size(); i++)
	{
		if (currentButton == i)
		{
			buttons[i]->isChosen = true;
			buttons[i]->SetTexture();
			buttons[i]->GetSprite().setOrigin(buttons[i]->GetSprite().getGlobalBounds().width / 2, buttons[i]->GetSprite().getGlobalBounds().height / 2);
			buttons[i]->GetSprite().setPosition((windowWidth / 2) - 400-15, 300 + i * 200);
		}
		else
		{
			buttons[i]->isChosen = false;
			buttons[i]->SetTexture();
			buttons[i]->GetSprite().setOrigin(buttons[i]->GetSprite().getGlobalBounds().width / 2, buttons[i]->GetSprite().getGlobalBounds().height / 2);
			buttons[i]->GetSprite().setPosition((windowWidth / 2) - 400, 300 + i * 200);
		}
		window->draw(buttons[i]->GetSprite());
	}
	if(isChoseColor)
	{
		for (int i = 0; i < colorButtons.size(); i++)
		{
			if (currentColorPlatform == i+1)
			{
				colorButtons[i]->isChosen = true;
				colorButtons[i]->SetTexture();
				colorButtons[i]->GetSprite().setOrigin(colorButtons[i]->GetSprite().getGlobalBounds().width / 2, colorButtons[i]->GetSprite().getGlobalBounds().height / 2);
				colorButtons[i]->GetSprite().setPosition((windowWidth / 2) + 400-15, 300 + i * 200);
			}
			else
			{
				colorButtons[i]->isChosen = false;
				colorButtons[i]->SetTexture();
				colorButtons[i]->GetSprite().setOrigin(colorButtons[i]->GetSprite().getGlobalBounds().width / 2, colorButtons[i]->GetSprite().getGlobalBounds().height / 2);
				colorButtons[i]->GetSprite().setPosition((windowWidth / 2) + 400, 300 + i * 200);
			}
			window->draw(colorButtons[i]->GetSprite());
		}
	}

}

void SettingMenu::Initialize()
{
	GetTextures(GetFileTextures("Textures\\SettingMenu"));
	for (int i = 0; i < textures.size() - 1; i = i + 2)
	{
		std::shared_ptr<Button> button = std::make_shared<Button>(textures[i], textures[i + 1]);
		buttons.push_back(button);
	}
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->GetSprite().setOrigin(buttons[i]->GetSprite().getGlobalBounds().width / 2, buttons[i]->GetSprite().getGlobalBounds().height / 2);
		buttons[i]->GetSprite().setPosition((windowWidth / 2) - 400 , 300 + i * 200);
	}
	currentButton = 0;
	textures.clear();
	GetTextures(GetFileTextures("Textures\\SettingMenu\\Colors"));
	for (int i = 0; i < textures.size() - 1; i = i + 2)
	{
		std::shared_ptr<Button> colorButton = std::make_shared<Button>(textures[i], textures[i + 1]);
		colorButtons.push_back(colorButton);
	}
	for (int i = 0; i < buttons.size(); i++)
	{
		colorButtons[i]->GetSprite().setOrigin(buttons[i]->GetSprite().getGlobalBounds().width / 2, buttons[i]->GetSprite().getGlobalBounds().height / 2);
		colorButtons[i]->GetSprite().setPosition((windowWidth / 2) + 400, 300 + i * 200);
	}
	isChoseColor = false;
	LoadSettings();
}

void SettingMenu::GetTextures(std::vector<std::shared_ptr<sf::Texture>> texture)
{
	for (int i = 0; i < texture.size(); i++)
	{
		textures.push_back(texture[i]);
	}

}

void SettingMenu::LoadSettings()
{
	GetFileRead("", "Settings", settingsFile);

	while(!settingsFile.eof())
	{
		settingsFile >> currentColorPlatform;
	}
	settingsFile.close();
	

}

void SettingMenu::SaveSettings()
{
	GetFileWrite("", "Settings", settingsFile,true);
	settingsFile << currentColorPlatform;
	settingsFile.close();
}

