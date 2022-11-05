#pragma once
import FileStream;
#include <SFML/Audio.hpp>
class SoundManager
{
	std::vector<std::shared_ptr<sf::Music>> music{};
	std::vector<std::shared_ptr<sf::SoundBuffer>> soundBuffer{};
	std::vector<std::shared_ptr<sf::Sound>> sound{};
public:
	SoundManager();
	void PlaysSound(int soundID);
	void PlayMusic(int musicID);
	void StopMusic(int musicID);

};

