#pragma once
#include "Ui.h"
class HighScoreMenu : public Ui
{
	sf::Font font;
public:
	std::vector<std::pair<std::string, int>> highScores;
	std::vector<std::shared_ptr<sf::Text >> highScoreText;
	std::shared_ptr<Button> backButton;
	std::fstream highScoreFile;
	void Draw(std::shared_ptr<sf::RenderWindow>& window) override;
	void Initialize() override;
	void GetTextures(std::vector<std::shared_ptr<sf::Texture>> texture) override;
	void UpdateHighScores();
	void SaveHighScore(const std::string& name, int score);
	
};

