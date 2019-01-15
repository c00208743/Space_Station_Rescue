#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>



class Missile
{
public:
	Missile();
	~Missile();
	void update();
	void render(sf::RenderWindow & window);

	void fire(sf::Vector2f pos);
	bool checkCollision();
	bool getStatus();

	float getNewOrientation(float currentOrientation, float velocity);
	void kinematicSeek(sf::Vector2f playerPosition);
	int damagedPlayer();

private:
	float m_speed;
	sf::Vector2f m_position;
	sf::Vector2f velocity;
	sf::Vector2f m_explosion;
	bool m_alive = false;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool collison = false;
	int timer = 0;
	int animate = 0;
	sf::Vector2f m_velocity;
	float m_velocityF;
	float m_orientation;
	float m_maxSpeed = 0.5f;
	int playerDamage = 0;
	sf::Vector2f m_playerPos;
	sf::Vector2f m_nestPos;
	
};