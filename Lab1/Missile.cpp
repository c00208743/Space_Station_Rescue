#include "Missile.h"

Missile::Missile()
{
	m_speed = 50.0f;
	//m_position = sf::Vector2f(100.0f, 100.0f);
	m_alive = false;

	if (!m_texture.loadFromFile("assets/laser/laser2.png"))
	{
		// error...
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(16, 2);

}

Missile::~Missile()
{

}

void Missile::render(sf::RenderWindow & window)
{
	if (m_alive) {
		window.draw(m_sprite);
	}
}

void Missile::update()
{
	if (m_alive)
	{
		m_position = m_position + m_velocity;
		m_sprite.setPosition(m_position);
		m_sprite.setRotation(m_orientation);
	}
	/*if (collison) {
		m_alive = false;
		collison = false;
	}*/
}



void Missile::fire(sf::Vector2f pos)
{

	//start on Alien Nest position
	
	if (timer % 1000 == 0) {
		m_position.x = pos.x;
		m_position.y = pos.y;
	}
	timer++;

	checkCollision();
	
	m_alive = true;
	
	
}

bool Missile::checkCollision()
{
	
	//box collsion formula 
	if (m_alive) {
		if (m_position.x < m_playerPos.x + 64
			&& m_position.x + 32> m_playerPos.x
			&& m_position.y + 4 > m_playerPos.y
			&& m_position.y < m_playerPos.y + 128)
		{
			// explosion
			collison = true;
			std::cout << "Player was hit" << std::endl;
			
		}
	}
	return collison;

}

void Missile::kinematicSeek(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;
	m_playerPos = playerPosition;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;

	m_orientation = getNewOrientation(m_orientation, m_velocityF);
	m_orientation = m_orientation + 180;

}
float Missile::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}
bool Missile::getStatus() {
	return m_alive;
}