#pragma once
#include "Entity.h"
class Ball : public Entity
{
public:
	sf::CircleShape ball;
	sf::Texture ballTexture;
	float angle;
	sf::Vector2f speed;
	float deafultSpeed = 400.0f;
	sf::FloatRect nextPos;

	void SetRadius(float radius);
	void SetSize(float width, float height) override;
	void SetPosition(float x, float y) override;
	void Initiate() override;

	bool BallLeft(sf::FloatRect player, sf::FloatRect block);
	bool BallRight(sf::FloatRect player, sf::FloatRect block);
	bool BallUp(sf::FloatRect player, sf::FloatRect block);
	bool BallBottom(sf::FloatRect player, sf::FloatRect block);
};

