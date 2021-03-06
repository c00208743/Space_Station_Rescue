#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Enemy.h"

class Sweeper_Bot : public Enemy
{
public:
	Sweeper_Bot();
	~Sweeper_Bot();
	float getNewOrientation(float currentOrientation, float velocity);
	float getRandom(int x, int y);
	void update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies, Level * cLevel);
	void render(sf::RenderWindow & window);

	void kinematicSeek(sf::Vector2f pos);
	void kinematicFlee(sf::Vector2f playerPosition);
	void kinematicWander(sf::Vector2f targetPosition);
	bool checkWorkerCollision(sf::Vector2f pos, int width, int height, bool alive);

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	int getWidth();
	int getHeight();
	int getHealth();
	int getScore();
	void setScore();
	int getId();
	void hit(int damage);
	bool radar(sf::Vector2f pos);
	bool workerRadar(sf::Vector2f pos);
	int getDamageToPlayer();

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
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	int health = 25;
	int timer = 0;
	int animate = 0;
	sf::Vector2f m_explosion;
	bool finishAnimate = false;
	sf::Texture m_textureExplosion;
	sf::Sprite m_spriteExplosion;
	bool inRange = false;
	int radarDistance = 100000;
	int workerRadarDis = 100000;
	bool workerInRange = false;

	//wander
	bool collison = false;
	int score = 0;
	int m_timerCount;
	const int m_timerCountLimit = 500;
	float wanderOrientation = 0;
	float targetOrientation = 0;
	float wanderRate = 0.3f;
	const float m_maxRotation = 360.0f;
	sf::Vector2f target;
	sf::Vector2f orientationAsVector;
	sf::Vector2f targetOrientationAsVector;
	void newTarget();
	void checkWall(Level * cLevel);
	sf::Vector2f rotate(sf::Vector2f P, sf::Vector2f Q, float theta);
	float length(sf::Vector2f vel);
	sf::Vector2f normalize(sf::Vector2f vel);
	sf::Vector2f worker;
	bool wall = false;
};