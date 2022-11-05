#include "HighScoreMenu.h"

void HighScoreMenu::SaveHighScore(const std::string& name, int score)
{
	std::pair<std::string, int> highScore = std::make_pair(name, score);
	highScores.push_back(highScore);
	GetFileWrite("", "HighScore", highScoreFile,false);
	highScoreFile << std::endl;
	highScoreFile << highScore.first << " " << highScore.second;
	highScoreFile.close();
	UpdateHighScores();
}
void HighScoreMenu::Draw(std::shared_ptr<sf::RenderWindow>& window)
{
	window->draw(backButton->GetSprite());
	std::ranges::for_each(std::ranges::take_view{ highScoreText,10 }, [&](auto& text) {
		window->draw(*text);
	});
}

void HighScoreMenu::Initialize()
{
	GetTextures(GetFileTextures("Textures\\HighScoreMenu"));
	std::regex PlayerNameRegex("^[a-zA-Z]{3,5}$");
	for (int i = 0; i < textures.size() - 1; i = i + 2)
	{
		backButton = std::make_shared<Button>(textures[i], textures[i + 1]);
		backButton->GetSprite().setOrigin(backButton->GetSprite().getGlobalBounds().width / 2, backButton->GetSprite().getGlobalBounds().height / 2);
		backButton->GetSprite().setPosition(windowWidth / 2, windowHeight - 200);
		backButton->isChosen = true;
	}
	GetFileRead("", "HighScore", highScoreFile);
	while(!highScoreFile.eof())
	{
		
		std::pair<std::string, int> highScore;
		highScoreFile >> highScore.first >> highScore.second;
		
		if(std::regex_match(highScore.first,PlayerNameRegex))
		{
			highScores.push_back(highScore);
		}
	}
	highScoreFile.close();
	UpdateHighScores();
}

void HighScoreMenu::UpdateHighScores()
{
	highScoreText.clear();
	std::ranges::sort(highScores, [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) { return a.second > b.second; });
	font = GetFont("Font");
	for (int i = 0; i < highScores.size(); i++)
	{
		std::shared_ptr<sf::Text> text = std::make_shared<sf::Text>();
		text->setFont(font);
		text->setString(std::to_string(i + 1) + ". " + highScores[i].first + " " + std::to_string(highScores[i].second));
		text->setCharacterSize(60);
		text->setOrigin(text->getGlobalBounds().width / 2, text->getGlobalBounds().height / 2);
		text->setPosition(windowWidth / 2, 100 + i * 60);
		if (i == 0)
			text->setFillColor(sf::Color(255, 215, 0));
		if (i == 1)
			text->setFillColor(sf::Color(192, 192, 192));
		if (i == 2)
			text->setFillColor(sf::Color(205, 127, 50));
		highScoreText.push_back(text);
	}
}

void HighScoreMenu::GetTextures(std::vector<std::shared_ptr<sf::Texture>> texture)
{
	for (int i = 0; i < texture.size(); i++)
	{
		textures.push_back(texture[i]);
	}
}
