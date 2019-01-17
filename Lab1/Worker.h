#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Level.h"

class Worker 
{
public:
	Worker();
	~Worker();
	void update(Level * cLevel);
	void render(sf::RenderWindow & window);

	//wall collison +player collison
	
	void kinematicWander(sf::Vector2f targetPosition);
	float getNewOrientation(float currentOrientation, float velocity);
	float getRandom(int x, int y);
	sf::Vector2f getPosition();
	void setPosition(float x, float y);
	void setCollected();
	bool getCollected();
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
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool collected = false;

	//wander
	int m_timerCount;
	const int m_timerCountLimit = 500;
	float wanderOrientation =0;
	float targetOrientation =0;
	float wanderRate = 0.3f;
	const float m_maxRotation = 360.0f;
	sf::Vector2f target;
	sf::Vector2f orientationAsVector;
	sf::Vector2f targetOrientationAsVector;
	void newTarget();
	void checkWall(Level * cLevel);
	sf::Vector2f rotate(sf::Vector2f P, sf::Vector2f Q, float theta);

	
	// Math methods
	float length(sf::Vector2f vel);
	sf::Vector2f normalize(sf::Vector2f vel);

};



