#pragma once
#include <SFML/Graphics.hpp>
class Entity
{
public:
	virtual void SetPosition(float x, float y) = 0;
	virtual void SetSize(float width, float height) = 0;
	virtual void Initiate() = 0;

	
};

