#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Enemy
{
public:
	virtual ~Enemy() {};
	virtual void update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies) =0;
	virtual void render(sf::RenderWindow & window)=0;
	virtual sf::Vector2f getPosition() =0 ;
	virtual sf::Vector2f getVelocity() =0 ;

protected:
	Enemy() {}
};
