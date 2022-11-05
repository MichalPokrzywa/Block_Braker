#pragma once
//game class for a game called breakout with sfml and c++
#include <algorithm>
#include <cmath>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <memory>
#include <memory>
#include <numbers>
#include <random>
#include <ranges>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

import Library;
import FileStream;
#include "Ball.h"
#include "Brick.h"
#include "Paddle.h"
#include "PowerUp.h"
#include "Boss.h"
#include "Menu.h"
#include "DifficultMenu.h"
#include "HighScoreMenu.h"
#include "SettingMenu.h"
#include "SoundManager.h"

class Game
{
	//window settings
	std::shared_ptr<sf::RenderWindow> window ;
	sf::Event e{};
	int frameWidth = GetSystemMetrics(SM_CXSCREEN);
	int frameHeight = GetSystemMetrics(SM_CYSCREEN);
	std::string title;
	//game decider
	bool debugMode;
	bool isGame;
	bool win;
	bool gameOver;
	bool stopTime;
	bool isMoving;
	bool isBossFight;
	//menu decider
	bool isMenu;
	bool isDifficultyMenu;
	bool isMainMenu;
	bool isOptionsMenu;
	bool isHighScoreMenu;
	bool isScoreMenu;
	//game variables
	float startingX = 0;
	float startingY = 0;
	int currentLevel;
	int chosenDifficulty;
	int scoreCounter;
	int buffsLimit;
	//game objects
	Ball ball2;
	Paddle paddle;
	Boss boss;
	std::vector<std::shared_ptr<Brick> > blocks{};
	std::vector<std::shared_ptr<PowerUp> > powerUps{};
	std::vector<std::shared_ptr<Ball> > bulletsLeft{};
	std::vector<std::shared_ptr<Ball> > bulletsRight{};
	//game ui
	Menu menu;
	DifficultMenu difficultMenu;
	HighScoreMenu highScoreMenu;
	SettingMenu settingMenu;
	//Sound and music
	SoundManager soundManager;
	//objects sizes adjusted to the window size
	float blockWidth = frameWidth /24.0f;
	float blockHeight = frameHeight /30.0f;
	float paddleWidth = frameWidth /12.8f;
	float paddleHeight = frameHeight /54.0f;
	//text variables and settings
	sf::Font font;

	//text constructs
	sf::Text levelClock;
	sf::Text levelFinalTime;
	sf::Time levelTimeComplition;
	sf::Clock levelTimer;

	sf::Clock buffClockSpawn;
	sf::Time buffTimeSpawnLimit;

	sf::Time bulletSpawn = sf::seconds(3.0f);
	sf::Clock bulletSpawnClock;

	sf::Text score;
	sf::Text finalScore;

	sf::Text gameOverTitle;
	sf::Text winTitle;

	sf::Text playerName;

	sf::Texture ballTexture;
	sf::Texture backgroundTexture;
	sf::Sprite background;
public:
	Game(int frameWidth, int frameHeight, const std::string& title);
	~Game();
	void Run();
	void Update(float deltaTime);
	void JoystickUpdate(float deltaTime);
	void Render();
	void HandleEvents(sf::Event event, float deltaTime);
	void LoadLevel(int level);
};

