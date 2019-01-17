#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Level.h"



class Bullet
{
public:
	Bullet(bool p);
	~Bullet();
	void update();
	void render(sf::RenderWindow & window);

	void fire(sf::Vector2f direction, sf::Vector2f pos, float rotation);
	bool checkCollision(sf::Vector2f pos, int width, int height);
	void checkWall(Level * cLevel);
	bool isThisAPlayerBullet();

private:
	bool m_playerBullet;
	float m_speed;
	sf::Vector2f m_position;
	sf::Vector2f velocity;
	sf::Vector2f m_explosion;
	bool m_alive;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool collison = false;
	int timer = 0;
	int animate = 0;
	
};