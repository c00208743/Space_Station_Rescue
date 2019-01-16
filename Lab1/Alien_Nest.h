#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Enemy.h"
#include "Missile.h"

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

	//double shortestTime = std::numeric_limits<double>::infinity();
	double shortestTime = 2000;
	sf::Vector2f firstTarget;
	sf::Vector2f firstRelativePos;
	sf::Vector2f firstRelativeVel;
	sf::Vector2f relativePos;
	sf::Vector2f relativeVel;
	sf::Vector2f steering;
	double firstMinSeparation = 0;
	double firstDistance = 0;
	double distance = 0;
	float radius = 300;
	float relativeSpeed = 0;
	float maxAcceleration = 3;
	double timeToCollision = 0;
	double minSeparation = 0;

	//cone of vision
	sf::Vector2f n_direction;
	float n_orientation;
	double n_distance = 0;
	float m_threshold;
	bool crash = false;


	int health = 100;
	int timer = 0;
	int animate = 0;
	sf::Vector2f m_explosion;
	bool finishAnimate =false;
	bool inRange = false;
	int radarDistance = 100000;
	Missile* m_missile;

};