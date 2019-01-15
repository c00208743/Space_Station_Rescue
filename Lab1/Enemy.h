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
	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual int getHealth() = 0;
	virtual int getScore() = 0;
	virtual int getDamageToPlayer() = 0;
	virtual void setScore() = 0;
	virtual int getId() = 0;
	virtual bool radar(sf::Vector2f pos) = 0;
	virtual bool workerRadar(sf::Vector2f pos) = 0;
	virtual void hit(int damage) = 0;
	virtual bool checkWorkerCollision(sf::Vector2f pos, int width, int height, bool alive) = 0;
protected:
	Enemy() {}
};
