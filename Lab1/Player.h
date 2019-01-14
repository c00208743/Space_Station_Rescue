#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Level.h"
#include <math.h>       /* floor */


class Player
{
public:
	Player();
	~Player();
	void update(double dt, Level * cLevel);
	void render(sf::RenderWindow & window);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	
private:
	
	sf::Vector2f rotate(sf::Vector2f P, sf::Vector2f Q, float theta);
	
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f direction;
	int size;
	const float PI = 3.14159265359;
	float orientation;
	float rotation;
	double speed;

	//Lab2
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	void currentTile(Level * cLevel);

};
