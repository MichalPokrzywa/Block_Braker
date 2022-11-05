module;
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
export module FileStream;

import <iostream>;
export import <filesystem>;
export import <regex>;
export import <sstream>;
export import <fstream>;
export import <ranges>;

export void GetFileRead(std::string path, std::string fileName, std::fstream& file)
{
	std::regex regex(fileName + ".(txt)$");
	std::filesystem::path p(std::filesystem::current_path()) ;

	for (const auto& entry : std::filesystem::directory_iterator(p))
	{
		std::string lookedFile = entry.path().filename().string();
		if (std::regex_match(lookedFile, regex))
		{
			std::string filePath = entry.path().string();
			file.open(filePath);
			return;
		}
	}
}

export void GetFileWrite(std::string path, std::string fileName, std::fstream& file,bool toOverride)
{
	std::regex regex(fileName + ".(txt)$");
	std::filesystem::path p(std::filesystem::current_path());

	for (const auto& entry : std::filesystem::directory_iterator(p))
	{
		std::string lookedFile = entry.path().filename().string();
		if (std::regex_match(lookedFile, regex))
		{
			std::string filePath = entry.path().string();
			if(!toOverride)
				file.open(filePath, std::ios::app);
			else
				file.open(filePath,std::ios::out | std::ios::trunc);
			return;
		}
	}
}

export std::vector<std::shared_ptr < sf::Texture> > GetFileTextures(std::string path)
{
	std::filesystem::path p(std::filesystem::current_path());
	p /= path;
	std::cout << p << std::endl;
	std::regex r("(.*)\\.(png|jpg|bmp)");
	std::vector<std::shared_ptr < sf::Texture> > textures;
	for (const auto& entry : std::filesystem::directory_iterator(p))
	{
		std::string fileName = entry.path().filename().string();
		if (std::regex_match(fileName, r))
		{
			std::shared_ptr < sf::Texture> texture = std::make_shared<sf::Texture>();
			texture->loadFromFile(entry.path().string());
			textures.push_back(texture);
		}
	}
	return textures;
}

export std::shared_ptr < sf::Texture> GetTexture(std::string path, std::string file)
{
	std::filesystem::path p(std::filesystem::current_path());
	p /= path;
	std::cout << p << std::endl;
	std::regex r(file+"\\.(png|jpg|bmp)");
	for (const auto& entry : std::filesystem::directory_iterator(p))
	{
		std::string fileName = entry.path().filename().string();
		if (std::regex_match(fileName, r))
		{
			std::shared_ptr < sf::Texture> texture = std::make_shared<sf::Texture>();
			texture->loadFromFile(entry.path().string());
			return texture;
		}
	}
}

export std::vector<std::shared_ptr<sf::SoundBuffer> > GetSounds(std::string path)
{
	std::filesystem::path p(std::filesystem::current_path());
	p /= path;
	std::cout << p << std::endl;
	std::regex regex("(.*)\\.(wav)$");
	std::vector<std::shared_ptr <sf::SoundBuffer> > Sounds;
	for (const auto& entry : std::filesystem::directory_iterator(p))
	{
		std::string fileName = entry.path().filename().string();
		if (std::regex_match(fileName, regex))
		{
			std::string filePath = entry.path().string();
			std::shared_ptr<sf::SoundBuffer> soundBuffer = std::make_shared<sf::SoundBuffer>();
			soundBuffer->loadFromFile(filePath);
			Sounds.push_back(soundBuffer);
		}
	}
	return Sounds;

}

export std::vector<std::shared_ptr<sf::Music>> GetMusics(std::string path)
{
	std::filesystem::path p(std::filesystem::current_path());
	p /= path;
	std::cout << p << std::endl;
	std::regex regex("(.*)\\.(wav)$");
	std::vector<std::shared_ptr<sf::Music>> musics;
	for(const auto& entry : std::filesystem::directory_iterator(p))
	{
		std::string fileName = entry.path().filename().string();
		if(std::regex_match(fileName, regex))
		{
			std::string filePath = entry.path().string();
			std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
			music->openFromFile(filePath);
			musics.push_back(music);
		}
	}
	return musics;

}

export sf::Font GetFont(std::string path)
{
	std::filesystem::path p(std::filesystem::current_path());
	p /= path;
	std::cout << p << std::endl;
	std::regex regex("(.*)\\.(ttf)$");
	for (const auto& entry : std::filesystem::directory_iterator(p))
	{
		std::string fileName = entry.path().filename().string();
		if (std::regex_match(fileName, regex))
		{
			std::string filePath = entry.path().string();
			sf::Font font;
			font.loadFromFile(filePath);
			return font;
		}
	}
}