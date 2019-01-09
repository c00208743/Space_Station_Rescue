#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Player.h"

class Worker 
{
public:
	Worker();
	~Worker();
	void update(sf::Vector2f playerPosition, Player* player);
	void render(sf::RenderWindow & window);

	//wall collison +player collison
	
	void kinematicWander(sf::Vector2f playerPosition);
	float getNewOrientation(float currentOrientation, float velocity);
	float getRandom(int x, int y);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();


private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_velocityF;
	float m_orientation;
	float m_maxSpeed;
	int m_size;
	double speed = 0.3;
	double maxRotation = 180;

	//Lab2
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	

};



