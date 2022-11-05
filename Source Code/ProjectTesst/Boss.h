#pragma once
#include "Entity.h"
class Boss : public Entity
{
public:
	sf::RectangleShape boss;
	int health;
	bool isAlive;
	bool isLeft = true;

	void SetPosition(float x, float y) override;
	void SetSize(float width, float height) override;
	void Initiate() override;
	bool Hit();

};