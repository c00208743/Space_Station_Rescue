#include "Player.h"
#include <iostream>
#include "math.h"


#define M_PI   3.14159265358979323846264338327950288

Player::Player() :
	m_position(300, 300),
	m_velocity(0, 0),
	size(50),
	speed(0)
{
	
	if (!m_texture.loadFromFile("assets/player/body_02.png"))
	{
		// error...
	}
	
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(64, 32);
	m_sprite.setPosition(m_position);
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
Player::~Player()
{
}

void Player::update(double dt, Level * cLevel)
{

	//increase velocity
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (speed < 3)
		{
			speed = speed + 0.02;
		}
	}
	else
	{
		if (speed > 0)
		{
			speed = speed - 0.02;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (speed > -3)
		{
			speed = speed - 0.02;
		}
	}
	else
	{
		if (speed < 0)
		{
			speed = speed + 0.02;
		}
	}
	//change rotation 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_sprite.rotate(-0.5);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_sprite.rotate(0.5);
	}

	//Apply direction to sprite
	float radians = m_sprite.getRotation()* M_PI / 180;
	direction.x = (cos(radians));
	direction.y = (sin(radians));
	m_sprite.setPosition(m_sprite.getPosition().x + (direction.x * speed), m_sprite.getPosition().y + (direction.y * speed));


	//looping screen 
	if (m_sprite.getPosition().x > 2100)
	{
		m_sprite.setPosition(-100, m_sprite.getPosition().y);
	}
	if (m_sprite.getPosition().x < -100)
	{
		m_sprite.setPosition(2100, m_sprite.getPosition().y);
	}
	if (m_sprite.getPosition().y < -100)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, 2100);
	}
	if (m_sprite.getPosition().y > 2100)
	{
		m_sprite.setPosition(m_sprite.getPosition().x, -100);
	}

	currentTile(cLevel);

}

void Player::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}


sf::Vector2f Player::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Player::getVelocity()
{
	direction.x * speed;
	direction.y * speed;
	return direction;
}

void Player::currentTile(Level * cLevel)
{
	// Get the square in front
	float posX = m_sprite.getPosition().x + 64;
	float posXB = m_sprite.getPosition().x - 64;
	float posY = m_sprite.getPosition().y;

	sf::Vector2f tileAhead = rotate(sf::Vector2f(posX, posY), m_sprite.getPosition(), m_sprite.getRotation());
	sf::Vector2f tileBehind = rotate(sf::Vector2f(posXB, posY), m_sprite.getPosition(), m_sprite.getRotation());


	int x = floor(tileAhead.x / 32);
	int y = floor(tileAhead.y / 32);

	int xb = floor(tileBehind.x / 32);
	int yb = floor(tileBehind.y / 32);

	if (cLevel->collide(sf::Vector2i(x, y)) || cLevel->collide(sf::Vector2i(xb, yb)))
	{
		speed = 0;
	}
}

sf::Vector2f Player::rotate(sf::Vector2f P, sf::Vector2f O, float theta)
{
	sf::Transform rotTran;
	rotTran.rotate(theta, O.x, O.y);
	return rotTran.transformPoint(P);
}