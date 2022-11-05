#include "Game.h"

Game::Game(int frameWidth,int frameHeight, const std::string& title)
{
	//thread do wczytywania plików

	//Initializing menus
	settingMenu.Initialize();
	highScoreMenu.Initialize();
	difficultMenu.Initialize();
	menu.Initialize();
	font = GetFont("Font");
	//Windows Settings
	window = std::make_shared<sf::RenderWindow>(sf::VideoMode(frameWidth, frameHeight), title, sf::Style::None);
	window->setFramerateLimit(60);
	//Game Settings
	debugMode = false;
	isGame = false;
	isMenu = true;
	gameOver = false;
	win = false;
	stopTime = false;
	isBossFight = false;
	isMoving = false;
	chosenDifficulty = 0;
	scoreCounter = 0;
	buffsLimit = 3;
	//UI settings
	isMainMenu = true;
	isOptionsMenu =false;
	isHighScoreMenu = false;
	isScoreMenu = false;
	isDifficultyMenu = false;
	//Game level settings
	currentLevel = 0;
	//Game Objects constructions
	ballTexture.loadFromFile("StarBall.png");
	ballTexture.setSmooth(true);
	backgroundTexture.loadFromFile("Textures\\BackGround.png");
	background.setTexture(backgroundTexture);
	//Timers constructions
	buffTimeSpawnLimit = sf::seconds(3.0f);

	//Text constructions
	score.setFont(font);
	score.setOutlineThickness(2.0f);
	score.setFillColor(sf::Color::White);
	score.setString("Score " + std::to_string(scoreCounter));
	score.setOrigin(score.getLocalBounds().width / 2, score.getLocalBounds().height / 2);
	score.setPosition(sf::Vector2f(score.getLocalBounds().width / 2 + 30, frameHeight - score.getLocalBounds().height));

	finalScore = score;

	levelClock.setFont(font);
	levelClock.setOutlineThickness(2.0f);
	levelClock.setFillColor(sf::Color::White);
	levelClock.setString(std::to_string(levelTimer.getElapsedTime().asSeconds()));
	levelClock.setOrigin(score.getLocalBounds().width / 2, score.getLocalBounds().height / 2);
	levelClock.setPosition(sf::Vector2f(frameWidth - levelClock.getLocalBounds().width - 10,frameHeight - score.getLocalBounds().height));

	gameOverTitle.setFont(font);
	gameOverTitle.setOutlineThickness(2.0f);
	gameOverTitle.setCharacterSize(150.0f);
	gameOverTitle.setFillColor(sf::Color::Red);
	gameOverTitle.setString("Game Over");
	gameOverTitle.setOrigin(gameOverTitle.getLocalBounds().width / 2.0f, gameOverTitle.getLocalBounds().height / 2.0f);
	gameOverTitle.setPosition(sf::Vector2f(frameWidth / 2, (frameHeight / 2) - 450));

	winTitle.setFont(font);
	winTitle.setOutlineThickness(2.0f);
	winTitle.setCharacterSize(150.0f);
	winTitle.setFillColor(sf::Color::Green);
	winTitle.setString("Level complete");
	winTitle.setOrigin(winTitle.getLocalBounds().width / 2.0f, winTitle.getLocalBounds().height / 2.0f);
	winTitle.setPosition(sf::Vector2f(frameWidth / 2, frameHeight / 2 - 450));

	levelFinalTime.setFont(font);
	levelFinalTime.setOutlineThickness(2.0f);
	levelFinalTime.setCharacterSize(150.0f);
	levelFinalTime.setFillColor(sf::Color::White);
	levelFinalTime.setString(std::to_string(levelTimeComplition.asSeconds()));
	levelFinalTime.setOrigin(winTitle.getLocalBounds().width / 2.0f, winTitle.getLocalBounds().height / 2.0f);
	levelFinalTime.setPosition(sf::Vector2f((frameWidth / 2) + 350, (frameHeight / 2) - 200));
	levelTimeComplition = levelTimer.getElapsedTime();

	playerName.setFont(font);
	playerName.setOutlineThickness(2.0f);
	playerName.setCharacterSize(150.0f);
	playerName.setFillColor(sf::Color::White);
	playerName.setString("AAA");
	playerName.setOrigin(playerName.getLocalBounds().width / 2.0f, playerName.getLocalBounds().height / 2.0f);
	playerName.setPosition(sf::Vector2f((frameWidth / 2) , (frameHeight / 2) ));
};

Game::~Game()
{
	blocks.clear();
	powerUps.clear();
};

void Game::Update(float deltaTime)
{
	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen(rd());  // to seed mersenne twister
	if (isGame)
	{
		if (!isBossFight)
		{
			int count = 0;
			for (auto& block : blocks)
			{
				if (!block->isDestroyed && block->health < 3)
					count++;
			}
			if (count <= 0)
			{
				soundManager.StopMusic(1);
				win = true;
				ball2.speed.y = 0.0f;
				ball2.speed.x = 0.0f;
				ball2.angle = 0.0f;
			}
		}
		else
		{
			if (boss.health <= 0)
			{
				soundManager.StopMusic(4);
				win = true;
				ball2.speed.y = 0.0f;
				ball2.speed.x = 0.0f;
				ball2.angle = 0.0f;
			}
		}
		if (ball2.speed.y == 0.0f && !isMoving)
		{
			ball2.ball.setPosition(sf::Vector2f(paddle.platform.getPosition().x - (ball2.ball.getRadius() / 2),
			                                    paddle.platform.getPosition().y - (paddle.platform.getSize().y / 2) - ball2.ball.getRadius()));
			levelTimer.restart();
			buffClockSpawn.restart();
			bulletSpawnClock.restart();
			levelClock.setString("0.000");
		}
		else
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(3) << levelTimer.getElapsedTime().asSeconds();
			levelClock.setString(ss.str());
			if (debugMode == true)
			{
				//in debug mode, the ball will move with the mouse
				ball2.ball.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)));
			}
			else
			{
				ball2.ball.setPosition(sf::Vector2f(ball2.ball.getPosition().x + (ball2.speed.x * deltaTime),
													ball2.ball.getPosition().y + (ball2.speed.y * deltaTime)));
			}
			//ball-boundary collision
			if (ball2.ball.getPosition().x + ball2.ball.getRadius() +0.3f>= frameWidth)
			{
				ball2.speed.x = -ball2.speed.x;
			}
			else if (ball2.ball.getPosition().x - ball2.ball.getRadius() -0.3f <= 0)
			{
				ball2.speed.x = -ball2.speed.x;
			}
			//ball - top boundary collision
			if (ball2.ball.getPosition().y - ball2.ball.getRadius() <= 0)
			{
				ball2.speed.y = -ball2.speed.y;
			}
			//ball - bottom boundary collision
			if (ball2.ball.getPosition().y + ball2.ball.getRadius() >= frameHeight)
			{
				if(!isBossFight)
					soundManager.StopMusic(1);
				else
					soundManager.StopMusic(2);
				gameOver = true;
			}
			//ball - paddle.platform collision
			if (PaddleGlobalBounds(paddle).intersects(ball2.nextPos) && ball2.BallBottom(BallGlobalBounds(ball2), PaddleGlobalBounds(paddle)))
			{
				BounceFromPlatform(ball2, paddle);
				ball2.ball.setPosition(sf::Vector2f(ball2.ball.getPosition().x, paddle.platform.getPosition().y - (paddle.platform.getSize().y / 2) - ball2.ball.getRadius()));
				soundManager.PlaysSound(0);
			}
			//collision with objects
			if (isBossFight == false)
			{
				for (auto& block : blocks)
				{
					UpdateNextPosition(ball2, deltaTime);
					//ball - block collison
					if (BlockGlobalBounds(block).intersects(ball2.nextPos))
					{
						if (!block->isDestroyed)
						{
							//collision on top of ball
							if (ball2.BallUp(BallGlobalBounds(ball2), BlockGlobalBounds(block)))
							{
								ball2.speed.y = -ball2.speed.y;
								ball2.ball.setPosition(sf::Vector2f(ball2.ball.getPosition().x,
									BlockGlobalBounds(block).top + BlockGlobalBounds(block).height + ball2.ball.getRadius()));
								if (block->Hit())
								{
									soundManager.PlaysSound(2);
								}
								else
								{
									soundManager.PlaysSound(5);
								}
								scoreCounter += 10;
								score.setString("Score " + std::to_string(scoreCounter));
							}
							//collision on bottom of ball
							if (ball2.BallBottom(BallGlobalBounds(ball2), BlockGlobalBounds(block)))
							{
								ball2.speed.y = -ball2.speed.y;
								ball2.ball.setPosition(sf::Vector2f(ball2.ball.getPosition().x,
									BlockGlobalBounds(block).top - ball2.ball.getRadius()));
								if (block->Hit())
								{
									soundManager.PlaysSound(2);
								}
								else
								{
									soundManager.PlaysSound(5);
								}
								scoreCounter += 10;
								score.setString("Score " + std::to_string(scoreCounter));
							}
							//collision on left of ball
							if (ball2.BallLeft(BallGlobalBounds(ball2), BlockGlobalBounds(block)))
							{
								ball2.speed.x = -ball2.speed.x;
								ball2.ball.setPosition(sf::Vector2f(
									BlockGlobalBounds(block).left + BlockGlobalBounds(block).width + ball2.ball.getRadius(),
									ball2.ball.getPosition().y));
								if (block->Hit())
								{
									soundManager.PlaysSound(2);
								}
								else
								{
									soundManager.PlaysSound(5);
								}
								scoreCounter += 10;
								score.setString("Score " + std::to_string(scoreCounter));
							}
							//collision on right of ball
							if (ball2.BallRight(BallGlobalBounds(ball2), BlockGlobalBounds(block)))
							{
								ball2.speed.x = -ball2.speed.x;
								ball2.ball.setPosition(sf::Vector2f(BlockGlobalBounds(block).left - ball2.ball.getRadius(),
									ball2.ball.getPosition().y));
								if (block->Hit())
								{
									soundManager.PlaysSound(2);
								}
								else
								{
									soundManager.PlaysSound(5);
								}
								scoreCounter += 10;
								score.setString("Score " + std::to_string(scoreCounter));
							}
						}
					}
				}
			}
			//boss collision
			else
			{
				if (boss.isAlive)
				{
					UpdateNextPosition(ball2, deltaTime);
					if (BossGlobalBounds(boss).intersects(ball2.nextPos))
					{

						//collision on top of ball
						if (ball2.BallUp(BallGlobalBounds(ball2), BossGlobalBounds(boss)))
						{
							ball2.speed.y = -ball2.speed.y;
							ball2.ball.setPosition(sf::Vector2f(ball2.ball.getPosition().x,
								BossGlobalBounds(boss).top + BossGlobalBounds(boss).height + ball2.ball.getRadius()));
							if (boss.Hit())
							{
								win = true;
							}
							else
							{
								soundManager.PlaysSound(2);
							}
						}
						//collision on bottom of ball
						if (ball2.BallBottom(BallGlobalBounds(ball2), BossGlobalBounds(boss)))
						{
							ball2.speed.y = -ball2.speed.y;
							ball2.ball.setPosition(sf::Vector2f(ball2.ball.getPosition().x,
								BossGlobalBounds(boss).top - ball2.ball.getRadius()));
							if (boss.Hit())
							{
								win = true;
							}
							else
							{
								soundManager.PlaysSound(2);
							}
						}
						//collision on left of ball
						if (ball2.BallLeft(BallGlobalBounds(ball2), BossGlobalBounds(boss)))
						{
							boss.isLeft = !boss.isLeft;
							ball2.speed.x = -ball2.speed.x;
							ball2.ball.setPosition(sf::Vector2f(
								BossGlobalBounds(boss).left + BossGlobalBounds(boss).width + ball2.ball.getRadius(),
								ball2.ball.getPosition().y));
							if (boss.Hit())
							{
								win = true;
							}
							else
							{
								soundManager.PlaysSound(2);
							}
							scoreCounter += 10;
							score.setString("Score " + std::to_string(scoreCounter));
						}
						//collision on right of ball
						if (ball2.BallRight(BallGlobalBounds(ball2), BossGlobalBounds(boss)))
						{
							boss.isLeft = !boss.isLeft;
							ball2.speed.x = -ball2.speed.x;
							ball2.ball.setPosition(sf::Vector2f(BossGlobalBounds(boss).left - ball2.ball.getRadius(),
								ball2.ball.getPosition().y));
							if (boss.Hit())
							{
								win = true;
							}
							else
							{
								soundManager.PlaysSound(2);
							}
						}

					}
					//moving a boss
					if (boss.isLeft)
					{
						boss.boss.move(-200 * deltaTime, 0);
					}
					else
					{
						boss.boss.move(200 * deltaTime, 0);
					}
					if (boss.boss.getPosition().x <= 300)
					{
						boss.isLeft = false;
					}
					if (boss.boss.getPosition().x >= frameWidth - 300)
					{
						boss.isLeft = true;
					}
					//boss shooting into platform

					if (bulletSpawnClock.getElapsedTime().asSeconds() > bulletSpawn.asSeconds() && paddle.platform.getPosition().x < boss.boss.getPosition().x - boss.boss.getSize().x / 2)
					{

						bulletSpawnClock.restart();
						auto bullet = std::make_shared<Ball>();
						bullet->SetRadius(10.0f);
						bullet->ball.setFillColor(sf::Color::White);
						bullet->SetPosition(boss.boss.getPosition().x - boss.boss.getSize().x / 2, boss.boss.getPosition().y);
						bullet->angle = acos((paddle.platform.getPosition().y - boss.boss.getPosition().y) /
							sqrt(pow(boss.boss.getPosition().x - (boss.boss.getSize().x / 2) - paddle.platform.getPosition().x, 2)
								+ pow(boss.boss.getPosition().y - paddle.platform.getPosition().y, 2)));
						std::cout << bullet->angle * 180 / 3.141592 << " " << paddle.platform.getPosition().x << std::endl;
						bullet->speed.y = cos(bullet->angle) * bullet->deafultSpeed;
						bullet->speed.x = -sin(bullet->angle) * bullet->deafultSpeed;
						bulletsLeft.push_back(bullet);
					}
					if (bulletSpawnClock.getElapsedTime().asSeconds() > bulletSpawn.asSeconds() && paddle.platform.getPosition().x > boss.boss.getPosition().x + boss.boss.getSize().x / 2)
					{

						bulletSpawnClock.restart();
						auto bullet = std::make_shared<Ball>();
						bullet->SetRadius(10.0f);
						bullet->ball.setFillColor(sf::Color::White);
						bullet->SetPosition(boss.boss.getPosition().x + boss.boss.getSize().x / 2, boss.boss.getPosition().y);
						bullet->angle = acos((paddle.platform.getPosition().y - boss.boss.getPosition().y) /
							sqrt(pow(boss.boss.getPosition().x + (boss.boss.getSize().x / 2) - paddle.platform.getPosition().x, 2)
								+ pow(boss.boss.getPosition().y - paddle.platform.getPosition().y, 2)));
						std::cout << bullet->angle * 180 / 3.141592 << " " << paddle.platform.getPosition().x << std::endl;
						bullet->speed.y = cos(bullet->angle) * bullet->deafultSpeed;
						bullet->speed.x = sin(bullet->angle) * bullet->deafultSpeed;
						bulletsRight.push_back(bullet);
					}
					if (bulletSpawnClock.getElapsedTime().asSeconds() > bulletSpawn.asSeconds() && paddle.platform.getPosition().x > boss.boss.getPosition().x - boss.boss.getSize().x / 2 && paddle.platform.getPosition().x < boss.boss.getPosition().x + boss.boss.getSize().x / 2)
					{
						bulletSpawnClock.restart();
						auto bullet = std::make_shared<Ball>();
						bullet->SetRadius(10.0f);
						bullet->ball.setFillColor(sf::Color::Red);
						bullet->SetPosition(boss.boss.getPosition().x + boss.boss.getSize().x / 2, boss.boss.getPosition().y + boss.boss.getSize().y / 2);
						bullet->speed.y = 1 * bullet->deafultSpeed;
						bullet->speed.x = 0 * bullet->deafultSpeed;
						bulletsRight.push_back(bullet);
						auto bullet2 = bullet;
						bullet2->SetPosition(boss.boss.getPosition().x - boss.boss.getSize().x / 2, boss.boss.getPosition().y + boss.boss.getSize().y / 2);
						bulletsLeft.push_back(bullet2);
					}
					for (auto& bullet : bulletsLeft)
					{
						std::cout << "LEFT" << std::endl;
						bullet->ball.setPosition(sf::Vector2f(bullet->ball.getPosition().x + (bullet->speed.x * deltaTime),
							bullet->ball.getPosition().y + (bullet->speed.y * deltaTime)));
						UpdateBulletNextPosition(bullet, deltaTime);
						if (PaddleGlobalBounds(paddle).intersects(bullet->nextPos))
						{
							gameOver = true;
						}
					}
					for (auto& bullet : bulletsRight)
					{
						std::cout << "Right" << std::endl;
						bullet->ball.setPosition(sf::Vector2f(bullet->ball.getPosition().x + (bullet->speed.x * deltaTime),
							bullet->ball.getPosition().y + (bullet->speed.y * deltaTime)));
						UpdateBulletNextPosition(bullet, deltaTime);
						if (PaddleGlobalBounds(paddle).intersects(bullet->nextPos))
						{
							gameOver = true;
						}
					}
					ResizeBulletVector(bulletsLeft);
					ResizeBulletVector(bulletsRight);
				}

			}
			//power-up spawner
			if(buffTimeSpawnLimit.asSeconds() < buffClockSpawn.getElapsedTime().asSeconds() && powerUps.size() < buffsLimit)
			{
				
				buffClockSpawn.restart();
				auto buff = std::make_shared<PowerUp>();
				buff->SetSize(40, 40);
				buff->isPowerUp = false;
				buff->buffType = BuffType();
				buff->buff.setPosition(DistanceX(frameWidth), DistanceY(frameHeight));
				buff->Initiate();
				powerUps.push_back(buff);
			}
			//resize power-ups
			ResizeBuffVector(powerUps);
			//power-up collision && power-up effect
			for (auto& Buff : powerUps)
			{
				UpdateNextPosition(ball2, deltaTime);
				if (PowerUpGlobalBounds(Buff).intersects(ball2.nextPos)&&!Buff->isPowerUp)
				{
					Buff->isPowerUp = true;
					switch (Buff->buffType)
					{
					//speed up
					case 0:
						Buff->buffTime = sf::seconds(3);
						ball2.deafultSpeed *= 1.5f;
						soundManager.PlaysSound(3);
						break;
					//wide paddle
					case 1:
						Buff->buffTime = sf::seconds(4);
						paddle.platform.setSize(sf::Vector2f(paddle.platform.getSize().x *1.4f, paddle.platform.getSize().y));
						paddle.platform.setOrigin(paddle.platform.getSize().x / 2, paddle.platform.getSize().y / 2);
						soundManager.PlaysSound(3);
						break;
					//bigger ball
					case 2:
						Buff->buffTime = sf::seconds(5);
						ball2.ball.setRadius(ball2.ball.getRadius() * 1.5f);
						ball2.ball.setOrigin(ball2.ball.getRadius(), ball2.ball.getRadius());
						soundManager.PlaysSound(3);
						break;
						//bonus Points
					case 3:
						Buff->buffTime = sf::seconds(0.1f);
						scoreCounter += 50;
						score.setString("Score " + std::to_string(scoreCounter));
						soundManager.PlaysSound(4);
						break;
						//add Ball
					case 4:
						Buff->buffTime = sf::seconds(0.1f);
						soundManager.PlaysSound(3);
						break;

					}
				}
				if(Buff->isPowerUp)
				{
					if(Buff->buffTime > sf::Time::Zero)
					{
						Buff->buffTime -= sf::seconds(deltaTime);
					}
					else
					{
						switch (Buff->buffType)
						{
						case 0:
							ball2.deafultSpeed /= 1.5f;
							break;

						case 1:
							paddle.platform.setSize(sf::Vector2f(paddle.platform.getSize().x / 1.4f, paddle.platform.getSize().y));
							paddle.platform.setOrigin(paddle.platform.getSize().x / 2, paddle.platform.getSize().y / 2);

							break;

						case 2:
							ball2.ball.setRadius(ball2.ball.getRadius() / 1.5f);
							ball2.ball.setOrigin(ball2.ball.getRadius(), ball2.ball.getRadius());
							break;
						case 3:
								break;
						case 4:
								break;
						default: ;
						}
						if(powerUps.size() == buffsLimit)
						{
							buffClockSpawn.restart();
						}
						Buff->isPowerUp = false;
					}
				}
			}
		}
	}
};

void Game::JoystickUpdate(float deltaTime)
{
	if (sf::Joystick::isConnected)
	{
		if (isGame)
		{
			if (!win && !gameOver)
			{
				if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) > 10)
				{
					paddle.platform.move(paddle.movespeed * deltaTime, 0);
				}
				if (sf::Joystick::getAxisPosition(0, sf::Joystick::X) < -10)
				{
					paddle.platform.move(-paddle.movespeed * deltaTime, 0);
				}
				if (paddle.platform.getPosition().x < paddle.platform.getSize().x / 2)
				{
					paddle.platform.setPosition(sf::Vector2f(paddle.platform.getSize().x / 2, paddle.platform.getPosition().y));
				}
				if (paddle.platform.getPosition().x > frameWidth - paddle.platform.getSize().x / 2)
				{
					paddle.platform.setPosition(sf::Vector2f(frameWidth - paddle.platform.getSize().x / 2, paddle.platform.getPosition().y));
				}
			}
		}
	}
}

void Game::LoadLevel(int level)
{
	if (isGame)
	{
		soundManager.StopMusic(0);
		paddle.SetSize(paddleWidth, paddleHeight);
		if(settingMenu.currentColorPlatform	== 1)
		{
			paddle.platform.setFillColor(sf::Color::Green);
		}
		if (settingMenu.currentColorPlatform == 2)
		{
			paddle.platform.setFillColor(sf::Color::Magenta);
		}
		if (settingMenu.currentColorPlatform == 3)
		{
			paddle.platform.setFillColor(sf::Color::Cyan);
		}
		paddle.platform.setOutlineThickness(-1.0f);
		paddle.platform.setOutlineColor(sf::Color::Blue);
		paddle.platform.setOrigin(paddle.platform.getSize() / 2.0f);
		paddle.platform.setPosition(sf::Vector2f(frameWidth / 2 - paddle.platform.getSize().x / 2,
												frameHeight - 60));
		ball2.Initiate();
		ball2.SetRadius(16);
		ball2.ball.setFillColor(sf::Color::Yellow);
		ball2.ball.setPosition(sf::Vector2f(paddle.platform.getPosition().x,
		                                    paddle.platform.getPosition().y - (paddle.platform.getSize().y / 2) - ball2.ball.getRadius()));
		ball2.deafultSpeed = 300.0f*chosenDifficulty;
		ball2.angle = 0.0f;
		ball2.speed = sf::Vector2f(0.0f, 0.0f);
		levelTimer.restart();
		stopTime = false;

		if(std::ranges::size(blocks)!=0)
		{
			blocks.erase(blocks.begin(), blocks.end());
			blocks.clear();
		}
		if(std::ranges::size(powerUps) != 0)
		{
			powerUps.erase(powerUps.begin(), powerUps.end());
			powerUps.clear();
		}
		if(std::ranges::size(bulletsLeft)!=0)
		{
			bulletsLeft.erase(bulletsLeft.begin(), bulletsLeft.end());
			bulletsLeft.clear();
		}
		if (std::ranges::size(bulletsRight) != 0)
		{
			bulletsRight.erase(bulletsRight.begin(), bulletsRight.end());
			bulletsRight.clear();
		}
		if (level == 0)
		{
			soundManager.PlayMusic(1);
			for (int i = 0; i <= 23; i++)
			{
				auto bptr = std::make_shared<Brick>();
				bptr->Initiate();
				bptr->SetSize(blockWidth, blockHeight);
				bptr->SetPosition(startingX + bptr->block.getSize().x / 2 + i * bptr->block.getSize().x,
				                  startingY + bptr->block.getSize().y / 2);
				bptr->health = 1;
				blocks.push_back(bptr);
			}
		}
		if (level == 1)
		{
			soundManager.PlayMusic(1);
			for (int j = 0; j <= 4; j++)
			{
				for (int k = 0; k <= 4; k++)
				{
					auto bptr = std::make_shared<Brick>();
					bptr->Initiate();
					bptr->SetSize(blockWidth, blockHeight);
					bptr->SetPosition(startingX + bptr->block.getSize().x / 2 + k * bptr->block.getSize().x,
					                  startingY + 5 * blockHeight + bptr->block.getSize().y / 2 + j * bptr->block.
					                  getSize().y);
					bptr->health = 1;
					blocks.push_back(bptr);
				}
			}
			for (int j = 0; j <= 4; j++)
			{
				for (int k = 0; k <= 4; k++)
				{
					auto bptr = std::make_shared<Brick>();
					bptr->Initiate();
					bptr->SetSize(blockWidth, blockHeight);
					bptr->SetPosition(startingX + 8 * blockWidth + bptr->block.getSize().x / 2 + k * bptr->block.getSize().x,
					                  startingY + 5 * blockHeight + bptr->block.getSize().y / 2 + j * bptr->block.getSize().y);
					bptr->health = 2;
					blocks.push_back(bptr);
				}
			}
		}
		if(level == 2)
		{
			soundManager.PlayMusic(4);
			boss.SetSize(200.0f, 400.0f);
			boss.health = 10;
			boss.SetPosition(frameWidth / 2, frameHeight / 2 - 200);
			boss.isAlive = true;
			isBossFight = true; 
		}
	}
	if(isMenu)
	{
		stopTime = false;
		if(level == 0)
		{
			
		}
		if(level == 1)
		{
			
		}
		if(level == 2)
		{
			
		}
	}
}

void Game::Render()
{
	window->draw(background);
	if (isGame)
	{	
		if (!isBossFight)
		{
			for (int i = 0; i < blocks.size(); ++i)
			{
				if (!blocks[i]->isDestroyed)
				{
					if (blocks[i]->health == 1)
					{
						blocks[i]->block.setFillColor(sf::Color::Magenta);
						blocks[i]->block.setOutlineColor(sf::Color::Blue);
						blocks[i]->block.setOutlineThickness(-0.5f);
					}
					if (blocks[i]->health == 2)
					{
						blocks[i]->block.setFillColor(sf::Color::Green);
						blocks[i]->block.setOutlineColor(sf::Color::Blue);
						blocks[i]->block.setOutlineThickness(-0.5f);
					}
					window->draw(blocks[i]->block);
				}
			}
		}
		else
		{
			if(boss.isAlive)
			{
				window->draw(boss.boss);
			}
		}
		window->draw(paddle.platform);
		if (!gameOver && !win)
		{
			window->draw(ball2.ball);
			window->draw(score);
			window->draw(levelClock);
			for (auto& Buff : powerUps)
			{
				if (!Buff->isPowerUp && Buff->buffTime.asSeconds() > sf::Time::Zero.asSeconds())
					window->draw(Buff->buff);
			}
			if (isBossFight)
			{
				for (auto& bullets1 : bulletsLeft)
				{
					window->draw(bullets1->ball);
				}
				for (auto& bullets1 : bulletsRight)
				{
					window->draw(bullets1->ball);
				}
			}
		}
		if (gameOver)
		{
			window->draw(gameOverTitle);
			finalScore.setString("Score " + std::to_string(scoreCounter));
			if(!stopTime)
			{
				soundManager.PlayMusic(3);
				stopTime = true;
			}
			finalScore.setPosition(sf::Vector2f(frameWidth / 2, (frameHeight / 2) + 30));
			window->draw(finalScore);
		}
		if (win)
		{
			window->draw(ball2.ball);
			window->draw(winTitle);
			if (!stopTime)
			{
				soundManager.PlayMusic(2);
				levelTimeComplition = levelTimer.getElapsedTime();
				std::stringstream ss;
				ss << std::fixed << std::setprecision(3) << levelTimer.getElapsedTime().asSeconds();
				levelFinalTime.setString(ss.str());
				stopTime = true;
				sf::Time timeLimit = sf::seconds(480);
				if (timeLimit - levelTimeComplition > sf::seconds(0))
				{
					scoreCounter = scoreCounter + ((timeLimit - levelTimeComplition).asSeconds() * 2) * chosenDifficulty;
				}
			}
			window->draw(levelFinalTime);
			window->draw(paddle.platform);
			finalScore.setString("Score " + std::to_string(scoreCounter));
			finalScore.setPosition(sf::Vector2f(frameWidth / 2, (frameHeight / 2) + 30));
			score.setString("Score " + std::to_string(scoreCounter));
			window->draw(finalScore);
		}
		if (win&&isBossFight)
		{
			window->draw(ball2.ball);
			winTitle.setString("You Win!");
			winTitle.setOrigin(winTitle.getLocalBounds().width / 2.0f, winTitle.getLocalBounds().height / 2.0f);
			winTitle.setPosition(sf::Vector2f(frameWidth / 2, (frameHeight / 2) - 450));
			window->draw(winTitle);
			if (!stopTime)
			{
				levelTimeComplition = levelTimer.getElapsedTime();
				std::stringstream ss;
				ss << std::fixed << std::setprecision(3) << levelTimer.getElapsedTime().asSeconds();
				levelFinalTime.setString(ss.str());
				stopTime = true;
				scoreCounter += 1000 * chosenDifficulty;
				sf::Time timeLimit = sf::seconds(480);
				if (timeLimit - levelTimeComplition > sf::seconds(0))
				{
					scoreCounter = scoreCounter + ((timeLimit - levelTimeComplition).asSeconds() * 2) * chosenDifficulty;
				}
				soundManager.PlayMusic(2);
			}
			window->draw(levelFinalTime);
			window->draw(paddle.platform);
			finalScore.setString("Score " + std::to_string(scoreCounter));
			finalScore.setPosition(sf::Vector2f(frameWidth / 2, (frameHeight / 2) + 30));
			score.setString("Score " + std::to_string(scoreCounter));
			window->draw(finalScore);
		}
	}
	if(isMenu)
	{
		if(isMainMenu)
		{
			menu.Draw(window);
		}
		if(isDifficultyMenu)
		{
			difficultMenu.Draw(window);
		}
		if(isScoreMenu)
		{
			finalScore.setPosition(sf::Vector2f(frameWidth / 2, (frameHeight / 2) - 60));
			window->draw(finalScore);
			window->draw(playerName);
		}
		if(isHighScoreMenu)
		{
			highScoreMenu.Draw(window);
		}
		if(isOptionsMenu)
		{
			settingMenu.Draw(window);
		}
	}
};

void Game::HandleEvents(sf::Event event, float deltaTime)
{
	switch (event.type)
	{
	case sf::Event::Closed:
	{
		window->close();
		break;
	}
	case sf::Event::MouseMoved:
	{
		//set position of paddle.platform on bottom of screen and move only left or right
		if (!gameOver)
		{

			if (!debugMode)
				paddle.platform.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, frameHeight - 60));
			else
				paddle.platform.setPosition(sf::Vector2f(frameWidth / 2, frameHeight - 60));
			if (paddle.platform.getPosition().x < paddle.platform.getSize().x / 2)
			{
				paddle.platform.setPosition(sf::Vector2f(paddle.platform.getSize().x / 2, paddle.platform.getPosition().y));
			}
			if (paddle.platform.getPosition().x > frameWidth - paddle.platform.getSize().x / 2)
			{
				paddle.platform.setPosition(sf::Vector2f(frameWidth - paddle.platform.getSize().x / 2, paddle.platform.getPosition().y));
			}
		}
		break;
	}
	case sf::Event::MouseButtonPressed:
	{
		if (!isMoving || debugMode)
		{
			ball2.ball.setPosition(sf::Vector2f(paddle.platform.getPosition().x,
				paddle.platform.getPosition().y - (paddle.platform.getSize().y / 2) - ball2.ball.getRadius()));
			StartFromPlatform(ball2);
			isMoving = true;
		}
		break;
	}
	case sf::Event::KeyPressed:
	{
		//Debug mode buttons
		//D button to enable debug mode
		if (event.key.code == sf::Keyboard::D)
		{
			debugMode = !debugMode;
		}
		//N button to go to next level
		if (event.key.code == sf::Keyboard::N && debugMode)
		{
			currentLevel += 1;
			LoadLevel(currentLevel);
		}
		//End of debug mode buttons
		//Buttons to play move throu menu
		//Escape button to close a game
		if (event.key.code == sf::Keyboard::Escape)
		{
			window->close();
		}

		break;
	}
	case sf::Event::TextEntered:
	{
		
		if (isMenu && isScoreMenu)
		{
			if (event.text.unicode == 8)
			{
				if (playerName.getString().getSize() > 0)
				{
					playerName.setString(playerName.getString().substring(0, playerName.getString().getSize() - 1));
				}
			}
			if (event.text.unicode >= 32 && event.text.unicode <= 126)
			{
				if (playerName.getString().getSize() < 5 && playerName.getString().getSize() >= 0)
				{
					playerName.setString(playerName.getString() + static_cast<char>(event.text.unicode));
				}
			}
		}
	}
	case sf::Event::JoystickConnected:
	{
		break;
	}
	case sf::Event::JoystickButtonPressed:
	{
		if (isGame)
		{
			//when right button on joystick is pressed , double movespeed
			if (event.joystickButton.button == 5)
			{
				paddle.movespeed *= 2.5f;
			}
			if (!isMoving && event.joystickButton.button == 0)
			{
				ball2.ball.setPosition(sf::Vector2f(paddle.platform.getPosition().x,
					paddle.platform.getPosition().y - (paddle.platform.getSize().y / 2) - ball2.ball.getRadius()));
				StartFromPlatform(ball2);
				isMoving = true;
			}
			if (win && event.joystickButton.button == 0)
			{
				if (!isBossFight)
				{
					currentLevel += 1;
					LoadLevel(currentLevel);
					isMoving = false;
					isGame = true;
					win = false;
					gameOver = false;
				}
				else
				{
					isMoving = false;
					isGame = false;
					win = false;
					gameOver = false;
					isBossFight = false;
					isMenu = true;
					isScoreMenu = true;
				}
			}
			if (gameOver && event.joystickButton.button == 0)
			{
				isMoving = false;
				isGame = false;
				win = false;
				gameOver = false;
				isMenu = true;
				isScoreMenu = true;
			}
		}
		else if (isMenu)
		{
			if (isMainMenu)
			{
				if (event.joystickButton.button == 0)
				{
					switch (menu.currentButton)
					{
					case 0: isMainMenu = false;
						isDifficultyMenu = true;
						LoadLevel(1);
						break;

					case 1: isMainMenu = false;
						isHighScoreMenu = true;
						LoadLevel(2);
						break;

					case 2: isMainMenu = false;
						isOptionsMenu = true;
						break;

					case 3: window->close();
						break;
					default: break;;
					}
				}
			}
			else if (isDifficultyMenu)
			{
				if (event.joystickButton.button == 0)
				{
					switch (difficultMenu.currentButton)
					{
					case 0: isDifficultyMenu = false;
						isMoving = false;
						isGame = true;
						win = false;
						gameOver = false;
						chosenDifficulty = 1;
						LoadLevel(0);
						break;

					case 1: isDifficultyMenu = false;
						isMoving = false;
						isGame = true;
						win = false;
						gameOver = false;
						chosenDifficulty = 2;
						LoadLevel(0);
						break;

					case 2: isDifficultyMenu = false;
						isMoving = false;
						isGame = true;
						win = false;
						gameOver = false;
						chosenDifficulty = 3;
						LoadLevel(0);
						break;

					default: break;
					}
				}
			}
			else if (isScoreMenu)
			{
				if (event.joystickButton.button == 0)
				{
					std::regex PlayerNameRegex("^[a-zA-Z]{3,5}$");
					std::string PlayerName = playerName.getString();
					if (std::regex_match(PlayerName, PlayerNameRegex))
					{
						isScoreMenu = false;
						isMenu = true;
						isHighScoreMenu = false;
						isDifficultyMenu = false;
						isMainMenu = true;
						highScoreMenu.SaveHighScore(PlayerName, scoreCounter);
						scoreCounter = 0;
						soundManager.PlayMusic(0);
					}
					else
					{
						playerName.setFillColor(sf::Color::Red);
					}
				}
			}
			else if(isHighScoreMenu)
			{
				if (event.joystickButton.button == 0)
				{
					isMainMenu = true;
					isHighScoreMenu = false;
					LoadLevel(0);
				}
			}
			else if (isOptionsMenu && settingMenu.isChoseColor == false)
			{
				if (event.joystickButton.button == 0)
				{
					switch (settingMenu.currentButton)
					{
					case 0: settingMenu.isChoseColor = true;
						break;

					case 1: isMainMenu = true;
						isOptionsMenu = false;
						LoadLevel(0);
						break;

					default: break;
					}
				}
			}
			else if (isOptionsMenu && settingMenu.isChoseColor == true)
			{
				if (event.joystickButton.button == 0)
				{
					switch (settingMenu.currentColorPlatform)
					{
					case 1: settingMenu.currentColorPlatform = 1;
						settingMenu.isChoseColor = false;
						settingMenu.SaveSettings();
						settingMenu.currentButton = 0;
						break;

					case 2: settingMenu.currentColorPlatform = 2;
						settingMenu.isChoseColor = false;
						settingMenu.SaveSettings();
						settingMenu.currentButton = 0;
						break;

					case 3: settingMenu.currentColorPlatform = 3;
						settingMenu.isChoseColor = false;
						settingMenu.SaveSettings();
						settingMenu.currentButton = 0;
						break;

					default: break;
					}
				}
			}
		}
		break;
	}
	case sf::Event::JoystickMoved:
		{
		if (isMainMenu)
		{
			if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position <0)
			{
				menu.currentButton++;
			}
			if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position >0)
			{
				menu.currentButton--;
			}
			if(menu.currentButton<0)
			{
				menu.currentButton = 0;
			}
			if(menu.currentButton>3)
			{
				menu.currentButton = 3;
			}
		}
			if(isDifficultyMenu)
			{
				if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position < 0)
				{
					difficultMenu.currentButton++;
				}
				if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position > 0)
				{
					difficultMenu.currentButton--;
				}
				if (difficultMenu.currentButton < 0)
				{
					difficultMenu.currentButton = 0;
				}
				if (difficultMenu.currentButton > 2)
				{
					difficultMenu.currentButton = 2;
				}
			}
			if(isOptionsMenu && settingMenu.isChoseColor == false)
			{
				if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position < 0)
				{
					settingMenu.currentButton++;
				}
				if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position > 0)
				{
					settingMenu.currentButton--;
				}
				if (settingMenu.currentButton < 0)
				{
					settingMenu.currentButton = 0;
				}
				if (settingMenu.currentButton > 1)
				{
					settingMenu.currentButton = 1;
				}
			}
			if (isOptionsMenu && settingMenu.isChoseColor == true)
			{
				if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position < 0)
				{
					settingMenu.currentColorPlatform++;
				}
				if (event.joystickMove.axis == sf::Joystick::PovY && event.joystickMove.position > 0)
				{
					settingMenu.currentColorPlatform--;
				}
				if (settingMenu.currentColorPlatform < 1)
				{
					settingMenu.currentColorPlatform = 1;
				}
				if (settingMenu.currentColorPlatform > 3)
				{
					settingMenu.currentColorPlatform = 3;
				}
			}
		break;
		}
	case sf::Event::JoystickButtonReleased:
		{
			//when right button on joystick is released , set movespeed to default
			if (event.joystickButton.button == 5)
			{
				paddle.movespeed /= 2.5f;
			}
			break;
		}
	defult: break;
	}
};

void Game::Run()
{
	sf::Clock gameClock;
	float deltaTime = 0.0;
	LoadLevel(0);
	currentLevel = 0;
	while (window->isOpen())
	{
		gameClock.restart();
		sf::Event e;
		while (window->pollEvent(e))
		{
			HandleEvents(e, deltaTime);
		}
		Update(deltaTime);
		JoystickUpdate(deltaTime);
		window->clear();
		Render();
		window->display();
		deltaTime = gameClock.getElapsedTime().asSeconds();
	}
};
