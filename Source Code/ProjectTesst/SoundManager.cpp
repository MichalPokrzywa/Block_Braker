#include "SoundManager.h"

SoundManager::SoundManager()
{
	soundBuffer = GetSounds("Sounds");
	for (int i = 0; i < soundBuffer.size(); i++)
	{
		sound.push_back(std::make_shared<sf::Sound>());
		sound[i]->setBuffer(*soundBuffer[i]);
	}
	music = GetMusics("Music");
	music[0]->setLoop(true);
	music[0]->play();
	music[1]->setLoop(true);
	music[4]->setLoop(true);
}

void SoundManager::PlaysSound(int soundID)
{
	sound[soundID]->play();
}

void SoundManager::PlayMusic(int musicID)
{

	music[musicID]->play();
}

void SoundManager::StopMusic(int musicID)
{
	music[musicID]->stop();
}
