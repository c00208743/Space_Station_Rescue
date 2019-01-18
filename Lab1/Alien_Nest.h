#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Enemy.h"
#include "Missile.h"
#include "Bullet.h"

class Alien_Nest : public Enemy
{
public:
	Alien_Nest();
	~Alien_Nest();
	float getNewOrientation(float currentOrientation, float velocity);

	void boundary(float x, float y);
	float getRandom(int x, int y);
	void update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies, Level * cLevel);
	void render(sf::RenderWindow & window);


	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	int getWidth();
	int getHeight();
	int getHealth();
	int getScore();
	void setScore();
	int getId();
	int getDamageToPlayer();
	void hit(int damage);
	bool radar(sf::Vector2f pos);
	bool workerRadar(sf::Vector2f pos);
	bool checkWorkerCollision(sf::Vector2f pos, int width, int height, bool alive);
	void setPos(sf::Vector2f newPos);
	void spawn(sf::Vector2f pos);


private:
	float m_timeToTarget;
	sf::Vector2f m_position;
	float m_orientation;
	sf::Vector2f m_velocity;
	float m_rotation;
	float m_velocityF;
	float m_maxSpeed;
	float m_maxRotation;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Texture m_textureExplosion;
	sf::Sprite m_spriteExplosion;

	// Predator ship spawning
	int m_spawnCounter;
	const int m_spawnTimerLimit = 600;

	int health = 100;
	int timer = 0;
	int animate = 0;
	sf::Vector2f m_explosion;
	bool finishAnimate =false;
	bool inRange = false;
	int radarDistance = 100000;
	Missile* m_missile;

};