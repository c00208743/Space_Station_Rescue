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
	void fire(float direction, sf::Vector2f pos);
	void checkCollision(sf::Vector2f size, sf::Vector2f pos);

private:
	float m_speed;
	sf::Vector2f m_size;
	sf::Vector2f m_pos;
	sf::RectangleShape m_rect;
	bool m_alive;
};