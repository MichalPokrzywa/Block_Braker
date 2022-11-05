#pragma once
#include "Ui.h"
class Menu : public Ui
{
public:
	int currentButton = 0;
	std::vector<std::shared_ptr<Button> > buttons;
	sf::Sprite title;
	void Draw(std::shared_ptr<sf::RenderWindow>& window) override;
	void Initialize() override;
	void GetTextures(std::vector<std::shared_ptr<sf::Texture>> texture) override;

};

