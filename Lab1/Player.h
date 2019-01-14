#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

class Player
{
public:
	Player();
	~Player();
	void update(double dt);
	void render(sf::RenderWindow & window);
	bool checkBulletCollision(sf::Vector2f pos, int width, int height);
	bool checkWorkerCollision(sf::Vector2f pos, int width, int height);
	sf::Vector2f getPosition();
	sf::Vector2f getVelocity();
	
private:

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f direction;
	int size;
	int animate = 0	;
	int timer = 0;
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
	int score = 0;


};
