#pragma once
#include "Ui.h"
class SettingMenu : public Ui
{
public:
	int currentButton = 0;
	int currentColorPlatform = 0;
	bool isChoseColor = false;
	std::vector<std::shared_ptr<Button> > buttons;
	std::vector<std::shared_ptr<Button> > colorButtons;
	std::fstream settingsFile;
	void Draw(std::shared_ptr<sf::RenderWindow>& window) override;
	void Initialize() override;
	void GetTextures(std::vector<std::shared_ptr<sf::Texture>> texture) override;
	void LoadSettings();
	void SaveSettings();
};

