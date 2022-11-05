#pragma once
#include "Entity.h"
class Brick : public Entity
{
public:
	sf::RectangleShape block;
	int health = 1;
	bool isDestroyed = false;

	void SetSize(float width ,float height) override;
	void SetPosition(float x, float y) override;
	void Initiate() override;
	bool Hit();

};

