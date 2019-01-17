#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"
#include "Level.h"
#include <math.h>       /* floor */


class Player
{
public:
	Player();
	~Player();
	void update(double dt, Level * cLevel);
	void render(sf::RenderWindow & window);
	bool checkBulletCollision(sf::Vector2f pos, int width, int height);
	bool checkWorkerCollision(sf::Vector2f pos, int width, int height, bool alive);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	void setScore(int enemyS);
	void setHealth(int dam);
	void hit(int d);

private:
	
	sf::Vector2f rotate(sf::Vector2f P, sf::Vector2f Q, float theta);
	
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f direction;
	int size;
	int animate = 0	;
	int timer = 0;
	const float PI = 3.14159265359;
	float orientation;
	float rotation;
	double speed;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Texture m_textureShield;
	sf::Sprite m_spriteShield;

	Bullet* m_bullet;

	bool shield = false;
	bool shieldReady = false;
	bool collison = false;
	int shieldCoolDown = 0;
	int shieldTimer = 0;
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_textScore;
	sf::Text scoreNu;
	sf::Text m_gameOver;
	sf::Text m_health;
	int score = 0;
	int health = 100;

	void currentTile(Level * cLevel);

	sf::Vector2i previousTile;

};
