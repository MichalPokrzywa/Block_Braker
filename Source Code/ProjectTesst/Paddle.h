#pragma once
#include "Entity.h"
class Paddle : public Entity
{
public:
	sf::RectangleShape platform;
	float movespeed = 400.0f;

	void SetPosition(float x, float y) override;
	void SetSize(float width, float height) override;
	void Initiate() override;
	
};

