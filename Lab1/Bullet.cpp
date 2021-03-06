#include "Bullet.h"

Bullet::Bullet(bool p) 
{
	m_playerBullet = p;

	m_speed = 25.0f;
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
	//only render the bullet when its alive
	if (m_alive)
	{
		window.draw(m_sprite);
	}
	
	
}

void Bullet::update()
{
	//only update the position of the bullet whenits alive
	if (m_alive)
	{
		m_position.x += velocity.x;
		m_position.y += velocity.y;
		m_sprite.setPosition(m_position);
	}
	//if the bullet collides with anythin it dies
	if (collison) {
		m_alive = false;
		collison = false;
	}
}

bool Bullet::isThisAPlayerBullet()
{
	return m_playerBullet;
}

void Bullet::fire(sf::Vector2f direction, sf::Vector2f pos, float rotation)
{
	//calculate trigetory
	velocity.x = m_speed * direction.x;
	velocity.y = m_speed * direction.y;
	//start on players position
	m_position.x = pos.x;
	m_position.y = pos.y;
	//sets bullet rotation as the players
	m_sprite.setRotation(rotation);
	if (!m_playerBullet)
	{
		m_sprite.setRotation(m_sprite.getRotation() + 90);
	}
	m_alive = true;
	collison = false;
}

bool Bullet::checkCollision(sf::Vector2f pos, int width, int height)
{
	collison = false;
	//box collsion formula 
	if (m_alive) {
		if (m_position.x < pos.x + width
			&& m_position.x + 32> pos.x
			&& m_position.y + 4 > pos.y
			&& m_position.y < pos.y + height)
		{
			// explosion
			collison = true;
			m_alive = false;
		}
		else {
			collison = false;
		}
	}
	return collison;

}


void Bullet::checkWall(Level * cLevel)
{
	// Get the square in front
	float posX = m_position.x;
	float posY = m_position.y;
	
	int x = floor(posX / 32);
	int y = floor(posY / 32);
	
	if (cLevel->collide(sf::Vector2i(x, y)))
	{
		m_alive = false;
	}
}