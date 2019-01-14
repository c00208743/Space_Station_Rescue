#include "Bullet.h"

Bullet::Bullet() 
{
	m_speed = 50.0f;
	//m_position = sf::Vector2f(100.0f, 100.0f);
	m_alive = false;

	if (!m_texture.loadFromFile("assets/laser/laser1.png"))
	{
		// error...
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(16, 2);
	m_sprite.setPosition(m_position);

}

Bullet::~Bullet()
{

}

void Bullet::render(sf::RenderWindow & window)
{
	if (m_alive)
	{
		window.draw(m_sprite);
	}
	
	
}

void Bullet::update()
{
	if (m_alive)
	{
		m_position.x += velocity.x;
		m_position.y += velocity.y;
		m_sprite.setPosition(m_position);
	}
	if (collison) {
		m_alive = false;
		collison = false;
	}
}



void Bullet::fire(sf::Vector2f direction, sf::Vector2f pos, float rotation)
{
	m_speed = 50.0f;
	//calculate trigetory
	velocity.x = m_speed * direction.x;
	velocity.y = m_speed * direction.y;
	//start on players position
	m_position.x = pos.x;
	m_position.y = pos.y;

	m_sprite.setRotation(rotation);
	m_alive = true;
}

bool Bullet::checkCollision(sf::Vector2f pos, int width, int height)
{

	//box collsion formula 
	if (m_alive) {
		if (m_position.x < pos.x + width
			&& m_position.x + 32> pos.x
			&& m_position.y + 4 > pos.y
			&& m_position.y < pos.y + height)
		{
			// explosion
			collison = true;
		}
	}
	return collison;

}