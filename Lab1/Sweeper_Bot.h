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
	void boundary(float x, float y);
	float getRandom(int x, int y);
	void update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies);
	void render(sf::RenderWindow & window);

	void kinematicSeek(sf::Vector2f pos);
	void kinematicFlee(sf::Vector2f playerPosition);
	void kinematicWander(sf::Vector2f playerPosition);
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
	float wanderOrientation = 0;
	float targetOrientation = 0;
	float wanderRate = 0.3f;
	sf::Vector2f target;
	sf::Vector2f orientationAsVector;
	sf::Vector2f targetOrientationAsVector;

	sf::Vector2f asVector(float orientation);
	sf::Vector2f worker;
	bool collison = false;
	int score = 0;
	

};