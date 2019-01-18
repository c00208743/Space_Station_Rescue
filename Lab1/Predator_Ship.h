#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include "Enemy.h"
#include "Missile.h"
#include "Bullet.h"

class Predator_Ship : public Enemy
{
public:
	Predator_Ship();
	~Predator_Ship();
	float getNewOrientation(float currentOrientation, float velocity);
	void kinematicSeek(sf::Vector2f playerPosition);
	void kinematicArrive(sf::Vector2f playerPosition);
	void boundary(float x, float y);
	float getRandom(int x, int y);
	void update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies, Level * cLevel);
	void render(sf::RenderWindow & window);

	int getId();
	bool radar(sf::Vector2f pos);

	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	int getWidth();
	int getHeight();
	int getHealth();
	void hit(int damage);
	bool workerRadar(sf::Vector2f pos);
	void collison(std::vector<Enemy*> enemies);
	int getScore();
	void setScore();
	bool checkWorkerCollision(sf::Vector2f pos, int width, int height, bool alive);
	int getDamageToPlayer();

	bool checkBulletCollision(sf::Vector2f pos, int width, int height);
	void spawn(sf::Vector2f pos);

	void setPos(sf::Vector2f newPos);

private:

	void newTarget();
	void checkWall(Level * cLevel);
	sf::Vector2f rotate(sf::Vector2f P, sf::Vector2f Q, float theta);
	void kinematicWander(sf::Vector2f targetPosition);
	sf::Vector2f nextTile(Level * cLevel, sf::Vector2f playerPos);
	float m_timeToTarget;
	sf::Vector2f target;
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
	int m_timerCount;
	const int m_timerCountLimit = 500;

	int m_wallCount;
	const int m_wallCountLimit = 50;


	//cone of vision
	sf::Vector2f n_direction;
	float n_orientation;
	double n_distance = 0;
	float m_threshold;
	bool crash = false;

	int health = 50;
	int timer = 0;
	int animate = 0;
	sf::Vector2f m_explosion;
	bool finishAnimate = false;
	sf::Texture m_textureExplosion;
	sf::Sprite m_spriteExplosion;

	int radarDistance = 100000;

	// Math methods
	float length(sf::Vector2f vel);
	sf::Vector2f normalize(sf::Vector2f vel);

	// Missile
	Missile* m_missile;

	// Bullet
	Bullet* m_bullet;
	int m_fireCooldownCounter;
	const int m_fireCooldownLimit = 200;
	
	//Projectiles
	bool m_fireBullet;
	int m_bulletsShot;
	const int m_bulletsShotLimit = 4;

	// Formation
	void inFormation(int numInForm, sf::Vector2f playerPos);
	int formationPos;
	const float formationRadius = 200.0f;
	sf::Vector2f formPos;

};