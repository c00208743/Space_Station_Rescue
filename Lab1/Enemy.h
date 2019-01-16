#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Player.h"

class Enemy
{
public:
	virtual ~Enemy() {};
	virtual void update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies, Level * level) = 0;
	virtual void render(sf::RenderWindow & window)=0;
	virtual sf::Vector2f getPosition() =0 ;
	virtual sf::Vector2f getVelocity() =0 ;
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getHealth() = 0;
	virtual int getId() = 0;
	virtual bool radar(sf::Vector2f pos) = 0;
	virtual void hit(int damage) = 0;

protected:
	Enemy() {}
};
