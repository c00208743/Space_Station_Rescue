#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>



class Bullet
{
public:
	Bullet();
	~Bullet();
	void update();
	void render(sf::RenderWindow & window);

	void fire(sf::Vector2f direction, sf::Vector2f pos, float rotation);
	bool checkCollision(sf::Vector2f pos, int width, int height);
	//void checkCollision(sf::Vector2f size, sf::Vector2f pos);

private:
	float m_speed;
	sf::Vector2f m_position;
	sf::Vector2f velocity;
	sf::Vector2f m_explosion;
	bool m_alive;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	bool collison = false;
	int timer = 0;
	int animate = 0;
};