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
	void setPosition(float x, float y);
	sf::Vector2f getVelocity();
	sf::Vector2f asVector(float orientation);


private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_velocityF;
	float m_orientation;
	float m_maxSpeed;
	int m_size;
	double speed = 0.3;
	double maxRotation = 180;
	int timer =0;

	//Lab2
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	
	//wander
	float wanderOrientation =0;
	float targetOrientation =0;
	float wanderRate = 0.3f;
	sf::Vector2f target;
	sf::Vector2f orientationAsVector;
	sf::Vector2f targetOrientationAsVector;
};



