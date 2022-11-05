#pragma once
#include "Entity.h"
class PowerUp : public Entity
{
public:

	sf::RectangleShape buff;
	sf::Time buffTime = sf::seconds(1);
	int buffType;
	bool isPowerUp;

	void SetPosition(float x, float y) override;
	void SetSize(float width, float height) override;
	void Initiate() override;
	
	
};

